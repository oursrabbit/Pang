/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.1.4

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class GUIDesign  : public juce::Component,
                   public juce::ComboBox::Listener,
                   public juce::Button::Listener
{
public:
    //==============================================================================
    GUIDesign ();
    ~GUIDesign() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::ComboBox> samplerateComboBox;
    std::unique_ptr<juce::ComboBox> bitDepthComboBox;
    std::unique_ptr<juce::TextEditor> outputTextEditor;
    std::unique_ptr<juce::ComboBox> resampleComboBox;
    std::unique_ptr<juce::ComboBox> channelsComboBox;
    std::unique_ptr<juce::Label> sampleRateLabel;
    std::unique_ptr<juce::Label> bitDepthLabel;
    std::unique_ptr<juce::Label> channelsLabel;
    std::unique_ptr<juce::Label> outputLabel;
    std::unique_ptr<juce::Label> resampleLabel;
    std::unique_ptr<juce::TextButton> outputButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GUIDesign)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

