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

		if (player) {
			hex_board.print_board();
			move = read_move();
		} else{
			move = random_move();
		}


		make_move(move);
		next_turn();
	}

}

square game::read_move() {
	char x, y;

	std::cout << std::endl << "Your move: ";
	std::cin >> x >> y;
	if (x > 96)
		x = char(x - 32);

	square move = std::make_pair(x - 65, y - '1');

	if (!hex_board.is_free_square(move)) {
		std::cout << "Your move should something like: A1" << std::endl;
		move = read_move();
	}
	return move;
}

square game::random_move() {

	int x = randomize.prob_int(0,hex_board.size()-1);
	int y = randomize.prob_int(0,hex_board.size()-1);

	return std::make_pair(x,y);
}

void game::reset() {
	player = 0;
	rounds = 0;
	hex_board.reset();
}

void game::make_move(const square &move) {
	color col = (color) (player+1);
	std::cout << "Player " <<col << " "<<move.first << " " << move.second << std::endl;
	hex_board.set_color(move, col);
}

void game::next_turn() {
	 player=(player+1) % 2;
}

