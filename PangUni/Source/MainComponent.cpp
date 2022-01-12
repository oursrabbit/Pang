/*
  ==============================================================================

    MainComponent.cpp
    Created: 12 Jan 2022 12:51:19pm
    Author:  YC

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    menu.reset(new PangMenuComponent());
    addAndMakeVisible(menu.get());
    mainComp.reset(new SearchWindowMainComponent());
    addAndMakeVisible(mainComp.get());

    setSize(1000, 600);
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
}

void MainComponent::resized()
{
    menu->setBounds(0, 0, getWidth(), 30);
    mainComp->setBounds(0, 30, getWidth(), getHeight() - 30);
}
