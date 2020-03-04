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
	board(const int board_size = 11);

	void print_graph();
	void print_board();
	virtual ~board() = default;
private:
	int board_size;
	graph tablero;
	std::vector<int> square_values;
	std::vector<const char*> marker { ".", "x", "o" };
};

#endif /* BOARD_H_ */
