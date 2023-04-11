#ifndef HEADER_H_
#define HEADER_H_

#include "misc.h"

#define LED1 11 /* PORTB3 / pin 11. */
#define REMOTESTART 12 /* PORTB4 / pin 12. */

#define LED1_ON PORTB |= (1 << LED1)
#define LED1_OFF PORTB &= ~(1 << LED1)


#define REMOTESTART_PRESSED (PINB & (1 << REMOTESTART))




#endif /* HEADER_H_ */