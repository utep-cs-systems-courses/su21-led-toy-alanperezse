#ifndef led_included
#define led_included

#define LED_GREEN BIT6             // P1.6
#define LEDS BIT6

void led_init();
void greenOn(int on);

#endif // included
