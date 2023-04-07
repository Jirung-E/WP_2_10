#pragma once

#include "Util.h"
#include "Tile.h"
#include "Stone.h"

#include <vector>


class Field {
private:
	const int row;
	const int col;
	const int margin_per;

	int horizontal_length;
	int vertical_length;
	RECT valid_area;
	RectSize tile_size;
	std::vector<std::vector<Tile*>> tile;
	Stone stone[2];

public:
	Field(int row, int col);

public:
	void show(const HWND& hwnd, const HDC& hdc);
	void reset();

	void moveLeft(int stone_index);
	void moveRight(int stone_index);
	void moveUp(int stone_index);
	void moveDown(int stone_index);

private:
	void updateStone(int stone_index);
	void syncSize(const HWND& hwnd);
	void showField(const HDC& hdc);
	void showObjects(const HDC& hdc);
	void setObjects();
};