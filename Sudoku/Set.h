#ifndef SET_H
#define SET_H

#include "square.h"
#include "board.h"

using namespace std;

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>

/*
Set is the parent class for Row, Col, and Grid. They all have different properties but they are all collections of 9 squares, and to
be complete they have to have the numbers 1-9 in all of them. Initializing is the main difference, but once that is done they can be roughly
treated the same.

*/

class Set
{
protected: //maybe private???? Need to research difference 
	int _index;
	bool _values[9]; //if _values[0] == true, then this set already has "1", _values[7] -> "6"
	square* _squares[9]; //the squares in the set, staightforward for row/col, less simple for grid
	char _type;
	bool _already_removed[9]; //This is used for step 2 of the simplifying program. In a set if 2 squares are the only one's able to have a given value,
								//if they share another set (in the same row/grid, col/grid, then that value can be removed from the possible values in every
								//other square in that set. The functions are remove_similar_two and _three if you would like to see the details. The purpose of
								//this variable is to keep the process from repeating each time you look at the set. If the value has been removed once, it doesn't
								//need to be removed each time. Could also help with recursion because the function can be called without worry of it getting caught in
								//a loop... like it is right now (11/23/2015)

public:
	Set()
	{
		_index = 0;

		for (int i = 0; i < 9; i++)//maybe off by 1
		{
			_values[i] = false;
			_already_removed[i] = false;
		}
	}
	void initialize(int index, square board[9])
	{
		//will be overridden by children. Getting the squares of a row will
		//be different than getting the squares of a col or grid.
	}

	bool is_complete(void)
		//the same for all the types, checks to see if 1-9 are present
	{
		update_values();
		for (int i = 0; i < 9; i++)
		{
			if (_values[i] == false)
			{
				return false;
			}
		}
		return true;
	}

	char get_type()
	{
		return _type;
	}

	void set_already_removed(int index) //pass in the index, not the value
	{
		_already_removed[index] = true;
	}

	bool already_removed(int index)
	{
		if (_already_removed[index] == false)//has not already been removed
		{
			return false;
		}
		else
		return true;
	}

	void set_elements(square* elements[9])
		//once the squares that are part of the set are collected, this imports them
	{
		for (int i = 0; i < 9; i++) //possibly not the most efficient, but not sure if there is a way to copy over "square * []"
		{
			_squares[i] = elements[i];
		}
	}

	square** get_elements(void)
		//returns the squares in the set, not sure if * square[] or square**
	{
		return _squares;
	}

	void print_set(void)
		//perhaps inefficient
	{
		for (int i = 0; i < 9; i++)
		{
			int val = 0;
			square temp_square = *_squares[i];
			val = temp_square.get_val();
			cout << val << ",";
			//val = _squares[i].get_val();
		}
		//cout << endl;
	}

	vector<square> get_existing(void)
		// if the set is "1,5,0,0,0,2,3,0,0" this will return a vector of THE SQUARES (not just ints) "1,5,2,3"
	{
		vector<square> already_exist;
		for (int i = 0; i < 9; i++)
		{
			square temp = *_squares[i];
			if (temp.get_val() != 0) // not blank
			{
				already_exist.push_back(temp);
			}
		}
		return already_exist;
	}

	vector<square*> get_remaining(void)
		// if the set is "1,5,0,0,0,2,3,0,0" this will return a vector REFERENCES of the SQUARES ("0,0,0,0,0") to work with the unsolved ones
	{
		vector<square*> remaining;
		for (int i = 0; i < 9; i++)
		{
			square temp = *_squares[i];
			if (_squares[i]->get_val() == 0) // blank
			{
				remaining.push_back(_squares[i]);
			}
		}
		return remaining;
	}

	void set_values(vector<int> already_exist)
		//should work in conjuction with "get_existing", setting the bool _values, but it's passing in a vector
		//of ints, and the above funtion returns a vector of squares. May be possible inefficiency somewhere in the program
	{
		for (int i = 0; i < already_exist.size(); i++)
		{
			_values[already_exist[i] - 1] = true;
		}
	}

	void print_missing_to_file(ofstream file)
	{
		file << "This set is still missing values: ";
		for (int i = 0; i < 9; i++)
		{
			if (_values[i]== false)
			{
				file << i + 1 << ", ";
			}
		}
		file << endl;
	}

	void set_possible(vector<int> already_exist)
		//should be called after set_values, or after on update has been made to the known values in the set, 
		//it will take the boolean set and for all that are not in the set, will tell each square that it no longer can be that value. The equivalent 
		//of writting the little numbers in the box, and erasing them as you find solutions. Should be called in the initialize function for Row/Grid/Col 
		//and then later on

