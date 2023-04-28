// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI Peripheral device
// Refer to the "Wire Peripheral Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

#include <Arduino.h>
#include <Wire.h>

void setup()
{
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
}

int16_t x = 0x7FFF;
uint8_t yLow = x;
uint8_t yHigh = (uint16_t)x >> 8;

char zLow = yLow;
char zHigh = yHigh;

void loop()
{
  Serial.print("yLow: ");
  Serial.print(yLow);
  Serial.print("   yHigh: ");
  Serial.println(yHigh);
  Serial.print("\n");

  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(yLow);        // sends five bytes
  Wire.write(yHigh);              // sends one byte
  Wire.endTransmission();    // stop transmitting

  Serial.print("yLow: ");
  Serial.print(yLow);
  Serial.print("   yHigh: ");
  Serial.println(yHigh);
  Serial.print("\n");  

  delay(500);
}