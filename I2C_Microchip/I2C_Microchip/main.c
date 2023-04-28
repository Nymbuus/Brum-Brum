#include "i2c.h"
#include "serial.h"

#define Slave_Address 0x08 // Slavens adress skiftad ett steg till v�nster.

// Deklarerar variabler.
char yLow;
char yHigh;
uint8_t zLow;
int16_t zHigh;
int16_t xNew;
static int16_t distances[3];
static int count = 0;

int main(void)
{
   serial_init(); // Initierar utskrift till terminal.
   
   I2C_Slave_Init(Slave_Address); // Initierar I2C som slav med slav adress.
   
   serial_print_string("Slave Device");
   serial_print_new_line();
   
   while (1)
   {
      switch(I2C_Slave_Listen())   // Check for SLA+W or SLA+R
      {
         case 0:
         {  
            yLow = I2C_Slave_Receive();     // Tar emot f�rsta data byten
            zLow = yLow;
            
            yHigh = I2C_Slave_Receive();	  // Tar emot andra data byten
            zHigh = ((int16_t)yHigh << 8);  // Skiftar datan 8 bitar till v�nster.
            
            xNew = zHigh + zLow;            // Addrerar ihop de tv� bytev�rdena.
            distances[count] = xNew;        // L�gger in v�rde i arrayen
            count++;
            
            // N�r count �r lika med tre �r arrayen fylld med v�rde till v�nster, center och h�ger.
            // Skriver ut alla v�rden.
            if (count >= 3)
            {
               count = 0;
               serial_print_string("Left: ");
               serial_print_integer(distances[0]);
               serial_print_string("   Center: ");
               serial_print_integer(distances[1]);
               serial_print_string("   Right: ");
               serial_print_integer(distances[2]);
               serial_print_new_line();
               serial_print_new_line();
               serial_print_new_line();
            }               
            
            (void)I2C_Slave_Receive(); // Tar emot stoppbyten och sl�nger den.
                     
            break;
         }
         
         case 1: // Ifall v�rdet fr�n I2C_Listen f�r ett konstigt v�rde kommer switchsatsen hit.
         {
            serial_print_string("\nNot SLA+W (case 1)\n");
            break;
         }
         
         default: // Ifall v�rdet fr�n I2C_Listen f�r ett konstigt v�rde kommer switchsatsen hit.
            serial_print_string("\nNot SLA+W (default)\n");
            break;
       }
    }
}