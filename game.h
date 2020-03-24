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
#include "hex_path.h"

#include<map>

class game {
public:
	game(const int &board_size = 11);
	virtual ~game() = default;

	void instructions();
	void select_color();
	void play();
	void reset();
	square read_move();
	square random_move();
	void make_move(const square &move);
	void next_turn();
	bool winner();
	color player_color();
	color player_color(const int &a);

private:
	board hex_board;
	std::vector<HexPath> paths;
	random_gen randomize;
	color selected_color;
	int player = 0;
};

#endif /* GAME_H_ */
