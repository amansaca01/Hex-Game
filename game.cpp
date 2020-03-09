/*
 * game.cpp
 *
 *  Created on: Mar 5, 2020
 *      Author: amanda.salazar
 */

#include "game.h"

game::game(const int &board_size) :
		hex_board(board_size) {
}

void game::reset() {
	player = 0;
	rounds = 0;
	hex_board.reset();
}

void game::make_move(const int &x, const int &y) {

}


int game::next_turn() {
	return player++ % 2;
}
