#pragma once

#include <JuceHeader.h>
#include "../Source/Module/FxDB.h"
#include "../Source/Module/Fx.h"
#include "../Source/Module/Fx.h"
#include "DatabaseEditorFxTableMod.h"
#include "DatabaseEditorFxInfoTableMod.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class DatabaseEditorComponent  : public juce::Component, public juce::Button::Listener
{
public:
    FxDB newFxDB;
    DatabaseEditorFxTableMod fxTable;
    DatabaseEditorFxInfoTableMod fxInfoTable;

    //==============================================================================
    DatabaseEditorComponent();
    ~DatabaseEditorComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    virtual void buttonClicked(juce::Button* btn) override;

private:
    //==============================================================================
    // Your private member variables go here...
    juce::TextButton addFxButton; 
    int addFxButtonWidth;

    juce::TextButton deleteFxButton;
    int deleteFxButtonWidth;

    juce::TextButton addCustomInfoButton;
    int addCustomInfoButtonWidth;

    juce::TextButton deleteCustomInfoButton;
    int deleteCustomInfoButtonWidth;

    juce::TextButton openDBButton;
    int openDBButtonWidth;

    juce::TextButton openDBFolderButton;
    int openDBFolderButtonWidth;

    juce::TextButton saveDBButton;
    int saveDBButtonWidth;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DatabaseEditorComponent)
};
