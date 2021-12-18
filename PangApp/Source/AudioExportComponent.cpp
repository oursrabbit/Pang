#include <JuceHeader.h>
#include "AudioExportComponent.h"
#include "DatabaseHelper.h"

//==============================================================================
AudioExportComponent::AudioExportComponent()
                        :   thumbnailCache(5),                            // [4]
                            thumbnail(512, formatManager, thumbnailCache) // [5]
{
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

    exportButton.reset(new juce::TextButton("exportButton"));
    addAndMakeVisible(exportButton.get());
    exportButton->setButtonText(TRANS("EXPROT"));
    exportButton->addListener(this);

    formatManager.registerBasicFormats();

    setSize(600, 400);
}

AudioExportComponent::~AudioExportComponent()
{
    preFileButton = nullptr;
    stopPlayButton = nullptr;
    playOrPauseButton = nullptr;
    clearSelectionButton = nullptr;
    nextFileButton = nullptr;
    exportButton = nullptr;
    readerSource = nullptr;
}

void AudioExportComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    juce::Rectangle<int> thumbnailBounds(0, 40, getWidth(), 200);
    if (thumbnail.getNumChannels() == 0)
    {
        g.setColour(juce::Colours::darkgrey);
        g.fillRect(thumbnailBounds);
        g.setColour(juce::Colours::white);
        g.drawFittedText(TRANS("No File Loaded"), thumbnailBounds, juce::Justification::centred, 1);
    }
    else
    {
        g.setColour(juce::Colours::darkgrey);
        g.fillRect(thumbnailBounds);
        g.setColour(juce::Colours::darkgreen);
        thumbnail.drawChannels(g, thumbnailBounds, 0.0, thumbnail.getTotalLength(), 1.0f);

        g.setColour(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
        g.fillRect(0, 40 + 100 - 10, getWidth(), 20);
        g.setColour(juce::Colour(juce::uint8(211), 211, 211, 0.2f));
        g.fillRect(300, 40, 100, 200);
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
    
    exportButton->setBounds(getWidth() - 100, 0, 100, 30);
    clearSelectionButton->setBounds(getWidth() - 100 - 10 - 100, 0, 100, 30);
}

void AudioExportComponent::buttonClicked(juce::Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == preFileButton.get())
    {
    }
    else if (buttonThatWasClicked == stopPlayButton.get())
    {
    }
    else if (buttonThatWasClicked == playOrPauseButton.get())
    {
    }
    else if (buttonThatWasClicked == clearSelectionButton.get())
    {
    }
    else if (buttonThatWasClicked == nextFileButton.get())
    {
    }
    else if (buttonThatWasClicked == exportButton.get())
    {
    }
}

void AudioExportComponent::selectedFileChanged()
{
    if (DatabaseHelper::CurrentFxFileReader != nullptr)
    {
        auto newSource = std::make_unique<juce::AudioFormatReaderSource>(DatabaseHelper::CurrentFxFileReader, true);   // [11]
        transportSource.setSource(newSource.get(), 0, nullptr, DatabaseHelper::CurrentFxFileReader->sampleRate);       // [12]      
        thumbnail.setSource(new juce::FileInputSource(DatabaseHelper::CurrentFx->AudioFile));                            // [7]// [13]
        readerSource.reset(newSource.release());                                          // [14]
        repaint();
    }
}