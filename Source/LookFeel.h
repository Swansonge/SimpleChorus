/*
  ==============================================================================

    LookFeel.h
    Created: 18 May 2023 2:28:44pm
    Author:  ericr

    custom look and feel for simple chorus plugin

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OtherLookAndFeel : public juce::LookAndFeel_V4
{
public:
    OtherLookAndFeel()
    {
        setColour(juce::ResizableWindow::backgroundColourId, juce::Colours::ghostwhite);

        //labels
        setColour(juce::Label::textColourId, juce::Colours::black);  

        //slider
        setColour(juce::Slider::thumbColourId, juce::Colours::black);
        setColour(juce::Slider::trackColourId, juce::Colours::darkgrey);
        setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lightgrey);
        setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::lightgrey);
        
    };

};