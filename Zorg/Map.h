#pragma once

#include "BlockType.h"
#include "BlockPair.h"

class Map
{
public:
	constexpr static const uint8_t MaxX = 20;
	constexpr static const uint8_t MaxY = 20;
	constexpr static const uint8_t HalfMaxX = (MaxX / 2);
	constexpr static const uint8_t MemorySize = (HalfMaxX * MaxY);
	
private:
	BlockPair data[MemorySize];
	
	
	#ifndef DEBUG
	constexpr uint16_t GetOffset(uint8_t x, uint8_t y)
	{
		return (x / 2) + ((MaxX / 2) * y);
	}
	#else
	uint16_t GetOffset(uint8_t x, uint8_t y)
	{
		uint16_t column = (x / 2) + (y * HalfMaxX);
		if(column < MemorySize)
			return column;
				
		Serial.println(F("Invalid arguments to GetOffset"));
		Serial.println(x);
		Serial.println(y);
		return 0;
	}
	#endif
public:

	/*BlockPair & GetBlockPair(uint8_t x, uint8_t y)
	{
		//if (x >= MaxX || y >= MaxY)
			//return BlockPair();
		
		return this->data[GetOffset(x, y)];
	}*/

	const BlockPair GetBlockPair(uint8_t x, uint8_t y) const
	{
		/*if (x >= MaxX || y >= MaxY)
			return BlockPair();*/
		
		return this->data[GetOffset(x, y)];
	}

	BlockType GetBlockType(uint8_t x, uint8_t y) const
	{			
		BlockPair block = GetBlockPair(x, y);
		return (x % 2 == 0) ? block.GetHighType() : block.GetLowType();
	}

	uint8_t GetBlockSpriteOrDefault(uint8_t x, uint8_t y, uint8_t defaultValue) const
	{
		if (x >= MaxX || y >= MaxY)
			return defaultValue;
			
		BlockPair block = GetBlockPair(x, y);
		BlockType blockret = (x % 2 == 0) ? block.GetHighType() : block.GetLowType();

    switch(blockret){
      case BlockType::
    }
    
	}

	void SetBlockPair(uint8_t x, uint8_t y, BlockPair pair)
	{
		if (x >= MaxX || y >= MaxY)
			return;
		
		this->data[GetOffset(x,y)] = pair;
	}

	void SetBlockType(uint8_t x, uint8_t y, BlockType type)
	{
		if (x >= MaxX || y >= MaxY)
			return;
		
		BlockPair block = GetBlockPair(x, y);
		if(x % 2 == 0)
			block.SetHighType(type);
		else
			block.SetLowType(type);
		
		SetBlockPair(x, y, block);
	}
	
	BlockPair & operator[](const uint16_t & index)
	{
		return this->data[index];
	}
	
	const BlockPair & operator[](const uint16_t & index) const
	{
		return this->data[index];
	}
};
