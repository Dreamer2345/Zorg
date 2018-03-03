#include <Arduboy2.h>
#include "ArduboyBeep.h"
Arduboy2 ard;
Sprites sprites;
BeepPin1 beep;
#include "ENumsThatArentActualyEnums.h"
#include "Game.h"

void setup() {
  ard.begin();
  ard.clear();
  ard.initRandomSeed();
  SetBlock(0,1,5);
  SetBlock(1,1,6);
  ard.println(GetBlock(0,1));
  ard.println(GetBlock(1,1));
  ard.display();
}

void loop() {
  ard.pollButtons();
}
