#include "PuzzleNode.h"

PuzzleNode::PuzzleNode()
{
	head = nullptr;
	algorithmChoice = 0;
	nodesExpanded = 0;
	goal = false;
}

void PuzzleNode::addNode(int number)
{
	Node* node = new Node;
	node->value = number;
	node->up = nullptr;
	node->left = nullptr;
	node->right = nullptr;
	node->down = nullptr;
	node->hn = 0;
	node->gn = 0;

	if (head == nullptr)
	{
		head = node;
	}

	gq.push(node);
}

void PuzzleNode::printNodes()
{
	Node* currentNode = head;
}

void PuzzleNode::setAlgorithmChoice(int algorithmNumber)
{
	algorithmChoice = algorithmNumber;
	if (algorithmChoice == 1)
	{ 
		cout << algorithmChoice << " was selected. Solving the puzzle using Uniform Cost Search.\n\n";
	}
	else if (algorithmChoice == 2)
	{
		cout << algorithmChoice << " was selected. Solving the puzzle using Misplaced Tile Heuristic.\n\n";
	}
	else if (algorithmChoice == 3)
	{
		cout << algorithmChoice << " was selected. Solving the puzzle using Manhattan Distance Heuristic.\n\n";
	}
}

int PuzzleNode::countMisplacedTiles(vector<vector<int>> board)
{
	vector<vector<int>> finalState
	{
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 0}
	};

	int misplacedTilesNum = 0;

	if (algorithmChoice == 1) // h(x) is hardcoded to 0 for uniform cost search
	{
		return 0;
	}
	else if (algorithmChoice == 2) // misplaced tiles calculation
	{
		for (int i = 0; i < finalState.size(); i++)
		{
			for (int j = 0; j < finalState.size(); j++)
			{
				if (board[i][j] != finalState[i][j])
				{
					misplacedTilesNum++;
				}
			}
		}
	}
	else if (algorithmChoice == 3) // manhattan distance calculation, referenced https://stackoverflow.com/questions/25611622/how-to-access-to-the-index-of-a-2d-vector-by-at-function to get "xy" coordinates of indices for the contents of the boards
	{
		for (int x2 = 0; x2 < finalState.size(); x2++)
		{
			for (int y2 = 0; y2 < finalState.size(); y2++)
			{
				for (int x1 = 0; x1 < finalState.size(); x1++)
				{
					for (int y1 = 0; y1 < finalState.size(); y1++)
					{
						if (finalState.at(x2).at(y2) == board.at(x1).at(y1))
						{
							misplacedTilesNum += (abs(x2 - x1) + abs(y2 - y1));
						}
					}
				}
			}
		}
	}
	return misplacedTilesNum;
}

void PuzzleNode::search(Node* node)
{
	if (algorithmChoice == 1) // - uniform cost search = bfs = A* with h(n) hardcoded to 0 https://www.geeksforgeeks.org/uniform-cost-search-dijkstra-for-large-graphs/
	{

	}
	else if (algorithmChoice == 2) // - A* with misplaced tile heuristic = how many tiles on the board are wrong from desired goal state of while disregarding number of moves to move each number to correct position 
	{

	}
	else if (algorithmChoice == 3) // - A* with Manhattan distance heuristic = how many moves are needed to move the wrong tiles into the correct spot while disregarding other tiles that may be in its way to move it to the correct position
	{

	}
}

/*
*
* function general-search(problem, queueing-function)
* {
*	nodes = make-queue(make-node(problem.initial-state);
*	loop do
*	{
*		if empty(nodes)
*		{
*			return fail;
*		}
*		node = remove-front(nodes);
*		if problem.goal-test(node.state)
*		{
*			return node;
*		}
*		nodes = queueing-function(nodes, expand(node, problem operators));
*	}
*/