#pragma once


#define MAXX 20
#define MAXY 20
#define MAXGEN 15
#define CENTERX 63
#define CENTERY 31
#define MEMSIZE ((MAXX/2)*MAXY)
uint8_t MAP[MEMSIZE];

enum class GameState { 
      MainMenu, 
      GameStart,
      Game ,
      Dead ,
};
GameState gameState = GameState::GameStart;

void Switch(uint8_t & x,uint8_t & x1){
  uint8_t o = x;
  x = x1;
  x1 = o;
}

uint16_t GetOffset(uint8_t x,uint8_t y){
  uint16_t ColCheck = ((x/2)+(y*(MAXX/2)));
  if (ColCheck < (MEMSIZE))
    return ColCheck;
  else
    {
    Serial.println(F("Collision:"));
    Serial.println(x);
    Serial.println(y);
    Serial.println(ColCheck-MEMSIZE);
    
    return 0;
    }
}

uint8_t GetBlock(uint8_t x,uint8_t y){
 if (x >= MAXX || y >= MAXY){return 1;}
 uint8_t Block = 0;
 if (x % 2 == 0){
    Block = MAP[GetOffset(x,y)] >> 4;
 } else {
    Block = MAP[GetOffset(x,y)] & 0x0F;
 }
 return Block;
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


uint8_t GetBlockTrans(uint8_t x, uint8_t y) {
  uint8_t Block = 0;
  if ((x < 0) || (y < 0) || (x >= MAXX) || (y >= MAXY)) {
    if (LEVEL == 0)
      Block = 12;
    else
      Block = 13;
    return Block;
  }
  else
  {
    uint8_t p[4];
    uint8_t Block = GetBlock(x,y);
    p[2] = GetBlock(x+1,y);
    p[3] = GetBlock(x-1,y);
    p[1] = GetBlock(x,y+1);
    p[0] = GetBlock(x,y-1);

    if (Block == 0) {if(GetSurround8(x,y,0) <= 5) Block = 11;}
    if (Block == 2) {Block = 6;}
    if (Block == 1){if (LEVEL == 0)
                      Block = 12;
                    else
                      Block = 13;}
  return Block;
  }
}


void SetBlock(uint8_t x,uint8_t y,uint8_t b){
 uint8_t Block = MAP[GetOffset(x,y)];
 uint8_t AddBlock = b;
 if (x % 2 == 0){
    AddBlock = AddBlock << 4;
    Block &= 0x0F;
 } else {
    Block &= 0xF0;
 }
 Block |= AddBlock;
 MAP[GetOffset(x,y)] = Block;
}




