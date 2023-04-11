#ifndef I2C_H_
#define I2C_H_

#define F_CPU 16000000UL	//--- CPU Clock Frequency

#include <avr/io.h>

/******************************************************************************************
* i2c_init: Initiering av I2C kommunikation.
******************************************************************************************/
void i2c_init()
{
   TWSR = 0x00;		 // Prescaler värde satt till 1. TWPS0 = 0, TWPS1 = 0.
   TWBR = 0x72;		 // Baud rate är beräknad med denna formel: SCL frekvens = CPU Clock Frequency / (16 + 2 * TWBR * prescaler värde).
   TWAR = 0b00000010; // Adressen till Slave bit 7 till 1. bit 0 är
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
* i2c_write: Skriver data till Slave-enhet.
******************************************************************************************/
void i2c_write(unsigned char data)
{
   TWDR = data;						      // data som ska skrivas till Slave läggs i TWDR-registret.
   TWCR = (1 << TWINT) | ( 1<< TWEN);	// Ställer interupt-flaggan till 0 genom att skriva 1 till den. TWEN aktiverar I2C skrivning.
   while ((TWCR & (1 << TWINT)) == 0);	// Kollar om skrivning gått bra och TWDR rensas.
}

/******************************************************************************************
* i2c_read: läser data från Master-enhet.
******************************************************************************************/
unsigned char i2c_read()
{
   TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);	// Ställer interupt-flaggan till 0 genom att skriva 1 till den. TWEN aktiverar I2C skrivning.
   while ((TWCR & (1 << TWINT)) == 0);	               // Kollar om läsning gått bra och TWDR fått all data.
   return TWDR;                                       // Returnerar data som en usigned char.
}

#endif /* I2C_H_ */