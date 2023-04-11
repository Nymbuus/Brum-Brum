#include "header.h"


int main(void)
{
	DDRB  = (1 << LED1);
	PORTB = (1 << REMOTESTART);
	
	while (1)
	{
		if (REMOTESTART_PRESSED)
		{
			LED1_ON;
		}
		else
		{
			LED1_OFF;
		}
	}
}

