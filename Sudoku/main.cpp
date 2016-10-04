#include "windows.h"
#include "board.h"

int main(void)
{
	string name;
	//cout << "Please enter the csv file 'example.csv' " << endl;
	//cin >> name;
	cout << "Hello! Welcome to sudoku! There are several options to choose from." << endl;
	cout << "1. Play!" << endl;      
	cout << "2. Have the computer solve it!" << endl;
	int option;
	do
	{
		option = 2; ////////remove later. Just for testing
		//cin >> option;
	} while (option <= 0 || option >= 3);
	name = "sudoku6.csv";
	Board board(name);
	//board.getBoard(name);
	board.printBoard();
	system("pause");
	system("cls");
	if (option == 1) // person wants to play
	{
		board.player();
	}
	if (option == 2) // computer solve
	{
		board.computer();
	}


	return 0;
}

