#include "Shape.h"


Shape::Shape(const COLORREF& color) : color { color } {

}

void Shape::show(const HDC& hdc, const RECT& area) const {
	HBRUSH br = CreateSolidBrush(color);
	HBRUSH old = (HBRUSH)SelectObject(hdc, br);

	draw(hdc, area);

	SelectObject(hdc, old);
	DeleteObject(br);
}



Rect::Rect(const COLORREF& color) : Shape { color } {

}

void Rect::draw(const HDC& hdc, const RECT& area) const {
	Rectangle(hdc, area.left, area.top, area.right, area.bottom);
}


Triangle::Triangle(const COLORREF& color) : Shape { color } {

}

void Triangle::draw(const HDC& hdc, const RECT& area) const {
	POINT* p = new POINT[3];
	p[0].x = area.left + (area.right - area.left) / 2;
	p[0].y = area.top;
	p[1].x = area.left;
	p[1].y = area.bottom;
	p[2].x = area.right;
	p[2].y = area.bottom;
	Polygon(hdc, p, 3);
}


Circle::Circle(const COLORREF& color) : Shape { color } {

}

void Circle::draw(const HDC& hdc, const RECT& area) const {
	Ellipse(hdc, area.left, area.top, area.right, area.bottom);
}


Diamond::Diamond(const COLORREF& color) : Shape { color } {

}

void Diamond::draw(const HDC& hdc, const RECT& area) const {
	POINT* p = new POINT[4];
	POINT center = getCenterOf(area);
	p[0].x = center.x;
	p[0].y = area.top;
	p[1].x = area.left;
	p[1].y = center.y;
	p[2].x = center.x;
	p[2].y = area.bottom;
	p[3].x = area.right;
	p[3].y = center.y;
	Polygon(hdc, p, 4);
}