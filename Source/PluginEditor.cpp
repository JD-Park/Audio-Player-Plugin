/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PluginProcessor.cpp"

//==============================================================================
AudioPlayerAudioProcessorEditor::AudioPlayerAudioProcessorEditor (AudioPlayerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    addAndMakeVisible(openButton);
    openButton.setButtonText("Open...");
    openButton.onClick = [this] { openButtonClicked(); };

    addAndMakeVisible(playButton);
    playButton.setButtonText("Play");
    playButton.onClick = [this] { playButtonClicked(); };
    playButton.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    playButton.setEnabled(false);

    addAndMakeVisible(pauseButton);
    pauseButton.setButtonText("Pause");
    pauseButton.onClick = [this] { pauseButtonClicked(); };
    pauseButton.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    pauseButton.setEnabled(false);

    addAndMakeVisible(stopButton);
    stopButton.setButtonText("Stop");
    stopButton.onClick = [this] { stopButtonClicked(); };
    stopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    stopButton.setEnabled(false);

    addAndMakeVisible(audioSourceLabel);
    audioSourceLabel.setColour(audioSourceLabel.textColourId, juce::Colours::white);
    audioSourceLabel.setText("Please open a file", juce::NotificationType::dontSendNotification);
}

AudioPlayerAudioProcessorEditor::~AudioPlayerAudioProcessorEditor()
{
}

//==============================================================================
void AudioPlayerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void AudioPlayerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    int lMargin = 20;
    int rMargin = lMargin * 2;
    openButton.setBounds(lMargin, 10, getWidth() - rMargin, 40);
    playButton.setBounds(lMargin, 60, getWidth() - rMargin, 40);
    stopButton.setBounds(lMargin, 160, getWidth() - rMargin, 40);
    pauseButton.setBounds(lMargin, 110, getWidth() - rMargin, 40);
    audioSourceLabel.setBounds(lMargin, 210, getWidth() - rMargin, 40);

}

void AudioPlayerAudioProcessorEditor::openButtonClicked()
{
    addAudioFile();
    playButton.setEnabled(true);
}

void AudioPlayerAudioProcessorEditor::playButtonClicked()
{
    if ((state == AudioPlayerAudioProcessor::TransportState::Stopped) || (state == AudioPlayerAudioProcessor::TransportState::Paused))
    {
        audioProcessor.changeState(AudioPlayerAudioProcessor::TransportState::Starting);
        //playButton.setButtonText("Pause");
    }
    else if (state == AudioPlayerAudioProcessor::TransportState::Playing)
    {
        audioProcessor.changeState(AudioPlayerAudioProcessor::TransportState::Pausing);
        playButton.setButtonText("Resume");
    }
    //stopButton.setButtonText("Stop");
    pauseButton.setEnabled(true);
    openButton.setEnabled(false);
    stopButton.setEnabled(true);
}

void AudioPlayerAudioProcessorEditor::pauseButtonClicked()
{
    //if (state == AudioPlayerAudioProcessor::TransportState::Playing)
    {
        audioProcessor.changeState(AudioPlayerAudioProcessor::TransportState::Pausing);
        //pauseButton.setButtonText("Resume");
    }
}

void AudioPlayerAudioProcessorEditor::stopButtonClicked()
{
    if (state == AudioPlayerAudioProcessor::TransportState::Paused) 
    {
        audioProcessor.changeState(AudioPlayerAudioProcessor::TransportState::Stopped);
    }
    else
    {
        audioProcessor.changeState(AudioPlayerAudioProcessor::TransportState::Stopping);
    }
    playButton.setButtonText("Play");
    //stopButton.setButtonText("Stop");
    openButton.setEnabled(true);
    pauseButton.setEnabled(false);
}

void AudioPlayerAudioProcessorEditor::addAudioFile()
{
    juce::FileChooser chooser("Select an audio file to play...", {}, "*.wav");
    if (chooser.browseForFileToOpen())
    {
        audioSource = chooser.getResult();
        audioProcessor.loadFile(audioSource);
        juce::String labelText = "Audio File Loaded:  " + audioSource.getFileName();
        audioSourceLabel.setText(labelText, juce::NotificationType::dontSendNotification); \
            //auto file = chooser.getResult();                                        
            //auto* reader = formatManager.createReaderFor(file);                   

            //if (reader != nullptr)
        {
            //std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
            //transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);                                
            //playButton.setEnabled(true);                                                                                
            //readerSource.reset(newSource.release());                                                                   
        }
    }
}