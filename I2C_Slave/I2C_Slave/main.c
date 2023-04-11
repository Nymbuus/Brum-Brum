#include "i2c.h"

int main(void)
{
   DDRD = 0xFF;                    // S�tter I/O-portar D till output. Anv�nds f�r indiktions-leds att data har skrivits.
   PORTC |= ((1 << 4) | (1 << 5)); // S�tter PORTC4 och PORTC5 till utportar. PORTC4 �r ihopkopplad med SDA porten och PORTC5 �r ihopkopplad med SCL porten.
   i2c_init();			              // Initierar I2C kommunikation.
   i2c_start();		              // Start f�r att b�rja snacka med Master.
   (void)i2c_read();               // L�ser av adressen och h�rdvara kollar om den st�mmer sedan sl�ngs v�rdet.
   PORTD = i2c_read();          	  // L�ser av data och skriver det till PORTD. Detta anv�nds f�r att t�nda leds och se att skrivningen har skett korrekt.
   
   while(1)
   {
   }
   
   return 0;
}