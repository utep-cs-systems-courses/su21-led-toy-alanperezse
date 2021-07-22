#include <msp430.h>
#include "stateMachines.h"
#include "buzzer.h"


enum notes {Quiet = 0, Continue = 1, Do = 523, Re = 587, Mi = 659, Fa = 698, Sol = 784, La = 880, Si = 988};
#define TEMPO 80;


// Plays the note for TEMPO/250 of a second, beginning at 25/250 of a second
short play_note(short note) {
  static short state = 0;
  short move = 0;
  
  if(state == 0) buzzer_set_period(0);
  if(state == 25) play_hz(note);

  state = ++state % TEMPO;
  // If a full state cycle has passed
  if(state == 0) move = 1;

  return move;
}

short play_silence() {
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

void state_advance() {
  static short super = 0;
  static short sequence[] = {Mi, Mi, Mi, Continue, Mi, Mi, Mi, Continue, Mi, Sol, Do, Re, Mi, Continue, Continue, Continue, Fa, Fa, Fa, Fa, Fa, Mi, Mi, Mi, Mi, Re, Re, Mi, Re, Continue, Sol, Continue};
  short move = 0;
  short size = sizeof(sequence) / sizeof(short);

  //if(sequence[super] == 0) move = lengthen();
  //else move = play_note(sequence[super]);

  switch(sequence[super]) {
  case 0:
    move = play_silence();
    break;
  case 1:
    move = lengthen();
    break;
  default:
    move = play_note(sequence[super]);
    break;
  }

  if(move) super = ++super % size;
}

  
