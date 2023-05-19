
/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleChorusAudioProcessorEditor::SimpleChorusAudioProcessorEditor (SimpleChorusAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
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
    rateSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::antiquewhite);
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
    depthSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::antiquewhite);
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
    delaySlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::antiquewhite);
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
    feedbackSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::antiquewhite);
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
    mixSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::antiquewhite);
    mixSlider.setColour(juce::Slider::textBoxHighlightColourId, juce::Colours::black);
    addAndMakeVisible(mixSlider);
    mixSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "MIX", mixSlider);
    //MIX LABEL
    mixLabel.setText("Mix", juce::dontSendNotification);
    mixLabel.setJustificationType(juce::Justification::centred);
    mixLabel.attachToComponent(&mixSlider, false);
    mixLabel.setFont(newFont);
    addAndMakeVisible(mixLabel);

    setSize (700, 200);
}

SimpleChorusAudioProcessorEditor::~SimpleChorusAudioProcessorEditor()
{
}

//==============================================================================
void SimpleChorusAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (30.0f);
}

void SimpleChorusAudioProcessorEditor::resized()
{
    const float sliderWidth = 0.2f;
    const float sliderHeight = 0.5f;

    rateSlider.setBoundsRelative(0.0f, 0.3f, sliderWidth, sliderHeight);
    depthSlider.setBoundsRelative(0.2f, 0.3f, sliderWidth, sliderHeight);
    delaySlider.setBoundsRelative(0.4f, 0.3f, sliderWidth, sliderHeight);
    feedbackSlider.setBoundsRelative(0.6f, 0.3f, sliderWidth, sliderHeight);
    mixSlider.setBoundsRelative(0.8f, 0.3f, sliderWidth, sliderHeight);
}
