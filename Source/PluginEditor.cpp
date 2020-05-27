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
	mCutSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	mCutSlider.setRange(20, 200, 1);
	mCutSlider.setValue(100);
	addAndMakeVisible(mCutSlider);
}

IdraCleanVstAudioProcessorEditor::~IdraCleanVstAudioProcessorEditor()
{
}

//==============================================================================
void IdraCleanVstAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::ghostwhite);

   
}

void IdraCleanVstAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	mCutSlider.setBounds(400, 200, 100, 100);
}

void IdraCleanVstAudioProcessorEditor::sliderValueChanged(Slider *slider) {
	processor.mCutFreq = mCutSlider.getValue();
}