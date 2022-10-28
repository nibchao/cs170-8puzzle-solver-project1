#pragma once
#ifndef PUZZLENODE_H
#define PUZZLENODE_H

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class PuzzleNode
{
	private:
		struct Node
		{
			int value;
			Node* up;
			Node* left;
			Node* right;
			Node* down;
			int hn; // h(n) = estimated distance to the goal
			int gn; // g(n) = cost to get to a node
		};
		Node* head;
		int algorithmChoice;
		int nodesExpanded;
		bool goal;
		priority_queue<Node*, vector<Node*>, greater<int>> gq; // referenced https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/ and https://www.geeksforgeeks.org/implement-min-heap-using-stl/ for how to make a min-heap using priority queue to put lowest f(n) = g(n) + h(n)
		vector<Node*> visitedNodes;
	public:
		PuzzleNode();
		void addNode(int);
		void printNodes();
		void setAlgorithmChoice(int);
		int countMisplacedTiles(vector<vector<int>>);
		void search(Node*);
};

#endif
