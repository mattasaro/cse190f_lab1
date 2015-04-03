/*
  ATmega128RFA1 Dev Board Basic Chat
  by: Jim Lindblom
      SparkFun Electronics
  date: July 3, 2012
  License: Beerware. Feel free to use, reuse, and modify this code
  as you please. If you find it useful, you can buy me a beer.

  This code sets up the ATmega128RFA1's wireless transciever in
  the most basic way possible to serve as a serial gateway.
  Serial into the ATmega128RFA1's UART0 will go out the RF radio.
  Data into the RF radio will go out the MCU's UART0.
*/

#include "RadioFunctions.h"

  extern unsigned long totalTime;
  bool done;
  int bytesRead;

void setup()
{
  Serial.begin(115200);  // Start up serial
  Serial1.begin(9600);
  rfBegin(12);  // Initialize ATmega128RFA1 radio on channel 11 (can be 11-26)
  
  // Send a message to other RF boards on this channel
  rfPrint("ATmega128RFA1 Dev Board Online!\r\n");
}



void loop()
{
//  if (Serial.available())  // If serial comes in...
//  {
//    rfWrite(Serial.read()); // ...send it out the radio.
//  }
  if (rfAvailable())  // If data receievd on radio...
  {
    bytesRead++;
    char byteRead = rfRead();
    //Serial.print(byteRead);  // ... send it out serial.
    if (byteRead == 'b') done = true;
  }
  
  if (done){
      Serial.print("\r\nBandwidth: ");
     Serial.print((1.0 * bytesRead * 8 / 1024) / (1.0 * totalTime / 1000));
     Serial.print(" kbps");
     
      Serial.print("\r\nError Rate: ");
     Serial.print( 1.0 * (128 - bytesRead) / 128 );
      done = false;
      bytesRead = 0;
      totalTime = 0;
   }

}
