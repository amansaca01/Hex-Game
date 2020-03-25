/*
 * hex_path.cpp
 *
 *  Created on: Mar 23, 2020
 *      Author: teletrabajo3.produccion
 */

#include "hex_path.h"
#include<iostream> //borrar

HexPath::HexPath(board* B, const color &col, const board_sides &sides) :
		hex_board(B), col(col), sides(sides) {
	connections.resize(hex_board->V(), 0);
}

bool HexPath::check_paths() {

	std::fill(connections.begin(), connections.end(), -1);

	for (auto &origin : sides.first) {
		if (connections.at(origin) < 0
				&& hex_board->get_node_color(origin) == col) {
			connections.at(origin) = origin;
			for (auto &target : sides.second) {
				if (hex_board->get_node_color(target) == col)
					if (check_neighbors(origin, origin, target)) {
						return true;
					}
			}
		}
	}
	return false;
}

bool HexPath::check_neighbors(const int &node, const int &origin,
		const int &target) {

	std::vector<int> adjacents = hex_board->neighbors(node, col);
	for (auto &ad : adjacents) {
		if (ad == target)
			return true;
		if (connections.at(ad) < 0) {
			connections.at(ad) = origin;
			if (check_neighbors(ad, origin, target))
				return true;
		}
	}
	return false;
}
