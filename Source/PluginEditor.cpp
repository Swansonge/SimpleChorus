
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
    presetMenu.addItem("Default", default_setting);
    presetMenu.addItem("Basic chorus", basic_chorus);
    presetMenu.addItem("Basic flange", basic_flange);
    presetMenu.addItem("Vibe-rato", vibe_rato);
    presetMenu.addItem("Air support", air_support);
    presetMenu.addItem("Zap!", zap);
    presetMenu.addItem("Start ur engines", start_ur_engines);
    presetMenu.addItem("Rubber chicken", rubber_chicken);
    presetMenu.addItem("Boinnng", boinnng);
    presetMenu.addItem("Warning: infinite noise", infinite_noise);
    presetMenu.setSelectedId(1);
    presetMenu.setColour(juce::ComboBox::backgroundColourId, juce::Colours::lightgrey);
    presetMenu.setColour(juce::ComboBox::textColourId, juce::Colours::black);
    presetMenu.setColour(juce::ComboBox::outlineColourId, juce::Colours::black);
    addAndMakeVisible(presetMenu);
    presetMenu.addListener(this);
    
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

//change slider values when user changes preset
void SimpleChorusAudioProcessorEditor::comboBoxChanged(juce::ComboBox* comboBox)
{
    switch (presetMenu.getSelectedId())
    {
        case default_setting:
            rateSlider.setValue(0);
            depthSlider.setValue(0.0f);
            delaySlider.setValue(0);
            feedbackSlider.setValue(0.0f);
            mixSlider.setValue(0.0f);
            break;
        case basic_chorus:
            rateSlider.setValue(3,juce::sendNotificationSync);
            depthSlider.setValue(0.12f);
            delaySlider.setValue(7);
            feedbackSlider.setValue(0.1f);
            mixSlider.setValue(0.5f);
            break;
        case basic_flange:
            rateSlider.setValue(10);
            depthSlider.setValue(0.06f);
            delaySlider.setValue(3);
            feedbackSlider.setValue(0.55f);
            mixSlider.setValue(0.7f);
            break;
        case vibe_rato:
            rateSlider.setValue(3);
            depthSlider.setValue(0.2f);
            delaySlider.setValue(14);
            feedbackSlider.setValue(0.0f);
            mixSlider.setValue(1.0f);
            break;
        case air_support:
            rateSlider.setValue(15);
            depthSlider.setValue(0.18f);
            delaySlider.setValue(3);
            feedbackSlider.setValue(0.5f);
            mixSlider.setValue(0.37f);
            break;
        case zap:
            rateSlider.setValue(20);
            depthSlider.setValue(0.26f);
            delaySlider.setValue(3);
            feedbackSlider.setValue(0.38f);
            mixSlider.setValue(0.7f);
            break;
        case start_ur_engines:
            rateSlider.setValue(40);
            depthSlider.setValue(0.15f);
            delaySlider.setValue(2);
            feedbackSlider.setValue(0.23f);
            mixSlider.setValue(0.56f);
            break;
        case rubber_chicken:
            rateSlider.setValue(77);
            depthSlider.setValue(0.53f);
            delaySlider.setValue(1);
            feedbackSlider.setValue(0.72f);
            mixSlider.setValue(0.57f);
            break;
        case boinnng:
            rateSlider.setValue(7);
            depthSlider.setValue(0.27f);
            delaySlider.setValue(100);
            feedbackSlider.setValue(0.0f);
            mixSlider.setValue(1.0f);
            break;
        case infinite_noise:
            rateSlider.setValue(99);
            depthSlider.setValue(1.0f);
            delaySlider.setValue(100);
            feedbackSlider.setValue(1.0f);
            mixSlider.setValue(0.01f);
            break;
    }
}