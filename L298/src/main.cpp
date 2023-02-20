/* Include directives */
#include <Arduino.h>
#include <Wire.h>

/* Macro defenitions */
#define ENA 9
#define IN1 7
#define IN2 8
#define SW1 2
#define STATUS_LED 6

/* Enumerations */
enum MOTOR_STATE
{
    MOTOR_STATE_OFF = 0,
    MOTOR_STATE_FORWARD = 1,
    MOTOR_STATE_REVERSE = 2
};

/* Function declarations */
void motor_run(uint8_t speed);
void motor_accelerate(uint8_t target_speed);
void motor_decelerate(uint8_t target_speed);
void motor_switch_state(enum MOTOR_STATE target_state);
void ISR_SW1(void);

/* Declaration of variables with global scope. */
static uint8_t current_speed;
static enum MOTOR_STATE current_state;
static bool motor_enable, STATUS_LED_enable;

/****************************************************************************************************
 * setup: 
 ****************************************************************************************************/
void setup() 
{
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(SW1, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(SW1), ISR_SW1, RISING);
    pinMode(STATUS_LED, OUTPUT);

    current_speed = 0;
    current_state = MOTOR_STATE_OFF;
    motor_enable = false;
    STATUS_LED_enable = false;

    Serial.begin(9600);
    while (!Serial);
}

/****************************************************************************************************
 * loop: 
 ****************************************************************************************************/
void loop() 
{
    while (motor_enable)
    {   
        motor_switch_state(MOTOR_STATE_FORWARD);
        motor_run(25);
        delay(5000);

        motor_run(50);
        delay(5000);

        motor_run(75);
        delay(5000);

        motor_run(100);
        delay(5000);

        motor_run(0);
        motor_switch_state(MOTOR_STATE_OFF);
        delay(5000);
    }
}

/* Function definitions */

/****************************************************************************************************
 * motor_run: 
 ****************************************************************************************************/
void motor_run(uint8_t speed)
{
    if (speed > 100 || speed < 0 || speed == current_speed) return;
    
    if (speed > current_speed)
    {
        motor_accelerate(speed);
    }
    else
    {
        motor_decelerate(speed);
    }

    return;
}
/****************************************************************************************************
 * motor_accelerate: 
 ****************************************************************************************************/
void motor_accelerate(uint8_t target_speed)
{
    uint8_t current_pwm_value = (uint8_t)map(current_speed, 0, 100, 0, 255);
    uint8_t target_pwm_value = (uint8_t)map(target_speed, 0, 100, 0, 255);

    for (uint8_t i = current_pwm_value; i < target_pwm_value; i++)
    {
        analogWrite(ENA, i);
        delay(10);
    }

    current_speed = target_speed;
    return;
}

/****************************************************************************************************
 * motor_decelerate: 
 ****************************************************************************************************/
void motor_decelerate(uint8_t target_speed)
{
    uint8_t current_pwm_value = (uint8_t)map(current_speed, 0, 100, 0, 255);
    uint8_t target_pwm_value = (uint8_t)map(target_speed, 0, 100, 0, 255);

    for (uint8_t i = current_pwm_value; i > target_pwm_value; i--)
    {
        analogWrite(ENA, i);
        delay(10);
    }

    current_speed = target_speed;
    return;
}

/****************************************************************************************************
 * motor_switch_state:  
 ****************************************************************************************************/
void motor_switch_state(enum MOTOR_STATE target_state)
{
    if (current_state == target_state) return;

    switch (target_state)
    {
        case MOTOR_STATE_OFF:
        {
            motor_decelerate(0);
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, LOW);
            
            break;
        }
        case MOTOR_STATE_FORWARD:
        {
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);

            break;
        }
        case MOTOR_STATE_REVERSE:
        {
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, HIGH);

            break;
        }
        default:
        {
            break;
        }
    }

    current_state = target_state;
    return;
}

/****************************************************************************************************
 * ISR_SW1: 
 ****************************************************************************************************/
void ISR_SW1(void)
{
    motor_enable = !motor_enable;
    STATUS_LED_enable = !STATUS_LED_enable;

    if (STATUS_LED_enable)
    {
        digitalWrite(STATUS_LED, HIGH);
    }
    else if (!STATUS_LED_enable)
    {
        digitalWrite(STATUS_LED, LOW);
    }

    return;
}