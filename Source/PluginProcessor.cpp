/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
IdraCleanVstAudioProcessor::IdraCleanVstAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	), highPassFilter(dsp::IIR::Coefficients<float>::makeHighPass(44100.0f, 20.0f)), treeState(*this, nullptr)
#endif
{
	NormalisableRange<float> cutoffRange(20.0f, 200.0f);

	treeState.createAndAddParameter("cutoff", "Cutoff", "cutoff", cutoffRange, 65.0f, nullptr, nullptr);
}

IdraCleanVstAudioProcessor::~IdraCleanVstAudioProcessor()
{
}

//==============================================================================
const String IdraCleanVstAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool IdraCleanVstAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool IdraCleanVstAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool IdraCleanVstAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double IdraCleanVstAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int IdraCleanVstAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int IdraCleanVstAudioProcessor::getCurrentProgram()
{
    return 0;
}

void IdraCleanVstAudioProcessor::setCurrentProgram (int index)
{
}

const String IdraCleanVstAudioProcessor::getProgramName (int index)
{
    return {};
}

void IdraCleanVstAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void IdraCleanVstAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

	dsp::ProcessSpec spec;
	spec.sampleRate = sampleRate;
	spec.maximumBlockSize = samplesPerBlock;
	spec.numChannels = getTotalNumOutputChannels();
	highPassFilter.prepare(spec);
	highPassFilter.reset();


}

void IdraCleanVstAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool IdraCleanVstAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void IdraCleanVstAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

	dsp::AudioBlock<float> block(buffer);

	highPassFilter.process(dsp::ProcessContextReplacing<float>(block));

	float cutFreqTree = *treeState.getRawParameterValue(CUT_ID);
	//relay changes in UI -> update the filter
	*highPassFilter.state = *dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), cutFreqTree);

		//hpF è un process duplicator non un filter, etro nel PD e prendo lo state
}

//==============================================================================
bool IdraCleanVstAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* IdraCleanVstAudioProcessor::createEditor()
{
    return new IdraCleanVstAudioProcessorEditor (*this);
}

//==============================================================================
void IdraCleanVstAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void IdraCleanVstAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new IdraCleanVstAudioProcessor();
}
