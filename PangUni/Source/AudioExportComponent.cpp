#include <JuceHeader.h>
#include "AudioExportComponent.h"
#include "SystemHelper.h"
#include "RegionSpotter.h"

//==============================================================================
AudioExportComponent::AudioExportComponent(SearchDataStruct* newData)
    :thumbCache(256), thumb(128, manager, thumbCache)
{
    this->newData = newData;
    threadKey = 0;
    timeCursorLineX = 0;

    preFileButton.reset(new juce::TextButton("preFileButton"));
    addAndMakeVisible(preFileButton.get());
    preFileButton->setButtonText(TRANS("PRE"));
    preFileButton->addListener(this);

    stopPlayButton.reset(new juce::TextButton("stopPlayButton"));
    addAndMakeVisible(stopPlayButton.get());
    stopPlayButton->setButtonText(TRANS("STOP"));
    stopPlayButton->addListener(this);

    playOrPauseButton.reset(new juce::TextButton("playOrPauseButton"));
    addAndMakeVisible(playOrPauseButton.get());
    playOrPauseButton->setButtonText(TRANS("PLAY"));
    playOrPauseButton->addListener(this);

    clearSelectionButton.reset(new juce::TextButton("clearSelectionButton"));
    addAndMakeVisible(clearSelectionButton.get());
    clearSelectionButton->setButtonText(TRANS("DE-SEL"));
    clearSelectionButton->addListener(this);

    nextFileButton.reset(new juce::TextButton("nextFileButton"));
    addAndMakeVisible(nextFileButton.get());
    nextFileButton->setButtonText(TRANS("NEXT"));
    nextFileButton->addListener(this);

    autoPlayButton.reset(new juce::ToggleButton(""));
    addAndMakeVisible(autoPlayButton.get());

    autoPlayLabel.reset(new juce::Label("", TRANS("Auto-Play")));
    addAndMakeVisible(autoPlayLabel.get());
    autoPlayLabelWidth = juce::LookAndFeel::getDefaultLookAndFeel().getLabelFont(*autoPlayLabel.get()).getStringWidth(TRANS(TRANS("Auto-Play")));

    exportButton.reset(new juce::TextButton("exportButton"));
    addAndMakeVisible(exportButton.get());
    exportButton->setButtonText(TRANS("EXPROT"));
    exportButton->addListener(this);

    waveImageLoadStateLabel.reset(new juce::Label("waveImageLoadStateLabel", TRANS("")));
    addAndMakeVisible(waveImageLoadStateLabel.get());
    waveImageLoadStateLabel->addMouseListener(this, true);

    selectionCover.reset(new ThumbnailCoverComponent());
    addAndMakeVisible(selectionCover.get());
    selectionCover->setBounds(-100, 40, 0, 200);

    manager.registerBasicFormats();
    thumb.addChangeListener(this);
    ifSucceedLoaded = false;

    transportSource.addChangeListener(this);
    readyToPlay = false;
    readerSource = nullptr;

    setSize(600, 400);

    setAudioChannels(0, 2);
    startTimer(40);
}

AudioExportComponent::AudioExportComponent()
    :thumbCache(256), thumb(128, manager, thumbCache)
{}

AudioExportComponent::~AudioExportComponent()
{
    shutdownAudio();

    preFileButton = nullptr;
    stopPlayButton = nullptr;
    playOrPauseButton = nullptr;
    clearSelectionButton = nullptr;
    nextFileButton = nullptr;
    exportButton = nullptr;
    waveImageLoadStateLabel = nullptr;
    selectionCover = nullptr;
}

void AudioExportComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    juce::Rectangle<int> thumbnailBounds(0, 40, getWidth(), 200);
    g.setColour(juce::Colour(juce::uint8(48), 66, 37, 1.0f));
    g.fillRect(thumbnailBounds);

    if (ifSucceedLoaded && thumb.isFullyLoaded())
    {
        g.setColour(juce::Colour(juce::uint8(109), 170, 69, 1.0f));
        thumb.drawChannels(g, thumbnailBounds, 0.0, thumb.getTotalLength(), 1.0f);

        g.setColour(juce::Colours::white);
        g.drawLine(timeCursorLineX, 40.0f, timeCursorLineX, 240.0f, 2.0f);
    }
}

