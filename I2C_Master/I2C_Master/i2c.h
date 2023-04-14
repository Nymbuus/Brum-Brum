#ifndef I2C_H_
#define I2C_H_

#define F_CPU 16000000UL	//CPU klock frekvens

#include <avr/io.h>        // I/O-definitioner f�r AVR-enheter.
#include <avr/interrupt.h> // Implementering av avbrott p� AVR-enheter.
#include <util/delay.h>    // Bibliotek f�r generering av f�rdr�jning utan timers.
#include <stdint.h>        // Definitioner av heltalsdatatyper.
#include <stdio.h>         // Bibliotek f�r I/O-implementering i C.
#include <stdlib.h>        // C:s standardbibliotek, beh�vs h�r.
#include <string.h>        // F�r att kunna anv�nda sprintf().
#include "serial.h"        // Skrivning till terminal.

/******************************************************************************************
* i2c_init: Initiering av I2C kommunikation.
*           Baud rate till i2c �r ber�knad med denna formel:
*           SCL frekvens = CPU Clock Frequency / (16 + 2 * TWBR * Prescaler).
******************************************************************************************/

void i2c_init()
{
   TWSR = 0;  // Prescaler v�rde satt till 1. TWPS0 = 0, TWPS1 = 0.
   TWBR = 72; // Anv�nds f�r att f� r�tt baud rate.
}

/******************************************************************************************
* i2c_start: F�r att starta upp i2c-kommunikationen.
******************************************************************************************/
uint8_t I2C_Start(char write_address)
{
   uint8_t status;		                             
   TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT); // Generar start tillst�nd.
   while (!(TWCR & (1 << TWINT)));	                 // V�ntar tills TWI �r klar.
   status = TWSR & 0xF8;		                       // L�ser av statusregistret f�r att v�lja vad som ska h�nda.
   if (status != 0x08)		                          // Kollar om start tillst�nd har skickats.
   return 0;			                                // Returnerar 0 om det misslyckats.
   TWDR = write_address;		                       // Skriver SLA+W (slaveadress + skrivbit) till TWDR.
   TWCR = (1 << TWEN) | (1 << TWINT);	              // Aktiverar TWI och nollar interupt-flaggan.
   while (!(TWCR & (1 << TWINT)));	                 // V�ntar till TWI �r klar.
   status = TWSR & 0xF8;		                       // L�ser av statusregistret f�r att v�lja vad som ska h�nda.
   if (status == 0x18)		                          // Kollar om SLA+W har skickats och ACK har tagits emot.
   return 1;			                                // Returnerar 1 om ACK har tagits emot.
   if (status == 0x20)		                          // Kollar om SLA+W har skickats och NACK har tagits emot.
   return 2;			                                // Returnerar 2 om NACK har tagits emot.
   else
   return 3;			                                // Returnerar 3 om SLA+W har misslyckats helt.
}

/******************************************************************************************
* i2c_repeated_start: repeterad start tillst�nd f�r att l�sa fr�n Slave.
******************************************************************************************/
uint8_t I2C_Repeated_Start(char read_address)
{
   uint8_t status;
   TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT); // Genererar start tillst�nd.
   while (!(TWCR & (1 << TWINT)));	                 // V�ntar tills TWI �r klar
   status = TWSR & 0xF8;		                       // L�ser av statusregistret f�r att v�lja vad som ska h�nda.
   if (status != 0x10)		                          // Kollar om repeterat start tillst�nd har skickats.
   return 0;			                                // Returnerar 0 om det misslyckats.
   TWDR = read_address;		                          // Skriver SLA+R (slaveadress + l�sbit) till TWDR.
   TWCR = (1 << TWEN) | (1 << TWINT);	              // Aktiverar TWI och nollar interupt-flaggan.
   while (!(TWCR & (1 << TWINT)));	                 // V�ntar till TWI �r klar.
   status = TWSR & 0xF8;		                       // L�ser av statusregistret f�r att v�lja vad som ska h�nda.
   if (status == 0x40)		                          // Kollar om SLA+R har skickats och ACK har tagits emot.
   return 1;			                                // Returnerar 1 om ACK har tagits emot.
   if(status == 0x48)		                          // Kollar om SLA+R har skickats och NACK har tagits emot.
   return 2;			                                // Returnerar 2 om NACK har tagits emot.
   else
   return 3;			                                // Returnerar 3 om SLA+R har misslyckats helt.
}

/******************************************************************************************
* i2c_stop: Stop tillst�nd f�r att sluta snacka med Slave.
******************************************************************************************/
void I2C_Stop()
{
   TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN); // Genererar stopp tillst�nd.
   while (TWCR & (1 << TWSTO));	                    // V�ntar till stopp tillst�ndet �r klart.
}

/******************************************************************************************
* i2c_write: Skriver data till Slave-enhet.
******************************************************************************************/
uint8_t I2C_Write(char data)
{
   uint8_t status;
   TWDR = data;			              // Skriver datan som ska skickas till slaven i TWDR.
   TWCR = (1 << TWEN) | (1 << TWINT); // Aktiverar TWI och nollar interupt-flaggan.
   while (!(TWCR & (1 << TWINT)));	  // V�ntar till TWI �r klar.
   status = TWSR & 0xF8;		        // L�ser av statusregistret f�r att v�lja vad som ska h�nda.
   if (status == 0x28)	              // Kollar om datan har skickats och ACK har tagits emot.
   return 0;			                 // Returnerar 0 om ACK har tagits emot.
   if(status == 0x30)		           // Kollar om datan har skickats och NACK har tagits emot.
   return 1;			                 // Returnerar 1 om ACK har tagits emot.
   else
   return 2;			                 // Returnerar 2 om skickandet av datan misslyckats helt.
}

/******************************************************************************************
* i2c_read_ACK: L�ser av datan p� SDA (Serial DAta) linan och returnerar ACK och s�ger
*               till slaven att skicka mer data.
******************************************************************************************/
char I2C_Read_Ack()
{
   TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA); // Aktiverar TWI, nollar interupt-flaggan och g�r att master kan generera ACK.
   while (!(TWCR & (1 << TWINT)));	                // V�ntar till TWI �r klar.
   return TWDR;	                     		       // Returnerar mottagen data.
}

/******************************************************************************************
* i2c_read_NACK: L�ser av datan p� SDA (Serial DAta) linan och returnerar NACK och s�ger
*                till slaven att inte skicka mer data.
******************************************************************************************/
char I2C_Read_Nack()
{
   TWCR = (1 << TWEN) | (1 << TWINT); // Aktiverar TWI och nollar interupt-flaggan.
   while (!(TWCR & (1 << TWINT)));	  // V�ntar till TWI �r klar.
   return TWDR;		                 // Returnerar mottagen data.
}

#endif /* I2C_H_ */