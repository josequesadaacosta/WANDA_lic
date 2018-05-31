/*********************************************************************************************************************************
Wanda.cpp is a demo library for a wireless ad hoc diffusion network for digital audio.

Methods herein implemented:

*Ping setup for simple test
*Ping loop for simple test
*Pong method for simple test
*Hello World:
  -Transmitter
  -Receiver
*Package Handling method
*Multiceiver Configuration for nRF24L01
  -Setup for Transmitter
  -Setup for Receiver
*Multiceiver method
  -Loop for Transmitter
  -Loop for Receiver


Data Rate: 1Mbps

CRC: 16 bits (robustness)

Range: 100 m

nRF24: for more information, please refer to: https://maniacbug.github.io/RF24/classRF24.html


Multiceiver: this nRF24L01 feature is the one that provides the wireless diffusion functionality for this network.
It is a feature used in RX mode that contains a set of 6 parallel data pipes with unique addresses. A data pipe is a
logical channel in the physical RF channel. Each data pipe has its own physical address decoding in the nRF24L01.


The data and control interface gives you access to all the features in the nRF24L01. The data and control
interface consists of the following six 5Volt tolerant digital signals:
• IRQ (this signal is active low and is controlled by three maskable interrupt sources)
• CE (this signal is active high and is used to activate the chip in RX or TX mode)
• CSN (SPI signal)
• SCK (SPI signal)
• MOSI (SPI signal)
• MISO (SPI signal)

You can use the SPI to activate the nRF24L01 data FIFOs or the register map by 1 byte SPI commands
during all modes of operation.

The data FIFOs are used to store payload that is transmitted (TX FIFO) or payload that is received and ready to be clocked
out (RX FIFO). The FIFOs are accessible in both PTX mode and PRX mode.



*********************************************************************************************************************************/

// Libraries needed
#include "Wanda.h"
#include <RF24.h>
#include <stdio.h>
#include <SPI.h>
#include <Audio.h>
#include <stdint.h>
#include <AudioStream.h>


//Variable definition


role_e role;
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"}; //easier debug names
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
int ce_pin = 9;
int csn_pin = 10;
RF24 radio(ce_pin, csn_pin);

const uint64_t wAddress[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL, 0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL};


/****************************************************************************************************************************
Method Name: ping_setup()
Input: pipes[2]
Output: none
Description: Method is used for a simple ping trial between two Teensy + nRF24L01 modules
*****************************************************************************************************************************/

void Wanda::ping_setup(uint64_t pipes[2]){

  role = role_ping_out;
  Serial.begin(9600);
  Serial.println("Pingtest/\n");
  Serial.print("ROLE: ");
  Serial.println(role_friendly_name[role]);
  radio.begin();
  radio.setRetries(15,15); // (pause between attempts, number of attempts)
  Serial.println("Setting up channel");

  //Payload: part of the transmitted data that is the actual intended message. Packet = header (source and destination) + payload (actual data)

	radio.setPayloadSize(8);
	radio.setChannel(0x4c);

  // PA Level: Power Amplifier Level. The PA control is used to set the output power from the nRF24L01 power amplifier (PA). In TX mode PA
  //control has four programmable steps, see Table 14 in the nRF24L01 datasheet.

  //PA_MIN for modules that are really close.

  radio.setPALevel(RF24_PA_MAX);

  Serial.println("Setting up pipes");
  if ( role == role_ping_out )
  {
    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]);
  }
  else
  {
    radio.openWritingPipe(pipes[1]);
    radio.openReadingPipe(1,pipes[0]);
  }
  Serial.println("Start listening");
  // Sets module as receiver
  radio.startListening();
  radio.printDetails();
  Serial.println("End of setup process. Starting loop");
}



/****************************************************************************************************************************
Method Name: ping_loop()
Input: none
Output: none
Description: Method is used for a simple ping trial between two Teensy + nRF24L01 modules
*****************************************************************************************************************************/

