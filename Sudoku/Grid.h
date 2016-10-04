#ifndef GRID_H	
#define GRID_H

#include "Set.h"
#include "board.h"

class Grid: public Set
{
private:


public:
	void initialize(int row_index, int col_index, square board[9][9]) //This may not work super well
	{

		_type = 'g';

		int num = get_grid_num(col_index, row_index);
		square * elements[9];
		elements[0] = &board[row_index][col_index];
		board[row_index][col_index].set_grid(num);
		elements[1] = &board[row_index][col_index+1];
		board[row_index][col_index + 1].set_grid(num);
		elements[2] = &board[row_index][col_index+2];
		board[row_index][col_index + 2].set_grid(num);
		elements[3] = &board[row_index+1][col_index];
		board[row_index + 1][col_index].set_grid(num);
		elements[4] = &board[row_index+1][col_index + 1];
		board[row_index + 1][col_index + 1].set_grid(num);
		elements[5] = &board[row_index+1][col_index + 2];
		board[row_index + 1][col_index + 2].set_grid(num);
		elements[6] = &board[row_index+2][col_index];
		board[row_index + 2][col_index].set_grid(num);
		elements[7] = &board[row_index+2][col_index + 1];
		board[row_index + 2][col_index + 1].set_grid(num);
		elements[8] = &board[row_index+2][col_index + 2];
		board[row_index + 2][col_index + 2].set_grid(num);

			//elements[i] = &board[index][i];
		set_elements(elements);


		vector<int> already_exists;
		//square * elements[9];
		for (int i = 0; i < 9; i++)
		{
			int val = 0;
			//elements[i] = &board[index][i]; //difference between row/col
			if (elements[i]->get_val() != 0)
			{
				already_exists.push_back(elements[i]->get_val());
			}
		}
		set_values(already_exists);
		set_possible(already_exists);
		//set_elements(elements);
		//set_values(already_exists);
	}

	int get_grid_num(int col, int row)
	{
		int num = 0;
		if (row == 0)
		{
			if (col == 0)
			{
				num = 0;
			}
			if (col == 3)
			{
				num = 1;
			}
			if (col == 6)
			{
				num = 2;
			}
		}
		if (row == 3)
		{
			if (col == 0)
			{
				num = 3;
			}
			if (col == 3)
			{
				num = 4;
			}
			if (col == 6)
			{
				num = 5;
			}
		}
		if (row == 6)
		{
			if (col == 0)
			{
				num = 6;
			}
			if (col == 3)
			{
				num = 7;
			}
			if (col == 6)
			{
				num = 8;
			}
		}
		return num;
	}

	//add a function to take in the col and row indexes and turn them into grid numbers. Pretty straight forward but would make the above 
	//function needlessly messy (10/20/2015) Done

};




#endif