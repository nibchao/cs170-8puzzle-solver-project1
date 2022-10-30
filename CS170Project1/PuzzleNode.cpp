#include "PuzzleNode.h"

vector<vector<int>> finalState // represents the goal board state
{
	{1, 2, 3 },
	{4, 5, 6 },
	{7, 8, 0 }
};

PuzzleNode::PuzzleNode() // constructor
{
	nodesExpanded = 0;
	maxQueueSize = 0;
	solutionDepth = 0;
	head = nullptr;
}

/*
* referenced https://www.geeksforgeeks.org/2d-vector-in-cpp-with-user-defined-size/ on how to create 2D vector with values
* creates puzzle using user's inputted values
* assumes user always inputs correct values, so program will break if any incorrect value is inputted
*/
Node* PuzzleNode::createPuzzle()
{
	Node* node = new Node;
	node->left = nullptr; node->midleft = nullptr; node->midright = nullptr; node->right = nullptr;
	node->hn = 0; node->gn = 0;

	vector<vector<int>> custom;
	vector<int> customrow;

	int square1 = 0, square2 = 0, square3 = 0;

	cout << "\nEnter your own puzzle using 0 as the blank square. Put a space in between your numbers.\n";
	for (int cnt = 0; cnt < finalState.size(); cnt++)
	{
		cout << "Enter row " << cnt + 1 << ": ";
		cin >> square1 >> square2 >> square3;
		customrow.push_back(square1); customrow.push_back(square2); customrow.push_back(square3);
		custom.push_back(customrow);
		node->currentBoard.push_back(customrow);
		customrow.clear();
	}
	cout << "\nThis is the puzzle you entered.\n";
	printBoard(node);
	head = node;
	gq.push(node);
	return node;
}

/*
* referenced https://www.geeksforgeeks.org/2d-vector-in-cpp-with-user-defined-size/ on how to create 2D vector with values
* uses hardcoded puzzle board for program
*/
Node* PuzzleNode::defaultPuzzle()
{
	Node* node = new Node;
	node->left = nullptr; node->midleft = nullptr; node->midright = nullptr; node->right = nullptr;
	node->hn = 0; node->gn = 0;

	vector<vector<int>> depth8
	{
		{1, 3, 6},
		{5, 0, 2},
		{4, 7, 8}
	};
	node->currentBoard.push_back(depth8[0]);
	node->currentBoard.push_back(depth8[1]);
	node->currentBoard.push_back(depth8[2]);
	cout << "\nThis is the default puzzle of depth 8.\n";
	printBoard(node);
	head = node;
	gq.push(node);
	return node;
}

