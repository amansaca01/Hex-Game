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

using namespace std;

board::board(const int &board_size) :
		board_size(board_size), tablero(pow(board_size, 2), 0) {
//	for (int a = 0; a < tablero.V() - 1; a++) {
//		if (((a + 1) % board_size) > 0)
//			tablero.add_edge(a, a + 1, 1);
//		if ((a + board_size) < tablero.V()) {
//			if ((a % board_size) > 0 && (a + board_size - 1) < tablero.V()) {
//				tablero.add_edge(a, a + board_size - 1, 1);
//			}
//			tablero.add_edge(a, a + board_size, 1);
//		}
//	}
//	tablero.add_edge(tablero.V() - 2, tablero.V() - 1, 1);
}

graph board::get_tablero() {
	return tablero;
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

void board::set_color(const int &node, const color &col) {

	// rellena el vector node_color. No hace nada más
	tablero.set_node_color(node, col);

	// edita la matriz de adyacencia en consecuencia
//	int near_node = node - 1;
//	if (tablero.get_node_color(near_node) == col) {
//		tablero.add_edge(node, near_node, 1);
//	}
	vector<int> near_nodes;
	// arriba
	near_nodes.push_back(node - board_size);
	near_nodes.push_back(node - board_size + 1);
	// a los lados
	near_nodes.push_back(node - 1);
	near_nodes.push_back(node + 1);
	// abajo
	near_nodes.push_back(node + board_size - 1);
	near_nodes.push_back(node + board_size);

	for (int &it : near_nodes) {
		if (tablero.get_node_color(it) == col) {
			tablero.add_edge(node, it, 1);
		}
	}

	cout << "Player " << col << " moves to hex " << node << ":" << endl;
}

int board::north_to_south() {
	// Ver si existe un camino ROJO de Norte a Sur (north_to_south)
	ShortestPath camino(tablero);
	for (int i = 0; i < board_size; ++i) {
		for (int j = board_size; j > 0; --j) {
			int north = i;
			int south = tablero.V() - j;
			if (tablero.get_node_color(north) == RED
					&& tablero.get_node_color(south) == RED) {
				int distance = camino.path_size(north, south);
				if (distance != -1) {
					cout << "---> GAME OVER <---" << endl;
					//				cout << "La distancia de " << north << " a " << south << " es "
					//						<< distance << endl;
					cout << "There is a red path from ("
							<< (north / board_size) + 1 << ","
							<< (north % board_size) + 1 << ") to ("
							<< (south / board_size) + 1 << ","
							<< (south % board_size) + 1 << ") of distance "
							<< distance << "." << endl;
					cout << "The winner is player 2: the red player (R)."
							<< endl;
					exit(EXIT_SUCCESS);
				}
			}
		}
	}
	return 0;
}

void board::west_to_east() {
	// Ver si existe un camino  AZUL de Oeste a Este (west_to_east)
	ShortestPath camino(tablero);
	for (int i = 0; i < board_size; ++i) {
		for (int j = 1; j < board_size + 1; ++j) {
			int west = i * board_size;
			int east = (j * board_size) - 1;
			if (tablero.get_node_color(west) == BLUE
					&& tablero.get_node_color(east) == BLUE) {
				int distance = camino.path_size(west, east);
				if (distance != -1) {
					cout << "---> GAME OVER <---" << endl;
//			cout << "La distancia de " << west << " a " << east << " es "
//					<< distance << endl;
					cout << "There is a red path from ("
							<< (west / board_size) + 1 << ","
							<< (west % board_size) + 1 << ") to ("
							<< (east / board_size) + 1 << ","
							<< (east % board_size) + 1 << ") of distance "
							<< distance << "." << endl;
					cout << "The winner is player 1: the blue player (B)."
							<< endl;
					exit(EXIT_SUCCESS);
				}
			}
		}
	}
}

void board::print_graph() {
	tablero.print_graph();
}

void board::print_board() {

	std::map<color, const char*> marker;
	marker.insert(std::make_pair(WHITE, "."));
	marker.insert(std::make_pair(RED, "R"));
	marker.insert(std::make_pair(BLUE, "B"));

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
		std::cout << i + 1 << "   ";
	std::cout << std::endl;
	std::cout << std::endl;
}
