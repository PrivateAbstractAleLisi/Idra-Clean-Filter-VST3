/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <JuceHeader.h>

// Include the string library
#include <string>
//#include "../JuceLibraryCode/JuceHeader.h"



//==============================================================================
IdraCleanVstAudioProcessorEditor::IdraCleanVstAudioProcessorEditor (IdraCleanVstAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 300);

	mCutSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mCutSlider.setRange(20.0f, 200.0f, 1.0f);
	mCutSlider.setValue(processor.mCutFreq);
	mCutSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
	mCutSlider.setColour(Slider::ColourIds::textBoxTextColourId, Colours::yellow);
	mCutSlider.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::yellow);
	mCutSlider.setColour(Slider::ColourIds::rotarySliderOutlineColourId, Colours::pink);

	mCutSlider.addListener(this);


	background = ImageCache::getFromMemory(BinaryData::bg_hd_png, BinaryData::bg_hd_pngSize);


	bgImage.setImage(background);
	bgImage.toBehind(&mCutSlider);
	mCutSlider.toFront(&bgImage);


	addAndMakeVisible(bgImage);
	addAndMakeVisible(mCutSlider);

	filterCutoffValue = new AudioProcessorValueTreeState::SliderAttachment(processor.treeState, "cutoff", mCutSlider);



}

IdraCleanVstAudioProcessorEditor::~IdraCleanVstAudioProcessorEditor()
{
}

//==============================================================================
void IdraCleanVstAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::darkslategrey);

	String conv = String::String(processor.mCutFreq);
	g.setColour(Colours::pink);
	g.drawSingleLineText("CUT FREQUENCY", 260, 280, juce::Justification::bottomLeft);
	/*
	Image background = ImageCache::getFromMemory(BinaryData::bg_hd_png, BinaryData::bg_hd_pngSize);

	ImageComponent bgImage;
	bgImage.setImage(background);
	bgImage.addAndMakeVisible();
	g.drawImageAt(background, 0, 0); */


   
}


void IdraCleanVstAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..


	bgImage.setBounds(0, 0, 500, 300);
	mCutSlider.setBounds(260, 140, 130, 130);
}

void IdraCleanVstAudioProcessorEditor::sliderValueChanged(Slider *slider) {
	if (slider == &mCutSlider) { //è un puntatore allo slider giusto?
		processor.mCutFreq = mCutSlider.getValue();
	}
	
	
}