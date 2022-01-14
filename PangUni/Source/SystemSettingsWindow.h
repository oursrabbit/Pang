/*
  ==============================================================================

    DatabaseEditorWindow.h
    Created: 11 Jan 2022 5:48:11pm
    Author:  YC

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SystemSettingsComponent.h"

class SystemSettingsWindow : public juce::DocumentWindow
{
public:
    SystemSettingsWindow(juce::String name)
        : DocumentWindow(name,
            juce::Desktop::getInstance().getDefaultLookAndFeel()
            .findColour(juce::ResizableWindow::backgroundColourId),
            DocumentWindow::allButtons)
    {
        setUsingNativeTitleBar(true);
        setContentOwned(new SystemSettingsComponent(), true);

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
        setVisible(false);
    }
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SystemSettingsWindow)
};