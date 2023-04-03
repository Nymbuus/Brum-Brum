/********************************************************************************
* setup.c:
********************************************************************************/

/* Include directives */
#include "global_header.h"

/* Local function declarations */
static inline void init_adc(void);
static inline void init_servo(void);
static inline void init_gpio(void);
static inline void init_interrupts(void);
static inline void init_motor_controller(void);

/* External function definitions */

void setup(void)
{
	init_gpio();
	init_adc();
	init_servo();
	init_motor_controller();
	serial_init(9600);
	init_interrupts();
	
	return;
}

/* Local function definitions */

/********************************************************************************
* init_adc: Performs an AD-conversion to initialize the hardware in order
*			to reduce conversion time of consequent conversions.
********************************************************************************/
static inline void init_adc(void)
{
	(void)adc_read(SENSOR_CENTER_PIN);
	
	return;
}

/********************************************************************************
* init_servo: Configures Timer1 to non-inverting Fast PWM-mode. Outputs a PWM
*			  signal at PORTB1 with a frequency of 50 Hz. The duty cycle of
*			  the PWM-signal is determined by the value stored in OCR1A.
********************************************************************************/
static inline void init_servo(void)
{
	TCCR1A = (0b10 << COM1A0) | (0b10 << WGM10);
	TCCR1B = (0b11 << WGM12) | (0b011 << CS10);
	ICR1 = 5000;
	// The servo motor mounted on the car accepts pulse widths from 1 to 2 ms.
	// A pulse width of 1.0 ms (1.0 ms / 4 us = 250 => OCR1A = 250) results in an angle of 0 degrees.
	// A pulse width of 1.5 ms (1.5 ms / 4 us = 375 => OCR1A = 375) results in an angle of 90 degrees.
	// A pulse width of 2.0 ms (2.0 ms / 4 us = 500 => OCR1A = 500) results in an angle of 180 degrees.
	OCR1A = SERVO_CENTER;
	
	return;
}

/********************************************************************************
* init_gpio: Configures GPIO-pins.
*********************************************************************************/
static inline void init_gpio(void)
{
	DDRB = (1 << SERVO_CONTROL_PIN);
	DDRD = (1 << M1A) | (1 << M1B);
	//PORTB = (1 << PORTD3) | (1 << PORTD2);
	
	return;
}

/********************************************************************************
* init_interrupts: Configures interrupts and enables interrupts globally.
*********************************************************************************/
static inline void init_interrupts(void)
{
	//EICRA = (0b11 << ISC10) | (0b11 << ISC00);
	//EIMSK = (0b11 << INT0);
	
	TIMSK0 = (1 << TOIE0);
	TIMSK1 = (1 << TOIE1);
	asm("SEI");
	
	return;
}

/********************************************************************************
* init_motor_controller: Configures Timer0 to Phase Correct PWM Mode 
*						 with a frequency of 3922 Hz. 
*						 Duty cycle of M1A is determined by the value of OCR0A,
*						 duty cycle of M1B is determined by OCR0B.
*						 By default the duty cycle is set to 0.
*********************************************************************************/
static inline void init_motor_controller(void)
{
	TCCR0A = (0b10 << COM0A0) | (0b10 << COM0B0) | (0b01 << WGM00);
	TCCR0B = (0b010 << CS00);
	OCR0A = 0x00;
	OCR0B = 0x00;
	
	return;
}