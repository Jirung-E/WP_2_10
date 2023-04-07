#include "Util.h"


COLORREF getRandomColor() {
	return RGB(random_color(rd), random_color(rd), random_color(rd));
}


POINT getCenterOf(const RECT& rect) {
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	return { rect.left + width/2, rect.top + height/2 };
}

RECT rectToSquare(const RECT& rect) {
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	int n = width < height ? width/2 : height/2;
	POINT center = getCenterOf(rect);
	return { center.x-n, center.y-n, center.x+n, center.y+n };
}