/*
 * graph.h
 *
 *  Created on: Jan 27, 2020
 *      Author: amanda.salazar
 */

#include<vector>
#include <string>
#include "random.h"

#ifndef GRAPH_H_
#define GRAPH_H_

typedef std::pair<int, int> pairs;

enum color {
	WHITE, RED, BLUE
};

class graph {
public:
	graph(const int &size = 1, const float &density = 0, const pairs &range =
			std::make_pair(1, 10));
	graph(const std::string file_name,
			const pairs &range = std::make_pair(1, 10));
	virtual ~graph() = default;

	int V() const; //returns the number of vertices in the graph
	int E(); //returns the number of edges in the graph
	bool adjacent(const int &x, const int &y) const; //tests whether there is an edge from node x to node y.
	bool adjacent(const int &x, const int &y, const color &col) const;
	std::vector<int> neighbors(const int &x); //lists all nodes y such that there is an edge from x to y.
	std::vector<int> neighbors(const int &x, const color &col);
	void add_edge(const int &x, const int &y); //adds the edge from x to y, if it is not there
	void add_edge(const int &x, const int &y, const int &distance); //adds the edge from x to y a certain distance
	void delete_edge(const int &x, const int &y); //removes the edge from x to y, if it is there.
	int get_edge_value(const int &x, const int &y) const; //returns the value associated to the edge (x,y).
	void set_edge_value(const int &x, const int &y, const int &distance); //sets the value associated to the edge (x,y) to v.
	int get_edge_id(const int &x, const int &y); // returns an ID for a graph
	pairs get_nodes(const int &edge_id); // gets the nodes that an edge connects
	color get_node_color(const int &x) const;
	void set_node_color(const int &x, const color &col);
	bool is_looped();
	int tree_cost(); // return the sum of all edge values
	void print_graph() const;

protected:
	std::vector<color> node_color;

private:
	std::vector<std::vector<int>> ad_matrix; // connectivity matrices are used
	int size; // number of nodes
	pairs range; // pair containing upper and lower edges distance range
	random_gen randomize;
};

#endif /* GRAPH_H_ */