void Wanda::ping_loop(){

  if (role == role_ping_out)
  {
    //Stop listening to send packet
    radio.stopListening();
    unsigned long time = millis();
    Serial.print("Now sending ");
    Serial.println(time);
    bool ok = radio.write( &time, sizeof(unsigned long) );
    if (ok)
      Serial.println("ok...\n");
    else
      Serial.println("failed.\n");

    radio.startListening();

    unsigned long started_waiting_at = millis();
    bool timeout = false;
    while ( ! radio.available() && ! timeout ) {
        delay(5); //add a small delay to let radio.available to check payload
      if (millis() - started_waiting_at > 200 )
        timeout = true;
    }

    if ( timeout )
    {
      Serial.println("Failed, response timed out.\n");
    }
    else
    {
      unsigned long got_time;
      radio.read( &got_time, sizeof(unsigned long) );
         Serial.print("Got response ");
         Serial.println(got_time);
         Serial.print("round-trip delay: ");
         Serial.println(millis()-got_time);
    }
    delay(1000);
  }
}


/****************************************************************************************************************************
Method Name: pong_loop()
Input: none
Output: none
Description: Method is used for a simple ping trial between two Teensy + nRF24L01 modules
*****************************************************************************************************************************/

void Wanda::pong_method(){

  if ( role == role_pong_back )
  {
    if ( radio.available() )
    {
      unsigned long got_time;
      bool done = false;

      while (!done)
      {
        done = radio.read( &got_time, sizeof(unsigned long) );
                Serial.print("Got payload(");
                Serial.print(sizeof(unsigned long));
                Serial.print(") ");
                Serial.print(got_time);
                Serial.print("\n");
        delay(20);
      }
      radio.stopListening();
      radio.write( &got_time, sizeof(unsigned long) );
      radio.startListening();
    }
  }
}

/****************************************************************************************************************************
Method Name: hello_world_transmitter_setup()
Input: ce_pin, csn_pin
Output: none
Description: Method is used for a simple hello world transmitter configuration between two Teensy + nRF24L01 modules
*****************************************************************************************************************************/

void Wanda::hello_world_transmitter_setup(){

  const uint64_t address = 0xF0F0F0F0E1LL; //random byte for address. It just needs to match the address in receiver code.
  //const byte address[6] = "00001";
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}

/****************************************************************************************************************************
Method Name: hello_world_transmitter_loop()
Input: ce_pin, csn_pin
Output: none
Description: Method is used for a simple hello world transmitter configuration between two Teensy + nRF24L01 modules
*****************************************************************************************************************************/
void Wanda::hello_world_transmitter_loop(){

  const char text[] = "HelloWorld";
  radio.write(&text, sizeof(text));
  delay(1000);
  radio.printDetails();
  Serial.println("Sent.\n");
}

/****************************************************************************************************************************
Method Name: hello_world_receiver()
Input: ce_pin, csn_pin
Output: none
Description: Method is used for a simple hello world transmissiom between two Teensy + nRF24L01 modules
*****************************************************************************************************************************/
void Wanda::hello_world_receiver_setup(){

  //const byte address[6] = "00001";
  const uint64_t address = 0xF0F0F0F0E1LL;
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
}


/****************************************************************************************************************************
Method Name: hello_world_receiver_loop()
Input: ce_pin, csn_pin
Output: none
Description: Method is used for a simple hello world transmissiom between two Teensy + nRF24L01 modules
*****************************************************************************************************************************/

void Wanda::hello_world_receiver_loop(){

  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println("Received: ");
    Serial.println(text);
  }

}

/****************************************************************************************************************************
Method Name: packet_handling()
Input:
Output: none
Description: Method is used for a simple ping trial between two Teensy + nRF24L01 modules
More info: Automatic packet assembly (nRF24L01). The automatic packet assembly assembles the preamble, address, packet control field, payload and CRC
to make a complete packet before it is transmitted. The preamble is automaticly generated based on the address field. The address is fetched from the TX_ADDR
register. The address field can be configured to be 3, 4 or 5 bytes long with the AW register. The payload is fetched from the TX FIFO. The CRC is automaticly
calculated based on the packet content with the polynomials. The number of bytes in the CRC is set by the CRCO bit in the CONFIG register.

*****************************************************************************************************************************/


/*void Wanda::packet_handling(){


}
*/



