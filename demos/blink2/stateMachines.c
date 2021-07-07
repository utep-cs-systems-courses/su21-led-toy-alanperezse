#include <msp430.h>
#include "stateMachines.h"
#include "led.h"

void toggle_red() {
  red_on = !red_on;
}

void toggle_green() {
  green_on = !green_on;
}

char state_machine_green() {
  static char state = 0;
  if(state == 5) {
    toggle_green();
    state++;
    return 1;
  }
  else if(state == 7) {
    toggle_green();
    state = 0;
    state++;
    return 1;
  }

  state++;
  
  return 0;
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
