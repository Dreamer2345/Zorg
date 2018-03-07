#pragma once 

void DisplayEnviroment()
{
  int tileX = playerobj.x;
  int tileY = playerobj.y;
    
  for (int i = -4; i < 5; i++)
  {
    for(int j = -4; j < 5; j++)
    {
      uint8_t block = GetBlockTrans(tileX + i, tileY + j);
      
      int drawX = (i * 8) + CENTERX;
      int drawY = (j * 8) + CENTERY;
      sprites.drawSelfMasked(drawX, drawY, Back, block);
    }
  }
  sprites.drawOverwrite(CENTERX, CENTERY, SpriteTiles, 0);
  if (ard.everyXFrames(15))
    playerobj.frame = !playerobj.frame;
  if (playerobj.frame)
    switch(playerobj.d){
    case 0: sprites.drawOverwrite(CENTERX, CENTERY-8, SpriteTiles, 8); break;
    case 1: sprites.drawOverwrite(CENTERX, CENTERY+8, SpriteTiles, 8); break;
    case 2: sprites.drawOverwrite(CENTERX+8, CENTERY, SpriteTiles, 8); break;
    case 3: sprites.drawOverwrite(CENTERX-8, CENTERY, SpriteTiles, 8); break;
    };
}


void FillRandom(){
  for(uint16_t i = 0; i<MEMSIZE; i++){
    uint8_t r = ((rand() % 2) << 4)+(rand() % 2);
    MAP[i] = r;
  }
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


