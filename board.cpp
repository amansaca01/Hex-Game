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

int board::size() {
	return board_size;
}

void board::reset() {
	for (int x = 0; x < tablero.V(); ++x)
		tablero.set_node_color(x, WHITE);
}

int board::get_node(const square &move) {
	int node = move.second * board_size + move.first;
	if (node < tablero.V())
		return node;
	else
		std::cout << "Coordinates (" << move.first << "," << move.second << ") are out of bounds.";
	return -1;
}

color board::get_color(const square &move) {
	int node = get_node(move);
	return tablero.get_node_color(node);
}

void board::set_color(const square &move, color &col) {
	int node = get_node(move);
	return tablero.set_node_color(node, col);
}

void board::print_graph() {
	return tablero.print_graph();
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

bool board::is_square(const square &move) {

	auto check_range = [this] (int i) {return (i >= 0 && i < board_size);};

	if (!check_range(move.first)) {
		std::cout << "Row is not valid, should be between A and "
				<< char(64 + board_size) << std::endl;
		return false;
	}
	if (!check_range(move.second)) {
		std::cout << "Column is not valid, should be between 1 and "
				<< board_size << std::endl;
		return false;
	}
	return true;
}

bool board::is_free_square(const square &move) {
	if (!is_square(move))
		return false;
	if (get_color(move) != WHITE) {
		std::cout << "Square " << move.first << move.second
				<< " is already in use." << std::endl;
		return false;
	}
	return true;
}

