#pragma once


#define MAXX 20
#define MAXY 20

uint8_t MAP[MAXX*MAXY];

enum class GameState { 
      MainMenu, 
      GameStart,
      NewLevel, 
      Game ,
      Dead ,
};

uint16_t GetOffset(uint8_t x,uint8_t y){
  return (x+(y*MAXX))/2;
}

uint8_t GetBlock(uint8_t x,uint8_t y){
 uint8_t Block = 0;
 if (x % 2 == 0){
    Block = MAP[GetOffset(x,y)] >> 4;
 } else {
    Block = MAP[GetOffset(x,y)] << 4;
    Block = Block >> 4;
 }
 return Block;
}

void SetBlock(uint8_t x,uint8_t y,uint8_t b){
 uint8_t Block = MAP[GetOffset(x,y)];
 uint8_t AddBlock = b;
 if (x % 2 == 0){
    AddBlock = AddBlock << 4;
    Block = Block << 4;
    Block = Block >> 4;
 } else {
    Block = Block >> 4;
    Block = Block << 4;
 }
 Block |= AddBlock;
 MAP[GetOffset(x,y)] = Block;
}
