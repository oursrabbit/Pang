#pragma once
#include <JuceHeader.h>

class FxTableListener
{
public:
    virtual void tableSelectedRowChanged() = 0;
    virtual ~FxTableListener() {}
};

class FxTable : public juce::Component, juce::TableListBoxModel
{
public:
    juce::TableListBox table;
    FxTable();
    ~FxTable() override;

    void paint(juce::Graphics& g) override;
    void resized() override;
    bool keyPressed(const juce::KeyPress& press) override;
    void Update();
    juce::String GetText(const int columnNumber, const int rowNumber);
    void SetText(const int columnNumber, const int rowNumber, const juce::String& newText);

    FxTableListener* Listener = nullptr;


private:
    virtual int getNumRows() override;
    virtual void paintRowBackground(juce::Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;
    virtual void paintCell(juce::Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    virtual void selectedRowsChanged(int) override;
    virtual juce::Component* refreshComponentForCell(int rowNumber, int columnId, bool /*isRowSelected*/, juce::Component* existingComponentToUpdate) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FxTable)
};


class EditableTextCustomComponent : public juce::Label
{
public:
    EditableTextCustomComponent(FxTable& td)
        : owner(td)
    {
        setEditable(false, true, false);
    }

    void mouseDown(const juce::MouseEvent& event) override
    {
        owner.table.selectRowsBasedOnModifierKeys(row, event.mods, false);

        Label::mouseDown(event);
    }

    void textWasEdited() override
    {
        owner.SetText(columnId, row, getText());
    }

    void setRowAndColumn(const int newRow, const int newColumn)
    {
        row = newRow;
        columnId = newColumn;
        setText(owner.GetText(columnId, row), juce::dontSendNotification);
    }

private:
    FxTable& owner;
    int row, columnId;
    juce::Colour textColour;
};
