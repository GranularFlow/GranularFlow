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

class GranularSynth : public Synth, public Component, public Slider::Listener, public Button::Listener
{
public:
    // Class
	GranularSynth();
	~GranularSynth()override;
    // GUI
    void paint(Graphics&) override;
	void resized();
    // -----------------
    // ProcessBlock
    // -----------------
    void prepareToPlay(float, int);
    void processBlock(AudioBuffer<float>&, MidiBuffer&);
    // -----------------    
    // Listeners
    void sliderValueChanged(Slider*) override;
    void buttonClicked(Button*)override;
    // Get
    int getNumTotalSamples();
    int getPlayerCount();
    // SYNTH
    void setKnobsListener(Knob::Listener*)override;
    void removeKnobsListener()override;
    // Tools
    void movePositionCallback();
    void setWaveCallback();
    // ---MIDI
    void handleMidi(MidiBuffer&);
    // -- Load from File
    void loadAudioFromFile(File);
    void loadAudioIntoSamples();    
    // ---Init
    void showPlayers();
    void clearAudioSamples();
    void addNewPlayer();
    void removePlayer();
    void selectPlayer(int playerNumber);
private:
    Knob::Listener* knobListener = nullptr;
    std::shared_ptr<RingBuffer> ringBufferPntr = nullptr;
    std::unique_ptr<juce::FileChooser> fileChooser = nullptr;
	
    int activePlayers = 0;
    int selectedPlayer = 0;

    GranularSettings topSettings;  
    GranularVisualiser visualiser;
    OwnedArray<GranularPlayer> players;
    AudioBuffer<float> audioSamples {2, 144000 };

    double increment = 1;
    int lastMidiNote = 255;
    float sampleRate = 48000;
    bool waveFormWasSet = false;
    bool midiNoteOn = false;
    bool inputFromFile = true;
};