/*
 * board.h
 *
 *  Created on: Mar 3, 2020
 *      Author: amanda.salazar
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "graph.h"

class board {
public:
	board(const int &board_size = 11);

	void reset();
	int get_node(const int &x,const int &y);
	color get_color(const int &node);
	void set_color(const int &node, color &col);
	void print_graph();
	void print_board();
	virtual ~board() = default;
private:
	int board_size;
	graph tablero;
};

#endif /* BOARD_H_ */
