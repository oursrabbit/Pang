/*
  ==============================================================================

    CreateDBComp.cpp
    Created: 6 Mar 2022 7:53:34pm
    Author:  YC

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CreateDBComp.h"
#include <vlc/vlc.h>
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

void CreateDBComp::createDB()
{
    if (suffixTextEditor.getText().isNotEmpty() && outputPathTextEditor.getText().isNotEmpty() && sourceListBox.SourcePaths.size() != 0)
    {
        juce::String outputString = "FileName\tDuration\tFullPath\tKeyWords\n";
        std::vector<MediaFileInfo> mediafiles;
        mediafiles.clear();

        libvlc_instance_t* inst;
        libvlc_media_t* m;

        inst = libvlc_new(0, NULL);

        for (size_t i = 0; i < sourceListBox.SourcePaths.size(); i++)
        {
            auto path = sourceListBox.SourcePaths[i];
            auto dir = juce::File::createFileWithoutCheckingPath(path);
            juce::StringArray suffixs;
            suffixs.addTokens(suffixTextEditor.getText(), "|", "");
            for (size_t j = 0; j < suffixs.size(); j++)
            {
                auto files = dir.findChildFiles(juce::File::findFiles, true, suffixs[j]);
                for (size_t k = 0; k < files.size(); k++)
                {
                    auto file = files[k];
                    juce::String duration = "";
                    //Create a new item
                    m = libvlc_media_new_path(inst, file.getFullPathName().toRawUTF8());
                    libvlc_media_parse(m);
                    auto time = libvlc_media_get_duration(m) / 1000; // s
                    libvlc_media_release(m);
                    int min = time / 60;
                    int seconds = time % 60;
                    duration = juce::String(min) + "'" + juce::String(seconds);
                    outputString +=
                        file.getFileName() + "\t" +
                        duration + "\t" +
                        file.getFullPathName() + "\t" +
                        "" /* Key Words */ + "\n";
                }
            }
        }
        auto outputdir = juce::File::createFileWithoutCheckingPath(outputPathTextEditor.getText());
        auto outputfile = outputdir.getChildFile("liuuni.txt");
        auto times = 1;
        while (outputfile.existsAsFile())
            outputfile = outputdir.getChildFile("liuuni(" + juce::String(times++) + ").txt");
        juce::FileOutputStream outputfilestream(outputfile);
        outputfilestream.writeString(outputString);
        outputfilestream.flush();
        libvlc_release(inst);
        juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::InfoIcon, "", TRANS("Done"));
    }
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
                    outputPathTextEditor.setText(file.getFullPathName(), false);
                }
            });
    }
    else if (btn == &addSourceButton)
    {
        chooser = std::make_unique<juce::FileChooser>(TRANS("Open"));
        auto chooserFlags = juce::FileBrowserComponent::canSelectDirectories | juce::FileBrowserComponent::useTreeView;
        chooser->launchAsync(chooserFlags, [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file != juce::File{} && file.isDirectory())
                {
                    sourceListBox.updateList(file.getFullPathName());
                }
            });
    }
    else if (btn == &deleteSourceButton)
    {
        sourceListBox.updateList("", false);
    }
    else if (btn == &createButton)
    {
        createDB();
    }
}
