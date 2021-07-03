/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class AudioPlayerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    enum TransportState
    {
        Stopped,
        Starting,
        Playing,
        Pausing,
        Paused,
        Stopping
    };
    AudioPlayerAudioProcessorEditor (AudioPlayerAudioProcessor&);
    ~AudioPlayerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPlayerAudioProcessor& audioProcessor;

    juce::TextButton openButton;
    juce::TextButton playButton;
    juce::TextButton stopButton;
    juce::TextButton pauseButton;
    juce::Label audioSourceLabel;
    juce::File audioSource;
    TransportState state;


    void openButtonClicked();
    void playButtonClicked();
    void stopButtonClicked();
    void pauseButtonClicked();
    void addAudioFile();



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPlayerAudioProcessorEditor)
};
