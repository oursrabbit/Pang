#include "MainComponent.h"
#include "SystemSettingsHelper.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    audioSearchComp.reset(new AudioSearchComponent());
    addAndMakeVisible(audioSearchComp.get());

    audioExportComp.reset(new AudioExportComponent());
    addAndMakeVisible(audioExportComp.get());

    audioSearchComp->Listener = audioExportComp.get();

    pangMenuComp.reset(new PangMenuComponent());
    addAndMakeVisible(pangMenuComp.get());

    setSize(900, 600);
}

MainComponent::~MainComponent()
{
    audioSearchComp = nullptr;
    audioExportComp = nullptr;
    pangMenuComp = nullptr;
    SystemSettingsHelper::Clear();
}

void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    pangMenuComp->setBounds(0, 0, getWidth(), 24);
    audioExportComp->setBounds(10, getHeight() - 8 - AudioExportComponent::FIXHEIGHT, getWidth() - 20, AudioExportComponent::FIXHEIGHT);
    audioSearchComp->setBounds(10, 24 + 8, getWidth() - 20, getHeight() - 24 - 8 - /* selfHeight- */8 - AudioExportComponent::FIXHEIGHT - 8);
}


