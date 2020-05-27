/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
IdraCleanVstAudioProcessorEditor::IdraCleanVstAudioProcessorEditor (IdraCleanVstAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 300);

	mCutSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mCutSlider.setRange(20.0f, 200.0f, 1.0f);
	mCutSlider.setValue(100.0f);
	mCutSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
	mCutSlider.setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);
	mCutSlider.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::yellow);

	mCutSlider.addListener(this);
	addAndMakeVisible(mCutSlider);
}

IdraCleanVstAudioProcessorEditor::~IdraCleanVstAudioProcessorEditor()
{
}

//==============================================================================
void IdraCleanVstAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::darkslategrey);

   
}


void IdraCleanVstAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	mCutSlider.setBounds(300, 150, 200, 200);
}

void IdraCleanVstAudioProcessorEditor::sliderValueChanged(Slider *slider) {
	if (slider == &mCutSlider) { //è un puntatore allo slider giusto?
		processor.mCutFreq = mCutSlider.getValue();
	}
	
	
}