#pragma once

#include "BlockType.h"

class BlockPair
{
protected:
	uint8_t value;

	constexpr static uint8_t Combine(uint8_t high, uint8_t low)
	{
		return static_cast<uint8_t>(((high & 0x0F) << 4) | ((low & 0x0F) << 0));
	}
public:
	constexpr BlockPair(void) : value(0) {}
	constexpr BlockPair(uint8_t value) : value(value) {}
	constexpr BlockPair(uint8_t high, uint8_t low) : value(Combine(high, low)) {}
	
	constexpr uint8_t GetHigh(void) const
	{
		return static_cast<uint8_t>((this->value >> 4) & 0x0F);
	}
	
	constexpr uint8_t GetLow(void) const
	{
		return static_cast<uint8_t>((this->value >> 0) & 0x0F);
	}
	
	constexpr BlockType GetHighType(void) const
	{
		return static_cast<BlockType>(this->GetHigh());
	}
	
	constexpr BlockType GetLowType(void) const
	{
		return static_cast<BlockType>(this->GetLow());
	}
	
	void SetHigh(uint8_t type)
	{
		this->value = (this->value & 0x0F) | ((type & 0x0F) << 4);	
	}
	
	void SetHighType(BlockType type)
	{
		this->SetHigh(static_cast<uint8_t>(type));
	}
	
	void SetLow(uint8_t type)
	{
		this->value = (this->value & 0xF0) | ((type & 0x0F) << 0);	
	}
	
	void SetLowType(BlockType type)
	{
		this->SetLow(static_cast<uint8_t>(type));
	}
	
	constexpr explicit operator uint8_t(void) const
	{
		return this->value;
	}
};