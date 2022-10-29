#include "PuzzleNode.h"

// function prototypes
int menu();

int main()
{
	PuzzleNode puzzleObj;
	Node* node;
	/*Node* node = new Node;
	node->currentBoard.push_back({ 1, 2, 3 });
	node->currentBoard.push_back({ 4, 5, 6 });
	node->currentBoard.push_back({ 7, 8, 0 });

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << node->currentBoard[i][j] << " ";
		}
		cout << "\n";
	}

	cout << "\nspacer\n";

	vector<vector<int>> swap10 = node->currentBoard;
	vector<vector<int>> swap01 = swap10;

	swap(swap10[0][0], swap10[2][0]);
	cout << "swap10\n";
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << swap10[i][j] << " ";
		}
		cout << "\n";
	}

	cout << "\n\nswap01\n";
	swap(swap01[0][0], swap01[0][1]);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << swap01[i][j] << " ";
		}
		cout << "\n";
	}*/

	int input = 0;
	int algorithmInput = 0;
	//puzzleObj.search(node, 1);
	do
	{
		input = menu();
		switch (input)
		{
			case 1:
				node = puzzleObj.defaultPuzzle();
				cout << "Select the search algorithm. Type '1' for Uniform Cost Search. Type '2' for Misplaced Tile Heuristic. Type '3' for Manhattan Distance Heuristic.\n";
				cin >> algorithmInput;
				if (algorithmInput == 1)
				{
					cout << algorithmInput << " was selected. Solving the puzzle using Uniform Cost Search.\n\n";
				}
				else if (algorithmInput == 2)
				{
					cout << algorithmInput << " was selected. Solving the puzzle using Misplaced Tile Heuristic.\n\n";
				}
				else if (algorithmInput == 3)
				{
					cout << algorithmInput << " was selected. Solving the puzzle using Manhattan Distance Heuristic.\n\n";
				}
				puzzleObj.search(node, algorithmInput);
				break;
			case 2:
				node = puzzleObj.createPuzzle();
				cout << "Select the search algorithm. Type '1' for Uniform Cost Search. Type '2' for Misplaced Tile Heuristic. Type '3' for Manhattan Distance Heuristic.\n";
				cin >> algorithmInput;
				if (algorithmInput == 1)
				{
					cout << algorithmInput << " was selected. Solving the puzzle using Uniform Cost Search.\n\n";
				}
				else if (algorithmInput == 2)
				{
					cout << algorithmInput << " was selected. Solving the puzzle using Misplaced Tile Heuristic.\n\n";
				}
				else if (algorithmInput == 3)
				{
					cout << algorithmInput << " was selected. Solving the puzzle using Manhattan Distance Heuristic.\n\n";
				}
				puzzleObj.search(node, algorithmInput);
				break;
			case 3:
				cout << "Ending program.\n";
				break;
			default:
				cout << "default\n";
				break;
		}
	} while (input != 3);

	return 0;
}

int menu()
{
	int input = 0;
	cout << "This program is an 8-Puzzle solver.\nType '1' to use a default puzzle.\nType '2' to create your own puzzle.\nType '3' to exit.\n";
	cin >> input;
	cin.clear();
	cin.ignore(9999, '\n');
	return input;
}