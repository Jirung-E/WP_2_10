#pragma once

#include <Windows.h>
#include <random>


static std::random_device rd;
static std::uniform_int_distribution<> random_color { 0 + 0x11, 0xFF - 0x11 };


COLORREF getRandomColor();
POINT getCenterOf(const RECT& rect);
RECT rectToSquare(const RECT& rect);

class RectSize {
public:
	double width;
	double height;
};