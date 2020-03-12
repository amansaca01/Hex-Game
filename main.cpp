#include "game.h"
#include<iostream>
#include "random.h"

int main() {

	random_gen cosa;
	game hex(7);
	//hex.print_board();

	std::cout << int('a') << " " << int('A') << " "<< 'a' -'A' << " " <<char('a' -32)<< std::endl;

	hex.play();
	//hex.print_graph();
	return 0;
}
