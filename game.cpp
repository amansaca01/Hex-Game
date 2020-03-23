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
		hex_board(board_size),connections(hex_board) {

	std::vector<int> upper_side,lower_side,left_side,right_side;

	for (int i = 1; i <= board_size; ++i) {
		upper_side.push_back(i-1);
		lower_side.push_back(pow(board_size, 2) - i);
		left_side.push_back((i-1) * board_size);
		right_side.push_back(i * board_size - 1);
	}

	sides[RED] = make_pair(upper_side, lower_side);
	sides[BLUE] = make_pair(left_side, right_side);

	instructions();
	select_color();

}

void game::instructions(){
	hex_board.print_board();
	std::cout << "Instructions:" << std::endl;
	std::cout << "* Blue (o) must go from left to right side." << std::endl;
	std::cout << "* Red (x) must go from upper to lower side." << std::endl;
	std::cout << "* Blue (o) begins the game." << std::endl;
	std::cout << "* Columns are marked by letters and rows by numbers." << std::endl;
	std::cout << "* Insert your move by tiping the column and then the row (i.e, A1)." << std::endl<< std::endl;
}

void game::select_color(){
	int selection;
	std::cout << "1. Red" << std::endl;
	std::cout << "2. Blue" << std::endl<< std::endl;

	std::cout << "Choose your color:" ;
	std::cin >> selection ;
	selected_color = player_color(selection-1);
}

void game::play() {

	square move;
	while (player != -1) {

		if (player_color()==selected_color) {
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

	pairs move = std::make_pair(x,y);

	if (!hex_board.is_free_square(move))
		move = random_move();

	return move;
}

void game::reset() {
	player = 0;
	rounds = 0;
	hex_board.reset();
}

void game::make_move(const square &move) {
	color col = player_color();
	hex_board.set_color(move, col);
}

int game::next_turn() {
	if (winner())
		return -1;
	return (player + 1) % 2;
}

bool game::winner() {

	auto side = sides[player_color()];
	if (connections.connected_sides(side, player_color()) > 0){
		hex_board.print_board();

		(player_color() == selected_color) ?
				std::cout << std::endl << ">>>> CONGRATULATIONS! <<<<<" << std::endl :
				std::cout << std::endl << ">>>> GAME OVER! <<<<<" << std::endl;

		return true;}

	return false;
}

color game::player_color() {
	return (color) (player + 1);
}

color game::player_color(const int &a) {
	return (color) (a + 1);
}
