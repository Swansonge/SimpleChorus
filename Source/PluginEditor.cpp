
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

    //RATE SLIDER, RATE LABEL
    customizeFx(&rateSlider, &rateLabel, newFont);
    addAndMakeVisible(rateSlider);
    rateSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "RATE", rateSlider);
    rateLabel.setText("Rate", juce::dontSendNotification);
    rateLabel.attachToComponent(&rateSlider, false);
    addAndMakeVisible(rateLabel);

    //DEPTH SLIDER, DEPTH LABEL
    customizeFx(&depthSlider, &depthLabel, newFont);
    addAndMakeVisible(depthSlider);
    depthSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "DEPTH", depthSlider);
    depthLabel.setText("Depth", juce::dontSendNotification);
    depthLabel.attachToComponent(&depthSlider, false);
    addAndMakeVisible(depthLabel);

    //DELAY SLIDER, DELAY LABEL
    customizeFx(&delaySlider, &delayLabel, newFont);
    addAndMakeVisible(delaySlider);
    delaySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "delay", delaySlider);
    delayLabel.setText("Delay", juce::dontSendNotification);
    delayLabel.attachToComponent(&delaySlider, false);
    addAndMakeVisible(delayLabel);

    //FEEDBACK SLIDER, FEEDBACK LABEL
    customizeFx(&feedbackSlider, &feedbackLabel, newFont);
    addAndMakeVisible(feedbackSlider);
    feedbackSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "feedback", feedbackSlider);
    feedbackLabel.setText("Feedback", juce::dontSendNotification);
    feedbackLabel.attachToComponent(&feedbackSlider, false);
    addAndMakeVisible(feedbackLabel);

    //MIX SLIDER, MIX LABEL
    customizeFx(&mixSlider, &mixLabel, newFont);
    addAndMakeVisible(mixSlider);
    mixSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "mix", mixSlider);
    mixLabel.setText("Mix", juce::dontSendNotification);
    mixLabel.attachToComponent(&mixSlider, false);
    addAndMakeVisible(mixLabel);

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
    const float sliderWidth = 0.175f;
    const float sliderHeight = 0.475f;

    rateSlider.setBoundsRelative(0.0f, 0.25f, sliderWidth, sliderHeight);
    depthSlider.setBoundsRelative(0.2f, 0.25f, sliderWidth, sliderHeight);
    delaySlider.setBoundsRelative(0.4f, 0.25f, sliderWidth, sliderHeight);
    feedbackSlider.setBoundsRelative(0.6f, 0.25f, sliderWidth, sliderHeight);
    mixSlider.setBoundsRelative(0.8f, 0.25f, sliderWidth, sliderHeight);
    imageComponent.setBoundsRelative(0.74f, 0.65f, 0.4f, 0.4f);
}

//customize slider and label graphics in this function to clean up code in constructor
void SimpleChorusAudioProcessorEditor::customizeFx(juce::Slider* slider, juce::Label* label, juce::Font font)
{
    //RATE SLIDER
    slider->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    slider->setTextBoxIsEditable(true);
    //for some reason can't edit text box colors in look and feel . . .
    slider->setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::lightgrey);
    slider->setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    slider->setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::ghostwhite);
    slider->setColour(juce::Slider::textBoxHighlightColourId, juce::Colours::black);

    //RATE LABEL
    label->setJustificationType(juce::Justification::centred);
    label->setFont(font);
}
