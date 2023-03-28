/********************************************************************************
* setup.c:
*********************************************************************************/

/* Include directives */
#include "gpio.h"

/* Static function declarations */
static inline void init_gpio(void);
static inline void init_interrupts(void);
static inline void init_timer0(void);

/* External function definitions */
/********************************************************************************
* setup:
*********************************************************************************/
void setup(void)
{
	init_gpio();
	init_timer0();
	init_interrupts();
	
	return;
}

/* Static function definitions */
/********************************************************************************
* init_gpio:
*********************************************************************************/
static inline void init_gpio(void)
{
	DDRD = (1 << M1A) | (1 << M1B);
	
	return;
}

/********************************************************************************
* init_timer0: Configures Timer0 to Non-inverted Fast PWM Mode with a frequency
*			   of 979 Hz. Duty cycle of M1A is determined by the value of OCR0A,
*			   duty cycle of M1B is determined by OCR0B. Alterations to the
*			   respective duty cycles during operation should be handled in the
*			   corresponding interrupt vector (TIMER0 OVF).
*			   By default the duty cycle is set to 0.
*********************************************************************************/
static inline void init_timer0(void)
{
	TCCR0A = (0b10 << COM0A0) | (0b10 << COM0B0) | (0b11 << WGM00);
	TCCR0B = (0b011 << CS00);
	OCR0A = 0x00;
	OCR0B = 0x00;
	TIMSK0 = (1 << TOIE0);
	
	return;
}

/********************************************************************************
* init_interrupts:
*********************************************************************************/
static inline void init_interrupts(void)
{
	asm("SEI");
	
	return;
}