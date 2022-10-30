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
			bool operator()(Node* board1, Node* board2)
			{
				if (board1->hn + board1->gn > board2->hn + board2->gn)
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
		int nodesExpanded;
		bool goal;
		priority_queue<Node*, vector<Node*>, customComparisonClass> gq; // referenced https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/ and https://www.geeksforgeeks.org/implement-min-heap-using-stl/ for how to make a min-heap using priority queue to put lowest f(n) = g(n) + h(n)
		vector<vector<vector<int>>> visitedBoards;
		int maxQueueSize;
		int solutionDepth;
	public:
		PuzzleNode();
		Node* createPuzzle();
		Node* defaultPuzzle();
		void printBoard(Node*);
		int countMisplacedTiles(vector<vector<int>>, int);
		bool search(Node*, int);
		void child(Node*, int, vector<vector<int>>);
		bool duplicateBoardChecker(vector<vector<int>>);
};
#endif
