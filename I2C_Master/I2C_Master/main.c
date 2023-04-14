#include "i2c.h"
#include "serial.h"

#define Slave_Write_Address 0x20
#define Slave_Read_Address  0x21 
#define count				    10   // Hur m�nga tecken som skickas

int main()
{
   serial_init();   // Initierar skrivning till terminalen.
   i2c_init();		  // Initierar I2C.
   char buffer[10]; // Inneh�ller de tecken som ska skrivas ut i terminalen.

   serial_print_string("Master Device");
   serial_print_new_line();
   
   while (1)
   {
      // Denna delen skickar data till slaven.
      serial_print_string("Sending :       ");
      serial_print_new_line();
      
      I2C_Start(Slave_Write_Address); // Startar I2C SLA+W (slaveadress + skrivbit).
      _delay_ms(5);
      
      // Skickar 10 tecken.
      for (uint8_t i = 0; i < count ; i++)
      {
         sprintf(buffer, "%d    ",i); // Skriver v�rdet i som en string till buffer.
         serial_print_string(buffer);
         serial_print_new_line();
         I2C_Write(i);                // Skriver v�rdet i till slave.
         _delay_ms(500);
      }
      
      // denna delen tar emot data fr�n slaven.
      serial_print_string("Receiving :       ");
      serial_print_new_line();
      
      I2C_Repeated_Start(Slave_Read_Address); // Repeterar start fast med att l�sa fr�n slaven.
      _delay_ms(5);
      
      // L�ser 10 tecken.
      for (uint8_t i = 0; i < count; i++)
      {
         // N�r sista tecknet �r l�st skickas en NACK (not acknowlegde)
         // f�r att s�ga till slaven att master inte vill ha mer data.
         if (i < count - 1)
         sprintf(buffer, "%d    ", I2C_Read_Ack());/* Read & Ack of data */
         else
         sprintf(buffer, "%d    ", I2C_Read_Nack());/* Read & Nack to data */
         serial_print_string(buffer);
         serial_print_new_line();
         _delay_ms(500);
      }
      I2C_Stop(); // Stoppar I2C;
   }
}