/*
 * hex_path.h
 *
 *  Created on: Mar 23, 2020
 *      Author: teletrabajo3.produccion
 */

#ifndef HEX_PATH_H_
#define HEX_PATH_H_

#include "board.h"

typedef std::pair<std::vector<int>, std::vector<int>> board_sides;

class HexPath {
public:
	HexPath( board* B, const color &col, const board_sides &sides);
	virtual ~HexPath() = default;

	bool check_paths();
	bool check_neighbors(const int &node, const int &origin, const int &target);
private:
	board* hex_board;
	color col;
	board_sides sides;
	std::vector<int> connections;
};

#endif /* HEX_PATH_H_ */
