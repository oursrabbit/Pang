/*
  ==============================================================================

    NewInfoAlertWindow.cpp
    Created: 12 Jan 2022 8:02:12pm
    Author:  YC

  ==============================================================================
*/

#include "NewInfoAlertWindow.h"

NewInfoAlertWindow::NewInfoAlertWindow(FxDB* newFxDB) {
    this->newFxDB = newFxDB;

    message.reset(new juce::Label());
    message->setText(TRANS("Input new FxInfo name."), juce::NotificationType::dontSendNotification);
    addAndMakeVisible(message.get());

    newInfoName.reset(new juce::TextEditor());
    addAndMakeVisible(newInfoName.get());

    setSize(200, 130);
}

NewInfoAlertWindow::NewInfoAlertWindow() {
}

NewInfoAlertWindow::~NewInfoAlertWindow(){}

void NewInfoAlertWindow::paint(juce::Graphics& g) {
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background
}

void NewInfoAlertWindow::resized(){

    message->setBounds(10, 10, 180, 30);
    newInfoName->setBounds(10, 40, 180, 30);
}