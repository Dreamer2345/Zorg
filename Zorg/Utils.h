#pragma once

template<typename T>
void swap(T & a, T & b)
{
	T t = a;
	a = b;
	b = t;
}

inline bool Between(uint8_t x, uint8_t y, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
	if (x > x1)
		swap(x, x1);
		
	if (y > y1)
		swap(y, y1);
		
	return ((x <= x2) && (x2 <= x1) && (y <= y2) && (y2 <= y1));
}