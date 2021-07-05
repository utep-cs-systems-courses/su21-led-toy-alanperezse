#include <msp430.h>
#include "stateMachines.h"
#include "led.h"

char toggle_red()		/* always toggle! */
{
  red_on = !red_on;//Always changes an led */
  return 1;
}

char toggle_green()	/* only toggle green if red is on!  */
{
  green_on = !green_on;
  return 1;			/* always changes an led */
}


void state_advance()		/* alternate between toggling red & green */
{
  static char stateRed = 0;
  static char stateGreen = 0;
  char changed = 0;
  if(++stateRed == 1) {
    toggle_red();
    stateRed = 0;
    changed = 1;
  }
  if(++stateGreen == 2) {
    toggle_green();
    stateGreen = 0;
    changed = 1;
  }
  
  led_changed = changed;
  led_update();
}
