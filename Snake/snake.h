#ifndef INCLUDED_SNAKE_H_
#define INCLUDED_SNAKE_H_

#include <string>
#include <utility>
#include <list>
#include <vector>

#define WIDTH 40
#define HEIGHT 20

class Banner {
public:
	Banner() : t_score_(0), banner_prefix_() {}
	int Length() const;
	const std::string GetBanner() const;
	void AddScore(int score) { t_score_ += score; }
	void SetBannerPrefix(const char* str) { banner_prefix_ = std::string(str); }
private:
	int t_score_;
	std::string banner_prefix_;
};

class Snake {
public:
	Snake();
	int Move(char input = 0);
	void Draw() const;
	void SetAnotherFruit();
	void SetBoard(int nx, int ny);
private:
	enum Direction {
		DIR_UP,
		DIR_DOWN,
		DIR_RIGHT,
		DIR_LEFT,
	};
	Direction dir_;
	int score_;
	std::list<std::pair<int, int>> tail_;
	std::pair<int, int> head_;
	std::pair<int, int> fruit_;
	Banner *banner_;
	std::vector<bool> board_;
};



#endif // INCLUDED_SNAKE_H_
