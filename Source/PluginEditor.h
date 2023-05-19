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
class SimpleChorusAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SimpleChorusAudioProcessorEditor (SimpleChorusAudioProcessor&);
    ~SimpleChorusAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

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

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rateSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> depthSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> delaySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleChorusAudioProcessorEditor)
};
