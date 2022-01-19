/*
  ==============================================================================

    AudioDeviceSettingsComponent.cpp
    Created: 16 Jan 2022 1:07:45pm
    Author:  YC

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AudioDeviceSettingsComponent.h"
#include "SystemHelper.h"

//==============================================================================
AudioDeviceSettingsComponent::AudioDeviceSettingsComponent()
{
    adsComp.reset(new juce::AudioDeviceSelectorComponent(*(SystemHelper::Helper->audioDeviceManager.get()), 0, 0, 2, 2, false, false, true, false));
    SystemHelper::Helper->audioDeviceManager->addChangeListener(this);
    addAndMakeVisible(adsComp.get());

    setupResTextEditor.reset(new juce::TextEditor());
    setupResTextEditor->setMultiLine(true, false);
    setupResTextEditor->setReturnKeyStartsNewLine(true);
    addAndMakeVisible(setupResTextEditor.get());
    setSize(1000, 1000);
}

AudioDeviceSettingsComponent::~AudioDeviceSettingsComponent()
{
    SystemHelper::Helper->audioDeviceManager->removeAllChangeListeners();
    adsComp = nullptr;
    setupResTextEditor = nullptr;
}

void AudioDeviceSettingsComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
}

void AudioDeviceSettingsComponent::resized()
{
    adsComp->setBounds(10, 10, getWidth() - 420, getHeight() - 20);
    setupResTextEditor->setBounds(getWidth() - 410, 10, 400, getHeight() -20);
}

void AudioDeviceSettingsComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == SystemHelper::Helper->audioDeviceManager.get())
    {
        std::unique_ptr<juce::AudioDeviceManager> device;
        device.reset(new juce::AudioDeviceManager());
        device->initialiseWithDefaultDevices(0, 2);
        auto setup = adsComp->deviceManager.getAudioDeviceSetup();
        auto error = device->setAudioDeviceSetup(setup, true);

        setupResTextEditor->moveCaretToEnd();
        setupResTextEditor->insertTextAtCaret("----------\r\n");
        if (error.isEmpty() && device->getCurrentAudioDevice() != nullptr)
        {
            auto currentDevice = device->getCurrentAudioDevice();
            setupResTextEditor->insertTextAtCaret(TRANS("Current audio device: ") + currentDevice->getName().quoted() + "\r\n");
            setupResTextEditor->insertTextAtCaret(TRANS("Sample rate: ") + juce::String(currentDevice->getCurrentSampleRate()) + " Hz" + "\r\n");
            setupResTextEditor->insertTextAtCaret(TRANS("Block size: ") + juce::String(currentDevice->getCurrentBufferSizeSamples()) + " samples" + "\r\n");
            setupResTextEditor->insertTextAtCaret(TRANS("Output Latency: ") + juce::String(currentDevice->getOutputLatencyInSamples()) + " samples" + "\r\n");
            setupResTextEditor->insertTextAtCaret(TRANS("Bit depth: ") + juce::String(currentDevice->getCurrentBitDepth()) + "\r\n");
            setupResTextEditor->insertTextAtCaret(TRANS("Output channel names: ") + currentDevice->getOutputChannelNames().joinIntoString(", ") + "\r\n");
            setupResTextEditor->insertTextAtCaret(TRANS("Active output channels: ") + getListOfActiveBits(currentDevice->getActiveOutputChannels()) + "\r\n");
            OnValueChanged();
        }
        else
        {
            setupResTextEditor->insertTextAtCaret(TRANS("No audio device open") + "\r\n");
            setupResTextEditor->insertTextAtCaret(TRANS("Error:") + "\r\n");
            setupResTextEditor->insertTextAtCaret(error + "\r\n");
        }
        device = nullptr;
    }
}

juce::String AudioDeviceSettingsComponent::getListOfActiveBits(const juce::BigInteger& b)
{
    juce::StringArray bits;

    for (int i = 0; i <= b.getHighestBit(); ++i)
        if (b[i])
            bits.add(juce::String(i));

    return bits.joinIntoString(", ");
}
