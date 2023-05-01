# GranularFlow
#### EN - Bachleors thesis - Jan Kalinic - BUT 2023
VST version 3 plugin mainly focusing on granular synthesis and creative LFOs.

This readme should provide users more information about this plugin i made as a part of my bachleor's thesis.
Because the plugin was created using separate modules each module will be closely described bellow.

## Wrapper Module
Wrapper is the initial screen you'll see when plugin is added to your DAW.
It consists of 3 synthesizers - additive, granular and wavetable. Each one has controlls that you can modify using LFOs. This screen also contains 4 different LFOs - color, math, wavetable and bounce.
To enable sound from a synthesizer you need to click on a cable that leads to the center output hub. To enable LFO you need to assign it to a parameter - which can be done in the desired synthesizer and then turn it off by clicking on a straight line that leads to LFO bus.

## Granular Synthesizer Module

When you choose to work with this module you'll have to choose if you want to synthesize from a daw buffer on a channel you placed this plugin or from a file. You'll be met with various parameters for a granular synthesis including:
- BUFFER / FILE - buttons that let you choose preferred synthesis source
- Length - sets maximum size of internal buffer
- Count - how many cursors/players are synthesizing at the time
- Select - selects current player-> this will display it's settings

When it comes to player settings there are:
- MODE - how would you like the cursor to get samples from the source -> in case of MIRROR there are actually two samples that are combined and play at the same time
- CURSOR - this can set the cursor on move
- MIDI - if note should be triggered by midi message
- WINDOW - there are three window types that shape the grains to become more linear
- LENGHT - how long should one grain be (up to a whole second)
- PITCH - this setting will increase or decrease the main pitch if the grain
- GRAINS - number of grains that should play at a time
- OFFSET -  between creating grains there is a sample offset so that the grains are not created all at once but with a slight time delay
- VOLUME - controlls volume of newly created grains
- PAN - this make the grains go stereo, rotation corresponds with virtual placement of the grains source

## Additive Synthesizer Module
This module creates a desired number of oscilators for achieving additive synthesis.
Basic module settings are similar to granular module:
- Count - number of oscilators
- Selected - view selected oscilators configuration

Single oscillator settings:
- MIDI - when turned on sound only gets played when midi key is pressed
- PHASE - offsets phase of the harmonic oscilator
- FREQUENCY - sets basic frequency for the wave
- VOLUME - controls volume of an oscilator
- PAN - makes oscilator stereo panned

## Wavetable Module
Wavetable synthesis where you can draw 3 waves, between those waves are computed so called inter waves.
If you want to synthesize the drawn waves, press synthesize button and sound will be produced as soon as the inter waves are interpolated.

- MIDI - either play sound in a loop or a only when a midi key is pressed
- FREQUENCY - sets basic frequency - this changes with wavecount whereas multiple waves create higher frequencies
- WAVE COUNT - goes up by two and sets how many inter waves are needed to be calculated with linear interpolation
- INTERPOLATION - this only affects the sound where inter samples are required, they are interpolated by one of these methods, currently there are two main, but in the future there should be more
- VOLUME - controls volume
- PAN - panning settings for wavetable module

## Color LFO
This LFO takes picture and based on color of the pixel determines output value.
Best way to describe this LFO is compare it to sample and hold LFO, where for a period of time the LFO holds a value of the color.
Parameters:
- DIRECTION - which way the selector should move and choose next pixel for color analysis
- SELECTED COLOR - value on the output depends on the selected R G or B color
- RATE - how fast to sample a new color
- DEPTH - how much to change parameters on output

## Bounce LFO
Creates semi linear sweep for the LFO wave by taking X or Y coordinate of the moving ball.
- BALL SPEED - how much the ball should move in each interval
- DIRECTION - should the output be X or Y position value
- RATE - how fast to set an output value
- DEPTH - how much to change parameters on output

## Math LFO
Works with predefined function values specified in the text input block.
For now the output of that function in range of 0.01 to 10 by step of 0.01 is only an argument for a sine... so anything you'll write there will result in differently shaped sine wave.
- Text input -  there you can write your own function, after you hit enter, the output wave will be shown above
- RATE - how fast to set an output value
- DEPTH - how much to change parameters on output

## Wavetable LFO
This LFO uses the same concept as wavetable synthesis. You can draw your own wave shapes for the output.
Parameters are:
- WAVE COUNT - goes up by two and sets how many inter waves are calculated between the drawn ones
- RATE - how fast to set an output value
- DEPTH - how much to change parameters on output

