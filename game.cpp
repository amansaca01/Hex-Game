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
#include <algorithm>    // std::random_shuffle

game::game(const int &board_size) :
		hex_board(board_size) {

	std::vector<int> upper_side, lower_side, left_side, right_side;

	for (int i = 1; i <= board_size; ++i) {
		upper_side.push_back(i - 1);
		lower_side.push_back(pow(board_size, 2) - i);
		left_side.push_back((i - 1) * board_size);
		right_side.push_back(i * board_size - 1);
	}

	paths.push_back(
			HexPath(&hex_board, RED, make_pair(upper_side, lower_side)));
	paths.push_back(
			HexPath(&hex_board, BLUE, make_pair(left_side, right_side)));

	instructions();
	select_color();

}

void game::instructions() {
	hex_board.print_board();
	std::cout << "Instructions:" << std::endl;
	std::cout << "* Blue (o) must go from left to right side." << std::endl;
	std::cout << "* Red (x) must go from upper to lower side." << std::endl;
	std::cout << "* Blue (o) begins the game." << std::endl;
	std::cout << "* Columns are marked by letters and rows by numbers."
			<< std::endl;
	std::cout
			<< "* Insert your move by tiping the column and then the row (i.e, A1)."
			<< std::endl << std::endl;
}

void game::select_color() {
	int selection;
	std::cout << "1. Red" << std::endl;
	std::cout << "2. Blue" << std::endl << std::endl;

	std::cout << "Choose your color:";
	std::cin >> selection;
	selected_color = player_color(selection - 1);
}

void game::play() {

	square move;
	while (!winner()) {

		next_turn();
		if (player_color() == selected_color) {
			hex_board.print_board();
			move = read_move();
		} else {
			//move = random_move();
			move = choose_move();
		}

		make_move(move);
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
		std::cout << "Square " << move.first << move.second
				<< " is already in use." << std::endl
				<< "Your move should something like: A1" << std::endl;
		std::cin.clear();
		move = read_move();
	}
	return move;
}

square game::random_move() {
	auto moves = hex_board.free_squares();
	return moves.at(randomize.prob_int(0, moves.size() - 1));
}

void game::reset() {
	player = 0;
	hex_board.reset();
}

void game::make_move(const square &move) {
	hex_board.set_color(move, player_color());
}

void game::next_turn() {
	player = (player + 1) % 2;
	return;
}

bool game::winner() {

	if (paths.at(player).check_paths()) {
		hex_board.print_board();

		(player_color() == selected_color) ?
				std::cout << std::endl << ">>>> CONGRATULATIONS! <<<<<"
						<< std::endl :
				std::cout << std::endl << ">>>> GAME OVER! <<<<<" << std::endl;

		return true;
	}

	return false;
}

square game::choose_move() {
	blank_nodes = hex_board.free_nodes();
	std::vector<int> points;

	for (auto node = blank_nodes.begin(); node != blank_nodes.end(); ++node) {
		points.push_back(eval_move(node, player_color()));
	}

	auto best = std::max_element(points.begin(), points.end());

	return hex_board.get_square(
			blank_nodes.at(std::distance(points.begin(), best)));
}

int game::eval_move(std::vector<int>::iterator node_it, const color &col) {

	hex_board.mock_colors();
	std::vector<int> blanks = blank_nodes;
	int n = 1000;
	int wins = 0;
	int turn;

	for (int i = 0; i < n; ++i) {
		std::random_shuffle(blanks.begin(), blanks.end());

		turn = col - 1;
		hex_board.set_node_color(*node_it, col);

		for (auto &position : blanks) {
			if (position == *node_it)
				continue;
			turn = (turn + 1) % 2;
			hex_board.set_node_color(position, player_color(turn));
		}
		if (paths.at(col - 1).check_paths())
			wins++;
		hex_board.reset_colors();
	}

	return wins;
}

color game::player_color() {
	return (color) (player + 1);
}

color game::player_color(const int &a) {
	return (color) (a + 1);
}

