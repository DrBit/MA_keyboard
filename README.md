[Arduino Artnet sender] (http://blog.drbit.nl/2013/10/arduino-artnet-keyboard-ps2-for-grand-ma2/)
=======================

This file describes the basic functionality of the Arduino PS2 Keyboard Arnet Sender for Grand MA2. The code is part of a bigger project descrived in my own blog [Arduino Artnet sender keyboard for MA2] (http://blog.drbit.nl/2013/10/arduino-artnet-keyboard-ps2-for-grand-ma2/)

The basic use is to have a standard PS2 Keyboard attached to `Arduino uno` and translate each single keycode into `Art-Net pakets` and broadcast them trough ethernet into a network with lighting especific software `grand MA2`.


Circuit
=======

The hardware connection can be seen in this picture:

![Arduino Connections](/ps2keyboard_schematic.png "Arduino Connections")
----------
![PS2 Pins](/PS2-pinout.jpg "PS2 Pins")

Pin 3 of `Arduino uno` is used for the IRQ (Clock). That's the default on Arduino UNO. Other devices might use other pins:

    Valid irq pins:
    Arduino Uno:  2, 3
    Arduino Due:  All pins, except 13 (LED)
    Arduino Mega: 2, 3, 18, 19, 20, 21
    Teensy 2.0:   All pins, except 13 (LED)
    Teensy 2.0:   5, 6, 7, 8
    Teensy 1.0:   0, 1, 2, 3, 4, 6, 7, 16
    Teensy++ 2.0: 0, 1, 2, 3, 18, 19, 36, 37
    Teensy++ 1.0: 0, 1, 2, 3, 18, 19, 36, 37
    Sanguino:     2, 10, 11

Pin 5 on `Arduino uno` is attached to the data pin of the PS2 connector. You can use other pins instead when changing acordingly the pin in the source code.

    const int DataPin = 5;


Configuration
=============

To map the keys to ArtNet (DMX) Channels you can do it by following the steps:

* Press the key combination `ctrl + esc` to enter mapping mode
* Press the key you want to map in the PS2 keyboard
* Type the Art-Net channel number using the numeric keys on your keyboard followed by enter

(Only one Artnet Channel can be attached to a key)

Right now when pressing the key we just maped we will se 255 bit information on the selected Art-Net Channel

As for now all channels are broadcasted into the univers 0 subnet 0. Future releases of the code will make abailable the selection of the universe without the need of complile the code.


Use
===

Now be sure that you have GrandMA software listening on Art-Net and just add as many input remotes as you want.

Check [MA Share] (http://MA-share.net) for further information on how to configure Grand MA software to receive Art-Net commands.

When having `2port node` in the same network check that `MA onPC` has been correctly detected. Typing `ver` in the command line you will see if there are parameters count. Remember to create session or no data will be getting in MA2.

Example of MA2onPC configuration:
![MA2onPC Remote Input Configuration](/MA2_remote_input.png "MA2 Remote inputs")


Code Updates
============

** 17-06-2014 V1.1 
* Fixed Bug in wich release keys would be missed and DMX not updated acordingly
* Added Max Refresh Rate of the DMX packets (default 50 Hz)

** 18-06-2014 V1.1.1
* Added function that will only broadcast DMX if there is data available. (Greatly reduces trafic on the network)
* Changed Serial transmit rate to 57600 to reduce delay when debugging

** 18-06-2014 V1.2
* Fixed bug, when pressing shift or alt and releasing + other keys and then releasing shift first would cause some problems.

** 19-06-2014 V1.2.1
* Fixed mapping issues
* Added refresh every 3 seconds


