/*
  ==============================================================================

    GranularSynth.h
    Created: 30 Oct 2022 1:56:00pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Utils/Constants.h"
#include "../../Utils/AudioLoad/AudioLoad.h"
#include "GranularPlayer/GranularPlayer.h"
#include "GranularVisualiser/GranularVisualiser.h"
#include "GranularSettings/GranularSettings.h"
#include "RingBuffer/RingBuffer.h"
#include "../Synth.h"

class GranularSynth : public Component, public Slider::Listener, public Button::Listener
{
public:
    // Class
	GranularSynth();
	~GranularSynth()override;
    // GUI
    void paint(Graphics&) override;
	void resized();
    // Listeners
    void sliderValueChanged(Slider*) override;
    void buttonClicked(Button*) override;
    void addListeners();
    void removeListeners();
    // Tools
    void handleMidi(MidiBuffer&);
    void loadAudioFromFile(File);
    void loadAudioIntoSamples();
    int getNumTotalSamples();
    void initAudioSamples(int);
    void clearAudioSamples();
    void addNewPlayer();
    void removePlayer();
    void selectPlayer(int8 playerNumber);

    // --------
    void prepareToPlay(float, int);
    void processBlock(AudioBuffer<float>&, MidiBuffer&);
    // --------
   
    // Getters    
    int8 getPlayerCount();

    void setKnobsListener(Knob::KnobListener*);

private:
    Knob::KnobListener* knobListener = nullptr;

    std::unique_ptr<juce::FileChooser> fileChooser = nullptr;
    // Players    
	OwnedArray<GranularPlayer> granularPlayers; //Owned array is similar to uniquePtr array
    // Visualiser
	GranularVisualiser granularVisualiser;
    // Top settings
    GranularSettings granularSettings;    
    // Samples [channel][sample]
    AudioBuffer<float> audioSamples {2, 256};
    // Ring buffer
    RingBuffer* ringBufferPntr = nullptr;

    float increment = 1.0f;
    int lastMidiNote = -1;
    int bufferSize = 256;
    float sampleRate = 48000;
    float maxPlayTime = 3.0; // 3s   
    // Buffer check
    bool waveFormWasSet = false;
    bool midiNoteOn = false;
    bool inputFromFile = true;
};