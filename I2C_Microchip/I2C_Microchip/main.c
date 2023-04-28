#include "i2c.h"
#include "serial.h"
#include <string.h> /* Include string header file */

#define Slave_Address 0x08

char yLow;
char yHigh;
uint8_t zLow;
int16_t zHigh;
int16_t xNew;
uint8_t while_check;

int main(void)
{
   serial_init();
   
   I2C_Slave_Init(Slave_Address);
   
   serial_print_string("Slave Device");
   serial_print_new_line();
   
   while (1)
   {
      switch(I2C_Slave_Listen())				/* Check for SLA+W or SLA+R */
      {
         case 0:
         {  
            do 
            {
               yLow = I2C_Slave_Receive();
               zLow = yLow;
            
               yHigh = I2C_Slave_Receive();	/* Receive data byte*/
               zHigh = ((int16_t)yHigh << 8);
            
               xNew = zHigh + zLow;
            
               serial_print_string("Receiving:   ");
               serial_print_string("zLow: ");
               serial_print_integer(zLow);
               serial_print_string("   zHigh: ");
               serial_print_integer(zHigh);
               serial_print_string("   sum: ");
               serial_print_integer(zHigh + zLow);
               serial_print_new_line();
               serial_print_new_line();
               serial_print_new_line();
               
               while_check = I2C_Slave_Receive();
            } while (while_check != 9);    
                     
            break;
         }
         case 1:
         {
            serial_print_string("\nNot SLA+W (case 1)\n");
            break;
         }
            default:
            serial_print_string("\nNot SLA+W (default)\n");
            break;
       }
    }
}