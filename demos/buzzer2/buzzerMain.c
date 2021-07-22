#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "led.h"

int main() {
    configureClocks();
    buzzer_init();
    led_init();
    //enableWDTInterrupts();
    or_sr(0x18);          // CPU off, GIE on
}