		//10/11/15, killing me how inefficient this is, maybe there a way to do it faster, will investigate further. Also confused on some of the inputs
		//get_existing() pulls gives a vector of squares, but I've been treating it as a vector of ints I think and it's been working fine...
		//nevermind, haven't called already_exists() yet, just been making vector_int in the initialization and been using that.
	{
		for (int i = 0; i < 9; i++)
		{
			if (!_squares[i]->get_known())//wasn't given by the computer
			{
				for (int j = 0; j < already_exist.size(); j++)// maybe <= or <, cant remember
				{
					_squares[i]->remove_from_possible(already_exist[j]);
				}
			}
		}
	}

	void update_possible()
		//will be called at the end of each cycle (or before once I get a more efficient version) will get the existing values in the set and update the
		//remaining unfinished squares

		//will have to wait a while before able to test effectiveness of this function
	{
		vector<int> already_exist; //will be given to set_possible at the end
		vector<square> existing;

		existing = get_existing(); //now have a vector of squares of know values in the set
		for (int i = 0; i < existing.size(); i++)
		{
			already_exist.push_back(existing[i].get_val());
		}

		set_possible(already_exist);
		set_values(already_exist);
	}

	void update_values()
		//the reason I have to do this is because when a value is changed in more than one set, it doesn't update that the "values" of the other 3 sets that the
		//square is in theoretically will only need to be called once at the beginning. Not SUPER efficient... but I've been coding 2 hours, I just want to get this
		//working
	{
		for (int i = 0; i < 9; i++)
		{
			if (_squares[i]->get_known()) //if the value is known
			{
				_values[_squares[i]->get_val() - 1] = true;
			}
		}

	}

	void remove_values(int val)
	//this function will take a val (val = 3) and set _values[val] = true meaning that 4 has been found
	{
		_values[val] = true;

		for (int i = 0; i < 9; i++)
		{
			if (_squares[i]->get_known() == false)
			{
				_squares[i]->remove_from_possible(val +1);
			}
		}
	}

	void remove_possible_other_set_two(square* sq1, square* sq2, int value)
		//this function takes two sqauares that share two sets, and in one set they are the only ones that can be that value.
		//this is called by the first set on the second set (still working on how exactly), saying to remove value from all the squares
		//except these two.
	{
		for (int i = 0; i < 9; i++)
		{
			if (!(_squares[i] == sq1) && !(_squares[i] == sq2) && !_squares[i]->get_known())
			{
				_squares[i]->remove_from_possible(value);
			}
		}
	}

	void remove_possible_other_set_three(square* sq1, square* sq2, square* sq3, int value)
		//this function takes two sqauares that share two sets, and in one set they are the only ones that can be that value.
		//this is called by the first set on the second set (still working on how exactly), saying to remove value from all the squares
		//except these two.
	{
		for (int i = 0; i < 9; i++)
		{
			if (!(_squares[i] == sq1) && !(_squares[i] == sq2) && !(_squares[i] == sq3) && !_squares[i]->get_known())
			{
				_squares[i]->remove_from_possible(value);
			}
		}
	}

	int get_similarities_two(square* sq1, square* sq2, bool* col, bool* row, bool* grid)
		//this will return how many values of the grid/col/row they have in common, every one will have 1 or 2, 2 meaning they have two similar sets
		//there should be a way to return WHAT similarities it has
	{
		int sim = 0;
		if (sq1->get_col() == sq2->get_col())
		{
			sim++;
			*col = true;
		}
		if (sq1->get_row() == sq2->get_row())
		{
			sim++;
			*row = true;
		}
		if (sq1->get_grid() == sq2->get_grid())
		{
			sim++;
			*grid = true;
		}
		return sim;
	}

	int get_similarities_three(square* sq1, square* sq2, square* sq3, bool* col, bool* row, bool* grid)
	{
		int sim = 0;
		if (sq1->get_col() == sq2->get_col() && sq1->get_col() == sq3->get_col()) //1 == 2, 1==3
		{
			sim++;
			*col = true;
		}
		if (sq1->get_row() == sq2->get_row() && sq1->get_row() == sq3->get_row()) // 1 == 2, 1 == 3
		{
			sim++;
			*row = true;
		}
		if (sq1->get_grid() == sq2->get_grid() && sq1->get_grid() == sq3->get_grid()) //1 ==2, 1 ==3
		{
			sim++;
			*grid = true;
		}
		return sim;
	}

