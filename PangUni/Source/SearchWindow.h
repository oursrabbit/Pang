/*
  ==============================================================================

    DatabaseEditorWindow.h
    Created: 11 Jan 2022 5:48:11pm
    Author:  YC

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SearchWindowMainComponent.h"
#include "SearchDataStruct.h"

class SearchWindow : public juce::DocumentWindow
{
public:
    SearchDataStruct* newData;

    SearchWindow(juce::String name)
        : DocumentWindow(name,
            juce::Desktop::getInstance().getDefaultLookAndFeel()
            .findColour(juce::ResizableWindow::backgroundColourId),
            DocumentWindow::allButtons)
    {
        newData = new SearchDataStruct();
        setUsingNativeTitleBar(true);
        setContentOwned(new SearchWindowMainComponent(newData), true);

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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SearchWindow)
};