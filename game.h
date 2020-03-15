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
	int next_turn();
	bool winner();
	color player_color();
	color player_color(const int &a);

private:
	board hex_board;
	random_gen randomize;
	color selected_color;
	std::map<color, std::pair<std::vector<int>,std::vector<int>>> sides;
	//std::vector<std::pair<std::vector<int>,std::vector<int>>> sides;
	int player = 1;
	int rounds = 0;
};

#endif /* GAME_H_ */
