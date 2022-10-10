#pragma once
#include<vector>
class Board
{
public:
	Board(int size);
	~Board() = default;

	void play();
	bool move();
	void spawn();
	void print();
	bool check_if_lost();
	int get_score();
	int biggest_value();

private:
	int board_size, score = 0;
	std::vector<std::vector<int>> quango; //quango[x][y]

};

