#include "i2c.h"

int main(void)
{
   PORTC |= ((1 << 4) | (1 << 5)); // S�tter PORTC4 och PORTC5 till utportar. PORTC4 �r ihopkopplad med SDA porten och PORTC5 �r ihopkopplad med SCL porten.
   i2c_init();				           // Initierar I2C kommunikation.
   i2c_start();		              // Start condition som skickas till Slave.
   i2c_write(0b00000010);		     // Adressen till Slave bit 7 till 1. bit 0 �r skriv eller l�s bit (Skriva = 0, L�sa = 1).
   i2c_write(0x02);                // Data som skrivs till Slave. I detta fall 2 i decimalform.
   i2c_stop();                     // Stop condition som skickas till Slave.
   
   while(1)
   {
   }
   
   return 0;
}