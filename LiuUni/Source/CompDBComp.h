/*
  ==============================================================================

    CompDBComp.h
    Created: 6 Mar 2022 7:53:54pm
    Author:  YC

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class CompDBComp  : public juce::Component
{
public:
    CompDBComp();
    ~CompDBComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompDBComp)
};
