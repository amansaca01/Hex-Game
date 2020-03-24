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

board::board(const int &board_size) :
		graph(pow(board_size, 2), 0), board_size(board_size) {

	for (int a = 0; a < V() - 1; a++) {
		if (((a + 1) % board_size) > 0)
			add_edge(a, a + 1, 1);
		if ((a + board_size) < V()) {
			if ((a % board_size) > 0) {
				add_edge(a, a + board_size - 1, 1);
			}
			add_edge(a, a + board_size, 1);
		}
	}
	add_edge(V() - 2, V() - 1, 1);

	marker.insert(std::make_pair(WHITE, "."));
	marker.insert(std::make_pair(RED, "x"));
	marker.insert(std::make_pair(BLUE, "o"));
}

int board::size() {
	return board_size;
}

void board::reset() {
	for (int x = 0; x < V(); ++x)
		set_node_color(x, WHITE);
}

int board::get_node(const square &move) const {
	int node = move.second * board_size + move.first;
	if (node < V())
		return node;
	else
		std::cout << "Coordinates (" << move.first << "," << move.second
				<< ") are out of bounds.";
	return -1;
}

color board::get_color(const square &move) const {
	int node = get_node(move);
	return get_node_color(node);
}

void board::set_color(const square &move, const color &col) {
	int node = get_node(move);
	set_node_color(node, col);
	return;
}

void board::print_board() {

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
			std::cout << marker[get_node_color(j++)] << " " << u8"—"<<" ";
		}
		std::cout << marker[get_node_color(j++)] << std::endl;
		print_repeat(i * 2 + 3, " ");
		if (j < V()) {
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
		return false;
	}
	return true;
}

std::vector<square> board::free_squares() {
	std::vector<square> squares;
	square move;
	for (int x = 0; x < size(); x++)
		for (int y = 0; y < size(); y++) {
			move = std::make_pair(x, y);
			if (is_free_square(move))
				squares.push_back(move);
		}
	return squares;
}

void board::mock_colors() {
	original_colors = node_color;
	return;
}


void board::reset_colors() {
	node_color=original_colors;
	return;
}