/****************************************************************************************************************************
Method Name: multi_config_tx()
Input:
Output: none
Description: Method is used for a simple ping trial between two Teensy + nRF24L01 modules
More info: Automatic packet assembly (nRF24L01). The automatic packet assembly assembles the preamble, address, packet control field, payload and CRC
to make a complete packet before it is transmitted. The preamble is automaticly generated based on the address field. The address is fetched from the TX_ADDR
register. The address field can be configured to be 3, 4 or 5 bytes long with the AW register. The payload is fetched from the TX FIFO. The CRC is automaticly
calculated based on the packet content with the polynomials. The number of bytes in the CRC is set by the CRCO bit in the CONFIG register.

*****************************************************************************************************************************/


void Wanda::multi_config_tx(){


  const uint64_t wAddress[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL, 0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL};
  const uint64_t PTXpipe = wAddress[ WHICH_NODE - 1 ];   // Pulls the address from the above array for this node's pipe
  byte counter = 1; //used to count the packets sent
  bool done = false; //used to know when to stop sending packets

  Serial.begin(115200);
  radio.begin();            //Start the nRF24 module
  radio.setPALevel(RF24_PA_LOW);  // "short range setting", Power Amplifier: LOW needed if distance is short
  radio.setChannel(108);          // the higher channels tend to be more "open"
  radio.openReadingPipe(0,PTXpipe);  //open reading or receive pipe
  radio.stopListening(); //go into transmit mode

}







/****************************************************************************************************************************
Method Name: multi_config_rx()
Input:
Output: none
Description: Method is used for a simple ping trial between two Teensy + nRF24L01 modules
More info: Automatic packet assembly (nRF24L01). The automatic packet assembly assembles the preamble, address, packet control field, payload and CRC
to make a complete packet before it is transmitted. The preamble is automaticly generated based on the address field. The address is fetched from the TX_ADDR
register. The address field can be configured to be 3, 4 or 5 bytes long with the AW register. The payload is fetched from the TX FIFO. The CRC is automaticly
calculated based on the packet content with the polynomials. The number of bytes in the CRC is set by the CRCO bit in the CONFIG register.

*****************************************************************************************************************************/

void Wanda::multi_config_rx(){

  const uint64_t rAddress[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL, 0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL };
  Serial.begin(115200);
  radio.begin();  //Start the nRF24 module

  radio.setPALevel(RF24_PA_LOW);  // "short range setting", Power Amplifier: LOW needed if distance is short
  radio.setChannel(108);          // the higher channels tend to be more "open"

  // Open up to six pipes for PRX to receive data
  radio.openReadingPipe(0,rAddress[0]);
  radio.openReadingPipe(1,rAddress[1]);
  radio.openReadingPipe(2,rAddress[2]);
  radio.openReadingPipe(3,rAddress[3]);
  radio.openReadingPipe(4,rAddress[4]);
  radio.openReadingPipe(5,rAddress[5]);

  radio.startListening();                 // Start listening for messages
}
}


/****************************************************************************************************************************
Method Name: multi_loop1_rx()
Input:
Output: none
Description: Method is used for a simple ping trial between two Teensy + nRF24L01 modules
More info: Automatic packet assembly (nRF24L01). The automatic packet assembly assembles the preamble, address, packet control field, payload and CRC
to make a complete packet before it is transmitted. The preamble is automaticly generated based on the address field. The address is fetched from the TX_ADDR
register. The address field can be configured to be 3, 4 or 5 bytes long with the AW register. The payload is fetched from the TX FIFO. The CRC is automaticly
calculated based on the packet content with the polynomials. The number of bytes in the CRC is set by the CRCO bit in the CONFIG register.

*****************************************************************************************************************************/





/****************************************************************************************************************************
Method Name: multi_loop1_tx()
Input:
Output: none
Description: Method is used for a simple ping trial between two Teensy + nRF24L01 modules
More info: Automatic packet assembly (nRF24L01). The automatic packet assembly assembles the preamble, address, packet control field, payload and CRC
to make a complete packet before it is transmitted. The preamble is automaticly generated based on the address field. The address is fetched from the TX_ADDR
register. The address field can be configured to be 3, 4 or 5 bytes long with the AW register. The payload is fetched from the TX FIFO. The CRC is automaticly
calculated based on the packet content with the polynomials. The number of bytes in the CRC is set by the CRCO bit in the CONFIG register.

*****************************************************************************************************************************/
