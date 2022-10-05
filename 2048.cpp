// 2048.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <vector>

#include "Board.h"

int main()
{
	int size;
	std::cout << "Podaj wielkość: ";
	std::cin >> size;
	system("pause");
	
	Board board(size);
	board.play();

}
