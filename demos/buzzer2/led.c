#include <msp430.h>
#include "led.h"

void led_init() {
  P1DIR |= LEDS;
  greenOn(0); // Initially off
}

void greenOn(int on) {
  if(on) P1OUT |= LED_GREEN;
  else P1OUT &= ~LED_GREEN;
}
