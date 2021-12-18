#pragma once

#include <JuceHeader.h>
#include "AudioSearchComponent.h"

//==============================================================================
/*
*/
class AudioExportComponent  : public juce::Component,
                              public juce::Button::Listener,
                              public AudioSearchComponentListener
{
public:
    AudioExportComponent();
    ~AudioExportComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void buttonClicked(juce::Button* buttonThatWasClicked) override;
    void selectedFileChanged() override;
    // 30 + 10 + 200
    const static int FIXHEIGHT = 240;
private:

    std::unique_ptr<juce::TextButton> preFileButton;
    std::unique_ptr<juce::TextButton> stopPlayButton;
    std::unique_ptr<juce::TextButton> playOrPauseButton;
    std::unique_ptr<juce::TextButton> clearSelectionButton;
    std::unique_ptr<juce::TextButton> nextFileButton;
    std::unique_ptr<juce::TextButton> exportButton;

    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    juce::AudioThumbnailCache thumbnailCache;                  // [1]
    juce::AudioThumbnail thumbnail;                            // [2]

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioExportComponent)
};
