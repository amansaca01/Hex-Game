/*
 * board.h
 *
 *  Created on: Mar 3, 2020
 *      Author: amanda.salazar
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "graph.h"
#include "shortest_path.h"

class board {
public:
	board(const int &board_size = 11);
	graph get_tablero();
	void reset();
	int get_node(const int &x, const int &y);
	color get_color(const int &node);
	void set_color(const int &node, const color &col);
	void print_graph();
	void print_board();
	virtual ~board() = default;
	void north_to_south();//const graph &G
	void west_to_east();

private:
	int board_size;
	graph tablero;
};

#endif /* BOARD_H_ */
