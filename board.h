/*
 * board.h
 *
 *  Created on: Mar 3, 2020
 *      Author: amanda.salazar
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "graph.h"

typedef std::pair<int, int> square;

class board : public graph{
public:
	board(const int &board_size = 11);

	int size();
	void reset();
	int get_node(const square &move);
	color get_color(const square &move);
	void set_color(const square &move, color &col);
	void print_board();
	bool is_square(const square &move);
	bool is_free_square(const square &move);

	virtual ~board() = default;
private:
	int board_size;
};

#endif /* BOARD_H_ */
