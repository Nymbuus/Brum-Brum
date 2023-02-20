#include <Arduino.h>
#include <Servo.h>

#define SERVO_PIN 9
#define SERVO_POSITION_MIN 45
#define SERVO_POSITION_MAX 135
#define SERVO_POSITION_CENTER 90


Servo servo;
uint8_t current_position;

void servo_turn_left(uint8_t target_position);
void servo_turn_right(uint8_t target_position);
void servo_return(void);
void servo_run(uint8_t target_position);

void setup() 
{
    servo.attach(SERVO_PIN);
    current_position = 90;

    Serial.begin(9600);
    while (!Serial);
}

void loop() 
{
    servo_run(SERVO_POSITION_CENTER);
    delay(2500);

    servo_run(SERVO_POSITION_MAX);
    delay(5000);

    servo_run(SERVO_POSITION_MIN);
    delay(5000);

}

void servo_turn_left(uint8_t target_position)
{
    for (uint8_t i = current_position; i > target_position; i--)
    {
        servo.write(i);
        delay(10);
    }

    current_position = target_position;
    return;
}

void servo_turn_right(uint8_t target_position)
{
    for (uint8_t i = current_position; i < target_position; i++)
    {
        servo.write(i);
        delay(10);
    }

    current_position = target_position;
    return;
}

void servo_return(void)
{
    if (current_position > 90)
    {
        servo_turn_left(90);
    }
    else if (current_position < 90)
    {
        servo_turn_right(90);
    }

    return;
}

void servo_run(uint8_t target_position)
{
    if (target_position < SERVO_POSITION_MIN)
    {
        target_position = SERVO_POSITION_MIN;
    }
    else if (target_position > SERVO_POSITION_MAX)
    {
        target_position = SERVO_POSITION_MAX;
    }

    if (target_position > current_position)
    {
        servo_turn_right(target_position);
    }
    else if (target_position < current_position)
    {
        servo_turn_left(target_position);
    }

    return;
}