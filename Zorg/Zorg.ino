#include <Arduboy2.h>
//#include "ArduboyBeep.h"
Arduboy2 ard;
Sprites sprites;
uint8_t LEVEL = 0;
//BeepPin1 beep;
#include "ENumsThatArentActualyEnums.h"
#include "Player.h"
#include "Bitmaps.h"
#include "Game.h"

void setup() {
  ard.begin();
  ard.clear();
  ard.initRandomSeed();
  ard.setFrameRate(30);
}

void loop() {
  if(!ard.nextFrame())
    return;

  ard.pollButtons();
  ard.clear();

  switch(gameState)
  {
    case GameState::GameStart: gen(0); break;
    case GameState::Game: Update(); break;
  }
  ard.display();
}
