#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switch.h"
#include "buzzer.h"


void update_enabler() {
/* update switch interrupt sense to detect changes from current buttons */
  P2IES |= (P2IN & SWITCHES);	/* if switch up, sense down */
  P2IES &= (P2IN | ~SWITCHES);	/* if switch down, sense up */
}

void
switch_interrupt_handler_1() {
  // update switch interrupt sense to detect changes from current buttons
  P1IES |= (P1IN & SW4);// if switch up, sense down
  P1IES &= (P1IN | ~SW4);// if switch down, sense up

  // up=red, down=green
  if (P1IN & SW4) {
    P1OUT &= ~LED_GREEN;
    buttonDown = 0;
  } else {
    P1OUT |= LED_GREEN;
    buttonDown = 1;
  }
}

switch_interrupt_handler_2() {
  update_enabler();

  // No buttons are being pressed
  if((P2IN & SWITCHES) == SWITCHES) {
    buttonDown = 0;
    play_hz(0);
    P1OUT &= ~LED_GREEN;
    return;
  }

  // If button currently pressed
  if(buttonDown) return;

  // Detect which button is being pressed
  if(!(P2IN & SW1)) { // SW1 is pressed
    buttonDown = 1;
    play_hz(587);
    P1OUT |= LED_GREEN;
  }
  else if(!(P2IN & SW2)) { // SW2 is pressed
    buttonDown = 1;
    P1OUT |= LED_GREEN;
    play_hz(659);
  }
  else if(!(P2IN & SW3)) { // SW2 is pressed
    buttonDown = 1;
    P1OUT |= LED_GREEN;
    play_hz(698);
  }
  else if(!(P2IN & SW4)) { // SW2 is pressed
    buttonDown = 1;
    P1OUT |= LED_GREEN;
    play_hz(784);
  }
}

/* Switch on P1 (S2)*/
void
__interrupt_vec(PORT1_VECTOR) Port_1(){
  if (P1IFG & SW4) { // did a button cause this interrupt?
    P1IFG &= ~SW4; // clear pending sw interrupts
    switch_interrupt_handler_1(); // single handler for all switches
  }
}

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if(P2IFG & SWITCHES) { // did a button cause this interrupt?
    P2IFG &= ~SWITCHES;	// clear pending sw interrupts
    switch_interrupt_handler_2(); // single handler for all switches
  }
}

void __interrupt_vec(WDT_VECTOR) WDT() {
  static int state = 0;
  if(state == 0) P1OUT ^= LED_RED;
  state = ++state % 125;
}
