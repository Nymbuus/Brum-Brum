#include "i2c.h"
#include "serial.h"
#include <string.h> /* Include string header file */

#define Slave_Address 0x20

int main(void)
{
   serial_init();
   
   char buffer[10];
   int8_t count = 0;
   
   I2C_Slave_Init(Slave_Address);
   
   serial_print_string("Slave Device");
   serial_print_new_line();
   
   while (1)
   {
      switch(I2C_Slave_Listen())				/* Check for SLA+W or SLA+R */
      {
         case 0:
         {
            serial_print_string("Receiving:       ");
            serial_print_new_line();
            count = I2C_Slave_Receive();
            do
            {
               sprintf(buffer, "%d    ", count);
               serial_print_string(buffer);
               serial_print_new_line();  
               count = I2C_Slave_Receive();	/* Receive data byte*/
            } while (count != -1);			   /* Receive until STOP/REPEATED START */
            count = 0;
            break;
         }
         case 1:
         {
            int8_t Ack_status;
            serial_print_string("Sending :       ");
            serial_print_new_line();
            do
            {
               Ack_status = I2C_Slave_Transmit(count); /* Send data byte */
               sprintf(buffer, "%d    ",count);
               serial_print_string(buffer);
               serial_print_new_line();
               count++;
            } while (Ack_status == 0);				/* Send until Ack is receive */
            break;
          }
          default:
          break;
       }
    }
}