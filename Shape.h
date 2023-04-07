#pragma once

#include "Util.h"


class Shape {
public:
	COLORREF color;

public:
	Shape(const COLORREF& color = getRandomColor());

public:
	void show(const HDC& hdc, const RECT& area) const;

protected:
	virtual void draw(const HDC& hdc, const RECT& area) const = 0;
};




class Rect : public Shape {
public:
	Rect(const COLORREF& color = getRandomColor());

protected:
	void draw(const HDC& hdc, const RECT& area) const;
};


class Triangle : public Shape {
public:
	Triangle(const COLORREF& color = getRandomColor());

protected:
	void draw(const HDC& hdc, const RECT& area) const;
};


class Circle : public Shape {
public:
	Circle(const COLORREF& color = getRandomColor());

protected:
	void draw(const HDC& hdc, const RECT& area) const;
};


class Diamond : public Shape {
public:
	Diamond(const COLORREF& color = getRandomColor());

protected:
	void draw(const HDC& hdc, const RECT& area) const;
};