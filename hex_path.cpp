/*
 * hex_path.cpp
 *
 *  Created on: Mar 23, 2020
 *      Author: teletrabajo3.produccion
 */

#include "hex_path.h"

HexPath::HexPath(const board &B, const color &col, const board_sides &sides) :
		hex_board(B), col(col), sides(sides) {
	connections.resize(hex_board.V(), 0);
}

bool HexPath::check_new(const int &new_node) {

	if (get_node_color(origin) != col || get_node_color(new_node) != col)
		return false;

	for (auto &origin : sides.first) {
		if (is_connected(origin, new_node))
			return is_connected(x, sides.second);

	}
	return false;
}

bool HexPath::is_connected(const int &x, const int &y) {

	if (get_node_color(x) != col || get_node_color(y) != col)
		return false;

	check_neighbours(hex_board.neighbors(x, col), x, y);

	return false;
}

bool HexPath::check_neighbours(const std::vector<int> &adjacents,
		const int &origin, const int &target) {

	for (auto &node : adjacents) {
		if (connections.at(node) == 0) {
			connections.at(node) = origin;
			if (node == target
					|| check_neighbours(hex_board.neighbors(node, col), origin,
							target))
				return true;
		}
	}
	return false;
}
