#include "Game.h"

void Game::Setup() {
	arduboy.begin();
	arduboy.clear();
	arduboy.initRandomSeed();
	arduboy.setFrameRate(30);
}

void Game::Loop() {
  if(!arduboy.nextFrame())
	return;

  arduboy.pollButtons();
  arduboy.clear();

  switch(gameState)
  {
	case GameState::GameStart:
		FillMapRandomly();
		GenerateStructure(StructureType::Forest);
		gameState = GameState::Game;
		break;
	case GameState::Game:
		Update();
		Render();
		break;
  }
  arduboy.display();	
}

void Game::Update() {
	
  if (arduboy.justPressed(UP_BUTTON)){
    if (player.direction == Direction::Up)
	    player.y -= 1;
	  else
	    player.direction = Direction::Up;
	}
  else if (arduboy.justPressed(DOWN_BUTTON)){
    if (player.direction == Direction::Down)
	    player.y += 1;
	  else
	    player.direction = Direction::Down;
	}
  else if (arduboy.justPressed(RIGHT_BUTTON)){
    if (player.direction == Direction::Right)
	    player.x += 1;
	  else  
	    player.direction = Direction::Right;
	}
  else if (arduboy.justPressed(LEFT_BUTTON)){
    if (player.direction == Direction::Left)
	    player.x -= 1;
	  else  
	    player.direction = Direction::Left;
	}   

  if (arduboy.justPressed(A_BUTTON)){
	gameState = GameState::GameStart;
  }
}

void Game::Render() {  
  DisplayEnvironment();
}

void Game::DisplayEnvironment()
{
	int tileX = player.x;
	int tileY = player.y;
	
	for (int i = -4; i < 5; i++)
	{
		for(int j = -4; j < 5; j++)
		{
			const auto block = worldMap.GetBlockSpriteOrDefault(tileX + i, tileY + j, BlockType::Fill);
	  
			int drawX = (i * 8) + CentreX;
			int drawY = (j * 8) + CentreY;
			sprites.drawSelfMasked(drawX, drawY, Back, static_cast<uint8_t>(block));
		}
	}
	sprites.drawOverwrite(CentreX, CentreY, SpriteTiles, 0);
}


void Game::FillMapRandomly() {
	for(uint16_t i = 0; i < Map::MemorySize; i++)
	{
		//worldMap[i] = ((rand() % 2) << 4) + (rand() % 2);
		worldMap[i] = rand() & 0x11; // Functionally equivalent and much cheaper
	}
}


uint8_t Game::CountSurrounding(uint8_t x, uint8_t y, BlockType type) {
  if (!Between(1, 1, Map::MaxX - 1, Map::MaxY - 1, x, y))
	return 4;
  
  uint8_t count = 0;
  
  if (worldMap.GetBlockTypeOrDefault(x + 1, y, BlockType::Tree) == type) ++count;
  if (worldMap.GetBlockTypeOrDefault(x - 1, y, BlockType::Tree) == type) ++count;
  if (worldMap.GetBlockTypeOrDefault(x, y + 1, BlockType::Tree) == type) ++count;
  if (worldMap.GetBlockTypeOrDefault(x, y - 1, BlockType::Tree) == type) ++count;
  if (worldMap.GetBlockTypeOrDefault(x + 1, y + 1, BlockType::Tree) == type) ++count;
  if (worldMap.GetBlockTypeOrDefault(x + 1, y - 1, BlockType::Tree) == type) ++count;
  if (worldMap.GetBlockTypeOrDefault(x - 1, y + 1, BlockType::Tree) == type) ++count;
  if (worldMap.GetBlockTypeOrDefault(x - 1, y - 1, BlockType::Tree) == type) ++count;
  
  return count;
}

void Game::GenerateStructure(StructureType type) {
	switch(type)
	{
		case StructureType::Forest: GenerateForest(); break;
	}
}

void Game::GenerateForest() {
	Map temp;
	for(uint8_t count = 0; count < MaxGen; count++)
	{
		for(uint8_t y = 0; y < Map::MaxY; y++)
		{
			for(uint8_t x = 0; x < Map::MaxX; x++)
			{
				const auto emptyCount = CountSurrounding(x, y, BlockType::None);
				if(
				((worldMap.GetBlockType(x, y) == BlockType::None) && (emptyCount >= 3)) ||
				((worldMap.GetBlockType(x, y) == BlockType::Tree) && (emptyCount >= 5))
				)
					temp.SetBlockType(x, y, BlockType::None);
				else
					temp.SetBlockType(x, y, BlockType::Tree);
			}
		}
		worldMap = temp;
	}
}


