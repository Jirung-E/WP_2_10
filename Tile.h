#pragma once

#include "Object.h"
#include "Stone.h"


class Tile : public Object {
public:
    const bool passable;

public:
    Tile(int x, int y, bool passable = true) : Object { x, y }, passable { passable } {
        shape = new Rect { };
    }

public:
    virtual void activate(Stone& stone) = 0;
};

class Obstacle : public Tile {
public:
    Obstacle(int x, int y) : Tile { x, y, false } {
        shape->color = RGB(0xff, 0, 0);
    }

public:
    virtual void activate(Stone& stone) {

    }
};

class ColorChange : public Tile {
public:
    ColorChange(int x, int y) : Tile { x, y } {

    }

public:
    virtual void activate(Stone& stone) {
        stone.shape->color = getRandomColor();
    }
};

class SizeChange : public Tile {
public:
    SizeChange(int x, int y) : Tile { x, y } {

    }

public:
    virtual void activate(Stone& stone) {
        if(stone.inc) {
            stone.size_inc++;
        }
        else {
            stone.size_inc--;
        }
    }
};

class ShapeChange : public Tile {
public:
    ShapeChange(int x, int y) : Tile { x, y } {

    }

public:
    virtual void activate(Stone& stone) {
        COLORREF c = stone.shape->color;
        stone.changeShape();
        stone.shape->color = c;
    }
};