#pragma once

#include "Shape.h"


class Object {
public:
    Shape* shape;
    int x;
    int y;

public:
    Object(int x, int y) : shape { nullptr }, x { x }, y { y } {

    }
    ~Object() {
        delete shape;
    }

public:
    void show(const HDC& hdc, const RECT& valid_area, const RectSize& size) const {
        int start_x = valid_area.left + x*size.width;
        int end_x = valid_area.left + (x+1)*size.width;
        int start_y = valid_area.top + y*size.height;
        int end_y = valid_area.top + (y+1)*size.height;
        shape->show(hdc, { start_x, start_y, end_x, end_y });
    }
};