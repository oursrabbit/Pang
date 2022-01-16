/*
  ==============================================================================

    DatabaseEditorWindow.h
    Created: 11 Jan 2022 5:48:11pm
    Author:  YC

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "DatabaseEditorMainComponent.h"
#include "DatabaseEditorDataStruct.h"

class DatabaseEditorWindow : public juce::DocumentWindow
{
public:
    DatabaseEditorDataStruct* newData;

    DatabaseEditorWindow(juce::String name)
        : DocumentWindow(name,
            juce::Desktop::getInstance().getDefaultLookAndFeel()
            .findColour(juce::ResizableWindow::backgroundColourId),
            DocumentWindow::allButtons)
    {
        newData = new DatabaseEditorDataStruct();
        setUsingNativeTitleBar(true);
        setContentOwned(new DatabaseEditorMainComponent(newData), true);

#if JUCE_IOS || JUCE_ANDROID
        setFullScreen(true);
#else
        setResizable(true, true);
        centreWithSize(getWidth(), getHeight());
#endif

        setVisible(true);
    }

    void closeButtonPressed() override
    {
        delete newData;
        setVisible(false);
    }
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DatabaseEditorWindow)
};