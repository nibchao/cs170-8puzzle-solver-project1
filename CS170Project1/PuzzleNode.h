#pragma once
#ifndef PUZZLENODE_H
#define PUZZLENODE_H

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node
{
	Node* left;
	Node* midleft;
	Node* midright;
	Node* right;
	int hn; // h(n) = estimated distance to the goal
	int gn; // g(n) = cost to get to a node
	vector<vector<int>> currentBoard;
};

class PuzzleNode
{
	class customComparisonClass // referenced https://stackoverflow.com/questions/16111337/declaring-a-priority-queue-in-c-with-a-custom-comparator on how to make custom comparison function instead of default greater<int> from other priority queue source i referenced
	{
		public:
			bool operator()(Node* node1, Node* node2)
			{
				if (node1->hn + node1->gn > node2->hn + node2->gn)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
	};
	private:
		Node* head;
		int nodesExpanded;
		bool goal;
		priority_queue<Node*, vector<Node*>, customComparisonClass> gq; // referenced https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/ and https://www.geeksforgeeks.org/implement-min-heap-using-stl/ for how to make a min-heap using priority queue to put lowest f(n) = g(n) + h(n)
		vector<Node*> visitedNodes;
		vector<vector<vector<int>>> visitedBoards;
	public:
		PuzzleNode();
		Node* createPuzzle();
		Node* defaultPuzzle();
		void printNodes();
		int countMisplacedTiles(vector<vector<int>>, int);
		bool search(Node*, int);
		void left(Node*, int, vector<vector<int>>);
		void midleft(Node*, int, vector<vector<int>>);
		void midright(Node*, int, vector<vector<int>>);
		void right(Node*, int, vector<vector<int>>);
		bool duplicateBoardChecker(vector<vector<int>>);
};
#endif
