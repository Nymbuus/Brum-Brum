#include "i2c.h"

int main(void)
{
   DDRD = 0xFF;                    // Sätter I/O-portar D till output. Används för indiktions-leds att data har skrivits.
   PORTC |= ((1 << 4) | (1 << 5)); // Sätter PORTC4 och PORTC5 till utportar. PORTC4 är ihopkopplad med SDA porten och PORTC5 är ihopkopplad med SCL porten.
   i2c_init();			              // Initierar I2C kommunikation.
   i2c_start();		              // Start för att börja snacka med Master.
   (void)i2c_read();               // Läser av adressen och hårdvara kollar om den stämmer sedan slängs värdet.
   PORTD = i2c_read();          	  // Läser av data och skriver det till PORTD. Detta används för att tända leds och se att skrivningen har skett korrekt.
   
   while(1)
   {
   }
   
   return 0;
}