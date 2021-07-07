#include <msp430.h>
#include "stateMachines.h"
#include "led.h"

void toggle_red() {
  red_on = !red_on;
}

void toggle_green() {
  green_on = !green_on;
}

char state_machine_green_dim() {
  static char state = 1;
  char rtn = 1;
  
  if(state == 3) {
    green_on = 0;
    rtn = 1;
  } else if(state >= 8) {
    green_on = 1;
    state = 0;
    rtn = 1;
  }

  state++;
  return rtn;
}

char state_machine_green() {
  static char superState = 0; // For seconds
  static char state = 0; // For 1/250 seconds
  char rtn = 0;

  // if in last state of the last super state, set the variables for the beginning of the next iteration
  if(superState == 2 && state == 249) {
    superState = 0;
    state = 0;
    return rtn;
  }

  // Beginning of new superstate
  if(state == 250) {
    superState++;
    state = 0;
  }
  
  // For ON
  if(superState == 0) {
    if(state == 0) { // Beginning of state
      green_on = 1;
      rtn = 1;
    }
  }
  // For Dim
  else if(superState == 1) {
    rtn = state_machine_green_dim();
  }
  // For off
  else if(superState == 2) {
    if(state == 0) { // Beginning of state
      green_on = 0;
      rtn = 1;
    }
  }

  state++;
  return rtn;
}

char state_machine_red() {
  red_on = 1;
  return 1;
}


void state_advance() {
  char changed = 0;
  changed = state_machine_green() || state_machine_red();
  
  led_changed = changed;
  led_update();
}
