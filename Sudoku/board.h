#ifndef BOARD_H	
#define BOARD_H


#include "StringSplitter.h"
#include "square.h"
#include "Set.h"
#include "Grid.h"
#include "Row.h"
#include "Column.h"

//The board should be a 9x9 of squares. when first initializing, the numbers should be
//read in the board.h and then put into the constructor for square.h. All current functions
//must be rewritten to show this change.

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>

using namespace chrono;

using namespace std;

class Board
{
private:
	square _board[9][9];
	Row _row[9];
	Column _col[9];
	Grid _grid[9];
	ofstream _file;

public:
	Board()
	{

	}
	Board(string name)
	{
		ifstream file;
		file.open(name);
		string row;
		string temp;
		vector<string> row_elements;
		int num;
		if (file.is_open() == true)
		{
			for (int i = 0; i < 9; i++)
			{
				getline(file, row);
				row_elements = StringSplitter::split(row, ",");
				for (int j = 0; j < 9; j++)
				{
					//temp = row[j];
					num = stoi(row_elements[j].c_str());
					if (num == 0)
					{
						_board[i][j].set_known(false);
						_board[i][j].set_val(0);
					}
					else
					{
						_board[i][j].set_known(true);
						_board[i][j].set_val(num);
					}
				}
			}
		}
		else
		{
			cout << "Something bad happened" << endl;
		}

		/*for (int i = 0; i < 9; i++)
		{
		for (int j = 0; j < 9; j++)
		{
		_board[i][j].set_known(false);
		_board[i][i].set_val(0);
		}
		}*/

		//not sure what the point of setting everything to zero was
		for (int i = 0; i < 9; i++)
		{
			/*square col[9];
			for (int j = 0; j < 9; j++)
			{
			col[j] = _board[j][i];
			}*/
			_row[i].initialize(i, _board);
			_col[i].initialize(i, _board);

			//col is correct in board, but turns into jsut the first value when passed into the function, maybe &/* will be needed
			//and could help. Grid will be a headache, if I can't pass 2d arrays into the function.
			//Resolved
		}
		_grid[0].initialize(0, 0, _board);
		_grid[1].initialize(0, 3, _board);
		_grid[2].initialize(0, 6, _board);
		_grid[3].initialize(3, 0, _board);
		_grid[4].initialize(3, 3, _board);
		_grid[5].initialize(3, 6, _board);
		_grid[6].initialize(6, 0, _board);
		_grid[7].initialize(6, 3, _board);
		_grid[8].initialize(6, 6, _board);

	}
	void printBoard()
	{
		cout << "   123   456   789" << endl;
		for (int i = 0; i < 9; i++)
		{

			if (i == 3)
			{
				cout << "   _ _ _ _ _ _ _ _" << endl;
				//cout << 4 << "  ";
			}
			if (i == 6)
			{
				cout << "   _ _ _ _ _ _ _ _" << endl;
				cout << 7 << "  ";
			}
			else
			{
				cout << i + 1 << "  ";
			}
			for (int j = 0; j < 9; j++)
			{
				//cout << j << "  ";
				if (j == 3 || j == 6)
				{
					cout << " | ";
				}
				cout << _board[i][j].get_val();
			}
			cout << endl;
		}
	}
	/*Set access_set(char type, int index)
		//will be called from inside one of the sets, if an operation needs to be done on another set
	{
		if (type == 'r')
		{
			return _row[index];
		}
		if (type == 'c')
		{
			return _col[index];
		}
		if (type == 'g')
		{
			return _grid[index];
		}
	}*/
	/*
	vector<int> get_row(int row_num)
	{
	if (row_num < 9)
	{
	vector<int> row;
	for (int j = 0; j < 9; j++)
	{
	row.push_back(_board[row_num][j]);
	}
	return row;
	}
	else
	{
	cout << "Invalid row" << endl;
	}
	}
	vector<int> get_col(int col_num)
	{
	if (col_num < 9)
	{
	vector<int> col;
	for (int i = 0; i < 9; i++)
	{
	col.push_back(_board[i][col_num]);
	}
	return col;
	}
	else
	{
	cout << "Invalid col" << endl;
	}
	}

	*/
	void player(void)
	{
		//printBoard();
		int row = 0;
		int col = 0;
		int val = 0;

		while (true)
		{
			system("cls");
			printBoard();
			//cout << "Enter 10 and 10 in the row/col to check if it is solved" << endl
			do{
				cout << "Please enter the row value" << endl;
				do
				{
					cin >> row;
				} while (row < 1 || row > 10);
				cout << "Please enter the col value" << endl;
				do
				{
					cin >> col;
				} while (col < 1 || col > 10);

				/*if (row == 10 && col == 10)
				{

				}*/

				if (_board[row - 1][col - 1].get_known() == true)
				{
					cout << "This value cannot be changed, please try again" << endl;
				}

			} while (_board[row - 1][col - 1].get_known() == true);

			cout << "Current value is " << _board[row - 1][col - 1].get_val() << endl;

			cout << "This value can be changed." << endl << endl;

			cout << "Please enter the new value" << endl;
			do
			{
				cin >> val;
				if (val < 1 || val > 9)
				{
					cout << "Please enter a valid number" << endl;
				}
				//should check the row/col/grid before doing anything else
			} while (val < 1 || val > 9);

			_board[row - 1][col - 1].set_val(val);

		}


	}
	void computer(void)
	{
		string str;
		string name = "log_file.txt";
		_file.open(name);
		if (_file.is_open() == true)
			cout << "Outfile prepared for writing" << endl;

		int choice;
		printBoard();
		int count = 0;
		cout << is_complete() << endl;

		system_clock::time_point start;
		system_clock::time_point end;
		start = system_clock::now();

		while (!is_complete())
		{
			/*for (int i = 0; i < 9; i++)
			{
			_row[i].print_set();
			cout << endl;
			}
			cout << endl;
			for (int i = 0; i < 9; i++)
			{
			_col[i].print_set();
			cout << endl;
			}
			cout << endl;
			for (int i = 0; i < 9; i++)
			{
			_grid[i].print_set();
			cout << endl;
			}*/
			_file << "ROUND #" << count << endl;
			for (int i = 0; i < 9; i++)
			{
				if (i == 1)
				{
					cout << endl;
				}
				if (!_row[i].is_complete())
				{
					_file << "Row " << i << " is not yet complete" << endl;
					simplify(_row[i]);
				}

				if (!_col[i].is_complete())
				{
					_file << "Col " << i << " is not yet complete" << endl;
					//write_to_file("Col " + " is not yet complete");
					simplify(_col[i]);
				}
				//cout << "col" << i + 1 << endl;
				//printBoard();
				//system("pause");
 				if (!_grid[i].is_complete())
				{
					_file << "Grid " << i << " is not yet complete" << endl;
					//write_to_file("Grid " + " is not yet complete");
					simplify(_grid[i]);
				}
				//cout << "grid" << i + 1 << endl;
				//printBoard();
			//may be a good way to call in succession to make most efficient
			}

			if (count == 100)
			{
				printBoard();
				system("pause");
			}
			cout << count << endl;

			count++;
			//printBoard();
			//system("pause");

			//cout << _row[0];
			//testing to see if row/col/grid worked as planned
		}
		printBoard();
		cout << "woooo" << endl;
		cout << count << endl;
		end = system_clock::now();
		cout << duration_cast<milliseconds>(end - start).count() << endl;
		system("pause");
	}

