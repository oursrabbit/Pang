#include <JuceHeader.h>
#include "ThumbnailComponent.h"
#include "SystemHelper.h"

//==============================================================================
ThumbnailComponent::ThumbnailComponent(SearchDataStruct* newData)
{
    this->newData = newData;
    selectionCover.reset(new ThumbnailCoverComponent());
    addAndMakeVisible(selectionCover.get());
    selectionCover->setBounds(-100, 40, 0, 200);

    setSize(600, 400);

    startTimer(40);
}

ThumbnailComponent::ThumbnailComponent()
{}

ThumbnailComponent::~ThumbnailComponent()
{
    selectionCover = nullptr;
}

void ThumbnailComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(juce::uint8(48), 66, 37, 1.0f));

    if (thumb != nullptr && thumb->isFullyLoaded())
    {
        auto thumbnailBounds = juce::Rectangle<int>(0, 0, getWidth(), getHeight());
        g.setColour(juce::Colour(juce::uint8(109), 170, 69, 1.0f));
        thumb->drawChannels(g, thumbnailBounds, 0.0, thumb->getTotalLength(), 1.0f);

        if (transportSource != nullptr && transportSource->isPlaying())
        {
            g.setColour(juce::Colours::white);
            auto audioPosition = transportSource->getCurrentPosition();
            auto audioLength = thumb->getTotalLength();
            auto timeCursorLineX = (audioPosition / audioLength) * (double)getWidth();
            g.drawLine(timeCursorLineX, 0, timeCursorLineX, getHeight(), 1.0f);
        }
    }
}

void ThumbnailComponent::resized()
{
}

bool ThumbnailComponent::keyPressed(const juce::KeyPress& press)
{
    return false;
}

void ThumbnailComponent::mouseDown(const juce::MouseEvent& event)
{
    selectionCoverStartX = event.getPosition().x;
    selectionCoverEndX = event.getPosition().x;
    selectionCover->setBounds(selectionCoverStartX, 0, 0, 200);
    repaint();
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   

void ThumbnailComponent::mouseDrag(const juce::MouseEvent& event)
{
    selectionCoverEndX = event.getPosition().x;
    auto start = selectionCoverEndX >= selectionCoverStartX ? selectionCoverStartX : selectionCoverEndX;
    auto width = std::abs(selectionCoverStartX - selectionCoverEndX);
    selectionCover->setBounds(start, 0, width, 200);
    repaint();
}

void ThumbnailComponent::mouseUp(const juce::MouseEvent& event)
{
    if (std::abs(selectionCoverStartX - selectionCoverEndX) < 5)
    {
        selectionCoverStartX = 0;
        selectionCoverEndX = 0;
        selectionCover->setBounds(-100, 0, 0, 200);
        repaint();
    }
    if (std::abs(selectionCoverStartX - selectionCoverEndX) < 1) // click
    {
        if (thumb != nullptr && transportSource != nullptr && thumb->isFullyLoaded())
        {
            transportSource->setPosition(transportSource->getLengthInSeconds() * event.getPosition().getX() / getWidth());
            repaint();
        }
    }
}

void ThumbnailComponent::timerCallback()
{
    if (thumb != nullptr && thumb->isFullyLoaded())
    {
        repaint();
    }
}