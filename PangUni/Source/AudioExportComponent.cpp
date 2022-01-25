#include <JuceHeader.h>
#include "AudioExportComponent.h"
#include "SystemHelper.h"

//==============================================================================
AudioExportComponent::AudioExportComponent(SearchDataStruct* newData)
    :thumbCache(256), thumb(128, manager, thumbCache)
{
    this->newData = newData;
    threadKey = 0;
    //timeCursorLineX = 0;

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

    thumbnailComp.reset(new ThumbnailComponent(newData));
    addAndMakeVisible(thumbnailComp.get());
    thumbnailComp->selectionCoverEndX = 0;
    thumbnailComp->selectionCoverStartX = 0;
    thumbnailComp->transportSource = nullptr;
    thumbnailComp->thumb = nullptr;
    thumbnailComp->selectionCover->setBounds(-100, 40, 0, 200);

    manager.registerBasicFormats();
    thumb.addChangeListener(this);
    //ifSucceedLoaded = false;

    transportSource.addChangeListener(this);
    readyToPlay = false;
    readerSource = nullptr;

    setSize(600, 400);
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
    thumbnailComp = nullptr;
    waitWindow = nullptr;
}

void AudioExportComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
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
    thumbnailComp->setBounds(0, 40, getWidth(), 200);
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
            auto device = SystemHelper::Helper->audioDeviceManager.get();
            // Check Audio Device
            if (device->getCurrentAudioDevice() != nullptr)
            {
                // Open Audio Device
                device->updateXml();
                auto stateXML = device->createStateXml();
                if (stateXML != nullptr)
                {
                    setAudioChannels(0, 2, stateXML.get());
                    // Play Audio
                    transportSource.start();
                }
            }
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
        thumbnailComp->selectionCoverEndX = 0;
        thumbnailComp->selectionCoverStartX = 0;
        thumbnailComp->selectionCover->setBounds(-100, 40, 0, 200);
    }
    else if (buttonThatWasClicked == exportButton.get())
    {
        if (this->newData->CurrentFx != nullptr && SystemHelper::Helper->userPerposeSpotDAW != "")
        {
            auto* reader = manager.createReaderFor(this->newData->CurrentFx->GetAudioFile());
            if (reader != nullptr)
            {
                waitWindow.reset(new juce::AlertWindow(TRANS("Export..."), "", juce::MessageBoxIconType::WarningIcon));
                waitWindow->enterModalState();
                // Convert Create
                auto outSampleRate = SystemHelper::Helper->systemSettingsHelper->GetSpotSampleRate();
                auto outBitDepth = SystemHelper::Helper->systemSettingsHelper->GetSpotDepth();
                auto outChannels = SystemHelper::Helper->systemSettingsHelper->GetSpotChannels();
                auto outFolderPath = SystemHelper::Helper->systemSettingsHelper->GetSpotOutputFolder();
                auto outResampleTypeString = SystemHelper::Helper->systemSettingsHelper->GetSpotResampleType();

                float totalLength = (float)getWidth();
                auto startPoint = this->thumbnailComp->selectionCover->getBounds().getX();
                auto endPoint = this->thumbnailComp->selectionCover->getBounds().getX() + this->thumbnailComp->selectionCover->getBounds().getWidth();
                auto totalSamples = reader->lengthInSamples;
                auto startSample = (int)(totalSamples * startPoint / totalLength);
                auto endSample = (int)(totalSamples * endPoint / totalLength);
                auto exportSamples = endSample - startSample;
                if (this->thumbnailComp->selectionCover->getBounds().getX() < 0)
                {
                    startSample = 0;
                    exportSamples = reader->lengthInSamples;
                }
                double ratio = reader->sampleRate / outSampleRate;
                double outSize = exportSamples / ratio;
                int outSizeInt = outSize + 1;
                juce::AudioBuffer<float> buffer = juce::AudioBuffer<float>(reader->numChannels, exportSamples);
                juce::AudioBuffer<float> outbuffer = juce::AudioBuffer<float>(outChannels, outSizeInt);

                // Read IN
                reader->read(&buffer, 0, exportSamples, startSample, true, true);

                // Convert
                if (outResampleTypeString == "WindowedSincInterpolator")
                {
                    juce::WindowedSincInterpolator resample;
                    for (int i = 0; (i < reader->numChannels) | (i < outChannels); i++)
                        resample.process(ratio, buffer.getReadPointer(i, 0), outbuffer.getWritePointer(i, 0), outSizeInt);
                }
                else if (outResampleTypeString == "LagrangeInterpolator")
                {
                    juce::LagrangeInterpolator resample;
                    for (int i = 0; (i < reader->numChannels) | (i < outChannels); i++)
                        resample.process(ratio, buffer.getReadPointer(i, 0), outbuffer.getWritePointer(i, 0), outSizeInt);
                }
                else if (outResampleTypeString == "CatmullRomInterpolator")
                {
                    juce::CatmullRomInterpolator resample;
                    for (int i = 0; (i < reader->numChannels) | (i < outChannels); i++)
                        resample.process(ratio, buffer.getReadPointer(i, 0), outbuffer.getWritePointer(i, 0), outSizeInt);
                }
                else if (outResampleTypeString == "LinearInterpolator")
                {
                    juce::LinearInterpolator resample;
                    for (int i = 0; (i < reader->numChannels) | (i < outChannels); i++)
                        resample.process(ratio, buffer.getReadPointer(i, 0), outbuffer.getWritePointer(i, 0), outSizeInt);
                }
                else  // if(outResampleTypeString == "ZeroOrderHoldInterpolator")
                {
                    juce::ZeroOrderHoldInterpolator resample;
                    for (int i = 0; (i < reader->numChannels) | (i < outChannels); i++)
                        resample.process(ratio, buffer.getReadPointer(i, 0), outbuffer.getWritePointer(i, 0), outSizeInt);
                }

                // Write OUT
                juce::File outFileFolder(outFolderPath);
                int createTimes = 0;
                juce::File outFile = outFileFolder.getChildFile(
                    this->newData->CurrentFx->GetAudioFile().getFileNameWithoutExtension()
                    + (createTimes == 0 ? "_Pang" : "_Pang(" + juce::String(createTimes) + ")")
                    + this->newData->CurrentFx->GetAudioFile().getFileExtension());
                while (outFile.existsAsFile())
                {
                    createTimes++;
                    outFile = outFileFolder.getChildFile(
                        this->newData->CurrentFx->GetAudioFile().getFileNameWithoutExtension()
                        + (createTimes == 0 ? "_Pang" : "_Pang(" + juce::String(createTimes) + ")")
                        + this->newData->CurrentFx->GetAudioFile().getFileExtension());
                }
                juce::WavAudioFormat waf;
                auto writer = waf.createWriterFor(new juce::FileOutputStream(outFile), outSampleRate, outChannels, outBitDepth, reader->metadataValues, 0);
                writer->writeFromAudioSampleBuffer(outbuffer, 0, outSizeInt);
                delete writer;
                delete reader;

                if (SystemHelper::Helper->userPerposeSpotDAW == "ProTools")
                {
                    SystemHelper::Helper->spotHelper->SpotToProTools(outFile, 0, outSizeInt);
                }

                waitWindow->exitModalState(0);
                waitWindow.reset(nullptr);
                juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::InfoIcon, "", TRANS("Export Successfully"));
            }
        }
    }
}

void AudioExportComponent::UpdataNewFx()
{
    shutdownAudio();
    thumbnailComp->selectionCoverEndX = 0;
    thumbnailComp->selectionCoverStartX = 0;
    thumbnailComp->transportSource = nullptr;
    thumbnailComp->thumb = nullptr;
    thumbnailComp->selectionCover->setBounds(-100, 40, 0, 200);
    waveImageLoadStateLabel->setText("", juce::NotificationType::dontSendNotification);
    thumb.setSource(nullptr);
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
        if (ifSucceedLoaded)
        {
            thumbnailComp->thumb = &thumb;
        }
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
                thumbnailComp->transportSource = &transportSource;
                juce::MessageManagerLock mml;
                if (autoPlayButton->getToggleState())
                {
                    auto device = SystemHelper::Helper->audioDeviceManager.get();
                    // Check Audio Device
                    if (device->getCurrentAudioDevice() != nullptr)
                    {
                        // Open Audio Device
                        device->updateXml();
                        auto stateXML = device->createStateXml();
                        if (stateXML != nullptr)
                        {
                            setAudioChannels(0, 2, stateXML.get());
                            // Play Audio
                            transportSource.start();
                        }
                    }
                }
            }
            });
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
