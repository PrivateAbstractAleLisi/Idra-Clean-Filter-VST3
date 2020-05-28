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
    mCutSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    mCutSlider.setColour(Slider::ColourIds::textBoxTextColourId, Colours::yellow);
    mCutSlider.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::yellow);
    mCutSlider.setColour(Slider::ColourIds::rotarySliderOutlineColourId, Colours::pink);
    
    
    
    background = ImageCache::getFromMemory(BinaryData::bg_hd_png, BinaryData::bg_hd_pngSize);
    
    
    bgImage.setImage(background);
    bgImage.toBehind(&mCutSlider);
    mCutSlider.toFront(&bgImage);
    
    
    addAndMakeVisible(bgImage);
    addAndMakeVisible(mCutSlider);
    
    sliderAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.treeState, "cutoff", mCutSlider);
    
    
    
}

IdraCleanVstAudioProcessorEditor::~IdraCleanVstAudioProcessorEditor()
{
}

//==============================================================================
void IdraCleanVstAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::darkslategrey);
    
    g.setColour(Colours::pink);
    g.drawSingleLineText("CUT FREQUENCY", 260, 280, juce::Justification::bottomLeft);
    
    
    
}


void IdraCleanVstAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    bgImage.setBounds(0, 0, 500, 300);
    mCutSlider.setBounds(260, 145, 130, 130);
}





