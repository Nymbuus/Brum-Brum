#ifndef I2C_H_
#define I2C_H_

#define F_CPU 16000000UL	//CPU klock frekvens

#include <avr/io.h>        // I/O-definitioner för AVR-enheter.
#include <avr/interrupt.h> // Implementering av avbrott på AVR-enheter.
#include <util/delay.h>    // Bibliotek för generering av fördröjning utan timers.
#include <stdint.h>        // Definitioner av heltalsdatatyper.
#include <stdio.h>         // Bibliotek för I/O-implementering i C.
#include <stdlib.h>        // C:s standardbibliotek, behövs här.
#include "serial.h"        // Skrivning till terminal.

/******************************************************************************************
* i2c_init: Initiering av I2C kommunikation.
******************************************************************************************/
void I2C_Slave_Init(uint8_t slave_address)
{
   TWAR = slave_address;		                      // Skriver slavens adress till TWAR så att den känner igen den när den blir kallad på
   TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT); // Aktiverar TWI, nollar interupt-flaggan och gör att slaven kan generera ACK.
}

/******************************************************************************************
* i2c_slave_listen: Lyssnar efter sin egen adress och agerar på vad som tagits emot efter.
******************************************************************************************/
int8_t I2C_Slave_Listen()
{
   while(1)
   {
      uint8_t status;
      while (!(TWCR & (1 << TWINT)));	     // Väntar på att bli adresserad.
      status = TWSR & 0xF8;		           // Läser av statusregistret för att välja vad som ska hända.
      if (status == 0x60 || status == 0x68) // Kollar om SLA+W har tagits emot och returnerar ACK.
      return 0;			                    // Returnerar 0 om ACK har tagits emot.
      if (status == 0xA8 || status == 0xB0) // Kollar om SLA+R har tagits emot och returnerar ACK.
      return 1;			                    // Returnerar 1 om ACK har tagits emot.
      if (status == 0x70 || status == 0x78) // Kollar om generel kallning har tagits emot och returnerar ACK.
      return 2;			                    // Returnerar 2 om ACK har tagits emot.
      else
      continue;			                    // Om inget tagits emot körs loopen om.
   }
}

/******************************************************************************************
* i2c_start: För att börja snacka med Master.
******************************************************************************************/
void i2c_start()
{
   TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA); // TWEN sätts till 1 för att aktviera I2C. TWEA sätts till 1 för att kunna känna igen sin egen adress som är angiven i TWAR och skicka tillbaka ACK till Master.
   while ((TWCR & (1<<TWINT)) == 0);                // Kollar om allt gick bra.
}

/******************************************************************************************
* i2c_stop: Används inte på Slave sidan.
******************************************************************************************/
void i2c_stop(void)
{
   TWCR = (1 << TWINT) | (1 << TWEN); // Stop Conditon. TWINT-flaggan sätts till 0 genom skriva 1 till den. TWEN sätts till 1 för att aktviera I2C. TWSTO skrivs till 1 för att sluta skriva med Slave.
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
* i2c_slave_receive: Tar emot data från master.
******************************************************************************************/
char I2C_Slave_Receive()
{
   uint8_t status;
   TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT); // Aktiverar TWI, nollar interupt-flaggan och gör att master kan generera ACK.
   while (!(TWCR & (1 << TWINT)));	                // Väntar till TWI är klar.
   status = TWSR & 0xF8;		                      // Läser av statusregistret för att välja vad som ska hända.
   if (status == 0x80 || status == 0x90)            // Kollar om datan har tagits emot och returnerar ACK.
   return TWDR;		                               // Returnerar data som tagits emot.
   if (status == 0x88 || status == 0x98)            // Kollar om datan är datan har tagits emot, NACK returnerats och ändrat till ej adresserad slave läge.
   return TWDR;		                               // Returnerar data som tagits emot.
   if (status == 0xA0)		                         // Kollar om stopp eller repetarad start tillstånd tagits emot.
   {
      TWCR |= (1 << TWINT);	                      // Nollar interupt-flaggan.
      return -1;
   }
   else
   return -2;
}

#endif /* I2C_H_ */