/*
 * priority_queue.h
 *
 *  Created on: Jan 29, 2020
 *      Author: amanda.salazar
 *
 *      The value of the PriorityQueue is to always have access to the vertex with the next shortest link
 *      in the shortest path calculation at the top of the queue.
 */

#ifndef HW2_PRIORITY_QUEUE_H_
#define HW2_PRIORITY_QUEUE_H_

#include<vector>
#include "graph.h"

class PriorityQueue {
public:
	PriorityQueue(const int &size);
	virtual ~PriorityQueue() = default;

	void chgPrioirity(const int &node, const int &priority); //changes the priority of queue element.
	void minPrioirty(); //removes the top element of the queue
	bool contains_node(const int &node);
	void insert(const int &node, const int &priority); //insert queue_element into queue (last position)
	int top(); //returns the top element of the queue
	int tail(); //returns the last element of the queue

	int size(); //return the number of queue_elements
	int get_priority(const int &node); //return the node priority
	void set_priority(const int &node,const int &priority); //sets node priority
	void priority_sort(); //sorts node_queue by priority


private:
	std::vector<int> node_queue; // Queue of nodes
	std::vector<int> node_priority; //Priority on nodes in the queue
};

#endif /* HW2_PRIORITY_QUEUE_H_ */
