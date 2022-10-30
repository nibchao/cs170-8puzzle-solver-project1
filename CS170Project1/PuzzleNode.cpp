#include "PuzzleNode.h"

vector<vector<int>> finalState
{
	{1, 2, 3 },
	{4, 5, 6 },
	{7, 8, 0 }
};

PuzzleNode::PuzzleNode()
{
	head = nullptr;
	nodesExpanded = 0;
	goal = false;
}

Node* PuzzleNode::createPuzzle() // referenced https://www.geeksforgeeks.org/2d-vector-in-cpp-with-user-defined-size/ on how to create 2D vector with values
{
	Node* node = new Node;
	node->left = nullptr;
	node->midleft = nullptr;
	node->midright = nullptr;
	node->right = nullptr;
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
	customrow.push_back(square1); customrow.push_back(square2); customrow.push_back(square3);
	custom.push_back(customrow);
	node->currentBoard.push_back(customrow);
	customrow.clear();
	cout << "Enter the second row: ";
	cin >> square1 >> square2 >> square3;
	customrow.push_back(square1); customrow.push_back(square2); customrow.push_back(square3);
	custom.push_back(customrow);
	node->currentBoard.push_back(customrow);
	customrow.clear();
	cout << "Enter the third row: ";
	cin >> square1 >> square2 >> square3;
	customrow.push_back(square1); customrow.push_back(square2); customrow.push_back(square3);
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
	node->left = nullptr;
	node->midleft = nullptr;
	node->midright = nullptr;
	node->right = nullptr;
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
	for (int i = 0; i < depth8.size(); i++)
	{
		for (int j = 0; j < depth8.size(); j++)
		{
			cout << depth8[i][j] << " ";
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

int PuzzleNode::countMisplacedTiles(vector<vector<int>> board, int queueingFunction)
{
	int misplacedTilesNum = 0;

	if (queueingFunction == 1) // h(x) is hardcoded to 0 for uniform cost search
	{
		// do nothing
	}
	else if (queueingFunction == 2) // misplaced tiles calculation
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

// referenced https://www.gatevidyalay.com/tag/a-algorithm-for-8-puzzle-problem/ to better understand A* and how to get f(n)
bool PuzzleNode::search(Node* node, int queueingFunction)
{
	vector<vector<int>> finalState
	{
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 0}
	};

	if (gq.empty())
	{
		cout << "fail";
		return false;
	}
	gq.pop();
	if (node->currentBoard == finalState)
	{
		goal = true;
		cout << "Goal! Expanded " << nodesExpanded << " nodes.\n\n";
		return true;
	}

	int blankPosition = 0;

	bool stop = false;
	for (int i = 0; i < finalState.size() && !stop; i++) // referenced https://stackoverflow.com/questions/9695902/how-to-break-out-of-nested-loops
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

	// board is [y, x] instead of [x, y]
	/*{ 0, 0 }, { 0, 1 }, { 0, 2 }
	  { 1, 0 }, { 1, 1 }, { 1, 2 }
	  { 2, 0 }, { 2, 1 }, { 2, 2 }*/
	if (blankPosition == 0) // blank is [0, 0] top left - check [0, 1] and [1, 0]
	{
		vector<vector<int>> swap01 = node->currentBoard;
		vector<vector<int>> swap10 = swap01;

		swap(swap01[0][0], swap01[0][1]);
		swap(swap10[0][0], swap10[1][0]);

		left(node, queueingFunction, swap01);
		midleft(node, queueingFunction, swap10);
	}
	else if (blankPosition == 1) // blank is [0, 1] top middle - check [0, 0], [0, 2], [1, 1]
	{
		vector<vector<int>> swap00 = node->currentBoard;
		vector<vector<int>> swap02 = swap00;
		vector<vector<int>> swap11 = swap00;

		swap(swap00[0][1], swap00[0][0]);
		swap(swap02[0][1], swap02[0][2]);
		swap(swap11[0][1], swap11[1][1]);

		left(node, queueingFunction, swap00);
		midleft(node, queueingFunction, swap02);
		midright(node, queueingFunction, swap11);
	}
	else if (blankPosition == 2) // blank is [0, 2] top right - check [0, 1], [1, 2]
	{
		vector<vector<int>> swap01 = node->currentBoard;
		vector<vector<int>> swap12 = swap01;

		swap(swap01[0][2], swap01[0][1]);
		swap(swap12[0][2], swap12[1][2]);

		left(node, queueingFunction, swap01);
		midleft(node, queueingFunction, swap12);
	}
	else if (blankPosition == 3) // blank is [1, 0] middle left - check [0, 0], [1, 1], [2, 0]
	{
		vector<vector<int>> swap00 = node->currentBoard;
		vector<vector<int>> swap11 = swap00;
		vector<vector<int>> swap20 = swap00;

		swap(swap00[1][0], swap00[0][0]);
		swap(swap11[1][0], swap11[1][1]);
		swap(swap20[1][0], swap20[2][0]);

		left(node, queueingFunction, swap00);
		midleft(node, queueingFunction, swap11);
		midright(node, queueingFunction, swap20);
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

		left(node, queueingFunction, swap10);
		midleft(node, queueingFunction, swap01);
		midright(node, queueingFunction, swap12);
		right(node, queueingFunction, swap21);
	}
	else if (blankPosition == 5) // blank is [1, 2] middle right - check [0, 2], [1, 1], [2, 2]
	{
		vector<vector<int>> swap02 = node->currentBoard;
		vector<vector<int>> swap11 = swap02;
		vector<vector<int>> swap22 = swap02;

		swap(swap02[1][2], swap02[0][2]);
		swap(swap11[1][2], swap11[1][1]);
		swap(swap22[1][2], swap22[2][2]);

		left(node, queueingFunction, swap02);
		midleft(node, queueingFunction, swap11);
		midright(node, queueingFunction, swap22);
	}
	else if (blankPosition == 6) // blank is [2, 0] bottom left - check [1, 0], [2, 1]
	{
		vector<vector<int>> swap10 = node->currentBoard;
		vector<vector<int>> swap21 = swap10;

		swap(swap10[2][0], swap10[1][0]);
		swap(swap21[2][0], swap21[2][1]);

		left(node, queueingFunction, swap10);
		midleft(node, queueingFunction, swap21);
	}
	else if (blankPosition == 7) // blank is [2, 1] bottom middle - check [2, 0], [1, 1], [2, 2]
	{
		vector<vector<int>> swap20 = node->currentBoard;
		vector<vector<int>> swap11 = swap20;
		vector<vector<int>> swap22 = swap20;

		swap(swap20[2][1], swap20[2][0]);
		swap(swap11[2][1], swap11[1][0]);
		swap(swap22[2][1], swap22[2][2]);

		left(node, queueingFunction, swap20);
		midleft(node, queueingFunction, swap11);
		midright(node, queueingFunction, swap22);
	}
	else // blank is [2, 2] bottom right - check [1, 2], [2, 1]
	{
		vector<vector<int>> swap12 = node->currentBoard;
		vector<vector<int>> swap21 = swap12;

		swap(swap12[2][2], swap12[1][2]);
		swap(swap21[2][2], swap21[2][1]);

		left(node, queueingFunction, swap12);
		midleft(node, queueingFunction, swap21);
	}

	if (gq.top())
	{
		search(gq.top(), queueingFunction);
	}
	return false;
}

void PuzzleNode::left(Node* node, int queueingFunction, vector<vector<int>> board)
{
	if (!duplicateBoardChecker(board))
	{
		Node* swapBoard = new Node;
		swapBoard->currentBoard = board;
		swapBoard->hn = countMisplacedTiles(swapBoard->currentBoard, queueingFunction);
		swapBoard->gn = node->gn + 1;
		node->left = swapBoard;
		visitedNodes.push_back(swapBoard);
		visitedBoards.push_back(board);
		gq.push(swapBoard);
		nodesExpanded++;
	}
}

void PuzzleNode::midleft(Node* node, int queueingFunction, vector<vector<int>> board)
{
	if (!duplicateBoardChecker(board))
	{
		Node* swapBoard = new Node;
		swapBoard->currentBoard = board;
		swapBoard->hn = countMisplacedTiles(swapBoard->currentBoard, queueingFunction);
		swapBoard->gn = node->gn + 1;
		node->midleft = swapBoard;
		visitedNodes.push_back(swapBoard);
		visitedBoards.push_back(board);
		gq.push(swapBoard);
		nodesExpanded++;
	}
}

void PuzzleNode::midright(Node* node, int queueingFunction, vector<vector<int>> board)
{
	if (!duplicateBoardChecker(board))
	{
		Node* swapBoard = new Node;
		swapBoard->currentBoard = board;
		swapBoard->hn = countMisplacedTiles(swapBoard->currentBoard, queueingFunction);
		swapBoard->gn = node->gn + 1;
		node->midright = swapBoard;
		visitedNodes.push_back(swapBoard);
		visitedBoards.push_back(board);
		gq.push(swapBoard);
		nodesExpanded++;
	}
}

void PuzzleNode::right(Node* node, int queueingFunction, vector<vector<int>> board)
{
	if (!duplicateBoardChecker(board))
	{
		Node* swapBoard = new Node;
		swapBoard->currentBoard = board;
		swapBoard->hn = countMisplacedTiles(swapBoard->currentBoard, queueingFunction);
		swapBoard->gn = node->gn + 1;
		node->right = swapBoard;
		visitedNodes.push_back(swapBoard);
		visitedBoards.push_back(board);
		gq.push(swapBoard);
		nodesExpanded++;
	}
}

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