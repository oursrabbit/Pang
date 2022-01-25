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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "GUIDesign.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
GUIDesign::GUIDesign ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    samplerateComboBox.reset (new juce::ComboBox ("samplerateComboBox"));
    addAndMakeVisible (samplerateComboBox.get());
    samplerateComboBox->setEditableText (false);
    samplerateComboBox->setJustificationType (juce::Justification::centredLeft);
    samplerateComboBox->setTextWhenNothingSelected (juce::String());
    samplerateComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    samplerateComboBox->addItem (TRANS("96000"), 1);
    samplerateComboBox->addItem (TRANS("48000"), 2);
    samplerateComboBox->addItem (TRANS("44100"), 3);
    samplerateComboBox->addItem (TRANS("8000"), 4);
    samplerateComboBox->addListener (this);

    samplerateComboBox->setBounds (264, 24, 150, 24);

    bitDepthComboBox.reset (new juce::ComboBox ("bitDepthComboBox"));
    addAndMakeVisible (bitDepthComboBox.get());
    bitDepthComboBox->setEditableText (false);
    bitDepthComboBox->setJustificationType (juce::Justification::centredLeft);
    bitDepthComboBox->setTextWhenNothingSelected (juce::String());
    bitDepthComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    bitDepthComboBox->addItem (TRANS("32"), 1);
    bitDepthComboBox->addItem (TRANS("24"), 2);
    bitDepthComboBox->addItem (TRANS("16"), 3);
    bitDepthComboBox->addListener (this);

    bitDepthComboBox->setBounds (240, 64, 150, 24);

    outputTextEditor.reset (new juce::TextEditor ("outputTextEditor"));
    addAndMakeVisible (outputTextEditor.get());
    outputTextEditor->setMultiLine (false);
    outputTextEditor->setReturnKeyStartsNewLine (false);
    outputTextEditor->setReadOnly (false);
    outputTextEditor->setScrollbarsShown (true);
    outputTextEditor->setCaretVisible (true);
    outputTextEditor->setPopupMenuEnabled (true);
    outputTextEditor->setText (juce::String());

    outputTextEditor->setBounds (216, 192, 150, 24);

    resampleComboBox.reset (new juce::ComboBox ("resampleComboBox"));
    addAndMakeVisible (resampleComboBox.get());
    resampleComboBox->setEditableText (false);
    resampleComboBox->setJustificationType (juce::Justification::centredLeft);
    resampleComboBox->setTextWhenNothingSelected (juce::String());
    resampleComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    resampleComboBox->addItem (TRANS("WindowedSincInterpolator"), 1);
    resampleComboBox->addItem (TRANS("LagrangeInterpolator"), 2);
    resampleComboBox->addItem (TRANS("CatmullRomInterpolator"), 3);
    resampleComboBox->addItem (TRANS("LinearInterpolator"), 4);
    resampleComboBox->addItem (TRANS("ZeroOrderHoldInterpolator"), 5);
    resampleComboBox->addListener (this);

    resampleComboBox->setBounds (240, 272, 150, 24);

    channelsComboBox.reset (new juce::ComboBox ("channelsComboBox"));
    addAndMakeVisible (channelsComboBox.get());
    channelsComboBox->setEditableText (false);
    channelsComboBox->setJustificationType (juce::Justification::centredLeft);
    channelsComboBox->setTextWhenNothingSelected (juce::String());
    channelsComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    channelsComboBox->addItem (TRANS("1"), 1);
    channelsComboBox->addItem (TRANS("2"), 2);
    channelsComboBox->addListener (this);

    channelsComboBox->setBounds (224, 144, 150, 24);

    sampleRateLabel.reset (new juce::Label ("sampleRateLabel",
                                            TRANS("Sample Rate:")));
    addAndMakeVisible (sampleRateLabel.get());
    sampleRateLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    sampleRateLabel->setJustificationType (juce::Justification::centredLeft);
    sampleRateLabel->setEditable (false, false, false);
    sampleRateLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    sampleRateLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    sampleRateLabel->setBounds (8, 16, 150, 24);

    bitDepthLabel.reset (new juce::Label ("bitDepthLabel",
                                          TRANS("Bit Depth:")));
    addAndMakeVisible (bitDepthLabel.get());
    bitDepthLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    bitDepthLabel->setJustificationType (juce::Justification::centredLeft);
    bitDepthLabel->setEditable (false, false, false);
    bitDepthLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    bitDepthLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    bitDepthLabel->setBounds (24, 64, 150, 24);

    channelsLabel.reset (new juce::Label ("channelsLabel",
                                          TRANS("Channels:")));
    addAndMakeVisible (channelsLabel.get());
    channelsLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    channelsLabel->setJustificationType (juce::Justification::centredLeft);
    channelsLabel->setEditable (false, false, false);
    channelsLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    channelsLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    channelsLabel->setBounds (40, 112, 150, 24);

    outputLabel.reset (new juce::Label ("outputLabel",
                                        TRANS("Output Folder:")));
    addAndMakeVisible (outputLabel.get());
    outputLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    outputLabel->setJustificationType (juce::Justification::centredLeft);
    outputLabel->setEditable (false, false, false);
    outputLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    outputLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    outputLabel->setBounds (24, 192, 150, 24);

    resampleLabel.reset (new juce::Label ("resampleLabel",
                                          TRANS("Resample Type:")));
    addAndMakeVisible (resampleLabel.get());
    resampleLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    resampleLabel->setJustificationType (juce::Justification::centredLeft);
    resampleLabel->setEditable (false, false, false);
    resampleLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    resampleLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    resampleLabel->setBounds (16, 224, 150, 24);

    outputButton.reset (new juce::TextButton ("outputButton"));
    addAndMakeVisible (outputButton.get());
    outputButton->setButtonText (TRANS("..."));
    outputButton->addListener (this);

    outputButton->setBounds (408, 200, 150, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

GUIDesign::~GUIDesign()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    samplerateComboBox = nullptr;
    bitDepthComboBox = nullptr;
    outputTextEditor = nullptr;
    resampleComboBox = nullptr;
    channelsComboBox = nullptr;
    sampleRateLabel = nullptr;
    bitDepthLabel = nullptr;
    channelsLabel = nullptr;
    outputLabel = nullptr;
    resampleLabel = nullptr;
    outputButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void GUIDesign::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void GUIDesign::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void GUIDesign::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == samplerateComboBox.get())
    {
        //[UserComboBoxCode_samplerateComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_samplerateComboBox]
    }
    else if (comboBoxThatHasChanged == bitDepthComboBox.get())
    {
        //[UserComboBoxCode_bitDepthComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_bitDepthComboBox]
    }
    else if (comboBoxThatHasChanged == resampleComboBox.get())
    {
        //[UserComboBoxCode_resampleComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_resampleComboBox]
    }
    else if (comboBoxThatHasChanged == channelsComboBox.get())
    {
        //[UserComboBoxCode_channelsComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_channelsComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void GUIDesign::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == outputButton.get())
    {
        //[UserButtonCode_outputButton] -- add your button handler code here..
        //[/UserButtonCode_outputButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="GUIDesign" componentName=""
                 parentClasses="public juce::Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
  <COMBOBOX name="samplerateComboBox" id="9778f529d86b0150" memberName="samplerateComboBox"
            virtualName="" explicitFocusOrder="0" pos="264 24 150 24" editable="0"
            layout="33" items="96000&#10;48000&#10;44100&#10;8000" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <COMBOBOX name="bitDepthComboBox" id="88dcbf3b57a46049" memberName="bitDepthComboBox"
            virtualName="" explicitFocusOrder="0" pos="240 64 150 24" editable="0"
            layout="33" items="32&#10;24&#10;16" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TEXTEDITOR name="outputTextEditor" id="25ce716d28d6b0fe" memberName="outputTextEditor"
              virtualName="" explicitFocusOrder="0" pos="216 192 150 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <COMBOBOX name="resampleComboBox" id="af2b041234a6f726" memberName="resampleComboBox"
            virtualName="" explicitFocusOrder="0" pos="240 272 150 24" editable="0"
            layout="33" items="WindowedSincInterpolator&#10;LagrangeInterpolator&#10;CatmullRomInterpolator&#10;LinearInterpolator&#10;ZeroOrderHoldInterpolator"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="channelsComboBox" id="a5681ba08b93d9ce" memberName="channelsComboBox"
            virtualName="" explicitFocusOrder="0" pos="224 144 150 24" editable="0"
            layout="33" items="1&#10;2" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="sampleRateLabel" id="cbc7e93054bf39d4" memberName="sampleRateLabel"
         virtualName="" explicitFocusOrder="0" pos="8 16 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Sample Rate:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="bitDepthLabel" id="bcf89b010ae4186d" memberName="bitDepthLabel"
         virtualName="" explicitFocusOrder="0" pos="24 64 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Bit Depth:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="channelsLabel" id="dd015cf6e2b2cda0" memberName="channelsLabel"
         virtualName="" explicitFocusOrder="0" pos="40 112 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Channels:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="outputLabel" id="4e9ee913a30d8ec8" memberName="outputLabel"
         virtualName="" explicitFocusOrder="0" pos="24 192 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Output Folder:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="resampleLabel" id="7471a8030cdf4515" memberName="resampleLabel"
         virtualName="" explicitFocusOrder="0" pos="16 224 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Resample Type:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="outputButton" id="709f61952d86b40c" memberName="outputButton"
              virtualName="" explicitFocusOrder="0" pos="408 200 150 24" buttonText="..."
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

