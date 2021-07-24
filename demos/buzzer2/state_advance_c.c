#include "stateMachines.h"
extern short size;
extern short super;
extern short sequence[];
void state_advance() {
  short move = 0;
  
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
