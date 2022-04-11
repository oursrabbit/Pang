/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.1.6

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

    resFileLabel.reset (new juce::Label ("resFileLabel",
                                         TRANS("Resource File:")));
    addAndMakeVisible (resFileLabel.get());
    resFileLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    resFileLabel->setJustificationType (juce::Justification::centredLeft);
    resFileLabel->setEditable (false, false, false);
    resFileLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    resFileLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    resFileLabel->setBounds (24, 16, 100, 24);

    openResFileButton.reset (new juce::TextButton ("openResFileButton"));
    addAndMakeVisible (openResFileButton.get());
    openResFileButton->setButtonText (TRANS("..."));
    openResFileButton->addListener (this);

    openResFileButton->setBounds (504, 16, 40, 24);

    resTextEditor.reset (new juce::TextEditor ("resTextEditor"));
    addAndMakeVisible (resTextEditor.get());
    resTextEditor->setMultiLine (false);
    resTextEditor->setReturnKeyStartsNewLine (false);
    resTextEditor->setReadOnly (false);
    resTextEditor->setScrollbarsShown (true);
    resTextEditor->setCaretVisible (true);
    resTextEditor->setPopupMenuEnabled (true);
    resTextEditor->setText (juce::String());

    resTextEditor->setBounds (144, 16, 328, 24);

    riffInfoTable.reset (new juce::Component());
    addAndMakeVisible (riffInfoTable.get());
    riffInfoTable->setBounds (32, 64, 512, 472);


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

    resFileLabel = nullptr;
    openResFileButton = nullptr;
    resTextEditor = nullptr;
    riffInfoTable = nullptr;


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

void GUIDesign::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == openResFileButton.get())
    {
        //[UserButtonCode_openResFileButton] -- add your button handler code here..
        //[/UserButtonCode_openResFileButton]
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
  <LABEL name="resFileLabel" id="39ff5392299b9a5d" memberName="resFileLabel"
         virtualName="" explicitFocusOrder="0" pos="24 16 100 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Resource File:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="openResFileButton" id="14c93ae23ad763dc" memberName="openResFileButton"
              virtualName="" explicitFocusOrder="0" pos="504 16 40 24" buttonText="..."
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="resTextEditor" id="b5e7802f29dd9ff6" memberName="resTextEditor"
              virtualName="" explicitFocusOrder="0" pos="144 16 328 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <JUCERCOMP name="riffInfoTable" id="32c3161528d5bb9c" memberName="riffInfoTable"
             virtualName="" explicitFocusOrder="0" pos="32 64 512 472" sourceFile=""
             constructorParams=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

