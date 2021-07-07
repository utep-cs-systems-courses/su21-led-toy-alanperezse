#include <msp430.h>
#include "stateMachines.h"
#include "led.h"

void toggle_red() {
  red_on = !red_on;
}

void toggle_green() {
  green_on = !green_on;
}

char dim_green_automaton() {
  static char state = 0;
  if(state == 2) {
    toggle_green();
    state++;
    return 1;
  }

  if(state == 5) {
    toggle_green();
    state = 0;
    return 1;
  }

  return 0;
}

void state_advance() {
  static char stateGreen = 1; // 1-starting counter
  char changed = 0;

  // Start of state ON
  if(stateGreen == 1) changed = green_on = 1;

  // State DIM
  else if(41 <= stateGreen && stateGreen <= 80) changed = dim_green_automaton;

  // Start of state OFF
  else if(stateGreen == 81) {
    green_on = 0;
    changed = 1;
  }

  // End of state OFF
  else if(stateGreen >= 120) stateGreen = 0; // set state for next iteration

  
  stateGreen++;
  led_changed = changed;
  led_update();
}
