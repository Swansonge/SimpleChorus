
/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleChorusAudioProcessorEditor::SimpleChorusAudioProcessorEditor(SimpleChorusAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setLookAndFeel(&otherLookAndFeel);

    //20 point font, bold
    auto newFont = juce::Font("Comic Sans", "Comic Sans MS Bold Italic", 20.0);

    //RATE SLIDER
    rateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    rateSlider.setTextBoxIsEditable(true);
    //for some reason can't edit text box colors in look and feel . . .
    rateSlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::lightgrey);
    rateSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    rateSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::ghostwhite);
    rateSlider.setColour(juce::Slider::textBoxHighlightColourId, juce::Colours::black);
    addAndMakeVisible(rateSlider);
    rateSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "RATE", rateSlider);
    //RATE LABEL
    rateLabel.setText("Rate", juce::dontSendNotification);
    rateLabel.setJustificationType(juce::Justification::centred);
    rateLabel.attachToComponent(&rateSlider, false);
    rateLabel.setFont(newFont);
    addAndMakeVisible(rateLabel);

    //DEPTH SLIDER
    depthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    depthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    depthSlider.setTextBoxIsEditable(true);
    depthSlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::lightgrey);
    depthSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    depthSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::ghostwhite);
    depthSlider.setColour(juce::Slider::textBoxHighlightColourId, juce::Colours::black);
    addAndMakeVisible(depthSlider);
    depthSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "DEPTH", depthSlider);
    //DEPTH LABEL
    depthLabel.setText("Depth", juce::dontSendNotification);
    depthLabel.setJustificationType(juce::Justification::centred);
    depthLabel.attachToComponent(&depthSlider, false);
    depthLabel.setFont(newFont);
    addAndMakeVisible(depthLabel);

    //DELAY SLIDER
    delaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    delaySlider.setTextBoxIsEditable(true);
    delaySlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::lightgrey);
    delaySlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    delaySlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::ghostwhite);
    delaySlider.setColour(juce::Slider::textBoxHighlightColourId, juce::Colours::black);
    addAndMakeVisible(delaySlider);
    delaySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "DELAY", delaySlider);
    //DELAY LABEL
    delayLabel.setText("Delay", juce::dontSendNotification);
    delayLabel.setJustificationType(juce::Justification::centred);
    delayLabel.attachToComponent(&delaySlider, false);
    delayLabel.setFont(newFont);
    addAndMakeVisible(delayLabel);

    //FEEDBACK SLIDER
    feedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    feedbackSlider.setTextBoxIsEditable(true);
    feedbackSlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::lightgrey);
    feedbackSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    feedbackSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::ghostwhite);
    feedbackSlider.setColour(juce::Slider::textBoxHighlightColourId, juce::Colours::black);
    addAndMakeVisible(feedbackSlider);
    feedbackSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "FEEDBACK", feedbackSlider);
    //FEEDBACK LABEL
    feedbackLabel.setText("Feedback", juce::dontSendNotification);
    feedbackLabel.setJustificationType(juce::Justification::centred);
    feedbackLabel.attachToComponent(&feedbackSlider, false);
    feedbackLabel.setFont(newFont);
    addAndMakeVisible(feedbackLabel);

    //MIX SLIDER
    mixSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    mixSlider.setTextBoxIsEditable(true);
    mixSlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::lightgrey);
    mixSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    mixSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::ghostwhite);
    mixSlider.setColour(juce::Slider::textBoxHighlightColourId, juce::Colours::black);
    addAndMakeVisible(mixSlider);
    mixSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "MIX", mixSlider);
    //MIX LABEL
    mixLabel.setText("Mix", juce::dontSendNotification);
    mixLabel.setJustificationType(juce::Justification::centred);
    mixLabel.attachToComponent(&mixSlider, false);
    mixLabel.setFont(newFont);
    addAndMakeVisible(mixLabel);

    //PREESET DROP-DOWN
    presetMenu.addItem("Default", 1);
    presetMenu.addItem("Basic chorus", 2);
    presetMenu.addItem("Basic flange", 3);
    presetMenu.addItem("Vibe-rato", 4);
    presetMenu.addItem("Air support", 5);
    presetMenu.addItem("Zap!", 6);
    presetMenu.addItem("Start ur engines", 7);
    presetMenu.addItem("Rubber chicken", 8);
    presetMenu.addItem("Boinnng", 9);
    presetMenu.addItem("Warning: infinite noise", 10);
    presetMenu.setSelectedId(1);
    presetMenu.setColour(juce::ComboBox::backgroundColourId, juce::Colours::lightgrey);
    presetMenu.setColour(juce::ComboBox::textColourId, juce::Colours::black);
    presetMenu.setColour(juce::ComboBox::outlineColourId, juce::Colours::black);
    addAndMakeVisible(presetMenu);
    
    //IMAGE
    auto image = juce::ImageCache::getFromMemory(BinaryData::simpeChorus_image_PNG, BinaryData::simpeChorus_image_PNGSize);
    //make sure image exists
    if (!image.isNull())
    {
        imageComponent.setImage(image);
        addAndMakeVisible(imageComponent);
    }
    else
        jassert(!image.isNull());


    setSize(700, 200);
}

SimpleChorusAudioProcessorEditor::~SimpleChorusAudioProcessorEditor()
{
}

//==============================================================================
void SimpleChorusAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(30.0f);
}

void SimpleChorusAudioProcessorEditor::resized()
{
    const float sliderWidth = 0.175f;
    const float sliderHeight = 0.475f;

    rateSlider.setBoundsRelative(0.0f, 0.15f, sliderWidth, sliderHeight);
    depthSlider.setBoundsRelative(0.2f, 0.15f, sliderWidth, sliderHeight);
    delaySlider.setBoundsRelative(0.4f, 0.15, sliderWidth, sliderHeight);
    feedbackSlider.setBoundsRelative(0.6f, 0.15f, sliderWidth, sliderHeight);
    mixSlider.setBoundsRelative(0.8f, 0.15f, sliderWidth, sliderHeight);
    presetMenu.setBoundsRelative(0.375f, 0.7f, sliderWidth*1.5, sliderHeight/3);
    imageComponent.setBoundsRelative(0.74f, 0.6f, 0.4f, 0.4f);
}