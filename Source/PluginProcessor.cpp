/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleChorusAudioProcessor::SimpleChorusAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                        //initialize apvts for holding parameters
                       ), parameters(*this, nullptr, "Parameters", createParameters())
#endif
{
    parameters.addParameterListener("RATE", this);
    parameters.addParameterListener("DEPTH", this);
    parameters.addParameterListener("DELAY", this);
    parameters.addParameterListener("FEEDBACK", this);
    parameters.addParameterListener("MIX", this);

    chorus.setRate(0);
    chorus.setDepth(0);
    chorus.setCentreDelay(1);
    chorus.setFeedback(0);
    chorus.setMix(0);
}

SimpleChorusAudioProcessor::~SimpleChorusAudioProcessor()
{
    parameters.removeParameterListener("RATE", this);
    parameters.removeParameterListener("DEPTH", this);
    parameters.removeParameterListener("DELAY", this);
    parameters.removeParameterListener("FEEDBACK", this);
    parameters.removeParameterListener("MIX", this);
}

//==============================================================================
const juce::String SimpleChorusAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimpleChorusAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SimpleChorusAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SimpleChorusAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SimpleChorusAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleChorusAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SimpleChorusAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleChorusAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SimpleChorusAudioProcessor::getProgramName (int index)
{
    return {};
}

void SimpleChorusAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SimpleChorusAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();
    //DBG("max block size" << samplesPerBlock);

    chorus.prepare(spec);
    chorus.reset();
}

void SimpleChorusAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleChorusAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SimpleChorusAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output channels that didn't contain input data
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    //create block of audio from sample buuffer
    auto audioBlock = juce::dsp::AudioBlock<float>(buffer);

    //ConTextReplacing indicates same auddio block is used for input and output
    auto context = juce::dsp::ProcessContextReplacing<float>(audioBlock);

    //process that block of audio though  the chorus
    chorus.process(context);
}

//==============================================================================
bool SimpleChorusAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SimpleChorusAudioProcessor::createEditor()
{
    //return new juce::GenericAudioProcessorEditor(*this);
    return new SimpleChorusAudioProcessorEditor (*this);
}

//==============================================================================
void SimpleChorusAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    //store your parameters in the memory block.
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void SimpleChorusAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    //restore your parameters from this memory block whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
    }
    
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleChorusAudioProcessor();
}

void SimpleChorusAudioProcessor::reset()
{
    chorus.reset();
}

void SimpleChorusAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "RATE")
        chorus.setRate(newValue);

    if (parameterID == "DEPTH")
        chorus.setDepth(newValue);

    if (parameterID == "DELAY")
        chorus.setCentreDelay(newValue);

    if (parameterID == "FEEDBACK")
        chorus.setFeedback(newValue);

    if (parameterID == "MIX")
        chorus.setMix(newValue);
}

juce::AudioProcessorValueTreeState::ParameterLayout SimpleChorusAudioProcessor::createParameters()
{
    juce::AudioProcessorValueTreeState::ParameterLayout params;

    //params.add(std::make_unique<juce::AudioParameterFloat>("RATE", "Rate", 0.0f, 99.0f, 0.0f));
    //params.add(std::make_unique<juce::AudioParameterFloat>("DEPTH", "Depth", 0.0f, 1.0f, 0.0f));
    //params.add(std::make_unique<juce::AudioParameterFloat>("DELAY", "Center Delay", 1.0f, 100.0f, 1.0f));
    //params.add(std::make_unique<juce::AudioParameterFloat>("FEEDBACK", "Feedback", -1.0f, 1.0f, 0.0f));
    //params.add(std::make_unique<juce::AudioParameterFloat>("MIX", "Wet Dry Mix", 0.0f, 1.0f, 0.0f));

    using Range = juce::NormalisableRange<float>;

    params.add(std::make_unique<juce::AudioParameterInt>("RATE", "Rate", 0, 99, 0));
    params.add(std::make_unique<juce::AudioParameterFloat>("DEPTH", "Depth", Range{ 0.0f, 1.0f, 0.01f }, 0.0f));
    params.add(std::make_unique<juce::AudioParameterInt>("DELAY", "Center Delay", 1, 100, 1));
    params.add(std::make_unique<juce::AudioParameterFloat>("FEEDBACK", "Feedback", Range{ -1.0f, 1.0f, 0.01f }, 0.0f));
    params.add(std::make_unique<juce::AudioParameterFloat>("MIX", "Wet Dry Mix", Range{ 0.0f, 1.0f, 0.01f }, 0.0f));
    //params.add(std::make_unique<juce::AudioParameterChoice>("PRESET", ))

    return params;
}