/*
* prints g(n) and h(n) of current tree node and also prints its game board
*/
void PuzzleNode::printBoard(Node* node)
{
	if (head)
	{
		cout << "The best state to expand with a g(n) = " << node->gn << " and h(n) = " << node->hn << " is...\n";
	}
	for (int i = 0; i < node->currentBoard.size(); i++)
	{
		for (int j = 0; j < node->currentBoard.size(); j++)
		{
			cout << node->currentBoard[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

/*
* counts number of incorrect tiles from goal board
* depending on queueingFunction, it changes how it counts the number of incorrect tiles
*/
int PuzzleNode::countMisplacedTiles(vector<vector<int>> board, int queueingFunction)
{
	int misplacedTilesNum = 0;
	if (queueingFunction == 2) // misplaced tiles calculation
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
	else if (queueingFunction == 3) // manhattan distance calculation, referenced https://stackoverflow.com/questions/25611622/how-to-access-to-the-index-of-a-2d-vector-by-at-function to get "xy" coordinates of indices for the contents of the boards
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

/*
* referenced https://www.gatevidyalay.com/tag/a-algorithm-for-8-puzzle-problem/ to better understand A* and how to implement
* main search function of program, roughly follows the pseudocode for general search algorithm
*/
bool PuzzleNode::search(Node* node, int queueingFunction)
{
	if (gq.empty())
	{
		cout << "fail";
		return false;
	}
	gq.pop();
	if (node->currentBoard == finalState)
	{
		cout << "Goal!\n";
		cout << "Max Solution Depth: " << solutionDepth << "\n";
		cout << "Nodes Expanded: " << nodesExpanded << "\n";
		cout << "Max Queue Size: " << maxQueueSize << "\n";
		
		return true;
	}
	int blankTilePosition = getBlankTilePosition(node);
	queue(node, queueingFunction, blankTilePosition);
	search(gq.top(), queueingFunction);
	return false;
}

/*
* function that creates a new child node containing the board with swapped values and g(n) + 1 to represent one level "deeper" on the tree
*/
void PuzzleNode::child(Node* node, int queueingFunction, vector<vector<int>> board)
{
	if (!duplicateBoardChecker(board)) // checks if the swapped board is duplicate or not; if it is, don't create a new node
	{
		Node* swapBoard = new Node;
		swapBoard->currentBoard = board;
		swapBoard->hn = countMisplacedTiles(swapBoard->currentBoard, queueingFunction);
		swapBoard->gn = node->gn + 1;
		if (node->left == nullptr)
		{
			node->left = swapBoard;
		}
		else if (node->midleft == nullptr)
		{
			node->midleft = swapBoard;
		}
		else if (node->midright == nullptr)
		{
			node->midright = swapBoard;
		}
		else if (node->right == nullptr)
		{
			node->right = swapBoard;
		}
		visitedBoards.push_back(board);
		gq.push(swapBoard);
		nodesExpanded++;
	}
}

/*
* checks for duplicate boards by looping through a vector containing 2D vectors and searches for any matches with passed in board parameter
*/
bool PuzzleNode::duplicateBoardChecker(vector<vector<int>> board)
{
	for (int cnt = 0; cnt < visitedBoards.size(); cnt++)
	{
		if (visitedBoards[cnt] == board)
		{
			return true;
		}
	}
	return false;
}

/*
* referenced https://stackoverflow.com/questions/9695902/how-to-break-out-of-nested-loops to implement stop to break out of nested for-loop
* used idea of moving the blank tile instead of a number to achieve goal
* this loop finds the index of the 0 "blank" tile in the current node's game board
*/
int PuzzleNode::getBlankTilePosition(Node* node)
{
	int blankPosition = 0;
	bool stop = false;
	for (int i = 0; i < finalState.size() && !stop; i++)
	{
		for (int j = 0; j < finalState.size() && !stop; j++)
		{
			if (node->currentBoard[i][j] == 0)
			{
				stop = true;
				break;
			}
			if (stop)
			{
				break;
			}
			blankPosition++;
		}
	}
	return blankPosition;
}

/*
* board is [y, x] instead of [x, y]
*
* [ 0, 0 ], [ 0, 1 ], [ 0, 2 ]
* [ 1, 0 ], [ 1, 1 ], [ 1, 2 ]
* [ 2, 0 ], [ 2, 1 ], [ 2, 2 ]
*
* the nodes = "QUEUEING-FUNCTION" line is represented by this lengthy if-else if chain
* creates clone game boards then swaps certain values depending on the neighbors of the 0 "blank" tile
* sets the current node's childs (up to 4 child nodes) equal to a new node with the swapped game board values
*/
void PuzzleNode::queue(Node* node, int queueingFunction, int blankPosition)
{
	
	if (blankPosition == 0) // blank is [0, 0] top left - check [0, 1] and [1, 0]
	{
		vector<vector<int>> swap01 = node->currentBoard;
		vector<vector<int>> swap10 = swap01;

		swap(swap01[0][0], swap01[0][1]);
		swap(swap10[0][0], swap10[1][0]);

		child(node, queueingFunction, swap01);
		child(node, queueingFunction, swap10);
	}
	else if (blankPosition == 1) // blank is [0, 1] top middle - check [0, 0], [0, 2], [1, 1]
	{
		vector<vector<int>> swap00 = node->currentBoard;
		vector<vector<int>> swap02 = swap00;
		vector<vector<int>> swap11 = swap00;

		swap(swap00[0][1], swap00[0][0]);
		swap(swap02[0][1], swap02[0][2]);
		swap(swap11[0][1], swap11[1][1]);

		child(node, queueingFunction, swap00);
		child(node, queueingFunction, swap02);
		child(node, queueingFunction, swap11);
	}
	else if (blankPosition == 2) // blank is [0, 2] top right - check [0, 1], [1, 2]
	{
		vector<vector<int>> swap01 = node->currentBoard;
		vector<vector<int>> swap12 = swap01;

		swap(swap01[0][2], swap01[0][1]);
		swap(swap12[0][2], swap12[1][2]);

		child(node, queueingFunction, swap01);
		child(node, queueingFunction, swap12);
	}
	else if (blankPosition == 3) // blank is [1, 0] middle left - check [0, 0], [1, 1], [2, 0]
	{
		vector<vector<int>> swap00 = node->currentBoard;
		vector<vector<int>> swap11 = swap00;
		vector<vector<int>> swap20 = swap00;

		swap(swap00[1][0], swap00[0][0]);
		swap(swap11[1][0], swap11[1][1]);
		swap(swap20[1][0], swap20[2][0]);

		child(node, queueingFunction, swap00);
		child(node, queueingFunction, swap11);
		child(node, queueingFunction, swap20);
	}
	else if (blankPosition == 4) // blank is [1, 1] middle - check [1, 0], [0, 1], [1, 2], [2, 1]
	{
		vector<vector<int>> swap10 = node->currentBoard;
		vector<vector<int>> swap01 = swap10;
		vector<vector<int>> swap12 = swap10;
		vector<vector<int>> swap21 = swap10;

		swap(swap10[1][1], swap10[1][0]);
		swap(swap01[1][1], swap01[0][1]);
		swap(swap12[1][1], swap12[1][2]);
		swap(swap21[1][1], swap21[2][1]);

		child(node, queueingFunction, swap10);
		child(node, queueingFunction, swap01);
		child(node, queueingFunction, swap12);
		child(node, queueingFunction, swap21);
	}
	else if (blankPosition == 5) // blank is [1, 2] middle right - check [0, 2], [1, 1], [2, 2]
	{
		vector<vector<int>> swap02 = node->currentBoard;
		vector<vector<int>> swap11 = swap02;
		vector<vector<int>> swap22 = swap02;

		swap(swap02[1][2], swap02[0][2]);
		swap(swap11[1][2], swap11[1][1]);
		swap(swap22[1][2], swap22[2][2]);

		child(node, queueingFunction, swap02);
		child(node, queueingFunction, swap11);
		child(node, queueingFunction, swap22);
	}
	else if (blankPosition == 6) // blank is [2, 0] bottom left - check [1, 0], [2, 1]
	{
		vector<vector<int>> swap10 = node->currentBoard;
		vector<vector<int>> swap21 = swap10;

		swap(swap10[2][0], swap10[1][0]);
		swap(swap21[2][0], swap21[2][1]);

		child(node, queueingFunction, swap10);
		child(node, queueingFunction, swap21);
	}
	else if (blankPosition == 7) // blank is [2, 1] bottom middle - check [2, 0], [1, 1], [2, 2]
	{
		vector<vector<int>> swap20 = node->currentBoard;
		vector<vector<int>> swap11 = swap20;
		vector<vector<int>> swap22 = swap20;

		swap(swap20[2][1], swap20[2][0]);
		swap(swap11[2][1], swap11[1][1]);
		swap(swap22[2][1], swap22[2][2]);

		child(node, queueingFunction, swap20);
		child(node, queueingFunction, swap11);
		child(node, queueingFunction, swap22);
	}
	else // blank is [2, 2] bottom right - check [1, 2], [2, 1]
	{
		vector<vector<int>> swap12 = node->currentBoard;
		vector<vector<int>> swap21 = swap12;

		swap(swap12[2][2], swap12[1][2]);
		swap(swap21[2][2], swap21[2][1]);

		child(node, queueingFunction, swap12);
		child(node, queueingFunction, swap21);
	}

	if (maxQueueSize < gq.size()) // stores the highest number of nodes in the queue for max queue size
	{
		maxQueueSize = gq.size();
	}
	if (solutionDepth < gq.top()->gn) // stores highest g(n) value for solution depth
	{
		solutionDepth = gq.top()->gn;
	}
	printBoard(gq.top());
}