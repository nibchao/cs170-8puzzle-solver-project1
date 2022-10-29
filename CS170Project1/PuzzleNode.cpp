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
		// do nothing
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

// referenced https://www.gatevidyalay.com/tag/a-algorithm-for-8-puzzle-problem/ to better understand A* and how to get f(n)
bool PuzzleNode::search(Node* node, int queueingFunction)
{
	int algorithmChoice = queueingFunction;

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
		cout << "goal, " << nodesExpanded << "\n";
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

		Node* swap01Board = new Node;
		swap01Board->currentBoard = swap01;
		swap01Board->hn = countMisplacedTiles(swap01Board->currentBoard, algorithmChoice);
		swap01Board->gn = node->gn + 1;
		node->left = swap01Board;
		for (int cnt = 0; cnt < visitedNodes.size(); cnt++)
		{
			if (visitedNodes.at(cnt) == swap01Board)
			{
				node->left = nullptr;
				break;
			}
		}
		visitedNodes.push_back(swap01Board);
		gq.push(swap01Board);

		Node* swap10Board = new Node;
		swap10Board->currentBoard = swap10;
		swap10Board->hn = countMisplacedTiles(swap10Board->currentBoard, algorithmChoice);
		swap10Board->gn = node->gn + 1;
		node->midleft = swap10Board;
		for (int cnt = 0; cnt < visitedNodes.size(); cnt++)
		{
			if (visitedNodes.at(cnt) == swap10Board)
			{
				node->midleft = nullptr;
				break;
			}
		}
		visitedNodes.push_back(swap10Board);
		gq.push(swap10Board);

		nodesExpanded += 2;
	}
	else if (blankPosition == 1) // blank is [0, 1] top middle - check [0, 0], [0, 2], [1, 1]
	{
		vector<vector<int>> swap00 = node->currentBoard;
		vector<vector<int>> swap02 = swap00;
		vector<vector<int>> swap11 = swap00;

		swap(swap00[0][1], swap00[0][0]);
		swap(swap02[0][1], swap02[0][2]);
		swap(swap11[0][1], swap11[1][1]);

		Node* swap00Board = new Node;
		swap00Board->currentBoard = swap00;
		swap00Board->hn = countMisplacedTiles(swap00Board->currentBoard, algorithmChoice);
		swap00Board->gn = node->gn + 1;
		node->left = swap00Board;
		for (int cnt = 0; cnt < visitedNodes.size(); cnt++)
		{
			if (visitedNodes.at(cnt) == swap00Board)
			{
				node->left = nullptr;
				break;
			}
		}
		visitedNodes.push_back(swap00Board);
		gq.push(swap00Board);

		Node* swap02Board = new Node;
		swap02Board->currentBoard = swap02;
		swap02Board->hn = countMisplacedTiles(swap02Board->currentBoard, algorithmChoice);
		swap02Board->gn = node->gn + 1;
		node->midleft = swap02Board;
		for (int cnt = 0; cnt < visitedNodes.size(); cnt++)
		{
			if (visitedNodes.at(cnt) == swap02Board)
			{
				node->midleft = nullptr;
				break;
			}
		}
		visitedNodes.push_back(swap02Board);
		gq.push(swap02Board);

		Node* swap11Board = new Node;
		swap11Board->currentBoard = swap11;
		swap11Board->hn = countMisplacedTiles(swap11Board->currentBoard, algorithmChoice);
		swap11Board->gn = node->gn + 1;
		node->midright = swap11Board;
		for (int cnt = 0; cnt < visitedNodes.size(); cnt++)
		{
			if (visitedNodes.at(cnt) == swap11Board)
			{
				node->midright = nullptr;
				break;
			}
		}
		visitedNodes.push_back(swap11Board);
		gq.push(swap11Board);

		nodesExpanded += 3;
	}
	else if (blankPosition == 2) // blank is [0, 2] top right - check [0, 1], [1, 2]
	{
		vector<vector<int>> swap01 = node->currentBoard;
		vector<vector<int>> swap12 = swap01;

		swap(swap01[0][2], swap01[0][1]);
		swap(swap12[0][2], swap12[1][2]);

		Node* swap01Board = new Node;
		swap01Board->currentBoard = swap01;
		swap01Board->hn = countMisplacedTiles(swap01Board->currentBoard, algorithmChoice);
		swap01Board->gn = node->gn + 1;
		node->left = swap01Board;
		for (int cnt = 0; cnt < visitedNodes.size(); cnt++)
		{
			if (visitedNodes.at(cnt) == swap01Board)
			{
				node->left = nullptr;
				break;
			}
		}
		visitedNodes.push_back(swap01Board);
		gq.push(swap01Board);

		Node* swap12Board = new Node;
		swap12Board->currentBoard = swap12;
		swap12Board->hn = countMisplacedTiles(swap12Board->currentBoard, algorithmChoice);
		swap12Board->gn = node->gn + 1;	
		node->midleft = swap12Board;
		for (int cnt = 0; cnt < visitedNodes.size(); cnt++)
		{
			if (visitedNodes.at(cnt) == swap12Board)
			{
				node->midleft = nullptr;
				break;
			}
		}
		visitedNodes.push_back(swap12Board);
		gq.push(swap12Board);

		nodesExpanded += 2;
	}
	else if (blankPosition == 3) // blank is [1, 0] middle left - check [0, 0], [1, 1], [2, 0]
	{
		vector<vector<int>> swap00 = node->currentBoard;
		vector<vector<int>> swap11 = swap00;
		vector<vector<int>> swap20 = swap00;

		swap(swap00[1][0], swap00[0][0]);
		swap(swap11[1][0], swap11[1][1]);
		swap(swap20[1][0], swap20[2][0]);

		Node* swap00Board = new Node;
		swap00Board->currentBoard = swap00;
		swap00Board->hn = countMisplacedTiles(swap00Board->currentBoard, algorithmChoice);
		swap00Board->gn = node->gn + 1;
		node->left = swap00Board;
		for (int cnt = 0; cnt < visitedNodes.size(); cnt++)
		{
			if (visitedNodes.at(cnt) == swap00Board)
			{
				node->left = nullptr;
				break;
			}
		}
		visitedNodes.push_back(swap00Board);
		gq.push(swap00Board);

		Node* swap11Board = new Node;
		swap11Board->currentBoard = swap11;
		swap11Board->hn = countMisplacedTiles(swap11Board->currentBoard, algorithmChoice);
		swap11Board->gn = node->gn + 1;
		node->midleft = swap11Board;
		for (int cnt = 0; cnt < visitedNodes.size(); cnt++)
		{
			if (visitedNodes.at(cnt) == swap00Board)
			{
				node->midleft = nullptr;
				break;
			}	
		}
		visitedNodes.push_back(swap11Board);
		gq.push(swap11Board);

		Node* swap20Board = new Node;
		swap20Board->currentBoard = swap20;
		swap20Board->hn = countMisplacedTiles(swap20Board->currentBoard, algorithmChoice);
		swap20Board->gn = node->gn + 1;
		node->midright = swap20Board;
		for (int cnt = 0; cnt < visitedNodes.size(); cnt++)
		{
			if (visitedNodes.at(cnt) == swap20Board)
			{
				node->midright = nullptr;
				break;
			}
		}
		visitedNodes.push_back(swap20Board);
		gq.push(swap20Board);

		nodesExpanded += 3;
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

		Node* swap10Board = new Node;
		swap10Board->currentBoard = swap10;
		swap10Board->hn = countMisplacedTiles(swap10Board->currentBoard, algorithmChoice);
		swap10Board->gn = node->gn + 1;
		node->left = swap10Board;
		for (int cnt = 0; cnt < visitedNodes.size(); cnt++)
		{
			if (visitedNodes.at(cnt) == swap10Board)
			{
				node->left = nullptr;
				break;
			}
		}
		visitedNodes.push_back(swap10Board);
		gq.push(swap10Board);

		Node* swap01Board = new Node;
		swap01Board->currentBoard = swap01;
		swap01Board->hn = countMisplacedTiles(swap01Board->currentBoard, algorithmChoice);
		swap01Board->gn = node->gn + 1;
		node->midleft = swap01Board;
		for (int cnt = 0; cnt < visitedNodes.size(); cnt++)
		{
			if (visitedNodes.at(cnt) == swap01Board)
			{
				node->midleft = nullptr;
				break;
			}
		}
		visitedNodes.push_back(swap01Board);
		gq.push(swap01Board);

		Node* swap12Board = new Node;
		swap12Board->currentBoard = swap12;
		swap12Board->hn = countMisplacedTiles(swap12Board->currentBoard, algorithmChoice);
		swap12Board->gn = node->gn + 1;
		node->midright = swap12Board;
		for (int cnt = 0; cnt < visitedNodes.size(); cnt++)
		{
			if (visitedNodes.at(cnt) == swap12Board)
			{
				node->midright = nullptr;
				break;
			}
		}
		visitedNodes.push_back(swap12Board);
		gq.push(swap12Board);

		Node* swap21Board = new Node;
		swap21Board->currentBoard = swap21;
		swap21Board->hn = countMisplacedTiles(swap21Board->currentBoard, algorithmChoice);
		swap21Board->gn = node->gn + 1;
		node->right = swap21Board;
		for (int cnt = 0; cnt < visitedNodes.size(); cnt++)
		{
			if (visitedNodes.at(cnt) == swap21Board)
			{
				node->right = nullptr;
				break;
			}
		}
		visitedNodes.push_back(swap21Board);
		gq.push(swap21Board);

		nodesExpanded += 4;
	}
	else if (blankPosition == 5) // blank is [1, 2] middle right - check [0, 2], [1, 1], [2, 2]
	{
		vector<vector<int>> swap02 = node->currentBoard;
		vector<vector<int>> swap11 = swap02;
		vector<vector<int>> swap22 = swap02;

		swap(swap02[1][2], swap02[0][2]);
		swap(swap11[1][2], swap11[1][1]);
		swap(swap22[1][2], swap22[2][2]);

		Node* swap02Board = new Node;
		swap02Board->currentBoard = swap02;
		swap02Board->hn = countMisplacedTiles(swap02Board->currentBoard, algorithmChoice);
		swap02Board->gn = node->gn + 1;
		node->left = swap02Board;
		for (int cnt = 0; cnt < visitedNodes.size(); cnt++)
		{
			if (visitedNodes.at(cnt) == swap02Board)
			{
				node->left = nullptr;
				break;
			}
		}
		visitedNodes.push_back(swap02Board);
		gq.push(swap02Board);

		Node* swap11Board = new Node;
		swap11Board->currentBoard = swap11;
		swap11Board->hn = countMisplacedTiles(swap11Board->currentBoard, algorithmChoice);
		swap11Board->gn = node->gn + 1;
		node->midleft = swap11Board;
		for (int cnt = 0; cnt < visitedNodes.size(); cnt++)
		{
			if (visitedNodes.at(cnt) == swap11Board)
			{
				node->midleft = nullptr;
				break;
			}
		}
		visitedNodes.push_back(swap11Board);
		gq.push(swap11Board);

		Node* swap22Board = new Node;
		swap22Board->currentBoard = swap22;
		swap22Board->hn = countMisplacedTiles(swap22Board->currentBoard, algorithmChoice);
		swap22Board->gn = node->gn + 1;
		node->midright = swap22Board;
		for (int cnt = 0; cnt < visitedNodes.size(); cnt++)
		{
			if (visitedNodes.at(cnt) == swap22Board)
			{
				node->midright = nullptr;
				break;
			}
		}
		visitedNodes.push_back(swap22Board);
		gq.push(swap22Board);

		nodesExpanded += 3;
	}
	else if (blankPosition == 6) // blank is [2, 0] bottom left - check [1, 0], [2, 1]
	{
		vector<vector<int>> swap10 = node->currentBoard;
		vector<vector<int>> swap21 = swap10;

		swap(swap10[2][0], swap10[1][0]);
		swap(swap21[2][0], swap21[2][1]);

		Node* swap10Board = new Node;
		swap10Board->currentBoard = swap10;
		swap10Board->hn = countMisplacedTiles(swap10Board->currentBoard, algorithmChoice);
		swap10Board->gn = node->gn + 1;
		node->left = swap10Board;
		for (int cnt = 0; cnt < visitedNodes.size(); cnt++)
		{
			if (visitedNodes.at(cnt) == swap10Board)
			{
				node->left = nullptr;
				break;
			}
		}
		visitedNodes.push_back(swap10Board);
		gq.push(swap10Board);

		Node* swap21Board = new Node;
		swap21Board->currentBoard = swap21;
		swap21Board->hn = countMisplacedTiles(swap21Board->currentBoard, algorithmChoice);
		swap21Board->gn = node->gn + 1;
		node->midleft = swap21Board;
		for (int cnt = 0; cnt < visitedNodes.size(); cnt++)
		{
			if (visitedNodes.at(cnt) == swap21Board)
			{
				node->midleft = nullptr;
				break;
			}
		}
		visitedNodes.push_back(swap21Board);
		gq.push(swap21Board);

		nodesExpanded += 2;
	}
	else if (blankPosition == 7) // blank is [2, 1] bottom middle - check [2, 0], [1, 1], [2, 2]
	{
		vector<vector<int>> swap20 = node->currentBoard;
		vector<vector<int>> swap11 = swap20;
		vector<vector<int>> swap22 = swap20;

		swap(swap20[2][1], swap20[2][0]);
		swap(swap11[2][1], swap11[1][0]);
		swap(swap22[2][1], swap22[2][2]);

		Node* swap20Board = new Node;
		swap20Board->currentBoard = swap20;
		swap20Board->hn = countMisplacedTiles(swap20Board->currentBoard, algorithmChoice);
		swap20Board->gn = node->gn + 1;
		node->left = swap20Board;
		for (int cnt = 0; cnt < visitedNodes.size(); cnt++)
		{
			if (visitedNodes.at(cnt) == swap20Board)
			{
				node->left = nullptr;
				break;
			}
		}
		visitedNodes.push_back(swap20Board);
		gq.push(swap20Board);

		Node* swap11Board = new Node;
		swap11Board->currentBoard = swap11;
		swap11Board->hn = countMisplacedTiles(swap11Board->currentBoard, algorithmChoice);
		swap11Board->gn = node->gn + 1;
		node->midleft = swap11Board;
		for (int cnt = 0; cnt < visitedNodes.size(); cnt++)
		{
			if (visitedNodes.at(cnt) == swap11Board)
			{
				node->midleft = nullptr;
				break;
			}
		}
		visitedNodes.push_back(swap11Board);
		gq.push(swap11Board);

		Node* swap22Board = new Node;
		swap22Board->currentBoard = swap22;
		swap22Board->hn = countMisplacedTiles(swap22Board->currentBoard, algorithmChoice);
		swap22Board->gn = node->gn + 1;
		node->midright = swap22Board;
		for (int cnt = 0; cnt < visitedNodes.size(); cnt++)
		{
			if (visitedNodes.at(cnt) == swap22Board)
			{
				node->midright = nullptr;
				break;
			}
		}
		visitedNodes.push_back(swap22Board);
		gq.push(swap22Board);

		nodesExpanded += 3;
	}
	else // blank is [2, 2] bottom right - check [1, 2], [2, 1]
	{
		vector<vector<int>> swap12 = node->currentBoard;
		vector<vector<int>> swap21 = swap12;

		swap(swap12[2][2], swap12[1][2]);
		swap(swap21[2][2], swap21[2][1]);

		Node* swap12Board = new Node;
		swap12Board->currentBoard = swap12;
		swap12Board->hn = countMisplacedTiles(swap12Board->currentBoard, algorithmChoice);
		swap12Board->gn = node->gn + 1;
		node->left = swap12Board;
		for (int cnt = 0; cnt < visitedNodes.size(); cnt++)
		{
			if (visitedNodes.at(cnt) == swap12Board)
			{
				node->left = nullptr;
				break;
			}
		}
		visitedNodes.push_back(swap12Board);
		gq.push(swap12Board);

		Node* swap21Board = new Node;
		swap21Board->currentBoard = swap21;
		swap21Board->hn = countMisplacedTiles(swap21Board->currentBoard, algorithmChoice);
		swap21Board->gn = node->gn + 1;
		node->midleft = swap21Board;
		for (int cnt = 0; cnt < visitedNodes.size(); cnt++)
		{
			if (visitedNodes.at(cnt) == swap21Board)
			{
				node->midleft = nullptr;
				break;
			}
		}
		visitedNodes.push_back(swap21Board);
		gq.push(swap21Board);

		nodesExpanded += 2;
	}

	if (gq.top())
	{
		search(gq.top(), algorithmChoice);
	}
	return false;
}