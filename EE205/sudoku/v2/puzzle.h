/* file: puzzle_v2.h */
#ifndef PUZZLE_H
#define PUZZLE_H

#include <curses.h>
#include "cell.h"

class Puzzle
{
 public:

/* constructors */
Puzzle();
~Puzzle();

/* mutators */
void insert(chtype c); // inserts number at current position 
void insert(chtype c, int x, int y); // inserts number at current position 
void insertnote(char c); // inserts a note in current square
void hint();	// reveals answer for current cell
void giveup();	// reveals everything
bool submit();	// check user's solution and returns true if it is the correct solution
		// otherwise, it returns false and highlight incorrect answers

/* helpful public functions */
void moveup(void);
void movedown(void);
void moveleft(void);
void moveright(void);
void message(const char * str);
void clearmessage();

/* puzzle initialization functions */
void clear();
void make();

 private:

int row, col;	// user's position of cursor

WINDOW *wnd;
Cell cells[9][9];
bool changed;

/* helper functions */
int realrow(int i); // converts puzzle row value to display row value
int realcol(int i); // converts puzzle column value to display column value
int fakerow(int i); // converts display row value to puzzle row value
int fakecol(int i); // converts display column value to puzzle column value

void drawrow(int i); // draws a row
void drawhor(int i); // draws a row with a horizontal line
void drawbold(int i); // draws a border

char inttochar(int x);
int chtypetoint(chtype x); 
int findbox(const int x, const int y)const; // returns box number(1-9) of current cell

/* puzzle solving functions */
void elimrow(int x, int y); // eliminates possibilities by row
void elimcol(int x, int y); // eliminates possibilities by column
void elimbox(int x, int y); // eliminates possibilities by box
bool CompleteSolution()const; // true if answer key is complete

};

#include "puzzle_inl.h"

#endif
