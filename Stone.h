#pragma once

#include "Object.h"


class Stone : public Object {
private:
	int current_shape;

public:
	int size_inc;
	int inc_max;
	bool inc;

public:
	Stone(int x, int y);

public:
	void changeShape();
	void show(const HDC& hdc, const RECT& valid_area, const RectSize& size);
};