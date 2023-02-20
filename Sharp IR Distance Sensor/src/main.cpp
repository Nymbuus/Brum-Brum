#include <Arduino.h>
#include <SharpIR.h>

#define SENSOR_LEFT_PIN A1
#define SENSOR_RIGHT_PIN A0

SharpIR sensor_left(SharpIR::GP2Y0A21YK0F, SENSOR_LEFT_PIN);
SharpIR sensor_right(SharpIR::GP2Y0A21YK0F, SENSOR_RIGHT_PIN);

enum SENSOR
{
    SENSOR_LEFT = 0,
    SENSOR_RIGHT = 1
};

static uint8_t distance_readings[2];

void sensor_read(void);
void display_readings(void);

void setup()
{
    Serial.begin(9600);
    while (!Serial);

    distance_readings[SENSOR_LEFT] = 0;
    distance_readings[SENSOR_RIGHT] = 0;
}

void loop() 
{
    sensor_read();
    display_readings();
    delay(1000);
}

void sensor_read(void)
{
    distance_readings[SENSOR_LEFT] = sensor_left.getDistance();
    delay(5);
    distance_readings[SENSOR_RIGHT] = sensor_right.getDistance();
    delay(5);

    return;
}

void display_readings(void)
{
    Serial.print("Left: ");
    Serial.print(distance_readings[SENSOR_LEFT]);
    Serial.print("\tRight: ");
    Serial.println(distance_readings[SENSOR_RIGHT]);

    return;
}