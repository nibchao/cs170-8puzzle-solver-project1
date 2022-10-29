#include "PuzzleNode.h"

// function prototypes
int menu();

int main()
{
	PuzzleNode puzzleObj;
	Node* node;

	int input = 0;
	int algorithmInput = 0;
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