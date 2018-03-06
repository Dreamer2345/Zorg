#pragma once 

void DisplayEnviroment()
{
  int tileX = playerobj.x;
  int tileY = playerobj.y;
    
  for (int i = -5; i < 5; i++)
  {
    for(int j = -5; j < 5; j++)
    {
      uint8_t block = GetBlockTrans(tileX + i, tileY + j);
      
      int drawX = (i * 8) + CENTERX;
      int drawY = (j * 8) + CENTERY;
      sprites.drawSelfMasked(drawX, drawY, Back, block);
    }
  }
  sprites.drawOverwrite(CENTERX, CENTERY, SpriteTiles, 0);
}


void FillRandom(){
  for(uint16_t i = 0; i<MEMSIZE; i++){
    uint8_t r = ((rand() % 2) << 4)+(rand() % 2);
    MAP[i] = r;
  }
}

void Switch(uint8_t & x,uint8_t & x1){
  uint8_t o = x;
  x = x1;
  x1 = o;
}

bool Between(uint8_t x,uint8_t y,uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2){
  if (x > x1) { Switch(x,x1); }
  if (y > y1) { Switch(y,y1); }
  if ((x <= x2)&&(x2 <= x1)&&(y <= y2)&&(y2 <= y1)){
    return true;
  } else {
    return false;
  }
}

uint8_t GetSurround8(uint8_t x,uint8_t y,uint8_t b){
  uint8_t a = 0;
  if (Between(1,1,MAXX-1,MAXY-1,x,y)){
    if (GetBlock(x+1,y) == b) { a++; }
    if (GetBlock(x-1,y) == b) { a++; }
    if (GetBlock(x,y+1) == b) { a++; }
    if (GetBlock(x,y-1) == b) { a++; }
    if (GetBlock(x+1,y+1) == b) { a++; }
    if (GetBlock(x+1,y-1) == b) { a++; }
    if (GetBlock(x-1,y+1) == b) { a++; }
    if (GetBlock(x-1,y-1) == b) { a++; }
  } else return 4;
  return a;
}

void GenCave(){
  uint8_t Temp[MEMSIZE];
  FillRandom();
  for(uint8_t count = 0; count < MAXGEN; count++) {
    for(uint8_t i = 0; i < MAXX; i++)
      for(uint8_t j = 0; j < MAXY; j++){
        if(((GetBlock(i,j) == 0)&&(GetSurround8(i,j,0) >= 3))||((GetBlock(i,j) == 1)&&(GetSurround8(i,j,0) >= 5)))
          if (i % 2 == 0){
              Temp[GetOffset(i,j)] &= 0x0F;
           } else {
              Temp[GetOffset(i,j)] &= 0xF0;
           }
        else
           if (i % 2 == 0){
              Temp[GetOffset(i,j)] &= 0x0F;
              Temp[GetOffset(i,j)] |= 0x10;
           } else {
              Temp[GetOffset(i,j)] &= 0xF0;
              Temp[GetOffset(i,j)] |= 0x01;
           }
        
    }
    for(uint16_t i = 0; i<MEMSIZE; i++){ MAP[i] = Temp[i]; }
  }
}






void gen(uint8_t Type){
  switch(Type){
    case 0: GenCave(); break;
  }
  gameState = GameState::Game;
}


void Update(){
  DisplayEnviroment();
  playerobj.PlayerMovement();
}


