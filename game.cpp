/*
 * game.cpp
 *
 *  Created on: Mar 5, 2020
 *      Author: amanda.salazar
 */

#include "game.h"
#include<iostream>

game::game(const int &board_size) :
		hex_board(board_size) {
}

void game::play() {
	square move;
	while (player != -1) {
		std::cout << player << std::endl;
		if (player) {

			move = read_move();
			std::cout << move.first << " " << move.second;

		}
		next_turn();
	}

}

square game::read_move() {
	char x, y;

	std::cout << std::endl << "Your move: ";
	std::cin >> x >> y;
	if (x > 96)
		x = char(x - 32);

	square move = std::make_pair(x - 65, y -'1');
	std::cout << move.second << std::endl;

	if (!hex_board.is_free_square(move)) {
		std::cout << "Your move should something like: A1" << std::endl;
		move = read_move();
	}
	return move;
}

void game::reset() {
	player = 0;
	rounds = 0;
	hex_board.reset();
}

void game::make_move(const int &x, const int &y) {
	int node = x + hex_board.size() * y;
	int player = next_turn() + 1;
	color col = (color) player;
	hex_board.set_color(node, col);
}

int game::next_turn() {
	return player++ % 2;
}

