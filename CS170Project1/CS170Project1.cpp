#include "PuzzleNode.h"

// function prototypes
int menu();
int getAlgorithmInput();

int main()
{
	PuzzleNode puzzleObj;
	Node* node;

	int input = menu();
	int algorithmInput = 0;
	switch (input)
	{
		case 1: // default puzzle option
			node = puzzleObj.defaultPuzzle();
			puzzleObj.search(node, getAlgorithmInput());
			break;
		case 2: // custom puzzle option
			node = puzzleObj.createPuzzle();
			puzzleObj.search(node, getAlgorithmInput());
			break;
		case 3:
			cout << "Ending program.\n";
			break;
		default:
			cout << "default, invalid input detected, ending program\n";
			break;
	}
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

int getAlgorithmInput()
{
	int algorithmInput = 0;
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
	return algorithmInput;
}