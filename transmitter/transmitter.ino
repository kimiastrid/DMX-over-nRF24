// RF Nano DMX by kimiko, 2025
// I used parts of code from mcnobby from the Arduino forum, 
// but even they said in a post that they used parts of code 
// from the internet, so thanks to everyone who contributed!

// upload this to the RF Nano that will act as a transmitter

#include <DMXSerial.h> // library: https://github.com/mathertel/DMXSerial
#include <SPI.h>
#include "nRF24L01.h" // library: https://github.com/maniacbug/RF24
#include "RF24.h"
#include <Wire.h>


#define MAXGROUPS 2 // default is 17 groups of 30 channels = 510 channels
#define MAXPAYLOAD 32 // max payload size for nrf24l01
#define BURSTTIMER 40 // 40ms between blasts of radio data

// this assumes CE pin 10, CSN pin 9
// it might be different on different RF nano clones, like CE pin 7 and CSN pin 8
// so it's best to check with the supplier
RF24 radio(10,9);

uint8_t pipe[6] = "DMXRF";
uint8_t payload[MAXPAYLOAD];
unsigned long timeslot, flashTimer;
uint8_t sequence = 0;

// TX & RX channels must be the same
// check the 2.4GHz (ISM band) frequencies in your area and pick the one least crowded
uint8_t channel = 108; 

void setup(void)
{
  DMXSerial.init(DMXReceiver);
  radio.begin();
  radio.setAutoAck(false);
  radio.setPayloadSize(MAXPAYLOAD);
  radio.setPALevel(RF24_PA_HIGH);    
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipe);
  radio.stopListening();
  radio.setChannel(channel);
}

void loop(void)
{
  if (millis() - timeslot > BURSTTIMER) {
    timeslot = millis();
    for (uint8_t group = 0; group < MAXGROUPS; group++) {
      payload[0] = group; // set first byte to point to group (groups of 30 bytes)
      payload[1] = sequence++; // second byte helps us monitor consistency of reception at receiver
      for (uint8_t chan = 1; chan<31; chan++) {
        payload[1+chan] = DMXSerial.read((group*30)+chan); // fill payload with DMX data
      }
      bool report = radio.write(&payload, sizeof(payload)); // dump payload to radio
      delayMicroseconds(20); // short delay between packets to ensure radio not overloaded
    }
  }
  // end of loop
}
