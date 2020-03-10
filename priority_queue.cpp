/*
 * priority_queue.cpp
 *
 *  Created on: Jan 29, 2020
 *      Author: amanda.salazar
 */

#include "priority_queue.h"

#include <iostream>
#include<vector>
#include <algorithm>

#include "graph.h"

PriorityQueue::PriorityQueue(const int &size) {
	node_priority.resize(size,0);
}

void PriorityQueue::chgPrioirity(const int &node, const int &priority) {
	if (contains_node(node)) {
		node_priority[node] = priority;

	}
}

void PriorityQueue::minPrioirty() {
	node_queue.erase(node_queue.begin());
}

bool PriorityQueue::contains_node(const int &node) {
	return std::find(node_queue.begin(), node_queue.end(), node)
			!= node_queue.end();
}
void PriorityQueue::insert(const int &node, const int &priority) {

	if (!contains_node(node)) {
		node_queue.push_back(node);
		chgPrioirity(node, priority);
	} else {
		if (get_priority(node) > priority)
			chgPrioirity(node, priority);
	}
}

int PriorityQueue::top() {
	return node_queue.front();
}

int PriorityQueue::tail() {
	return node_queue.back();
}

int PriorityQueue::size() {
	return node_queue.size();
}

int PriorityQueue::get_priority(const int &node) {
	return node_priority.at(node);

}

void PriorityQueue::priority_sort() {

	std::sort(node_queue.begin(), node_queue.end(),
			[this](int i, int j) {return get_priority(i)<get_priority(j);});

}
