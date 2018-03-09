#pragma once

#include "Direction.h"

class Player {
public:
  uint8_t x;
  uint8_t y;
  Direction direction;
  char H;
  byte Keys;
  byte Coins;
};
