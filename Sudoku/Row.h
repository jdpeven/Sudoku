#ifndef ROW_H	
#define ROW_H

#include "Set.h"

class Row: public Set
{
private:


public:
	void initialize(int index, square board[9][9])
	{
		_type = 'r';

		vector<int> already_exists;
		square * elements[9];
		for (int i = 0; i < 9; i++)
		{
			board[index][i].set_row(index);
			int val = 0;
			elements[i] = &board[index][i]; //difference between row/col  
			if (elements[i]->get_val() != 0)
			{
				already_exists.push_back(elements[i]->get_val()); //says that integers 3, 5, 9, etc already exist
			}
		}
		set_elements(elements);
		set_values(already_exists);
		set_possible(already_exists);
	}


};



#endif