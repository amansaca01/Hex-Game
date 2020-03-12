/*
 * game.h
 *
 *  Created on: Mar 5, 2020
 *      Author: amanda.salazar
 */

#ifndef GAME_H_
#define GAME_H_

#include "board.h"
#include "random.h"


class game {
public:
	game(const int &board_size = 11);
	virtual ~game() = default;

	void play();
	void reset();
	square read_move();
	square random_move();
	void make_move(const square &move);
	void next_turn();
private:
	board hex_board;
	random_gen randomize;
	int player = 1;
	int rounds = 0;
};

#endif /* GAME_H_ */
