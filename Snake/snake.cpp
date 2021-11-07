#include <utility>
#include <algorithm>
#include <string>
#include <cstring>
#include <random>
#include <vector>

#include <curses.h>

#include "snake.h"
#include "color.h"

Snake::Snake() : head_(5, 10), dir_(DIR_DOWN), score_(0), fruit_(20, 10),
				tail_(), board_(WIDTH * HEIGHT, false) {
	banner_ = new Banner();
	banner_->SetBannerPrefix("w:up, s:down, a:left, d:right  Score: ");
}

int Snake::Move(char input) {
	switch (input) {
	case 'w':
		if (dir_ != DIR_DOWN) dir_ = DIR_UP;
		break;
	case 's':
		if (dir_ != DIR_UP) dir_ = DIR_DOWN;
		break;
	case 'a':
		if (dir_ != DIR_RIGHT) dir_ = DIR_LEFT;
		break;
	case 'd':
		if (dir_ != DIR_LEFT) dir_ = DIR_RIGHT;
		break;
	case 'p':
		return -1;
	}
	int dx = 0, dy = 0;
	switch (dir_) {
	case DIR_UP: dy--; break;
	case DIR_DOWN: dy++; break;
	case DIR_LEFT: dx--; break;
	case DIR_RIGHT: dx++; break;
	}
	int nx, ny;
	nx = head_.first + dx;
	ny = head_.second + dy;
	if (nx <= 0 || nx >= WIDTH - 1 || ny <= 0 || ny >= HEIGHT - 1) {
		return 1;
	}
	SetBoard(nx, ny);
	if (board_[ny * WIDTH + nx]) {
		return 1;
	}
	if (nx == fruit_.first && ny == fruit_.second) {
		banner_->AddScore(10);
		SetAnotherFruit();
	}
	else {
		if (tail_.size() != 0) tail_.pop_back();
	}
	tail_.emplace_front(head_.first, head_.second);
	head_.first = nx;
	head_.second = ny;
	return 0;
}

void Snake::Draw() const {
	int sx, sy;
	sx = (COLS - WIDTH) / 2;
	sy = (LINES - HEIGHT) / 2;

	erase();
	// draw fruit
	move(sy, sx);
	attrset(C_DEFAULT);
	for (int i = 0; i < WIDTH; i++) addch(ACS_BLOCK);
	for (int i = 1; i < HEIGHT-1; i++) {
		mvaddch(sy + i, sx, ACS_BLOCK);
		mvaddch(sy + i, sx + WIDTH - 1, ACS_BLOCK);
	}
	move(sy + HEIGHT - 1, sx);
	for (int i = 0; i < WIDTH; i++) addch(ACS_BLOCK);
	// draw head
	attrset(C_RED);
	mvaddch(sy + head_.second, sx + head_.first, ACS_BLOCK);
	// draw tail
	attrset(C_GREEN);
	for (const auto& t : tail_) {
		mvaddch(sy + t.second, sx + t.first, ACS_BLOCK);
	}
	// draw fruit
	attrset(C_RED);
	mvaddch(sy + fruit_.second, sx + fruit_.first, 'o');
	
	// draw banner
	attrset(C_DEFAULT);
	::move(sy + HEIGHT, sx + WIDTH - banner_->Length());
	::addstr(banner_->GetBanner().c_str());
	refresh();
}

void Snake::SetAnotherFruit() {
	std::random_device rnd;
	int spc_size = (WIDTH - 2) * (HEIGHT - 2) - tail_.size() - 1;
	int num = rnd() % spc_size;
	int cnt = -1;
	for (int i = 0; i < WIDTH * HEIGHT; i++) {
		int x, y;
		x = i % WIDTH;
		y = i / WIDTH;
		if (!board_[i] && (x != 0 && x != (WIDTH - 1) && y != 0 && y != (HEIGHT - 1))) cnt++;
		if (cnt == num) {
			fruit_.first = x;
			fruit_.second = y;
			return;
		}
	}
}

void Snake::SetBoard(int nx, int ny) {
	fill(board_.begin(), board_.end(), false);
	for (const auto& p : tail_) {
		board_[p.second * WIDTH + p.first] = true;
	}
	board_[head_.second * WIDTH + head_.first] = true;
	board_[ny * WIDTH + nx];
}

int Banner::Length() const {
	return banner_prefix_.length() + std::to_string(t_score_).length();
}

const std::string Banner::GetBanner() const {
	return banner_prefix_ + std::to_string(t_score_);
}
