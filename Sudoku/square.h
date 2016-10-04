#ifndef SQUARE_H
#define SQUARE_H

#include "board.h"
//#include "Set.h"
#include "windows.h"

using namespace std;

/*
The square is just that, a square on the board. It has a value, whether is was initially given or not (more useful if a human is solving, less so if the
computer is working on it. The most important part is the _possible, which checks to see what values are still able to be put in there.
It would be nice to have other variables, so that the program could "echo out" so to speak when something changes. Right now I just want to get it to work,
so it will likely be O(N^2 or 3, or whatever), passing over each unsolved square and updating it, regardless of whether there has been a change each time. 
Ideally it would only pass over the square if something in its row/col/grid has been changed, but that will be for a later version.
*/

/*
10/11/2015 stupid idea. Rather than having the possible as a boolean array, so save space, could turn the boolean array into an 8-bit binary number
and store the integer representation. Actually that might not be the worst idea in the world, it would making comparing two much simpler. The reason you want
to compare to is that if 2 squares in a set have the same 2 possible (or 3 have same 3 possible, etc), you know the rest of the numbers in that set cannot have
those values, for instance, 2 squares next to each other can either be 8 or 9, you know that nothing else in that set can be 8 or 9 because if it were, then 
the problem wouldn't be solvable. */

class square
{
private:
	bool _known;
	int _val;
	vector<bool> _possible; //maybe not bool
	int _num_options; //number of possible numbers this square could be.
	int _row;
	int _col;
	int _grid;
	/*Set* _row_ptr;
	Set* _col_ptr;
	Set* _grid_ptr;*/

public:
	square()
	{
		/*_row_ptr = NULL;
		_col_ptr = NULL;
		_grid_ptr = NULL;*/
		//maybe save time by not setting _possible for _given ones
		for (int i = 0; i < 9; i++)
		{
			_possible.push_back(true); //in the beginning ANYTHING IS POSSIBLEEEEE
			_num_options = 9;
		}
	}
	void set_known(bool known)
	{
		_known = known;
	}
	bool get_known(void)
	{
		return _known;
	}
	void set_val(int val)
	{
		_val = val;
	}
	int get_val(void)
	{
		return _val;
	}
	void set_col(int col)
	{
		_col = col;
	}
	int get_col(void)
	{
		return _col;
	}

	void set_row(int row)
	{
		_row = row;
	}
	int get_row(void)
	{
		return _row;
	}

	void set_grid(int grid)
	{
		_grid = grid;
	}
	int get_grid(void)
	{
		return _grid;
	}

	/*void set_row_ptr(Set* row)
	{
		_row_ptr = row;
	}
	Set * get_row_ptr()
	{
		return _row_ptr;
	}

	void set_col_ptr(Set* col)
	{
		_col_ptr = col;
	}
	Set* get_col_ptr(Set* col)
	{
		return _col_ptr;
	}

	void set_grid_ptr(Set* grid)
	{
		_grid_ptr = grid;
	}
	Set* get_grid_ptr()
	{
		return _grid_ptr;
	}*/


	void remove_from_possible(int known)
	{
		if (_possible[known - 1] == true)
			//I just saved myself the biggest headache of having _num_options decrimented way too much when a 6 is in the same row/col so both call this function
		{
			_possible[known - 1] = false;
			_num_options -= 1;
			
			/*MUCH MORE EFFICENT WAY TO DO IT THAT WILL BE IMPLIMENTED AT A LATER TIME*/ //10/11/15
			/*if (_num_options == 1) //only one thing it can be
			{
				_given = true;
				for (int i = 0; i < 9; i++)
				{
					if (_possible[i])
					{
						set_val(i + 1);
					}
				}
			}*/
		}
	}
	int get_num_options()
	{
		return _num_options;
	}
	void update(int value)
	{
		_known = true;
		_val = value;
	}
	vector<bool> get_possible()
	{
		return _possible;
	}

	int get_only() //only called if know that _num_options == 1
	{
		if (_num_options == 1)
		{
			for (int i = 0; i < 9; i++)
			{
				if (_possible[i])
				{
					return (i+1);
				}
			}
		}
		else
		{
			//cout << "Something went wrong in the get_only() function" << endl;
			//system("pause");
		}
	}

	bool operator ==(const square& sq2)
	{
		if (_row == sq2._row && _col == sq2._col && _grid == sq2._grid)
		{
			return true;
		}
		return false;
	}
	/*void print_possible(void) // may not be able to print in a grid because of how the curser prints
	{
		for (int i = 0; i < 9; i++)
		{
			/*if (i == 3 || i == 6)
			{
				cout << endl;
			}
			if (_possible[i] == true)
			{
				cout << i + 1;
			}
			else
			{
				cout << "*";
			}
		}

	}*/



};

#endif