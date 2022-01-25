/*
  ==============================================================================

    MainWindowMainComponent.cpp
    Created: 11 Jan 2022 5:49:34pm
    Author:  YC

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RIFFEditorMainComponent.h"

//==============================================================================
RIFFEditorMainComponent::RIFFEditorMainComponent()
{
    openFileButton.reset(new juce::TextButton(""));
    openFileButton->setButtonText(TRANS("Open"));
    openFileButton->addListener(this);
    addAndMakeVisible(openFileButton.get());

    setSize(1000, 600);
}

RIFFEditorMainComponent::~RIFFEditorMainComponent()
{
    openFileButton = nullptr;
    chooser = nullptr;
}

void RIFFEditorMainComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background
}

void RIFFEditorMainComponent::resized()
{
    openFileButton->setBounds(100, 100, 100, 100);
}

void RIFFEditorMainComponent::buttonClicked(juce::Button* btn)
{
    if (btn == openFileButton.get())
    {
        chooser = std::make_unique<juce::FileChooser>(TRANS("Open"), juce::File{}, "*.wav");
        auto chooserFlags = juce::FileBrowserComponent::openMode;
        chooser->launchAsync(chooserFlags, [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file != juce::File{} && file.existsAsFile())
                {
                    if (file.getFileExtension() == ".wav")
                    {
                        auto wavExFormate = new WavAudioFormatPangEx(new juce::FileInputStream(file));
                        
                        delete wavExFormate;
                    }
                }
            });
    }
}