void AudioExportComponent::resized()
{
    // layout
    // Pre Play Stop Next       Clear Export
    // Waveform
    preFileButton->setBounds(0, 0, 100, 30);
    playOrPauseButton->setBounds(100 + 10, 0, 100, 30);
    stopPlayButton->setBounds(100 + 10 + 100 + 10, 0, 100, 30);
    nextFileButton->setBounds(100 + 10 + 100 + 10 + 100 + 10, 0, 100, 30);
    autoPlayButton->setBounds(100 + 10 + 100 + 10 + 100 + 10 + 100 + 10, 0, 25, 30);
    autoPlayLabel->setBounds(100 + 10 + 100 + 10 + 100 + 10 + 100 + 10 + 25 + 10, 0, autoPlayLabelWidth, 30);
    exportButton->setBounds(getWidth() - 100, 0, 100, 30);
    clearSelectionButton->setBounds(getWidth() - 100 - 10 - 100, 0, 100, 30);
    waveImageLoadStateLabel->setBounds(0, 40, getWidth(), 200);
}

bool AudioExportComponent::keyPressed(const juce::KeyPress& press)
{
    return false;
}

void AudioExportComponent::buttonClicked(juce::Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == preFileButton.get())
    {
        getParentComponent()->keyPressed(juce::KeyPress(juce::KeyPress::upKey));
    }
    else if (buttonThatWasClicked == stopPlayButton.get())
    {
        shutdownAudio();
        transportSource.stop();
        transportSource.setPosition(0);
    }
    else if (buttonThatWasClicked == playOrPauseButton.get())
    {
        if (readerSource != nullptr && !transportSource.isPlaying())
        {
            // Check Audio Device
            // Open Audio Device
            // Play Audio
            // transportSource.start();
        }
        else
            transportSource.stop();
    }
    else if (buttonThatWasClicked == nextFileButton.get())
    {
        getParentComponent()->keyPressed(juce::KeyPress(juce::KeyPress::downKey));
    }
    else if (buttonThatWasClicked == clearSelectionButton.get())
    {
        selectionCoverStartX = 0;
        selectionCoverEndX = 0;
        selectionCover->setBounds(-100, 40, 0, 200);
        repaint();
    }
    else if (buttonThatWasClicked == exportButton.get())
    {
        //if (DatabaseHelper::CurrentFx != nullptr)
        //{
        //    juce::AlertWindow waitWindow(TRANS("Export..."), "", juce::MessageBoxIconType::WarningIcon);
        //    waitWindow.enterModalState();
        //    auto* reader = manager.createReaderFor(DatabaseHelper::CurrentFx->GetAudioFile());
        //    if (reader != nullptr)
        //    {
        //        // Export All Audio
        //        if (selectionCover->getBounds().getX() < 0)
        //        {
        //            RegionSpotter::Spot(0, reader->lengthInSamples);
        //        }
        //        // Export Selection
        //        else
        //        {
        //            float totalLength = (float)getWidth();
        //            auto startPoint = selectionCover->getBounds().getX();
        //            auto endPoint = selectionCover->getBounds().getX() + selectionCover->getBounds().getWidth();
        //            auto totalSamples = reader->lengthInSamples;
        //            auto startSample = (int)(totalSamples * startPoint / totalLength);
        //            auto endSample = (int)(totalSamples * endPoint / totalLength);
        //            RegionSpotter::Spot(startSample, endSample);
        //        }
        //        delete reader;
        //    }
        //    waitWindow.exitModalState(0);
        //}
    }
}

