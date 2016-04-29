#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "arduinoLoRa.h"
#include <SPI.h>
#include <Wire.h>
#include <SeeedOLED.h>
/*
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 7, TXPin = 8;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
// Cooking API libraries
#include <arduinoUtils.h>

int e;
unsigned int i=0;
char *message;
char message1 [] = "i,45.7037,13.7201"; //lenght=mess+1
float latt, lngg;
int randNumber;

//These constants are used for reading the battery voltage
#define ADC_AREF 3.3
#define BATVOLTPIN A6
#define BATVOLT_R1 4.7
#define BATVOLT_R2 10

void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);

  Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();
  // Print a start message
  Serial.println(F("SX1272 module and Arduino: send packets with ACK"));
  
  // Power ON the module
  e = sx1272.ON();
  Serial.print(F("Setting power ON: state "));
  Serial.println(e, DEC);
  
  // Set transmission mode and print the result
  e |= sx1272.setMode(4);
  Serial.print(F("Setting Mode: state "));
  Serial.println(e, DEC);
  
  // Set header
  e |= sx1272.setHeaderON();
  Serial.print(F("Setting Header ON: state "));
  Serial.println(e, DEC);
  
  // Select frequency channel
  e |= sx1272.setChannel(CH_10_868);
  Serial.print(F("Setting Channel: state "));
  Serial.println(e, DEC);
  
  // Set CRC
  e |= sx1272.setCRC_ON();
  Serial.print(F("Setting CRC ON: state "));
  Serial.println(e, DEC);
  
  // Select output power (Max, High or Low)
  e |= sx1272.setPower('M');
  Serial.print(F("Setting Power: state "));
  Serial.println(e, DEC);
  
  // Set the node address and print the result
  e |= sx1272.setNodeAddress(3);
  Serial.print(F("Setting node address: state "));
  Serial.println(e, DEC);
  
  // Print a success message
  if (e == 0)
    Serial.println(F("SX1272 successfully configured"));
  else
    Serial.println(F("SX1272 initialization failed"));

   //Message
   Serial.println("Sequence latitude longitude identifier");
   randomSeed(analogRead(0));
   randNumber = random(999);
   //Serial.println("Sequence, latitude, longitude, identifier");

   //Setup Oled Display
   setupOled();
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read())){
      displayInfo();
      char buffer [50];
      sprintf (buffer, "%i", i);
      message = &buffer[0];
      latt= gps.location.lat();
      lngg= gps.location.lng();
      String mess = String(i);
      mess += ",";
      mess += String(latt,4);
      mess += ",";
      mess += String(lngg,4);
      mess += ",";
      mess += String(randNumber);
      //Serial.println(mess);

      mess.toCharArray(buffer,sizeof(buffer));
      Serial.println(buffer);
//      sx1272.getPayloadLength(); // Get Maximum Payload Bytes
      e = sx1272.sendPacketTimeoutACK(8,buffer);
      Serial.print(F("Packet sent, state "));
      Serial.println(e, DEC);
      if ( e == 0 )
        {
        //Serial.print(F("Packet number= "));
        //Serial.println(i); 
      //i=i+1;
      }
      i=i+1;
      oleddata(i,e,randNumber, latt, lngg);
 }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}


 void oleddata(unsigned int seq, int resp, int id, float lattt, float lnggg)
 {
//  DateTime now = rtc.now(); //get the current date-time    
  
  SeeedOled.init();                  //initialize SEEED OLED display
  SeeedOled.clearDisplay();          //clear the screen and set start position to top left corner
  SeeedOled.setTextXY(0,0);          //Set the cursor to Xth Page, Yth Column
  SeeedOled.putString("Id= ");
  SeeedOled.putNumber(id);
  SeeedOled.setTextXY(1,0);          //Set the cursor to Xth Page, Yth Column
  SeeedOled.putString("Sequence= ");
  SeeedOled.putNumber(seq);
  SeeedOled.setTextXY(3,0);          //Set the cursor to Xth Page, Yth Column  
  SeeedOled.putString("Status= ");
  if ( e == 0 ){ SeeedOled.putString("ACK OK");}
  else if (e == 3) {SeeedOled.putString("ACK bad");}
  else if (e == 1) {SeeedOled.putString("Error");}
  else  {SeeedOled.putString("Error");}
  SeeedOled.setTextXY(5,0);          //Set the cursor to Xth Page, Yth Column
  SeeedOled.putString("Lat=");
  SeeedOled.putFloat((latt),4);
  SeeedOled.setTextXY(6,0);          //Set the cursor to Xth Page, Yth Column
  SeeedOled.putString("Lng= ");
  SeeedOled.putFloat((lngg),4);
  //SeeedOled.setTextXY(6,0);          //Set the cursor to Xth Page, Yth Column
  int mv = getRealBatteryVoltage() * 1000.0;
  SeeedOled.setTextXY(7,0);          //Set the cursor to Xth Page, Yth Column
  SeeedOled.putString("Battery=");
  SeeedOled.putNumber(mv);
  SeeedOled.putString("mV");
 }
  
void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(),4);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 4);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}

void setupOled()
{
  SeeedOled.clearDisplay();          //clear the screen and set start position to top left corner
  SeeedOled.setNormalDisplay();      //Set display to normal mode (i.e non-inverse mode)
  SeeedOled.setPageMode();           //Set addressing mode to Page Mode
  SeeedOled.setTextXY(0,5);          //Set the cursor to Xth Page, Yth Column  
  SeeedOled.putString("LoRa Test"); //Print the String
  delay(1000);
 }
 float getRealBatteryVoltage()
{
  uint16_t batteryVoltage = analogRead(BATVOLTPIN);
  return (ADC_AREF / 1023.0) * (BATVOLT_R1 + BATVOLT_R2) / BATVOLT_R2 * batteryVoltage;
}
