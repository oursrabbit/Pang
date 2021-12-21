#pragma once

#include <JuceHeader.h>
#include "AudioSearchComponent.h"
#include "AudioCoverComponent.h"

//==============================================================================
/*
*/
class AudioExportComponent  : public juce::AudioAppComponent,
                              public juce::Button::Listener,
                              public AudioSearchComponentListener,
                              public juce::Timer,
                              public juce::ChangeListener
{
public:
    AudioExportComponent();
    ~AudioExportComponent() override;

    // Inherited via AudioAppComponent
    virtual void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    virtual void releaseResources() override;
    virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void buttonClicked(juce::Button* buttonThatWasClicked) override;
    void selectedFileChanged() override;
    
    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const juce::MouseEvent& event) override;
    void mouseUp(const juce::MouseEvent& event) override;
    // Inherited via Timer
    virtual void timerCallback() override;

    // Inherited via ChangeListener
    virtual void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    // 30 + 10 + 200
    const static int FIXHEIGHT = 240;

    std::unique_ptr<juce::Label> waveImageLoadStateLabel;
    std::unique_ptr<juce::TextButton> preFileButton;
    std::unique_ptr<juce::TextButton> stopPlayButton;
    std::unique_ptr<juce::TextButton> playOrPauseButton;
    std::unique_ptr<juce::TextButton> clearSelectionButton;
    std::unique_ptr<juce::TextButton> nextFileButton;
    std::unique_ptr<juce::ToggleButton> autoPlayButton;
    std::unique_ptr<juce::Label> autoPlayLabel;
    int autoPlayLabelWidth;
    std::unique_ptr<juce::TextButton> exportButton;
    std::unique_ptr<AudioCoverComponent> selectionCover;
    int selectionCoverStartX;
    int selectionCoverEndX;

    juce::AudioFormatManager manager;
    juce::AudioThumbnailCache thumbCache;
    juce::AudioThumbnail thumb;
    float timeCursorLineX;
    bool ifSucceedLoaded;

    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;

    long long int threadKey;
    bool readyToPlay;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioExportComponent)
};
