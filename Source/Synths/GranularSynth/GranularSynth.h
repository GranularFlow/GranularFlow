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
    // ----------------------
    // Class
	GranularSynth();
	~GranularSynth()override;
    // GUI
    void paint(Graphics&) override;
	void resized();
    // ----------------------
    // ProcessBlock
    // ----------------------
    void prepareToPlay(float, int);
    void processBlock(AudioBuffer<float>&, MidiBuffer&);
    // ----------------------  
    // Listeners
    // --- Knobs
    void setKnobsListener(Knob::Listener*)override;
    void removeKnobsListener()override;
    void sliderValueChanged(Slider*) override;
    void buttonClicked(Button*)override;
    // ----------------------
    // Get
    int getPlayerCount();
    bool isFileInput();
    // ----------------------
    // Tools
    void movePositionCallback();
    void setWaveCallback();
    // ---MIDI
    void handleMidi(MidiBuffer&);
    // -- Load from File
    void loadAudioFromFile(File);
    void loadAudioIntoSamples();    
    // ---Init
    void disableCursorMovements();
    void showPlayers();
    void clearAudioSamples();
    void addNewPlayer();
    void removePlayer();
    void selectPlayer(int);
private:
    // ----------------------
    // Players load
    int activePlayers = 0;
    int selectedPlayer = 0;
    // ----------------------
    std::shared_ptr<RingBuffer> ringBufferPtr = nullptr;
    std::unique_ptr<juce::FileChooser> fileChooser = nullptr;
    // ----------------------
    GranularSettings topSettings;  
    GranularVisualiser visualiser;
    OwnedArray<GranularPlayer> players;
    // ----------------------    
    AudioBuffer<float> audioSamples {2, BUFFER_SAMPLES };
    // ----------------------
    // MIDI
    double increment = 1;
    int lastMidiNote = 255;
    bool midiNoteOn = false;
    // ----------------------
    // Waveform load
    bool waveFormWasSet = false;    
    bool inputFromFile = true;
};