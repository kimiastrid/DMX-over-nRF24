# DMX-over-nRF24
Wireless DMX system that uses RF Nano (Arduino Nano with nRF24L01)

![RF Nano](pics/rf-nano.jpg)

## No DMX chip needed!
I didn't want to use a transceiver chip (MAX485 or SN75176) to receive the DMX signal, so I took apart the DMX controller and soldered a wire directly to the D (or DI - data input) pin of the transceiver inside. That way I actually bypassed the transceiver chip so the Arduino gets the usual UART signal levels.

## DMX transceiver pinout
![SN75176 pinout](pics/sn75176.jpg)

Find this chip in your DMX controller. You'll need three wires. I used wires from a network cable, they work well.
Solder these wires like this:
|SN75176|RF Nano|
|:-----:|:-----:|
|pin 4|RX|
|pin 5|GND|
|pin 8|VCC|
