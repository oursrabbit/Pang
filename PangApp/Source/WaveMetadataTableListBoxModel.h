/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.1.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "DatabaseHelper.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/

class WaveMetadataTableListBoxModelListener
{
public:
    virtual void tableSelectedRowChanged(int) {};
};

class WaveMetadataTableListBoxModel  : public juce::Component, juce::TableListBoxModel
{
public:
    //==============================================================================
    WaveMetadataTableListBoxModel ();
    ~WaveMetadataTableListBoxModel() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;

    void Update();
    WaveMetadataTableListBoxModelListener* Listener = nullptr;
private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    juce::TableListBox table;
    
    //[/UserVariables]

    //==============================================================================

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveMetadataTableListBoxModel)

    // Inherited via TableListBoxModel
    virtual int getNumRows() override;
    virtual void paintRowBackground(juce::Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;
    virtual void paintCell(juce::Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    virtual virtual void selectedRowsChanged(int lastRowSelected) override;
};

//[EndFile] You can add extra defines here...
//[/EndFile]

