// RF Nano DMX by kimiko, 2025
// upload this code to the RF nano that will act as a receiver
// (the one on the LED light)
// The light will receive all the DMX channels, so you still need
// to set the correct DMX starting address on the light

#include <SPI.h>
#include "nRF24L01.h" // library: https://github.com/maniacbug/RF24
#include "RF24.h"
#include <Wire.h>
#include "pins_arduino.h"

// this assumes CE pin 10, CSN pin 9
// it might be different on different RF nano clones, like CE pin 7 and CSN pin 8
// so it's best to check with the supplier
RF24 radio(10,9); 

uint8_t pipe[6] = "DMXRF";
#define MAXPAYLOAD 32 // max payload size for nrf24l01
#define MAXGROUPS 2   // default: 17 groups of 30 channels = 510 channels

uint8_t payload[MAXPAYLOAD];
uint8_t rf_channel=108; // important: make sure the transmitter and receiver use the same channel!

uint8_t dmx_data[513];

unsigned long timeStamp;


void setup(void)
{
  dmx_data[0] = 0; // start byte
  dmx_data[21] = 65;
  dmx_data[22] = 66;
  dmx_data[1] = 10;
  DDRD |= B00000010;
  PORTD |= B00000010;
  radio.begin();
  radio.setAutoAck(false);
  radio.setPayloadSize(MAXPAYLOAD);
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(rf_channel);
  radio.openReadingPipe(1,pipe);
  radio.startListening();
}

void loop(void)
{
  if (millis() - timeStamp > 10) {
    timeStamp = millis();
    Serial.begin(100100,SERIAL_8N2);
    Serial.write(0);
    Serial.end();
    Serial.begin(250000,SERIAL_8N2);
    for (uint8_t i = 0; i < 65; i++) {
      Serial.write(dmx_data[i]);
    }
    Serial.end();
    if ( radio.available() ) {
      uint8_t bytes = radio.getPayloadSize();  // get the size of the payload
      radio.read(&payload, bytes);             // fetch payload from FIFO
      for (uint8_t i = 0; i < 30; i++) {
        uint8_t chan = (30*payload[0])+i+1;  // dmx_data[0] must be left zero as the start byte
        dmx_data[chan] = payload[i+2];
      }
    }
  }
}
