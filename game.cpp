/*
 * game.cpp
 *
 *  Created on: Mar 5, 2020
 *      Author: amanda.salazar
 */

#include "game.h"

#include<iostream>
#include <numeric>
#include <math.h>

game::game(const int &board_size) :
		hex_board(board_size) {

	std::map<color, std::pair<std::vector<int>, std::vector<int>>> marker;

	std::vector<int> line(board_size);

	std::iota(line.begin(), line.end(), 0);
	std::vector<int> left_side = line;

	std::iota(line.begin(), line.end(), pow(board_size, 2) - 1);
	std::vector<int> right_side = line;

	sides[RED] = make_pair(left_side, right_side);

	int i = 0;
	std::iota(line.begin(), line.end(), i = i + board_size);
	std::vector<int> upper_side = line;

	i = board_size - 1;
	std::iota(line.begin(), line.end(), i = i + board_size);
	std::vector<int> lower_side = line;

	sides[BLUE] = make_pair(upper_side, lower_side);

}

void game::play() {
	square move;
	while (player != -1) {

		if (player) {
			hex_board.print_board();
			move = read_move();
		} else {
			move = random_move();
		}

		make_move(move);
		player = next_turn();
	}

}

square game::read_move() {
	char x;
	int y;

	std::cout << std::endl << "Your move: ";
	std::cin >> x >> y;
	if (x > 96)
		x = char(x - 32);

	square move = std::make_pair(x - 65, y - 1);

	if (!hex_board.is_free_square(move)) {
		std::cout << "Your move should something like: A1" << std::endl;
		std::cin.clear();
		move = read_move();
	}
	return move;
}

square game::random_move() {

	int x = randomize.prob_int(0, hex_board.size() - 1);
	int y = randomize.prob_int(0, hex_board.size() - 1);

	return std::make_pair(x, y);
}

void game::reset() {
	player = 0;
	rounds = 0;
	hex_board.reset();
}

void game::make_move(const square &move) {
	color col = player_color();
	std::cout << "Player " << col << " " << move.first << " " << move.second
			<< std::endl;
	hex_board.set_color(move, col);
}

int game::next_turn() {
	if (winner())
		return -1;
	return (player + 1) % 2;
}

bool game::winner() {

	auto side = sides[player_color()];
	if (hex_board.connections().connected_sides(side, player_color()) > 0)
		return true;

	return false;
}

color game::player_color() {
	return (color) (player + 1);
}
