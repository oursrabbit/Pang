#pragma once

#include <JuceHeader.h>
#include "AudioSearch/AudioSearchComponent.h"
#include "AudioPlayer/AudioExportComponent.h"
#include "Menu/PangMenuComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    void paint (juce::Graphics& g) override;
    void resized() override;

    bool keyPressed(const juce::KeyPress& press) override;
private:
    //==============================================================================
    // Your private member variables go here...

    std::unique_ptr<AudioSearchComponent> audioSearchComp;
    std::unique_ptr<AudioExportComponent> audioExportComp;
    std::unique_ptr<PangMenuComponent> pangMenuComp;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
