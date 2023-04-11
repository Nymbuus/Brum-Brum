#ifndef I2C_H_
#define I2C_H_

#define F_CPU 16000000UL	//--- CPU Clock Frequency

#include <avr/io.h>

/******************************************************************************************
* i2c_init: Initiering av I2C kommunikation.
******************************************************************************************/
void i2c_init()
{
   TWSR = 0x00;		 // Prescaler v�rde satt till 1. TWPS0 = 0, TWPS1 = 0.
   TWBR = 0x72;		 // Baud rate �r ber�knad med denna formel: SCL frekvens = CPU Clock Frequency / (16 + 2 * TWBR * prescaler v�rde).
   TWAR = 0b00000010; // Adressen till Slave bit 7 till 1. bit 0 �r
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
* i2c_write: Skriver data till Slave-enhet.
******************************************************************************************/
void i2c_write(unsigned char data)
{
   TWDR = data;						      // data som ska skrivas till Slave l�ggs i TWDR-registret.
   TWCR = (1 << TWINT) | ( 1<< TWEN);	// St�ller interupt-flaggan till 0 genom att skriva 1 till den. TWEN aktiverar I2C skrivning.
   while ((TWCR & (1 << TWINT)) == 0);	// Kollar om skrivning g�tt bra och TWDR rensas.
}

/******************************************************************************************
* i2c_read: l�ser data fr�n Master-enhet.
******************************************************************************************/
unsigned char i2c_read()
{
   TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);	// St�ller interupt-flaggan till 0 genom att skriva 1 till den. TWEN aktiverar I2C skrivning.
   while ((TWCR & (1 << TWINT)) == 0);	               // Kollar om l�sning g�tt bra och TWDR f�tt all data.
   return TWDR;                                       // Returnerar data som en usigned char.
}

#endif /* I2C_H_ */