#pragma once
#ifndef PUZZLENODE_H
#define PUZZLENODE_H

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node // struct to represent nodes on the tree
{
	/*
	* the blank tile can move up to four different spots (from middle), hence there may be up to four child nodes on the tree
	*/
	Node* left;
	Node* midleft;
	Node* midright;
	Node* right;

	int hn; // h(n) = estimated distance to the goal
	int gn; // g(n) = cost to get to a node
	vector<vector<int>> currentBoard; // represents the game board at the node on the tree
};

class PuzzleNode
{
	/*
	* referenced https://stackoverflow.com/questions/16111337/declaring-a-priority-queue-in-c-with-a-custom-comparator on how to make custom comparison function
	* started with greater<int> example from https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/ and https://www.geeksforgeeks.org/implement-min-heap-using-stl/
	*/
	class customComparisonClass
	{
		public:
			bool operator()(Node* board1, Node* board2)
			{
				if (board1->hn + board1->gn > board2->hn + board2->gn) // compares f(n) = h(n) + g(n) values of the two boards
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
		priority_queue<Node*, vector<Node*>, customComparisonClass> gq; // referenced https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/ and https://www.geeksforgeeks.org/implement-min-heap-using-stl/ to make a min-heap using priority queue
		vector<vector<vector<int>>> visitedBoards; // vector of 2D vectors to store previous calculated game boards, used to prevent duplicate board calculations
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
