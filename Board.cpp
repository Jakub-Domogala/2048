#include "Board.h"
#include <iostream>
#include <cmath>

Board::Board(int size)
{
	board_size = size;

	for (int i = 0; i < size; i++) {
		std::vector <int> row;
		for (int j = 0; j < size; j++) {
			row.push_back(0);
		}
		quango.push_back(row);
	}
}

void Board::play()
{
	int moves = 0;
	std::cout << "Your available moves are: \n\
W - up\n\
S - down\n\
D - right\n\
A - left\n\
normal and capitals accepted\n";
	system("pause");
	do 
	{
		system("CLS");
		spawn();
		print();
		move();
	} while (!check_if_lost());
	system("CLS");
	std::cout << "\nYOU LOST\n";
	std::cout << "\nYour Score is " << score << "\n\n";
	system("pause");
}

void Board::move()
{	
	char key;

	std::cout << "Tell me your next move:";
	std::cin >> key;
	int
		step,
		col_idx,
		curr_num,
		free_space;
	switch (key) {

		// UP
	case 'W':
	case 'w':	
		for (col_idx = 0; col_idx < board_size; col_idx++) {
			curr_num = -1;
			free_space = board_size - 1;
			for (step = board_size - 1; step >= 0; step--) {
				if (quango[col_idx][step] > 0) {									
					if (curr_num < 0) {												
						curr_num = quango[col_idx][step];	
						quango[col_idx][step] = 0;
					}
					else {
						if (quango[col_idx][step] == curr_num) {

							quango[col_idx][step] = 0;
							quango[col_idx][free_space] = curr_num + curr_num;
							score += curr_num + curr_num;
							free_space--;
							curr_num = -1;
						}
						else {
							
							quango[col_idx][free_space] = curr_num;
							curr_num = quango[col_idx][step];
							quango[col_idx][step] = 0;
							free_space--;
						}
					}
				}
				if (step == 0 && curr_num > 0) {
					quango[col_idx][step] = 0;
					quango[col_idx][free_space] = curr_num;
				}
			}

		}
		break;

		// DOWN
	case 'S':
	case 's':
		for (col_idx = 0; col_idx < board_size; col_idx++) {
			curr_num = -1;
			free_space = 0;
			for (step = 0; step < board_size; step++) {
				if (quango[col_idx][step] > 0) {
					if (curr_num < 0) {
						curr_num = quango[col_idx][step];
						quango[col_idx][step] = 0;
					}
					else {
						if (quango[col_idx][step] == curr_num) {

							quango[col_idx][step] = 0;
							quango[col_idx][free_space] = curr_num + curr_num;
							score += curr_num + curr_num;
							free_space++;
							curr_num = -1;
						}
						else {

							quango[col_idx][free_space] = curr_num;
							curr_num = quango[col_idx][step];
							quango[col_idx][step] = 0;
							free_space++;
						}
					}
				}
				if (step == board_size - 1 && curr_num > 0) {
					quango[col_idx][step] = 0;
					quango[col_idx][free_space] = curr_num;
				}
			}
		}
		break;

		// LEFT
	case'A':
	case 'a':
		for (col_idx = 0; col_idx < board_size; col_idx++) {
			curr_num = -1;
			free_space = 0;
			for (step = 0; step < board_size; step++) {
				if (quango[step][col_idx] > 0) {
					if (curr_num < 0) {
						curr_num = quango[step][col_idx];
						quango[step][col_idx] = 0;
					}
					else {
						if (quango[step][col_idx] == curr_num) {

							quango[step][col_idx] = 0;
							quango[free_space][col_idx] = curr_num + curr_num;
							score += curr_num + curr_num;
							free_space++;
							curr_num = -1;
						}
						else {

							quango[free_space][col_idx] = curr_num;
							curr_num = quango[step][col_idx];
							quango[step][col_idx] = 0;
							free_space++;
						}
					}
				}
				if (step == board_size - 1 && curr_num > 0) {
					quango[step][col_idx] = 0;
					quango[free_space][col_idx] = curr_num;
				}
			}
		}
		break;

		// RIGHT
	case 'D':
	case 'd':
		for (col_idx = 0; col_idx < board_size; col_idx++) {
			curr_num = -1;
			free_space = board_size - 1;
			for (step = board_size - 1; step >= 0; step--) {
				if (quango[step][col_idx] > 0) {
					if (curr_num < 0) {
						curr_num = quango[step][col_idx];
						quango[step][col_idx] = 0;
					}
					else {
						if (quango[step][col_idx] == curr_num) {

							quango[step][col_idx] = 0;
							quango[free_space][col_idx] = curr_num + curr_num;
							score += curr_num + curr_num;
							free_space--;
							curr_num = -1;
						}
						else {

							quango[free_space][col_idx] = curr_num;
							curr_num = quango[step][col_idx];
							quango[step][col_idx] = 0;
							free_space--;
						}
					}
				}
				if (step == 0 && curr_num > 0) {
					quango[step][col_idx] = 0;
					quango[free_space][col_idx] = curr_num;
				}
			}
		}
		break;
	}
}

void Board::spawn()
{	
	int x, y;
	do {
		x = rand() % board_size;
		y = rand() % board_size;
	} while (quango[x][y] > 0);

	int val = std::floor(std::log2(std::log2(score)));
	val = std::max(val, 1);
	val = std::pow(2, val);

	quango[x][y] = val;

	

}

int Board::biggest_value() {
	int val = 0;
	for (int i = 0; i < board_size; i++) {
		for (int j = 0; j < board_size; j++) {
			if (val < quango[i][j]) val = quango[i][j];
		}
	}
	return val;
}

void Board::print()
{
	std::cout << "Score: " << score;
	for (int y = board_size-1; y >= 0; y--) {
		std::cout << "    \n |||";
		for (int x = 0; x < board_size; x++) {
			if (quango[x][y] > 0) {
				std::cout << quango[x][y] << "\t";
			}
			else {
				std::cout << "\t";
			}
		}
	}
}

bool Board::check_if_lost()
{
	for (int i = 0; i < board_size; i++) {
		for (int j = 0; j < board_size; j++) {
			if (0 == quango[i][j]) return false;
		}
	}
	return true;
}

int Board::get_score()
{
	return 0;
}
