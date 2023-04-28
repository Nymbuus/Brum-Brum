#include <OPT3101.h>
#include <Arduino.h>
#include <Wire.h>

void OPT_init(); // Initierar OPT3101.
void sensor_get_distances(); // Skaffar alla värden från sensorn.
void write_i2c(int16_t distance); // Skriver alla värden till Mircochip Studio.

OPT3101 sensor;

// Deklarerar och definerar variabler.
int16_t distances[3];
int16_t x = 0x0000;
uint8_t yLow = 0;
uint8_t yHigh = 0;

// Initierar utskrift i terminal, akriverar I2C och OPT3101.
void setup()
{
  Serial.begin(9600);
  Wire.begin();

  OPT_init();
}

// Tar emot distansmått från sensorn.
void loop()
{
  sensor_get_distances();
}

// Initierar OPT3101.
void OPT_init()
{
  sensor.init();
  if (sensor.getLastError())
  {
    Serial.print(F("Failed to initialize OPT3101: error "));
    Serial.println(sensor.getLastError());
    while (1) {}
  }

  sensor.setFrameTiming(256);
  sensor.setChannel(0);
  sensor.setBrightness(OPT3101Brightness::Adaptive);

  sensor.startSample();
}

// Skaffar distansmått från sensorn.
void sensor_get_distances()
{
  if (sensor.isSampleDone())
  {
    sensor.readOutputRegs();

    distances[sensor.channelUsed] = sensor.distanceMillimeters;

      if (sensor.channelUsed == 2)
      {
        for (uint8_t i = 0; i < 3; i++)
        {
          switch (i)
          {
             case 0:
             {
                Serial.print("Left: ");
                break;
             }
             case 1:
             {
                Serial.print("Center: ");
                break;
             }
             case 2:
             {
                Serial.print("Right: ");
                break;
             }
          }
          Serial.print(distances[i]);
          Serial.print(", ");
          
          // Skickar alla distansmått via I2C till Microchip studio.
          write_i2c(distances[i]);
        }

        Serial.println();
      }

    sensor.nextChannel();
    sensor.startSample();
  }
}

// Skickar alla distansmått via I2C till Microchip studio.
void write_i2c(int16_t distance)
{
  yLow = distance;
  yHigh = (uint16_t)distance >> 8;

  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(yLow);          // sends one byte
  Wire.write(yHigh);         // sends one byte
  Wire.endTransmission();    // stop transmitting
}