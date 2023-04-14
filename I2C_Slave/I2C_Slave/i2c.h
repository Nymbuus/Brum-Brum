#ifndef I2C_H_
#define I2C_H_

#define F_CPU 16000000UL	//CPU klock frekvens

#include <avr/io.h>        // I/O-definitioner f�r AVR-enheter.
#include <avr/interrupt.h> // Implementering av avbrott p� AVR-enheter.
#include <util/delay.h>    // Bibliotek f�r generering av f�rdr�jning utan timers.
#include <stdint.h>        // Definitioner av heltalsdatatyper.
#include <stdio.h>         // Bibliotek f�r I/O-implementering i C.
#include <stdlib.h>        // C:s standardbibliotek, beh�vs h�r.
#include "serial.h"        // Skrivning till terminal.

/******************************************************************************************
* i2c_init: Initiering av I2C kommunikation.
******************************************************************************************/
void I2C_Slave_Init(uint8_t slave_address)
{
   TWAR = slave_address;		                      // Skriver slavens adress till TWAR s� att den k�nner igen den n�r den blir kallad p�
   TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT); // Aktiverar TWI, nollar interupt-flaggan och g�r att slaven kan generera ACK.
}

/******************************************************************************************
* i2c_slave_listen: Lyssnar efter sin egen adress och agerar p� vad som tagits emot efter.
******************************************************************************************/
int8_t I2C_Slave_Listen()
{
   while(1)
   {
      uint8_t status;
      while (!(TWCR & (1 << TWINT)));	     // V�ntar p� att bli adresserad.
      status = TWSR & 0xF8;		           // L�ser av statusregistret f�r att v�lja vad som ska h�nda.
      if (status == 0x60 || status == 0x68) // Kollar om SLA+W har tagits emot och returnerar ACK.
      return 0;			                    // Returnerar 0 om ACK har tagits emot.
      if (status == 0xA8 || status == 0xB0) // Kollar om SLA+R har tagits emot och returnerar ACK.
      return 1;			                    // Returnerar 1 om ACK har tagits emot.
      if (status == 0x70 || status == 0x78) // Kollar om generel kallning har tagits emot och returnerar ACK.
      return 2;			                    // Returnerar 2 om ACK har tagits emot.
      else
      continue;			                    // Om inget tagits emot k�rs loopen om.
   }
}

/******************************************************************************************
* i2c_start: F�r att b�rja snacka med Master.
******************************************************************************************/
void i2c_start()
{
   TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA); // TWEN s�tts till 1 f�r att aktviera I2C. TWEA s�tts till 1 f�r att kunna k�nna igen sin egen adress som �r angiven i TWAR och skicka tillbaka ACK till Master.
   while ((TWCR & (1<<TWINT)) == 0);                // Kollar om allt gick bra.
}

/******************************************************************************************
* i2c_stop: Anv�nds inte p� Slave sidan.
******************************************************************************************/
void i2c_stop(void)
{
   TWCR = (1 << TWINT) | (1 << TWEN); // Stop Conditon. TWINT-flaggan s�tts till 0 genom skriva 1 till den. TWEN s�tts till 1 f�r att aktviera I2C. TWSTO skrivs till 1 f�r att sluta skriva med Slave.
}

/******************************************************************************************
* i2c_slave_transmit: Skrickar data till master.
******************************************************************************************/
int8_t I2C_Slave_Transmit(char data)
{
   uint8_t status;
   TWDR = data;			                            /* Write data to TWDR to be transmitted */
   TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA); /* Enable TWI & clear interrupt flag */
   while (!(TWCR & (1 << TWINT)));	                /* Wait until TWI finish its current job */
   status = TWSR & 0xF8;		                      /* Read TWI status register */
   if (status == 0xA0)		                         /* Check for STOP/REPEATED START received */
   {
      TWCR |= (1 << TWINT);	                      /* Clear interrupt flag & return -1 */
      return -1;
   }
   if (status == 0xB8)		                         /* Check for data transmitted &ack received */
   return 0;			                               /* If yes then return 0 */
   if (status == 0xC0)		                         /* Check for data transmitted &nack received */
   {
      TWCR |= (1 << TWINT);	                      /* Clear interrupt flag & return -2 */
      return -2;
   }
   if (status == 0xC8)		                         /* Last byte transmitted with ack received */
   return -3;			                               /* If yes then return -3 */
   else			                                     /* else return -4 */
   return -4;
}

/******************************************************************************************
* i2c_slave_receive: Tar emot data fr�n master.
******************************************************************************************/
char I2C_Slave_Receive()
{
   uint8_t status;
   TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT); // Aktiverar TWI, nollar interupt-flaggan och g�r att master kan generera ACK.
   while (!(TWCR & (1 << TWINT)));	                // V�ntar till TWI �r klar.
   status = TWSR & 0xF8;		                      // L�ser av statusregistret f�r att v�lja vad som ska h�nda.
   if (status == 0x80 || status == 0x90)            // Kollar om datan har tagits emot och returnerar ACK.
   return TWDR;		                               // Returnerar data som tagits emot.
   if (status == 0x88 || status == 0x98)            // Kollar om datan �r datan har tagits emot, NACK returnerats och �ndrat till ej adresserad slave l�ge.
   return TWDR;		                               // Returnerar data som tagits emot.
   if (status == 0xA0)		                         // Kollar om stopp eller repetarad start tillst�nd tagits emot.
   {
      TWCR |= (1 << TWINT);	                      // Nollar interupt-flaggan.
      return -1;
   }
   else
   return -2;
}

#endif /* I2C_H_ */