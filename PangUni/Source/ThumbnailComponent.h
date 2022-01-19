#pragma once

#include <JuceHeader.h>
#include "SearchDataStruct.h"
#include "ThumbnailCoverComponent.h"

//==============================================================================
/*
*/
class ThumbnailComponent : public juce::Component, public juce::Timer
{
public:
    ThumbnailComponent();
    ThumbnailComponent(SearchDataStruct* newData);
    ~ThumbnailComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    bool keyPressed(const juce::KeyPress& press) override;

    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const juce::MouseEvent& event) override;
    void mouseUp(const juce::MouseEvent& event) override;
    // Inherited via Timer
    virtual void timerCallback() override;

    SearchDataStruct* newData;

    std::unique_ptr<ThumbnailCoverComponent> selectionCover;
    int selectionCoverStartX;
    int selectionCoverEndX;

    juce::AudioThumbnail* thumb;

    juce::AudioTransportSource* transportSource;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ThumbnailComponent)
};
