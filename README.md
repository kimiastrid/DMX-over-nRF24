# DMX-over-nRF24
Wireless DMX system that uses RF Nano (Arduino Nano with nRF24L01)

![RF Nano](pics/rf-nano.jpg)

## Transmitter

### Upload the code from Arduino IDE
Upload the transmitter code from Arduino IDE. Before that, make sure you have both libraries (RF24 and DMXSerial) in your Arduino/libraries folder.

### No DMX chip needed!
Normally, you'd have to use a DMX transceiver chip like MAX485 or SN75176 to receive the DMX signal from your DMX controller, but if you don't have the this chip and you're fine with slightly modifying your DMX controller, you can solder a wire directly to the D pin of the transceiver inside the controller. This is where the chip gets the raw signal before sending it to the DMX cable. We want that raw signal, and it will make the Arduino happy. The DMX chip should still work and you'll be able to use both the wireless and the usual wired system.

DMX transceiver pinout:
![SN75176 pinout](pics/sn75176.jpg)

Find this chip in your DMX controller. You'll need three wires. I used wires from a network cable, they work well.
Solder these wires like this:

|SN75176|RF Nano|
|:-----:|:-----:|
|pin 4|RX|
|pin 5|GND|
|pin 8|VCC|

Do not remove the chip, just solder onto its pins.

## Receiver

Upload the transmitter code from Arduino IDE.

### Hacking the LED light

We can bypass the DMX transceiver chip again, but this time, you'll have to cut the PCB trace that leads to pin 1. After this, you will not be able to use the usual DMX cable connection, only wireless.
It is necessary to cut the PCB trace because the DMX chip interferes with the signal, and you can't just "inject" the signal from RF Nano.
Solder a wire to the trace that you cut, but not on the side of the chip, but on the other side of the gap.

```
               _______
----- cut -----| pin 1
   |            |
   |
  wire
```