void AudioExportComponent::UpdataNewFx()
{
    shutdownAudio();
    timeCursorLineX = 0;
    selectionCoverStartX = 0;
    selectionCoverEndX = 0;
    selectionCover->setBounds(-100, 40, 0, 200);
    waveImageLoadStateLabel->setText("", juce::NotificationType::dontSendNotification);
    thumb.setSource(nullptr);
    ifSucceedLoaded = false;
    repaint();

    long long int currentThreadKey = threadKey++;
    playOrPauseButton->setButtonText(TRANS("PLAY"));
    transportSource.setSource(nullptr, 0, nullptr);
    readyToPlay = false;
    if (this->newData->CurrentFx != nullptr && this->newData->CurrentFx->GetAudioFile().existsAsFile())
    {
        // Thumbnail
        waveImageLoadStateLabel->setText(TRANS("Loading Thumbnail Image..."), juce::NotificationType::dontSendNotification);
        ifSucceedLoaded = thumb.setSource(new juce::FileInputSource(this->newData->CurrentFx->GetAudioFile()));
        // Player
        juce::Thread::launch([this, currentThreadKey]() {
            auto* reader = manager.createReaderFor(this->newData->CurrentFx->GetAudioFile());
            if (reader != nullptr)
            {
                auto newSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);   // [11]
                newSource->setLooping(true);
                transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);       // [12]                                                   // [13]
                readerSource.reset(newSource.release());
                readyToPlay = true;
                juce::MessageManagerLock mml;
                if (autoPlayButton->getToggleState())
                {
                    // Check Audio Device
                    // Open Audio Device
                    // Play Audio
                    // transportSource.start();
                }
            }
            });
    }
}

void AudioExportComponent::mouseDown(const juce::MouseEvent& event)
{
    if (ifSucceedLoaded && thumb.isFullyLoaded())
    {
        selectionCoverStartX = event.getPosition().x;
        selectionCoverEndX = event.getPosition().x;
        selectionCover->setBounds(selectionCoverStartX, 40, 0, 200);
        repaint();
    }
}

void AudioExportComponent::mouseDrag(const juce::MouseEvent& event)
{
    if (ifSucceedLoaded && thumb.isFullyLoaded())
    {
        selectionCoverEndX = event.getPosition().x;
        auto start = selectionCoverEndX >= selectionCoverStartX ? selectionCoverStartX : selectionCoverEndX;
        auto width = std::abs(selectionCoverStartX - selectionCoverEndX);
        selectionCover->setBounds(start, 40, width, 200);
        repaint();
    }
}

void AudioExportComponent::mouseUp(const juce::MouseEvent& event)
{
    if (std::abs(selectionCoverStartX - selectionCoverEndX) < 5)
    {
        selectionCoverStartX = 0;
        selectionCoverEndX = 0;
        selectionCover->setBounds(-100, 40, 0, 200);
        repaint();
    }
    if(std::abs(selectionCoverStartX - selectionCoverEndX) < 1) // click
    {
        if (ifSucceedLoaded && thumb.isFullyLoaded())
        {
            transportSource.setPosition(transportSource.getLengthInSeconds() * event.getPosition().getX() / getWidth());
            repaint();
        }
    }
}

void AudioExportComponent::timerCallback()
{
    if (ifSucceedLoaded && thumb.isFullyLoaded())
    {
        auto audioPosition = transportSource.getCurrentPosition();
        auto audioLength = thumb.getTotalLength();
        timeCursorLineX = (float)(audioPosition / audioLength) * getWidth();
        repaint();
    }
}

void AudioExportComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &thumb)
    {
        if (thumb.isFullyLoaded())
        {
            auto loadState = this->newData->CurrentFx == nullptr ? "" : ifSucceedLoaded ? "" : TRANS("Loading Thumbnail Image Failed");
            waveImageLoadStateLabel->setText(loadState, juce::NotificationType::dontSendNotification);
        }
    }
    if (source == &transportSource)
    {
        playOrPauseButton->setButtonText(transportSource.isPlaying() ? TRANS("PAUSE") : TRANS("PLAY"));
    }
}

void AudioExportComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void AudioExportComponent::releaseResources()
{
    transportSource.releaseResources();
}

void AudioExportComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (readyToPlay)
        transportSource.getNextAudioBlock(bufferToFill);
    else
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }
}
