#include <SPI.h>
#include <RH_RF95.h>
 
// Singleton instance of the radio driver
RH_RF95 rf95;

 
void setup() 
{
 
//  pinMode(led, OUTPUT);     
  Serial.begin(9600);
  while (!Serial) ; // Wait for serial port to be available
  if (!rf95.init()) {
        Serial.println("init failed from server");  

  }
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
 rf95.setSpreadingFactor(7);
 rf95.setCodingRate4(5);
 rf95.setTxPower(20, false);
 rf95.setSignalBandwidth(125000);
}
 
void loop()
{
  if (rf95.available())
  {
    // Should be a message for us now   
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf95.recv(buf, &len))
    {
//      digitalWrite(led, HIGH);
//      RH_RF95::printBuffer("request: ", buf, len);
//      Serial.print("got request: ");
//      Serial.println((char*)buf);
//      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);
      
      // Send a reply
      uint8_t data[] = "And hello back to you";
      rf95.send(data, sizeof(data));
      rf95.waitPacketSent();
//      Serial.println("Sent a reply");
//       digitalWrite(led, LOW);
    }
    else
    {
      Serial.println("recv failed");
    }
  }
}
 
