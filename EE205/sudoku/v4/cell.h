/* file: cell_v2.h */

#ifndef CELL_H
#define CELL_H

#define BLANK 0

class Cell
{

public:
Cell(); // Constructor that initializes all data to 0
Cell(int ans, bool given); // Constructor, given a number, inputs it into the cell (blank if given nothing)

/* mutators */
void clear();	// resets cell to factory default
void nincrement(); //increments the note count
void nclear(); // clears the note count
void hide();	// sets the cell to be initially blank
void setanswer(int x);	// sets the answer for the cell
void setnumber(int x);	// sets number of the cell (user input)
void reveal();	// sets the cell to be initially given
void resetposs(); // resets all the possibilities to be true
bool eliminate(const int x); // true if it eliminates x from possible solutions
void setlevel(const int x); // Sets the protection level (Guessing algorithm)



/* accessor */
int getncount() const;	// returns note count
bool isgiven() const;	// returns true if the cell contains a given number
int getanswer() const;	// returns the answer
bool iscorrect() const;	// returns true if the inserted number is correct
int getnumber() const; // return the current number in the cell
bool possibility(const int x) const; // returns true if x is a possibility
float probability(const int x) const; // returns probability of x being a solution
int getlevel() const; //returns the protection level (Guessing algorithm) 



private:

int ncount; //counts the number of notes currently in the cell
int number; //Current number in that cell
int answer; //Number that is "supposed" to be in that cell (solution)
bool fgiven; //flag for if the number is a given or not
bool possible[10]; // possible answers for cell
int protlevel; //Sets the protection level for our guessing algorithim

};

#include "cell_inl.h"

#endif
