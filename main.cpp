//	1. Draw the board using ASCII symbols and a given size, such as 7 by 7 or 11 by 11.

//	2. Input a move and determine if a move is legal.
//	A simple way to input a move would be to have the player enter an (i,j) coordinate corresponding to a currently empty hexagon
//	and have the program check that this is legal and if not ask for another choice.

//	3. Determine who has won.
//	hex.print_graph();

#include "graph.h"
#include "priority_queue.h"
#include "shortest_path.h"
#include "game.h"

#include <iostream>
#include <ctime>
#include <math.h>
#include <numeric>

using namespace std;

int main() {

	srand(time(NULL));

	//	1. Draw the board using ASCII symbols and a given size, such as 7 by 7 or 11 by 11.
	int size = 3;
	int N = pow(size, 2) - 1;
	board hex(size);
	// Print
	cout << "The game starts: " << endl;
	hex.print_board();

	int it = 0;
	while (hex.north_to_south() == 0 && it <= N) {

		// PLAYER 1: BLUE (B)
		//	2. Input a move and determine if a move is legal.
		int blue_node = (rand() % N) + 1;
		while (hex.get_tablero().get_node_color(blue_node) != WHITE) {
			blue_node = (rand() % N) + 1;
		}
		hex.set_color(blue_node, BLUE);
		// Print
		hex.print_board();
		//	3. Determine who has won.
		// Check if player 1 (player blue, B) has won
		hex.west_to_east();

		// PLAYER 2: RED (R)
		//	2. Input a move and determine if a move is legal.
		int red_node = (rand() % N) + 1;
		while (hex.get_tablero().get_node_color(red_node) != WHITE) {
			red_node = (rand() % N) + 1;
		}
		hex.set_color(red_node, RED);
		// Print
		hex.print_board();
		// Check if player 2 (player red, R) has won
		hex.north_to_south();
		it++;
	}
	cout << "The game has ended with " << it
			<< " moves and the following associated graph:" << endl;
	hex.print_graph();
	return 0;
}
