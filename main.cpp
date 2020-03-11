#include "graph.h"
#include "priority_queue.h"
#include "shortest_path.h"

#include "game.h"

#include <iostream>
using namespace std;

int main() {

	int size = 3;
	board hex(size);

	// Introducir un movimiento
//	hex.set_color(1, BLUE);
//	hex.set_color(4, BLUE);
//	hex.set_color(7, BLUE);

	hex.set_color(3, BLUE);
	hex.set_color(4, BLUE);
	hex.set_color(5, BLUE);

	hex.set_color(1, RED);
	hex.set_color(4, RED);
	hex.set_color(7, RED);

	// Print
	hex.print_board();
//	hex.print_graph();

// Check if player 1 (player blue, B, X) has won
	hex.west_to_east();
	// Check if player 2 (player red, R, X) has won
	hex.north_to_south();	//hex.get_tablero()

//	1. Draw the board using ASCII symbols and a given size, such as 7 by 7 or 11 by 11.

//	2. Input a move and determine if a move is legal.
//	A simple way to input a move would be to have the player enter an (i,j) coordinate corresponding to a currently empty hexagon

//	and have the program check that this is legal and if not ask for another choice.

//	3. Determine who has won.
//	hex.print_graph();

	return 0;
}
