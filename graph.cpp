/*
 * graph.cpp
 *
 *  Created on: Jan 27, 2020
 *      Author: amanda.salazar
 */

#include "graph.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<iterator>
#include <numeric> //acumulate

using namespace std;

graph::graph(const int &size, const float &density, const pairs &range) :
		size(size), range(range) {

	ad_matrix.resize(size, std::vector<int>(size, 0)); // initializes adjacents matrix with 0s

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < i; ++j) {
			if (prob() < density) {
				add_edge(i, j);
			}
		}
	}
}

graph::graph(const string file_name, const pairs &range) :
		range(range) {

	ifstream data_file(file_name);

	if (!data_file.is_open()) {
		throw(std::runtime_error("Unable to open file."));
	}

	data_file >> size;

	ad_matrix.resize(size, std::vector<int>(size, 0)); // initializes adjacents matrix with 0s

	int x, y, distance;
	while (!data_file.eof()) {
		data_file >> x >> y >> distance;
		add_edge(x, y, distance);
	}

}

float graph::prob() {
	return rand() / static_cast<float>(RAND_MAX);
}

int graph::prob_int(const pairs &range) {
	int total_range = range.second - range.first + 1;
	return (rand() % total_range) + range.first;
}

int graph::V() const {
	return size;
}
int graph::E() {

	int edges = 0;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < i; ++j) {
			if (adjacent(i, j))
				edges++;
		}
	}

	return edges;
}

bool graph::adjacent(const int &x, const int &y) const {
	return ad_matrix[x][y] != 0;
}

std::vector<int> graph::neighbors(const int &x) {
	std::vector<int> adjacents;
	for (int i = 0; i < size; ++i) {
		if (adjacent(x, i))
			adjacents.push_back(i);
	}
	return adjacents;
}

void graph::add_edge(const int &x, const int &y) {
	add_edge(x, y, prob_int(range));
}

void graph::add_edge(const int &x, const int &y, const int &distance) {
	if (x > V() || y > V())
		std::cout << "LLamada a nodos fuera de la matriz en add_edge."
				<< std::endl;
	else if (!adjacent(x, y) && x != y) {
		ad_matrix[x][y] = distance;
		ad_matrix[y][x] = distance;
	}
}

void graph::delete_edge(const int &x, const int &y) {
	if (adjacent(x, y)) {
		ad_matrix[x][y] = 0;
		ad_matrix[y][x] = 0;
	}
}

int graph::get_edge_value(const int &x, const int &y) const {
	if (adjacent(x, y))
		return ad_matrix[x][y];
	return 0; // returns 0 if there is no edge
}

void graph::set_edge_value(const int &x, const int &y, const int &distance) {
	if (adjacent(x, y)) {
		ad_matrix[x][y] = distance;
		ad_matrix[y][x] = distance;
	}
}

int graph::get_edge_id(const int &x, const int &y) {
	return x * size + y;

}

pairs graph::get_nodes(const int &edge_id) {
	int x = edge_id / size;
	int y = edge_id - size * x;

	return std::make_pair(x, y);
}

bool graph::is_looped() {
	for (int i = 0; i < size; ++i) {
		if (ad_matrix[i][i] != 0)
			return false;
	}
	return true;
}

int graph::tree_cost() {
	int cost = 0;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < i; ++j) {
			cost += ad_matrix[i][j];
		}
	}
	return cost;
}

void graph::print_graph() {

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			cout << ad_matrix[i][j] << " ";
		}
		cout << endl;
	}
}
