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

class board {
public:
	board(const int &board_size = 11);

	int size();
	void reset();
	int get_node(const square &move);
	color get_color(const int &node);
	void set_color(const int &node, color &col);
	void print_graph();
	void print_board();
	bool is_square(const square &move);
	bool is_free_square(const square &move);


	virtual ~board() = default;
private:
	int board_size;
	graph tablero;
};

#endif /* BOARD_H_ */
