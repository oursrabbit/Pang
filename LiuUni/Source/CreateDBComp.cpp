/*
  ==============================================================================

    CreateDBComp.cpp
    Created: 6 Mar 2022 7:53:34pm
    Author:  YC

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CreateDBComp.h"

//==============================================================================
CreateDBComp::CreateDBComp()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(800, 600);

    suffixLabel.setText(TRANS("Suffix: "), juce::NotificationType::dontSendNotification);
    addAndMakeVisible(suffixLabel);

    suffixTextEditor.setText("*.wav|*.mp4|*.*");
    addAndMakeVisible(suffixTextEditor);
    
    addSourceButton.setButtonText(TRANS("Add Source"));
    addSourceButton.addListener(this);
    addAndMakeVisible(addSourceButton);

    deleteSourceButton.setButtonText(TRANS("Del Source"));
    deleteSourceButton.addListener(this);
    addAndMakeVisible(deleteSourceButton);

    addAndMakeVisible(sourceListBox);
    
    outputPathButton.setButtonText(TRANS("Output Path"));
    outputPathButton.addListener(this);
    addAndMakeVisible(outputPathButton);

    outputPathTextEditor.setText(juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getFullPathName(), juce::NotificationType::dontSendNotification);
    addAndMakeVisible(outputPathTextEditor);
    
    createButton.setButtonText(TRANS("Create Database"));
    createButton.addListener(this);
    addAndMakeVisible(createButton);
}

CreateDBComp::~CreateDBComp()
{
    chooser = nullptr;
}

void CreateDBComp::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("CreateDBComp", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void CreateDBComp::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    suffixLabel.setBounds(10, 10, 50, 30);
    suffixTextEditor.setBounds(70, 10, getWidth() - 80, 30);
    deleteSourceButton.setBounds(getWidth() - 110, 50, 100, 30);
    addSourceButton.setBounds(getWidth() - 220, 50, 100, 30);
    outputPathButton.setBounds(getWidth() - 330, 50, 100, 30);
    outputPathTextEditor.setBounds(10, 50, getWidth() - 350, 30);
    sourceListBox.setBounds(10, 90, getWidth() - 20, getHeight() - 140);
    createButton.setBounds(10, getHeight() - 40, getWidth() - 20, 30);
}

void CreateDBComp::buttonClicked(juce::Button* btn)
{
    if (btn == &outputPathButton)
    {
        chooser = std::make_unique<juce::FileChooser>(TRANS("Open"));
        auto chooserFlags = juce::FileBrowserComponent::canSelectDirectories | juce::FileBrowserComponent::useTreeView;
        chooser->launchAsync(chooserFlags, [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file != juce::File{} && file.isDirectory())
                {
                    auto audioFiles = file.findChildFiles(file.findFiles, true, "*.wav");
                    for (auto af : audioFiles)
                    {
                        newData->newFxDB->Fxs.push_back(new Fx(af.getFullPathName(), ""));
                    }
                    fxsTable->UpdateNewFxDB();
                }
            });
    }
}
