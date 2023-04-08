#include "Field.h"

#include <random>


Field::Field(int row, int col) : row { row }, col { col }, margin_per { 5 }, 
horizontal_length { 0 }, vertical_length { 0 }, valid_area { 0, 0, 0, 0 }, tile_size { 0.0, 0.0 },
tile { col }, stone { { 0, 0 }, { row-1, col-1 } } {
	for(int i = 0; i < col; ++i) {
		tile[i].reserve(row);
		for(int k = 0; k < row; ++k) {
			tile[i].push_back(nullptr);
		}
	}
	setObjects();
}


void Field::show(const HWND& hwnd, const HDC& hdc) {
	syncSize(hwnd);
	showField(hdc);
	showObjects(hdc);
}

void Field::reset() {
	for(int i = 0; i < col; ++i) {
		for(int k = 0; k < row; ++k) {
			delete tile[i][k];
			tile[i][k] = nullptr;
		}
	}
	setObjects();
}

void Field::syncSize(const HWND& hwnd) {
	RECT rect;
	GetClientRect(hwnd, &rect);
	int w = rect.right - rect.left;
	int h = rect.bottom - rect.top;
	valid_area.left = rect.left + w * margin_per / 100;
	valid_area.right = rect.right - w * margin_per / 100;
	valid_area.top = rect.top + h * margin_per / 100;
	valid_area.bottom = rect.bottom - h * margin_per / 100;
	horizontal_length = valid_area.right - valid_area.left;
	vertical_length = valid_area.bottom - valid_area.top;
	tile_size.width = double(horizontal_length) / row;
	tile_size.height = double(vertical_length) / col;
}

void Field::showField(const HDC& hdc) {
	Rectangle(hdc, valid_area.left, valid_area.top, valid_area.right, valid_area.bottom);
	for(int i = 1; i < col; ++i) {
		MoveToEx(hdc, valid_area.left, valid_area.top + i * vertical_length / col, NULL);
		LineTo(hdc, valid_area.right, valid_area.top + i * vertical_length / col);
	}
	for(int i = 1; i < row; ++i) {
		MoveToEx(hdc, valid_area.left + i * horizontal_length / row, valid_area.top, NULL);
		LineTo(hdc, valid_area.left + i * horizontal_length / row, valid_area.bottom);
	}
}

void Field::showObjects(const HDC& hdc) {
	for(int i = 0; i < col; ++i) {
		for(int k = 0; k < row; ++k) {
			if(tile[i][k] != nullptr) {
				tile[i][k]->show(hdc, valid_area, tile_size);
			}
		}
	}
	stone[0].show(hdc, valid_area, tile_size);
	stone[1].show(hdc, valid_area, tile_size);
}

void Field::setObjects() {
	std::uniform_int_distribution<> random_x { 0, row - 1 };
	std::uniform_int_distribution<> random_y { 0, col - 1 };
	std::uniform_int_distribution<> random_tile { 0, 3 };

	int rnd = (row < col ? row : col) / 2;
	for(int i = 0; i < rnd; ++i) {
		int x = random_x(rd);
		int y = random_y(rd);
		if(tile[y][x] != nullptr) {
			i--;
			continue;
		}
		if(stone[0].x == x && stone[0].y == y) {
			i--;
			continue;
		}
		if(stone[1].x == x && stone[1].y == y) {
			i--;
			continue;
		}
		switch (random_tile(rd)) {
		case 0:
			tile[y][x] = new Obstacle { x, y };
			break;
		case 1:
			tile[y][x] = new ColorChange{ x, y };
			break;
		case 2:
		tile[y][x] = new SizeChange { x, y };
			break;
		case 3:
			tile[y][x] = new ShapeChange{ x, y };
			break;
		}
	}

	stone[0].x = 0;
	stone[0].y = 0;
	stone[0].changeShape();
	stone[1].x = row-1;
	stone[1].y = col-1;
	stone[1].changeShape();
}

void Field::updateStone(int stone_index) {
	Stone& s = stone[stone_index];
	if(tile[s.y][s.x] == nullptr) {
		return;
	}

	tile[s.y][s.x]->activate(s);
}

void Field::moveLeft(int stone_index) {
	Stone& s = stone[stone_index];
	int next_x = s.x - 1;
	if(next_x < 0) {
		next_x = row - 1;
	}
	if(tile[s.y][next_x] != nullptr) {
		if(tile[s.y][next_x]->passable == false) {
			next_x = s.x;
		}
	}
	s.x = next_x;
	if(stone[0].x == stone[1].x && stone[0].y == stone[1].y) {
		moveRight(stone_index);
		return;
	}
	updateStone(stone_index);
}

void Field::moveRight(int stone_index) {
	Stone& s = stone[stone_index];
	int next_x = s.x + 1;
	if(next_x > row - 1) {
		next_x = 0;
	}
	if(tile[s.y][next_x] != nullptr) {
		if(tile[s.y][next_x]->passable == false) {
			next_x = s.x;
		}
	}
	s.x = next_x;
	if(stone[0].x == stone[1].x && stone[0].y == stone[1].y) {
		moveLeft(stone_index);
		return;
	}
	updateStone(stone_index);
}

void Field::moveUp(int stone_index) {
	Stone& s = stone[stone_index];
	int next_y = s.y - 1;
	if(next_y < 0) {
		next_y = col - 1;
	}
	if(tile[next_y][s.x] != nullptr) {
		if(tile[next_y][s.x]->passable == false) {
			next_y = s.y;
		}
	}
	s.y = next_y;
	if(stone[0].x == stone[1].x && stone[0].y == stone[1].y) {
		moveDown(stone_index);
		return;
	}
	updateStone(stone_index);
}

void Field::moveDown(int stone_index) {
	Stone& s = stone[stone_index];
	int next_y = s.y + 1;
	if(next_y > col - 1) {
		next_y = 0;
	}
	if(tile[next_y][s.x] != nullptr) {
		if(tile[next_y][s.x]->passable == false) {
			next_y = s.y;
		}
	}
	s.y = next_y;
	if(stone[0].x == stone[1].x && stone[0].y == stone[1].y) {
		moveUp(stone_index);
		return;
	}
	updateStone(stone_index);
}



void Field::generateMaze() {
	// 일단 꽉 채우기
	for(int i=0; i<col; ++i) {
		for(int k=0; k<row; ++k) {
			tile[i][k] = new Obstacle { k, i };
		}
	}

	// 플레이어 배치
	stone[0].x = 1;
	stone[0].y = 1;
	stone[1].x = row-2;
	stone[1].y = col-2;
	delete tile[1][1];
	tile[1][1] = nullptr;
	delete tile[col-2][row-2];
	tile[col-2][row-2] = nullptr;

	// 구멍뚫기

}