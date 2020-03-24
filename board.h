/*
 * board.h
 *
 *  Created on: Mar 3, 2020
 *      Author: amanda.salazar
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "graph.h"
#include <vector>
#include <map>

typedef std::pair<int, int> square;

class board: public graph {
public:
	board(const int &board_size = 11);

	int size();
	void reset();
	int get_node(const square &move) const;
	color get_color(const square &move) const;
	void set_color(const square &move, const color &col);
	void print_board();
	bool is_square(const square &move);
	bool is_free_square(const square &move);
	std::vector<square> free_squares();
	void mock_colors();
	void reset_colors();

	virtual ~board() = default;
private:
	int board_size;
	std::map<color, const char*> marker;
	std::vector<color> original_colors;
};

#endif /* BOARD_H_ */
