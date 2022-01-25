#pragma once

#include <JuceHeader.h>
#include "SearchDataStruct.h"
#include "ThumbnailComponent.h"
#include "ThumbnailCoverComponent.h"

//==============================================================================
/*
*/
class AudioExportComponent  : public juce::AudioAppComponent,
                              public juce::Button::Listener,
                              public juce::ChangeListener
{
public:
    AudioExportComponent();
    AudioExportComponent(SearchDataStruct* newData);
    ~AudioExportComponent() override;

    void UpdataNewFx();

    // Inherited via AudioAppComponent
    virtual void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    virtual void releaseResources() override;
    virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;

    void paint (juce::Graphics&) override;
    void resized() override;
    bool keyPressed(const juce::KeyPress& press) override;
    void buttonClicked(juce::Button* buttonThatWasClicked) override;

    // Inherited via ChangeListener
    virtual void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    // 30 + 10 + 200
    const static int FIXHEIGHT = 240;

    SearchDataStruct* newData;
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
    std::unique_ptr<ThumbnailComponent> thumbnailComp;
    std::unique_ptr <juce::AlertWindow> waitWindow;

    juce::AudioFormatManager manager;
    juce::AudioThumbnailCache thumbCache;
    juce::AudioThumbnail thumb;
    //float timeCursorLineX;
    bool ifSucceedLoaded;

    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;

    long long int threadKey;
    bool readyToPlay;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioExportComponent)
};
