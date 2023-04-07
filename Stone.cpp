#include "Stone.h"


static int getRandomShapeIndex() {
	std::uniform_int_distribution<> rs { 0, 3 };
	return rs(rd);
}

Stone::Stone(int x, int y) : Object { x, y }, size_inc { 0 }, current_shape { getRandomShapeIndex() }, inc_max { 0 }, inc { true } {
	changeShape();
}

void Stone::changeShape() {
	delete shape;
	switch(current_shape) {
	case 0:
		shape = new Triangle { };
		break;
	case 1:
		shape = new Circle { };
		break;
	case 2:
		shape = new Rect { };
		break;
	case 3:
		shape = new Diamond { };
		break;
	}
	current_shape++;
	if(current_shape > 3) {
		current_shape = 0;
	}
}

void Stone::show(const HDC& hdc, const RECT& valid_area, const RectSize& size) {
	int start_x = valid_area.left + x*size.width + size_inc;
	int end_x = valid_area.left + (x+1)*size.width - size_inc;
	int start_y = valid_area.top + y*size.height + size_inc;
	int end_y = valid_area.top + (y+1)*size.height - size_inc;
	RECT area = rectToSquare({ start_x, start_y, end_x, end_y });
	inc_max = (area.right-area.left)/2;
	if(size_inc > inc_max) {
		size_inc = inc_max;
		inc = false;

	}
	else if(size_inc <= 0) {
		size_inc = 0;
		inc = true;
	}
	shape->show(hdc, area);
}