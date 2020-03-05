/*
 * game.h
 *
 *  Created on: Mar 5, 2020
 *      Author: amanda.salazar
 */

#ifndef GAME_H_
#define GAME_H_

#include "board.h"

class game {
public:
	game(const int &board_size = 11);
	virtual ~game() = default;

	void reset();
	void make_move(const int &x, const int &y);
	int next_turn();
private:
	board hex_board;
	int player = 1;
	int rounds = 0;
};

#endif /* GAME_H_ */