	/*void simplify_second(int *set_index, char *set_type, vector<square*> *save, int *change, int *value_to_remove)
		//The reason simplify was split into two functions 10/22/2015 is because set have no knowledge of other sets
		//In order to delete values from other sets, the set has to have a way to access another set (grid[0] to access row[1]) which I do not think it can
		//If I'm able to do that the logic should be the same and I can just copy and paste it back, but for the moment this is all I can think of
		//This function is passed pointers to the type and index of a set that needs to be changed, as well as the pointer to a vector of squares of the
		//set that should be exempted from the deletion.
	{
		if (!is_complete())
		{
			vector<square*> remaining = get_remaining();
			//in a set, if there is only one square that has the value '8' in it, that has to be an 8. 
			//for every _value, have a vector of vector of ints/squares, if the set already has a '5' then name[4] will be empty,
			//we're looking for a vector that has only one value in it.
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
				if (val_remaining[i].size() != 0) //this set doesn't already have i+1
				{
					if (val_remaining[i].size() == 1) //only one way to get '4' in that set
					{
						val_remaining[i][0]->update(i + 1); //takes the pointer to the square at a vector that only has one option, for instance
						//if square[4] is the only one that can be '9' then val_remaining[8] will be of size 1, so you know i = 8, and the size is
						//only 1 so you can do [i][0]. You want to update that value to the index of the array + 1, so if we're in index 8, we know the
						//value must be 9.
						_values[i] = true; // if val_remianing[8] only has one option, 9 is updated so val_remaining[8] is true
						update_possible(); //not sure how necessary calling this here is... but it can't hurt right?
					}
					else if (val_remaining[i].size() == 2) //there are two (and only two) values in the set that get the '6'
						//This is where I can impliment a more complicated part of the algorithm. If there are only two squares
						//that have '6' in them, then obviously one of them has to be a six, and nothing else in that set can be as well
						//which is known already, but if those two are in the same other set, (same row/grid) or col/grid, can't be in same 
						//col/row... then 6 needs to be removed from all of the others in the set too, so there will have to be a function in
						//set that remove_from_possible_two(square1*, square2*, value) (should probably have the same function for if three are
						//in the same row/grid or col/grid and are the only ones that can have '6' (much less likely). The *square1 and *square2
						//will be passed in to make sure that '6' isn't removed from THEIR possible lists
					{
						bool col_same = false, row_same = false, grid_same = false;//used to see if the squares share more than 1 set in common
						int num_sim = get_similarities_two(val_remaining[i][0], val_remaining[i][1], &col_same, &row_same, &grid_same);
						//int grid_num = 0, col_num = 0, row_num = 0;
						//these values will be used if they share more than one row/col
						*value_to_remove = i + 1;
						if (num_sim == 2) //have two sets in common
						{
							*change = 1;
							if (_type == 'r') //this set is a row
							{
								if (grid_same == true) // same row and grid
								{
									*set_index = val_remaining[i][0]->get_grid();
									*set_type = 'g';
									//needs to call grid[grid_num].remove_possible_other_set_two(val_remaining[i][1], val_remaining[i][2], val_to_remove)
									//or will pass back these details. Must be careful of typos
									
								}
							}
							else if (_type == 'c') //this set is a col
							{
								if (grid_same == true) // same col and grid
								{
									*set_index = val_remaining[i][0]->get_grid();
									*set_type = 'g';
								}
							}
							else if (_type == 'g') //this set is a grid
							{
								if (col_same == true) //same grid and row
								{
									*set_index = val_remaining[i][0]->get_col();
									*set_type = 'c';
								}
								if (row_same == true) //same grid and col
								{
									*set_index = val_remaining[i][0]->get_row();
									*set_type = 'r';
								}
							}
							save->push_back(val_remaining[i][0]);
							save->push_back(val_remaining[i][1]);
							return;
						}
					}
					else if (val_remaining[i].size() == 3)
					{
						bool col_same = false, row_same = false, grid_same = false;//used to see if the squares share more than 1 set in common
						int num_sim = get_similarities_three(val_remaining[i][0], val_remaining[i][1], val_remaining[i][2], &col_same, &row_same, &grid_same);
						//int grid_num = 0, col_num = 0, row_num = 0;
						//these values will be used if they share more than one row/col
						*value_to_remove = i + 1;
						if (num_sim == 2) //have two sets in common
						{
							*change = 2;
							if (_type == 'r') //this set is a row
							{
								if (grid_same == true) // same row and grid
								{
									*set_index = val_remaining[i][0]->get_grid();
									*set_type = 'g';
								}
							}
							else if (_type == 'c') //this set is a col
							{
								if (grid_same == true) // same col and grid
								{
									*set_index = val_remaining[i][0]->get_grid();
									*set_type = 'g';
								}
							}
							else if (_type == 'g') //this set is a grid
							{
								if (col_same == true) //same grid and row
								{
									*set_index = val_remaining[i][0]->get_col();
									*set_type = 'c';
								}
								if (row_same == true) //same grid and col
								{
									*set_index = val_remaining[i][0]->get_row();
									*set_type = 'r';
								}
							}
						}
						save->push_back(val_remaining[i][0]);
						save->push_back(val_remaining[i][1]);
						save->push_back(val_remaining[i][2]);
						return;
					}
					//find a way to compare if two squares have the same possibilities, using operator overloading
				}
			}
			simplify_first();
			update_possible(); //will update the given set, so maybe a big update wont need to be called at the end

		}
	}*/

};



#endif