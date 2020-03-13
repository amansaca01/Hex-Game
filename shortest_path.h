/*
 * shortest_path.h
 *
 *  Created on: Jan 29, 2020
 *      Author: amanda.salazar
 */

#ifndef HW2_SHORTEST_PATH_H_
#define HW2_SHORTEST_PATH_H_

#include "graph.h"
#include "priority_queue.h"

class ShortestPath {
public:
	ShortestPath(const graph &G);
	virtual ~ShortestPath() = default;
	std::vector<int> vertices(); //list of vertices in G(V,E)
	int path_size(const int &u, const int &w); //return the path cost associated with the shortest path
	bool connected_sides(
			const std::pair<std::vector<int>, std::vector<int>> &sides,
			const color &col);
	void djistra_algo(const int &u, const int &w); //computes de Djistra algorithm
	void djistra_algo(const int &u, const int &w, const color &col);

private:
	graph G; // graph on which the algorithm is being run

	std::vector<PriorityQueue> nodes_queues; //qeues un nodes in the closed set
};

#endif /* HW2_SHORTEST_PATH_H_ */
