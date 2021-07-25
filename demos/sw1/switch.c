#include <msp430.h>
#include "switch.h"

void switch_init() {    

  P2REN |= SWITCHES;		// enables resistors for switches 
  P2IE |= SWITCHES;		// enable interrupts from switches
  P2OUT |= SWITCHES;		// pull-ups for switches 
  P2DIR &= ~SWITCHES;		// set switches' bits for input

  P1REN |= SW4;		/* enables resistors for switches */
  P1IE |= SW4;		/* enable interrupts from switches */
  P1OUT |= SW4;		/* pull-ups for switches */
  P1DIR &= ~SW4;		/* set switches' bits for input */
}
