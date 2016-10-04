#ifndef COLUMN_H
#define COLUMN_H

#include "Set.h"

class Column: public Set
{
private:


public:
	void initialize(int index, square board[9][9])
	{
		_type = 'c';

		vector<int> already_exists;
		square * elements[9];
		for (int i = 0; i < 9; i++)
		{
			board[i][index].set_col(index);
			int val = 0;
			elements[i] = &board[i][index]; //difference between row/col  
			if (elements[i]->get_val() != 0)
			{
				already_exists.push_back(elements[i]->get_val());
			}
		}
		set_elements(elements);
		set_values(already_exists);
		set_possible(already_exists);
		/*square * elements[9];
		for (int i = 0; i < 9; i++)
		{
			elements[i] = &board[index];
		}
		set_elements(elements);


		vector<int> already_exists;
		//square * elements[9];
		for (int i = 0; i < 9; i++)
		{
			int val = 0;
			elements[i] = &board[index]; //difference between row/col  
			if (elements[i]->get_val() != 0)
			{
				already_exists.push_back(elements[i]->get_val());
			}
		}
		set_elements(elements);
		//set_values(already_exists);*/
	}


};



#endif