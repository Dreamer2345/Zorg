

class PlayerClass {
  public:
  uint8_t x;
  uint8_t y;
  bool frame;
  byte d;
  char H;
  byte Keys;
  byte Coins;
  void PlayerMovement();
} playerobj;


void PlayerClass::PlayerMovement() {
  if (ard.justPressed(UP_BUTTON)){
      y-=1;
      d = 0;
    }
  if (ard.justPressed(DOWN_BUTTON)){
      y+=1;
      d = 1;
    }
  if (ard.justPressed(RIGHT_BUTTON)){
      x+=1;
      d = 2;
    }
  if (ard.justPressed(LEFT_BUTTON)){
      x-=1;
      d = 3;
    }   

  if (ard.justPressed(A_BUTTON)){
    LEVEL++;
    gameState = GameState::GameStart;
  }
}
