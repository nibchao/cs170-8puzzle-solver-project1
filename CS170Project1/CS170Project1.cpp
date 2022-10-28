#include "PuzzleNode.h"

// referenced https://www.geeksforgeeks.org/2d-vector-in-cpp-with-user-defined-size/ on how to create 2D vector with values
vector<vector<int>> depth8
{ 
	{1, 3, 6},
	{5, 0, 2},
	{4, 7, 8} 
};

vector<vector<int>> custom
{
	{ },
	{ },
	{ }
};

// function prototypes
int menu();
void defaultBoard();
void createCustomBoard();

int main()
{
	PuzzleNode puzzleObj;

	int input = 0;
	int algorithmInput = 0;
	do
	{
		input = menu();
		switch (input)
		{
			case 1:
				defaultBoard();
				cout << "Select the search algorithm. Type '1' for Uniform Cost Search. Type '2' for Misplaced Tile Heuristic. Type '3' for Manhattan Distance Heuristic.\n";
				cin >> algorithmInput;
				puzzleObj.setAlgorithmChoice(algorithmInput);
				break;
			case 2:
				custom.clear();
				createCustomBoard();
				cout << "Select the search algorithm. Type '1' for Uniform Cost Search. Type '2' for Misplaced Tile Heuristic. Type '3' for Manhattan Distance Heuristic.\n";
				cin >> algorithmInput;
				puzzleObj.setAlgorithmChoice(algorithmInput);
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

void defaultBoard()
{
	int input = 0;
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
}

void createCustomBoard()
{
	int square1 = 0, square2 = 0, square3 = 0;
	vector<int> temp;
	temp.clear();
	cout << "\nEnter your own puzzle using 0 as the blank square. Put a space in between your numbers.\n";
	cout << "Enter the first row: ";
	cin >> square1 >> square2 >> square3;
	temp.push_back(square1);
	temp.push_back(square2);
	temp.push_back(square3);
	custom.push_back(temp);
	temp.clear();
	cout << "Enter the second row: ";
	cin >> square1 >> square2 >> square3;
	temp.push_back(square1);
	temp.push_back(square2);
	temp.push_back(square3);
	custom.push_back(temp);
	temp.clear();
	cout << "Enter the third row: ";
	cin >> square1 >> square2 >> square3;
	temp.push_back(square1);
	temp.push_back(square2);
	temp.push_back(square3);
	custom.push_back(temp);
	temp.clear();
	cout << "\nYour game board is\n";
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << custom[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	cin.clear();
	cin.ignore(9999, '\n');
}