	//11/3/2015 I have an idea. The simplify function got really complicated and moved into two parts because each set has no 
	//knowledge of the other sets. This will be a mess so I'm backing it all up to a seperate file in case something gets messed up
	//everything looked really good until I realized that the sets would have to interact, for instance if the first two elements in row[0]
	//are the only two elements in the row that contain the possible value 8, then because they are in the same grid, you know that nothing else
	//in that grid can have a value 8 as well, so you have to remove 8 from their possibilities, which required the sets to have knowledge of eachother

	//11/3/2015 night update: Moved the simplify function over to board.h and everything works out. The next thing to do will be to move and condense
	//simplify_two function over to board as well. I think there is a better way to work the remove_two and remove_three functions and possibly combine
	//them into one function. That will require a lot more work though and right now I cannot focus on it enough to get it done. Maybe some weekend or a day
	//before class I can sit down and hammer it out but for now things are looking better.

	void simplify(Set set)
	{
		//set.print_missing_to_file(_file); //this is "referencing a deleted function" and I don't know why 11/22/2015

		int change = 0; //will track if anything happened
		set.update_values();
		vector<square*> remaining = set.get_remaining();

		//remaining[0]->set_col(100);
		//test to see if the changes are repeated back on the board

		//Using 'remaining' will save a lot of time, because it will skip checking the known values again and again and again. Lot faster
		//but right now there no way to update the value on the board. Unless get_remaining returns a vector of REFERENCES to squares
		//10/20/2015 rewrote get_remaining() to return a vector of REFERENCES to squares

		/*for (int i = 0; i < 9; i++)
		{
		if (!_squares[i]->get_known())//no point solving something that is already known
		{*/
		for (int i = 0; i < remaining.size(); i++)
		{

			//update_possible();
			//when this is uncommented, the number of iterations is brought down, but the speed will need to be benchmarked to see if it is actually
			//any faster. Finally something that can be benchmarked!!! 10/20/2015

			//10/21/2015. Need to find a good way to benchmark and average several attempts because one at a time it's easier

			if (remaining[i]->get_num_options() == 1) //simplest way to solve it
			{
				change = 1;
				remaining[i]->update(remaining[i]->get_only());//sets the square referenced to in remaining[i] to the only value it can be

				set.remove_values(remaining[i]->get_only() - 1);//now we know that if remaining[i]=9, _values[8] is now true
				_file << "Square[" << remaining[i]->get_row() << "][" << remaining[i]->get_col() << "] has been set to " << remaining[i]->get_only() << " because this is the only value it can be" << endl;
				set.update_possible(); //possibly doesn't need to be called or can be rewritten
				remaining = set.get_remaining(); //reset the remaing values because something has changed
				i = -1;
				if (remaining.size() == 0)//all done
				{
					_file << "This set is complete" << endl;
					return;
				}
				else //something has changed so we should shart over //////////this just lead to trouble 11/22/2015
				{
					//simplify(set);
				}
				//will keep working on given set
			}
		}

		//once things start working, maybe put this in an if(change == 1) loop so it isn't always called
		set.update_possible(); //will update the given set, so maybe a big update wont need to be called at the end
		
		
		//there's no easy answer unfortunately (10/20/2015)... time to get started
		//This is where the second simplification will come in, where sets need to be manipulated and moved together (11/5/2015)
		//I already have the code mostly written, but because of the different (more efficient) way it will be implemented now, it needs to be redone.

		
		if (!is_complete())
		{
			//this isn't needed because if there was a change it was already updated
			//vector<square*> remaining = set.get_remaining();
			
			//in a set, if there is only one square that has the value '8' in it, that has to be an 8. 
			//for every _value, have a vector of vector of ints/squares, if the set already has a '5' then name[4] will be empty,
			//we're looking for a vector that has only one value in it.
			vector<square*> remaining = set.get_remaining(); //have to call again because if a square got solved above it shouldn't be worked with down here
			vector<square*> val_remaining[9]; //an array of size 9 with vectors of pointers to squares
			for (int i = 0; i < remaining.size(); i++)
			{
				vector<bool> poss = remaining[i]->get_possible();
				for (int j = 0; j < 9; j++)
				{
					if (poss[j] == true)
					{
						val_remaining[j].push_back(remaining[i]);
					}
				}
			}
			//now if the remaining values are 2, 3, and 8, and the remaing[0] has (2,3), [1] has (2,8) and [2] has (2,3,8)
			//the the val_remaing will have rem[0,1,2] in val[1], rem[0,2] in val[2] and rem[1,2] in val[7]

			for (int i = 0; i < 9; i++)
			{
				if (val_remaining[i].size() != 0) //this set doesn't already have i+1, val_remaining[6].size() == 0 if 7 has already been found
				{
					if (val_remaining[i].size() == 1) //only one way to get '4' in that set
					{
						val_remaining[i][0]->update(i + 1); //takes the pointer to the square at a vector that only has one option, for instance
						//if square[4] is the only one that can be '9' then val_remaining[8] will be of size 1, so you know i = 8, and the size is
						//only 1 so you can do [i][0]. You want to update that value to the index of the array + 1, so if we're in index 8, we know the
						//value must be 9.
						_file << "Square[" << val_remaining[i][0]->get_row() << "][" << val_remaining[i][0]->get_col() << "]" << " has been set to " << i + 1 << " because only one in set with given value" << endl;
						set.remove_values(i); // if val_remianing[8] only has one option, 9 is updated so val_remaining[8] is true
						set.update_possible(); //not sure how necessary calling this here is... but it can't hurt right?
						
						//simplify(set); //something has changed, time to start over
					}
					/* something in here is messed up. Need to investigate what's making this program not even able to solve easy problems... 11/23/2015
					else if (val_remaining[i].size() == 2) //there are two (and only two) values in the set that get the '6'
						//This is where I can impliment a more complicated part of the algorithm. If there are only two squares
						//that have '6' in them, then obviously one of them has to be a six, and nothing else in that set can be as well
						//which is known already, but if those two are in the same other set, (same row/grid) or col/grid, can't be in same 
						//col/row... then 6 needs to be removed from all of the others in the set too, so there will have to be a function in
						//set that remove_from_possible_two(square1*, square2*, value) (should probably have the same function for if three are
						//in the same row/grid or col/grid and are the only ones that can have '6' (much less likely). The *square1 and *square2
						//will be passed in to make sure that '6' isn't removed from THEIR possible lists
					{
						_file << "Squares [" << val_remaining[i][0]->get_row() << "][" << val_remaining[i][0]->get_col() << "] and [" << val_remaining[i][1]->get_row() << "][" << val_remaining[i][1]->get_col() << "] are only two with value " << i + 1 << ". Now checking to see if in other set together" << endl;
						bool col_same = false, row_same = false, grid_same = false;//used to see if the squares share more than 1 set in common
						int num_sim = set.get_similarities_two(val_remaining[i][0], val_remaining[i][1], &col_same, &row_same, &grid_same);
						//int grid_num = 0, col_num = 0, row_num = 0;
						//these values will be used if they share more than one row/col
						int value_to_remove = i + 1;
						//11/5/2015 added in to replace the values that used to be passed in as pointers
						int set_index = 0;
						char set_type = 'z';
						//vector<square*> save;

						if (num_sim == 2 && set.already_removed(i) == false) //have two sets in common and this hasn't been done before
						{
							set.set_already_removed(i);
							//*change = 1; 11/5/2015 don't think this is necessary but very well could be wrong
							if (set.get_type() == 'r') //this set is a row
							{
								if (grid_same == true) // same row and grid
								{
									set_index = val_remaining[i][0]->get_grid();
									//set_type = 'g';
									_grid[set_index].remove_possible_other_set_two(val_remaining[i][0], val_remaining[i][1], i);
									_file << "They share the same grid, removed value " << i + 1 << "from all squares in Grid " << set_index << endl;

								}
							}
							else if (set.get_type() == 'c') //this set is a col
							{
								if (grid_same == true) // same col and grid
								{
									set_index = val_remaining[i][0]->get_grid();
									//set_type = 'g';
									_grid[set_index].remove_possible_other_set_two(val_remaining[i][0], val_remaining[i][1], i);
									_file << "They share the same grid, removed value " << i + 1 << "from all squares in grid " << set_index << endl;
								}
							}
							else if (set.get_type() == 'g') //this set is a grid
							{
								if (col_same == true) //same grid and row
								{
									set_index = val_remaining[i][0]->get_col();
									//set_type = 'c';
									_col[set_index].remove_possible_other_set_two(val_remaining[i][0], val_remaining[i][1], i);
									_file << "They share the same col, removed value " << i + 1 << "from all squares in col " << set_index << endl;
								}
								if (row_same == true) //same grid and col
								{
									set_index = val_remaining[i][0]->get_row();
									//set_type = 'r';
									_row[set_index].remove_possible_other_set_two(val_remaining[i][0], val_remaining[i][1], i);
									_file << "They share the same row, removed value " << i + 1 << "from all squares in row " << set_index << endl;
								}
							}
							//save.push_back(val_remaining[i][0]);
							//save.push_back(val_remaining[i][1]);
							//simplify(set); //something has changed, time to start over
							//return;
						}
						else
						{
							_file << "Nope" << endl;
						}
					}


					else if (val_remaining[i].size() == 3 && set.already_removed(i) == false)
					{
						bool col_same = false, row_same = false, grid_same = false;//used to see if the squares share more than 1 set in common
						int num_sim = set.get_similarities_three(val_remaining[i][0], val_remaining[i][1], val_remaining[i][2], &col_same, &row_same, &grid_same);
						//int grid_num = 0, col_num = 0, row_num = 0;
						//these values will be used if they share more than one row/col
						
						int set_index = 0;
						char set_type = 'z';
						vector<square*> save;
						int value_to_remove = i + 1;
						if (num_sim == 2) //have two sets in common
						{
							set.set_already_removed(i);
							//*change = 2;
							if (set.get_type() == 'r') //this set is a row
							{
								if (grid_same == true) // same row and grid
								{
									set_index = val_remaining[i][0]->get_grid();
									set_type = 'g';
									_grid[set_index].remove_possible_other_set_three(val_remaining[i][0], val_remaining[i][1], val_remaining[i][2], i);
									_file << "They share the same grid, removed value " << i + 1 << "from all squares in Grid " << set_index << endl;
								}
							}
							else if (set.get_type() == 'c') //this set is a col
							{
								if (grid_same == true) // same col and grid

								{
									set_index = val_remaining[i][0]->get_grid();
									set_type = 'g';
									_grid[set_index].remove_possible_other_set_three(val_remaining[i][0], val_remaining[i][1], val_remaining[i][2], i);
									_file << "They share the same grid, removed value " << i + 1 << "from all squares in grid " << set_index << endl;
								}
							}
							else if (set.get_type() == 'g') //this set is a grid
							{
								if (col_same == true) //same grid and row
								{
									set_index = val_remaining[i][0]->get_col();
									set_type = 'c';
									_col[set_index].remove_possible_other_set_three(val_remaining[i][0], val_remaining[i][1], val_remaining[i][2], i);
									_file << "They share the same col, removed value " << i + 1 << "from all squares in col " << set_index << endl;
								}
								if (row_same == true) //same grid and col
								{
									set_index = val_remaining[i][0]->get_row();
									set_type = 'r';
									_row[set_index].remove_possible_other_set_three(val_remaining[i][0], val_remaining[i][1], val_remaining[i][2], i);
									_file << "They share the same row, removed value " << i + 1 << "from all squares in row " << set_index << endl;
								}
							}
						}
						//save.push_back(val_remaining[i][0]);
						//save.push_back(val_remaining[i][1]);
						//save.push_back(val_remaining[i][2]);
						//simplify(set); //something has changed, time to start over
						return;
					}
					*/
					
					//this is where I should call to change the other sets that used to be done in board. This is where the change variable might be
					//useful.

					//find a way to compare if two squares have the same possibilities, using operator overloading
				}
			}
			//simplify_first();
			set.update_possible(); //will update the given set, so maybe a big update wont need to be called at the end
			if (set.is_complete())
			{
				_file << "This set is complete" << endl;
			}
		}
	}
	bool is_complete(void)
	{
		//something is saying that right now this is not complete even though I entered it 10/3/15
		//fixed the problem with initializing col/grid 10/3/15

		//TODO possibly inefficient way to do this, because each is_complete() updates the values which is probably soemthing like O(n^10) or something ridiculous
		//but becaus the max size is 9 algorithmic efficiency is really only for theory, in practice the times are probably about the same.
		for (int i = 0; i < 9; i++)
		{
			if (_row[i].is_complete() == false || _col[i].is_complete() == false || _grid[i].is_complete() == false)
			{
				return false;
			}
		}
		return true;
	}

	void write_to_file(string str)
	{
		_file << str << endl;
	}

};




#endif