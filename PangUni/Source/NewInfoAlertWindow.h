/*
  ==============================================================================

    NewInfoAlertWindow.h
    Created: 12 Jan 2022 8:02:12pm
    Author:  YC

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "FxDB.h"

class NewInfoAlertWindow : public juce::Component
{
public:
    FxDB* newFxDB;
    std::unique_ptr<juce::Label> message;
    std::unique_ptr<juce::TextEditor> newInfoName;

    NewInfoAlertWindow();
    NewInfoAlertWindow(FxDB* newFxDB);
    ~NewInfoAlertWindow() override;
    void paint(juce::Graphics& g) override;
    void resized() override;
};