/*
  ==============================================================================

    MainWindowMainComponent.cpp
    Created: 11 Jan 2022 5:49:34pm
    Author:  YC

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SearchWindowMainComponent.h"

//==============================================================================
SearchWindowMainComponent::SearchWindowMainComponent()
{
    setSize(1000, 600);
}

SearchWindowMainComponent::~SearchWindowMainComponent()
{
}

void SearchWindowMainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
}

void SearchWindowMainComponent::resized()
{

}
