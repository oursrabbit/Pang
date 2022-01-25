#include "MainComponent.h"

int ConvertToInt(char* buffer)
{
    return (int)((int)(buffer[0] << 0) & 0x000000FF)
        + (int)((int)(buffer[1] << 8) & 0x0000FF00)
        + (int)((int)(buffer[2] << 16) & 0x00FF0000)
        + (int)((int)(buffer[3] << 24) & 0xFF000000);
}

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize(800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired(juce::RuntimePermissions::recordAudio)
        && !juce::RuntimePermissions::isGranted(juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
            [&](bool granted) { setAudioChannels(granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels(2, 2);
    }


    juce::WavAudioFormat waf;

    juce::File* audioFile = new juce::File("C:\\Users\\YC\\Desktop\\Pang\\PantTestDB\\TESTRES\\093 Brk Full Pow.wav");
    juce::FileInputStream* inFileStream = new juce::FileInputStream(*audioFile);
    auto reader = waf.createReaderFor(inFileStream, true);
    juce::AudioBuffer<float> buffer = juce::AudioBuffer<float>(2, reader->lengthInSamples);
    reader->read(&buffer, 0, reader->lengthInSamples, 0, true, true);
    juce::String metaString = "";
    auto copyright = reader->metadataValues.getDescription();
    copyright = reader->metadataValues.getValue("riffInfoCopyright", "23");
    for (auto mvk : reader->metadataValues.getAllKeys())
    {
        metaString += mvk + " | " + reader->metadataValues.getValue(mvk, "") + "\r\n";
    }
    reader->metadataValues.set("riffInfoCopyright", "Pang C++");

    double ratio = reader->sampleRate / 48000.0;
    double outSize = reader->lengthInSamples / ratio;
    int outSizeInt = outSize + 1;
    juce::AudioBuffer<float> outbuffer = juce::AudioBuffer<float>(2, outSizeInt);
    outbuffer.clear();

    juce::LinearInterpolator resample;
    resample.process(ratio, buffer.getReadPointer(0, 0), outbuffer.getWritePointer(0, 0), outSizeInt);
    resample.process(ratio, buffer.getReadPointer(1, 0), outbuffer.getWritePointer(1, 0), outSizeInt);

    juce::File* outFile = new juce::File("C:\\Users\\YC\\Desktop\\out.wav");
    juce::FileOutputStream* outFileStream = new juce::FileOutputStream(*outFile);
    auto writer = waf.createWriterFor(outFileStream, 48000, 2, 16, reader->metadataValues, 0);
    writer->writeFromAudioSampleBuffer(outbuffer, 0, outSizeInt);
    delete writer;
    delete outFile;
    delete reader;
    delete audioFile;
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    bufferToFill.clearActiveBufferRegion();
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
