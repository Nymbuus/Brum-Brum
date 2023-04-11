#ifndef I2C_H_
#define I2C_H_

#define F_CPU 16000000UL	// CPU Clock Frequency

#include <avr/io.h>

/******************************************************************************************
* i2c_init: Initiering av I2C kommunikation.
******************************************************************************************/

void i2c_init()
{
   TWSR = 0x00; // Prescaler värde satt till 1. TWPS0 = 0, TWPS1 = 0.
   TWBR = 0x72; // Baud rate är beräknad med denna formel: SCL frekvens = CPU Clock Frequency / (16 + 2 * TWBR * prescaler värde).
}

/******************************************************************************************
* i2c_start: Start condition för att snacka med Slave.
******************************************************************************************/
void i2c_start(void)
{
   TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA); // Start Conditon. TWINT-flaggan sätts till 0 genom skriva 1 till den. TWEN sätts till 1 för att aktviera I2C. TWSTA skrivs till 1 för att generera ett start condition.
   while ((TWCR & (1<<TWINT)) == 0);			        // Kollar om start condition gick bra.
}

/******************************************************************************************
* i2c_stop: Stop condition för att sluta snacka med Slave.
******************************************************************************************/
void i2c_stop(void)
{
   TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO); // Stop Conditon. TWINT-flaggan sätts till 0 genom skriva 1 till den. TWEN sätts till 1 för att aktviera I2C. TWSTO skrivs till 1 för att sluta skriva med Slave.
}

/******************************************************************************************
* i2c_write: Skriver data till Slave-enhet.
******************************************************************************************/
void i2c_write(unsigned char data)
{
   TWDR = data;						      // data som ska skrivas till Slave läggs i TWDR-registret.
   TWCR = (1 << TWINT) | ( 1<< TWEN);	// Ställer interupt-flaggan till 0 genom att skriva 1 till den. TWEN aktiverar I2C skrivning.
   while ((TWCR & (1 << TWINT)) == 0);	// Kollar om skrivning gått bra och TWDR rensas.
}

/******************************************************************************************
* i2c_read: läser data från Slave-enhet.
******************************************************************************************/
unsigned char i2c_read()
{
   TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA); // Ställer interupt-flaggan till 0 genom att skriva 1 till den. TWEN aktiverar I2C skrivning.
   while ((TWCR & (1 << TWINT)) == 0);	             // Kollar om läsning gått bra och TWDR fått all data.
   return TWDR;                                     // Returnerar data som en usigned char.
}

#endif /* I2C_H_ */