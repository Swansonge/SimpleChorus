/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LookFeel.h"

//==============================================================================
/**
*/
class SimpleChorusAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                          public juce::ComboBox::Listener
{
public:
    SimpleChorusAudioProcessorEditor (SimpleChorusAudioProcessor&);
    ~SimpleChorusAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void comboBoxChanged(juce::ComboBox* comboBox) override;

private:
    // This reference is provided as a quick way for your editor to access the processor object that created it.
    SimpleChorusAudioProcessor& audioProcessor;

    OtherLookAndFeel otherLookAndFeel;

    juce::Slider rateSlider;
    juce::Slider depthSlider;
    juce::Slider delaySlider;
    juce::Slider feedbackSlider;
    juce::Slider mixSlider;

    juce::Label rateLabel;
    juce::Label depthLabel;
    juce::Label delayLabel;
    juce::Label feedbackLabel;
    juce::Label mixLabel;
    juce::Label title;

    juce::ComboBox presetMenu;

    enum presets
    {
        default_setting = 1,
        basic_chorus,
        basic_flange,
        vibe_rato,
        air_support,
        zap,
        start_ur_engines,
        rubber_chicken,
        boinnng,
        infinite_noise
    };

    juce::ImageComponent imageComponent;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rateSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> depthSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> delaySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixSliderAttachment;

    //comboBox not tied to APVTS
    //std::unique_ptr<juce::ComboBoxParameterAttachment> presetMenuAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleChorusAudioProcessorEditor)
};
