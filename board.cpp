/*
 * board.cpp
 *
 *  Created on: Mar 3, 2020
 *      Author: amanda.salazar
 */

#include "board.h"
#include<iostream>
#include <math.h>
#include <numeric>
#include <map>

board::board(const int &board_size) :
		board_size(board_size), tablero(pow(board_size, 2) - 1, 0) {

	for (int a = 0; a < tablero.V() - 1; a++) {
		if (((a + 1) % board_size) > 0)
			tablero.add_edge(a, a + 1, 1);
		if ((a + board_size) < tablero.V()) {
			if ((a % board_size) > 0 && (a + board_size - 1) < tablero.V()) {
				tablero.add_edge(a, a + board_size - 1, 1);
			}
			tablero.add_edge(a, a + board_size, 1);
		}
	}
	tablero.add_edge(tablero.V() - 2, tablero.V() - 1, 1);
}

void board::reset() {
	for (int x = 0; x < tablero.V(); ++x)
		tablero.set_node_color(x, WHITE);
}

int board::get_node(const int &x, const int &y) {
	int node = x * board_size + y;
	if (node < tablero.V())
		return node;
	else
		std::cout << "Coordinates (" << x << "," << y << ") are out of bounds.";
	return -1;
}

color board::get_color(const int &node) {
	tablero.get_node_color(node);
}

void board::set_color(const int &node, color &col) {
	tablero.set_node_color(node, col);
}

void board::print_graph() {
	tablero.print_graph();
}

void board::print_board() {

	std::map<color, const char*> marker;
	marker.insert(std::make_pair(WHITE, "."));
	marker.insert(std::make_pair(RED, "x"));
	marker.insert(std::make_pair(BLUE, "o"));

	auto print_repeat = [] (int n,std::string x) {
		while (n--)
		std::cout << x;
	};

	std::vector<int> rows(board_size);
	std::iota(rows.begin(), rows.end(), 0);

	int j = 0;
	for (auto i : rows) {
		std::cout << i + 1;
		print_repeat(int(i < 9) + i * 2, " ");

		while (j < board_size * (i + 1) - 1) {
			std::cout << marker[tablero.get_node_color(j++)] << " " << u8"—"<<" ";
		}
		std::cout << marker[tablero.get_node_color(j++)] << std::endl;
		print_repeat(i * 2 + 3, " ");
		if (j < tablero.V()) {
			print_repeat(board_size - 1, "\\ / ");
			std::cout << "\\" << std::endl;
		}
	}
	std::cout << std::endl;
	print_repeat(board_size, "  ");
	for (auto i : rows)
		std::cout << char(i + 65) << "   ";
	std::cout << std::endl;
}
