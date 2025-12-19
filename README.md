# DMX-over-nRF24
Wireless DMX system that uses RF Nano (Arduino Nano with nRF24L01)

## No DMX chip needed!
I didn't want to use a transceiver chip (MAX485 or SN75176) to receive the DMX signal, so I took apart the DMX controller and soldered a wire directly to the DI (or D) pin of the transceiver inside. That way I actually bypassed the transceiver chip so the Arduino gets the usual UART signal levels.

## DMX transceiver pinout
![SN75176 pinout](pics/sn75176.jpg)
