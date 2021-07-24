#include <msp430.h>
#include "stateMachines.h"
#include "buzzer.h"
#include "led.h"


enum notes {Quiet = 0, Continue = 1, Do = 523, Re = 587, Mi = 659, Fa = 698, Sol = 784, La = 880, Si = 988};

// The lower the tempo, the higher the notes are played
#define TEMPO 80;

// Sequence of notes to be played
short sequence[] = {Mi, Mi, Mi, Continue, Mi, Mi, Mi, Continue, Mi, Sol, Do, Re, Mi, Continue, Continue, Continue, Fa, Fa, Fa, Fa, Fa, Mi, Mi, Mi, Mi, Re, Re, Mi, Re, Continue, Sol, Continue};

// Size of sequence array
short size = sizeof(sequence) / sizeof(short);

// Plays the note for TEMPO/250 of a second, beginning at 25/250 of a second
short play_note(short note) {
  static short state = 0;
  short move = 0;
  
  if(state == 0) {
    buzzer_set_period(0);
    greenOn(0);
  }
  if(state == 25) {
    play_hz(note);
    greenOn(1);
  }
  
  state = ++state % TEMPO;
  // If a full state cycle has passed
  if(state == 0) move = 1;

  return move;
}

short play_silence() {
  greenOn(0);
  static short state = 0;
  short move = 0;
  if(state == 0) buzzer_set_period(0);
  state = ++state % TEMPO;
  if(state == 0) move = 1;
  return move;
}

short lengthen() {
  static short state = 0;
  short move = 0;
  state = ++state % TEMPO;
  if(state == 0) move = 1;
  return move;
}

// For state_advance
short super = 0;
