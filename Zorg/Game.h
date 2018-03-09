#pragma once

#include <Arduboy2.h>

//#include "ArduboyBeep.h"
//BeepPin1 beep;
#include "Bitmaps.h"
#include "Map.h"
#include "Player.h"
#include "Utils.h"
#include "GameState.h"
#include "StructureType.h"

class Game
{
public:	
	constexpr static const uint8_t MaxGen = 15;
	constexpr static const uint8_t CentreX = (WIDTH / 2) - 1;
	constexpr static const uint8_t CentreY = (HEIGHT / 2) - 1;
	
private:
	Arduboy2 arduboy;
	Sprites sprites;
	
	Map worldMap; // Can't use 'map' because Arduino defines a map macro
	Player player;
	GameState gameState = GameState::GameStart;
	
public:
	void Setup();
	void Loop();

	void Update();
	void Render();

private:
	void DisplayEnvironment();
	void FillMapRandomly();
	uint8_t CountSurrounding(uint8_t x, uint8_t y, BlockType type);
	
	void GenerateForest();
	void GenerateStructure(StructureType type);

	uint8_t GetBlockTrans(uint16_t x, uint16_t y);
};