#include "PuzzleNode.h"

PuzzleNode::PuzzleNode()
{
	head = nullptr;
	nodesExpanded = 0;
	goal = false;
}

Node* PuzzleNode::createPuzzle() // referenced https://www.geeksforgeeks.org/2d-vector-in-cpp-with-user-defined-size/ on how to create 2D vector with values
{
	Node* node = new Node;
	node->up = nullptr;
	node->left = nullptr;
	node->right = nullptr;
	node->down = nullptr;
	node->hn = 0;
	node->gn = 0;

	vector<vector<int>> custom
	{
		{ },
		{ },
		{ }
	};

	vector<int> customrow
	{
		{ }
	};

	custom.clear(); customrow.clear();
	int square1 = 0, square2 = 0, square3 = 0;

	cout << "\nEnter your own puzzle using 0 as the blank square. Put a space in between your numbers.\n";
	cout << "Enter the first row: ";
	cin >> square1 >> square2 >> square3;
	customrow.push_back(square1);
	customrow.push_back(square2);
	customrow.push_back(square3);
	custom.push_back(customrow);
	node->currentBoard.push_back(customrow);
	customrow.clear();
	cout << "Enter the second row: ";
	cin >> square1 >> square2 >> square3;
	customrow.push_back(square1);
	customrow.push_back(square2);
	customrow.push_back(square3);
	custom.push_back(customrow);
	node->currentBoard.push_back(customrow);
	customrow.clear();
	cout << "Enter the third row: ";
	cin >> square1 >> square2 >> square3;
	customrow.push_back(square1);
	customrow.push_back(square2);
	customrow.push_back(square3);
	custom.push_back(customrow);
	node->currentBoard.push_back(customrow);
	customrow.clear();
	cout << "\nYour game board is\n";
	for (int i = 0; i < custom.size(); i++)
	{
		for (int j = 0; j < custom.size(); j++)
		{
			cout << custom[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";

	head = node;

	gq.push(node);

	return node;
}

Node* PuzzleNode::defaultPuzzle() // referenced https://www.geeksforgeeks.org/2d-vector-in-cpp-with-user-defined-size/ on how to create 2D vector with values
{
	Node* node = new Node;
	node->up = nullptr;
	node->left = nullptr;
	node->right = nullptr;
	node->down = nullptr;
	node->hn = 0;
	node->gn = 0;

	vector<vector<int>> depth8
	{
		{1, 3, 6},
		{5, 0, 2},
		{4, 7, 8}
	};

	vector<int> depth8row1
	{
		{1, 3, 6}
	};
	vector<int> depth8row2
	{
		{5, 0, 2}
	};
	vector<int> depth8row3
	{
		{4, 7, 8}
	};

	cout << "\nThis is the default puzzle.\n";
	cout << "\nDepth 8\n";
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << depth8[i][j];
		}
		cout << "\n";
	}

	node->currentBoard.push_back(depth8row1);
	node->currentBoard.push_back(depth8row2);
	node->currentBoard.push_back(depth8row3);

	head = node;

	gq.push(node);

	return node;
}

void PuzzleNode::printNodes()
{
	Node* currentNode = head;
}

int PuzzleNode::countMisplacedTiles(vector<vector<int>> board, int algorithmChoice)
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

void PuzzleNode::search(Node* node, int queueingFunction)
{
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
	// remove top node in gq
	// push this node to a separate vector
	// check if the node was goal
	// expand the node by looking at its neighbors, set neighbor node gn = node->gn + 1 for all neighbors since every neighbor of the start node is 1 level down the "tree"
	// check if any neighbor is goal, then return success
	// apply misplacedTilesNum to each neighbor and add to gq if not in gq or second separate vector

	int algorithmChoice = queueingFunction;

	vector<vector<int>> finalState
	{
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 0}
	};

	int blankPosition = 0;

	for (int i = 0; i < finalState.size(); i++)
	{
		for (int j = 0; j < finalState.size(); j++)
		{
			blankPosition++;
		}
	}

	if (queueingFunction == 1) // - uniform cost search = bfs = A* with h(n) hardcoded to 0 https://www.geeksforgeeks.org/uniform-cost-search-dijkstra-for-large-graphs/
	{

	}
	else if (queueingFunction == 2) // - A* with misplaced tile heuristic = how many tiles on the board are wrong from desired goal state of while disregarding number of moves to move each number to correct position 
	{

	}
	else if (queueingFunction == 3) // - A* with Manhattan distance heuristic = how many moves are needed to move the wrong tiles into the correct spot while disregarding other tiles that may be in its way to move it to the correct position
	{

	}
}