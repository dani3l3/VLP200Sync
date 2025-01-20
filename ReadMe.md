# VLP200Sync
a custom device based on Arduino to trigger the drum machine on the Valeton VLP200 looper pedal on MIDI START and STOP messages
by Plank guitars and musical things by Shambien (Daniele Muscetta) - https://www.shambien.com

- 2025 01 19 - v1.0 - initial version

Tested on breadboard with Arduino UNO (but will impement the device/box using a smaller/different board, it should make no difference, as you only really need one analog pin and the serial RX pin - plus VCC and ground, of course - for this to work, so the smallest/cheapest Arduino clone you can find should work)


## What is it, what does it do and why?

I bought a [VLP200 looper pedal by Valeton](https://www.valeton.net/VLP200.html) which appeared to have a nice feature set with a very cheap price compared to the competition.
It includes a MIDI sync capability so that your recorded loop can be quantized and kept in time with its own internal drum patterns (which can be fancy or just a simple metronome) following the tempo/BPM or other electronic instruments (essential for my live performances). Unfortunately the instructions were not really clear and - while I didn't expect a fully configurable MIDI implementation such as on BOSS's pedals (which are the market leader for a reason but they are also more expensive) - I was at least expecting that, other than synchronizing BPM/tempo, the device would react to MIDI START and STOP (and maybe CONTINUE) commands/messages, so that the drum would start together with the rest when I press 'play' on the main sequencer.
Unfortunately, this does not happen and the drum patterns have to be started by pressing a rather small and finnicky little button... which makes it very hard to start "on the beat". Basically the MIDI IN implementation of the VLP200 only synchronizes MIDI clock/tempo/BPM, but doesn't react at all to START and STOP messages.
There have been discussions on the comments of [certain YouTube videos that were showcasing this pedal](https://www.youtube.com/watch?v=h4WQNo-W7gM) and some other users were really disappointed.
BUT the VLP200 has a jack input for a 'CTRL pedal' - which is just a simple analog interface for a momentary button: if the button is pressed once, quickly, this starts the drum pattern just like the small button on the device itself would do (you can also 'long press' for 'tap tempo' functionality, but I don't really use that part; I just want to trigger the drum machine to start) but with a bigger/more comfortable button, so that it is a little bit easier to start 'on the beat'. It works but it's still not perfect/ideal to do it by hand.

After analyzing the available options, I came up with the idea: I can build a small (additional) device/box that takes the same MIDI input (which has to be sent both to the VLP200 for MIDI clock AND to this additional box, from a MIDI thru box - or implementing the MIDI thru on this new device) and can process the START and STOP messages and 'emulate' the behaviour of a CTRL pedal with a relay. Basically, from the same MIDI signal in the chain, the VLP200 only consumes MIDI clock and adjust tempo/BPM, while this additional box would react to START and STOP messages and start it, giving me the missing functionality.

So I started studying and building it using Arduino - albeit, in this case, a lot of the circuitry is just for a MIDI IN interface (and I working to expand that to also spit out the same signal as MIDI THRU [TODO update schematics and this text when ready] so that it can be used in 'daisy chain' fashion without a MIDI THRU box) and the Arduino part is really really simple and straightforward and just serves as 'glue'.


## Hardware

1. Arduino
1. 1 Optocoupler 6N137
1. 220 Ohm resistor
1. 1 diode (any one should be fine, I used a 1N914 200mA 100V)
1. 4.7K Ohm resistor
1. 100nF capacitor (ceramic is fine i.e. 104)
1. single relay module for Arduino KY019
1. female MIDI mini 1/8' TRS jack OR DIN 5pins connector for MIDI IN (depending on what cable you use to deliver the MIDI signal to this box: I used the mini TRS because that was the same that was coming into the VLP200)
1. female MONO 1/4' jack (assuming you plug a male-to-male standard mono jack cable like those for pedals and guitars beween this device and into the CTRL port on the Valeton)


<img src="https://github.com/dani3l3/VLP200Sync/blob/master/img/circuit-MIDI-IN.jpg?raw=true" alt="MIDI IN circuit" width="250">

<img src="https://github.com/dani3l3/VLP200Sync/blob/master/img/circuit-RELAY.jpg?raw=true" alt="RELAY" width="250">


PS: The schematics for the MIDI IN interface have been mostly derived from [this forum post on stackexchange](https://arduino.stackexchange.com/questions/56279/how-do-i-properly-receive-midi-with-arduino-with-6n138/66746#66746)

[TODO add parts for MIDI THRU and update schematics once ready]



## Code
The code is really short and simple and it includes a lot of comments and it should be easy to figure out what to tweak (there is one delay for how long the relay keeps the circuit closed before re-opening it, simulating the momentary button press and a couple of instructions commented out that can be enabled to debug if the MIDI information is arriving to the Arduino - on boards such as Arduino UNO that have a special internal LED on pin 13 that can be turned on, since it's difficult to troubleshoot MIDI interfaces on some arduino's because the serial RX bus is shared with the USB connection - also making it impossible to upload projects to the board WHILE MIDI data is being received, which is kind of annoying).

Besides the code, in this repository you will find [some pictures I took during various phases of the build process and the circuit diagram I used](./img/).







