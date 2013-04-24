/* file: puzzle_v2.cc */

#include <curses.h>
#include "puzzle.h"
#include "cell.h"
#include <ncurses.h>
#include <iostream>
using namespace std;

/************************************************/
/*						*/
/*	Constructors				*/
/*						*/
/************************************************/
Puzzle :: Puzzle() : row(0), col(0), changed(true)
{
	wnd = initscr();

/* title screen */
	move(3,20);
	deleteln();
	insstr("/*************************************/");
	move(4,20);
	deleteln();
	insstr("/*                                   */");
	move(5,20);
	deleteln();
	insstr("/*          XTREME SUDOKU            */");
	move(6,20);
	deleteln();
	insstr("/*                                   */");
	move(7,20);
	deleteln();
	insstr("/*************************************/");
	move(9,12);
	insstr("by Matthew Fall, Ken Wallace, Sammy Khamis, Ed Nerad");
	move(15,12);
	insstr("please expand window size for the Extreme experience");
	move(20,28);
	insstr("press any key to continue");
	move(20,53);
	refresh();
	getchar();

/* initialize board */
	drawbold(0);
		drawrow(1);
		drawrow(2);
	        drawhor(3);
		drawrow(4);
		drawrow(5);
	        drawhor(6);
		drawrow(7);
		drawrow(8);
	drawbold(9);
		drawrow(10);
		drawrow(11);
	        drawhor(12);
		drawrow(13);
		drawrow(14);
	        drawhor(15);
		drawrow(16);
		drawrow(17);
	drawbold(18);
		drawrow(19);
		drawrow(20);
	        drawhor(21);
		drawrow(22);
		drawrow(23);
	        drawhor(24);
		drawrow(25);
		drawrow(26);
	drawbold(27);

/* display controls */
	move(1, 65);
	insstr("Controls");
	move(2, 65);
	insstr("wasd or hjkl = navigation");
	move(3, 65);
	insstr("n = enter note mode");
	move(4, 68);
	insstr("-- number = add note (max 3)");
	move(5, 68);
	insstr("-- BACKSPACE = clear all notes");
	move(6, 65);
	insstr("H = display hint");
	move(7, 65);
	insstr("G = give up");
	move(8, 65);
	insstr("S = submit solution");
	move(9, 65);
	insstr("Q = quit");

/* initialize cursor starting position */
row = 14;
col = 32;
move(row,col);
refresh();


}

Puzzle :: ~Puzzle()
{	endwin();	}

/************************************************/
/*						*/
/*	Mutators				*/
/*						*/
/************************************************/

void Puzzle :: insert(chtype c)
{
	/* don't insert anything if the number is already given */
	if(cells[realrow(row)][realcol(col)].isgiven())
		message("I wouldn't recommend changing that");

	else
	{	delch();
		insch(c);
		refresh();

		/* update data */
		if((c & A_CHARTEXT) == ' ' || (c & A_CHARTEXT) == 8)
			cells[realrow(row)][realcol(col)].setnumber(0);
		else
			cells[realrow(row)][realcol(col)].setnumber(chtypetoint(c));
	}
}

void Puzzle :: insert(chtype c, int x, int y)
{	move(x,y);
	delch();
	insch(c);
	move(row,col);
	refresh();
}

void Puzzle :: insertnote(char c)
{
	chtype ch;
	ch = c | A_BOLD;

	/* clears all notes */
	if(c == 8)
	{
		for(int i = col-3 ; i != col+3 ; i+=2)
		{	move(row-1 , i);
			delch();
			insch(' ');
		}
		cells[realrow(row)][realcol(col)].nclear();
	}

	/* if you try to add more than 3 notes */
	else if(cells[realrow(row)][realcol(col)].getncount() == 3)
	message("3 notes yo");

	/* add the note */
	else
	{
	move(row-1, col-3+2*cells[realrow(row)][realcol(col)].getncount());
	delch();
	insch(ch);
	cells[realrow(row)][realcol(col)].nincrement();
	}
	
	move(row, col);
	refresh();


}

void Puzzle :: hint()
{	chtype ans;

	/* get the answer */
	ans = inttochar(cells[realrow(row)][realcol(col)].getanswer()) | A_STANDOUT;

	/* show it */
	insert(ans);

	/* update the data */
	cells[realrow(row)][realcol(col)].reveal();
}

void Puzzle :: giveup()
{	for(int i = 0; i < 9; i++)
	   for(int j = 0; j < 9; j++)
	   	if(!cells[i][j].isgiven())
			insert(inttochar(cells[i][j].getanswer()), fakerow(i), fakecol(j));
	   
}

bool Puzzle :: submit()
{	bool correct = true;
	chtype num;

	for(int i = 0; i < 9; i++)
	   for(int j = 0; j < 9; j++)
		if(!cells[i][j].iscorrect())
		{	num = inttochar(cells[i][j].getnumber()) | A_REVERSE;
			insert(num, fakerow(i), fakecol(j));
			correct = false;
		}

	return correct;
}

/************************************************/
/*						*/
/*	Helpful public functions		*/
/*						*/
/************************************************/

void Puzzle :: message(const char * str)
{
	move(30, 1);
	deleteln();
	insstr(str);
	move(row,col);
	refresh();
}

void Puzzle :: clearmessage()
{
	move(30, 1);
	deleteln();
	move(row,col);
	refresh();
}

void Puzzle :: moveup(void)
{	/* move cursor to opposite side if end of board is reached */
	if(row == 2)	row = 26;
	else		row -=3;
	move(row,col);
	refresh();
}

void Puzzle :: movedown(void)
{	/* move cursor to opposite side if end of board is reached */
	if(row == 26)	row = 2;
	else		row +=3;
	move(row,col);
	refresh();
}

void Puzzle :: moveleft(void)
{	/* move cursor to opposite side if end of board is reached */
	if(col == 4)	col = 60;
	else		col -=7;
	move(row,col);
	refresh();
}

void Puzzle :: moveright(void)
{	/* move cursor to opposite side if end of board is reached */
	if(col == 60)	col = 4;
	else		col +=7;
	move(row,col);
	refresh();
}

/************************************************/
/*						*/
/*	Puzzle Initialization functions		*/
/*						*/
/************************************************/

void Puzzle :: clear()
{
	for(int i = 0; i < 9; i++)
	   for(int j = 0; j < 9; j++)
	   {	cells[i][j].setanswer(0);
		cells[i][j].hide();
		cells[i][j].nclear();
		cells[i][j].resetposs();
		insert(' ', fakerow(i), fakecol(j));
	   }
}

void Puzzle :: make()
{	chtype number;

	/* this is an easy puzzle that can be solved without guess mode */
	/* puzzle 1 easy book */
/*
	int solution[9][9] = {
	{3,0,1,0,7,9,0,2,5},
	{0,0,0,6,0,0,4,1,7},
	{0,0,0,0,1,5,3,0,0},
	{0,9,0,0,4,7,0,0,2},
	{0,0,4,3,0,8,0,7,0},
	{0,8,0,9,6,0,5,3,0},
	{7,0,5,0,9,6,0,4,8},
	{2,1,0,5,0,0,7,0,6},
	{0,4,0,7,0,1,2,5,0} };
*/

	/* another easy puzzle */
	/* puzzle 80 easy book */
/*
	int solution[9][9] = {
	{5,4,0,0,0,0,0,0,0},
	{0,0,0,7,0,0,0,0,0},
	{0,0,0,0,0,1,0,5,6},
	{0,7,0,0,0,0,0,3,0},
	{0,0,1,0,0,9,0,0,2},
	{8,0,5,0,0,0,0,0,0},
	{4,9,0,0,0,5,0,8,0},
	{0,3,2,9,0,0,4,7,0},
	{0,0,0,6,0,0,0,0,9} };

*/
	/* this is a medium puzzle that we must use the guess mode to solve */
	/* puzzle 40 medium book */

	int solution[9][9] = {
	{1,0,0,0,8,5,0,0,7},
	{0,0,0,0,3,0,0,0,0},
	{0,4,0,0,0,0,6,5,0},
	{5,0,0,0,7,6,0,0,0},
	{2,9,0,0,0,0,0,0,0},
	{0,0,4,5,0,3,0,8,0},
	{0,6,0,0,0,0,9,1,0},
	{0,0,0,9,0,0,0,0,0},
	{3,7,0,0,2,4,0,0,0} };

	/* insert answer matrix into cells */
	for(int i = 0; i < 9; i++)
	   for(int j = 0; j < 9; j++)
		cells[i][j].setanswer(solution[i][j]);

   /* solve */
   while(!CompleteSolution())
   {
	while(changed)
	{ changed = false;
	for(int i = 0; i < 9; i++)
	   for(int j = 0; j < 9; j++)
	   {
		elimrow(i,j);
		elimcol(i,j);
		elimbox(i,j);
	   }
	}
	if(!CompleteSolution())
	{	message("Time to Guess");
		break;
	}
   }
}

/************************************************/
/*						*/
/*	Helper Functions			*/
/*						*/
/************************************************/
void Puzzle :: drawrow(int i)
{	
	chtype bold = ' ' | A_REVERSE;
	chtype line = '|';
	chtype space = ' ';

	for(int n = 0 ; n < 64 ; n++)
	{

		move(i,col);
		delch();

		if(n%21 == 0)		insch(bold);
		else if(n%7 == 0)	insch(line);
		else			insch(space);
	
		refresh();
		col++;
	}
	col = 0;
}

void Puzzle :: drawhor(int i)
{	
	chtype bold = ' ' | A_REVERSE;
	chtype line = '|';
	chtype hor = '_';

	for(int n = 0 ; n < 64 ; n++)
	{
		move(i,col);
		delch();

		if(n%21 == 0)		insch(bold);
		else if(n%7 == 0)	insch(line);
		else			insch(hor);
	
		refresh();
		col++;
	}
	col = 0;
}

void Puzzle:: drawbold(int i)
{
	chtype dc = ' ' | A_REVERSE;

	for(int n = 0 ; n < 64 ; n++)
	{	
		move(i,col);
		delch();	

					insch(dc);

		refresh();
		col++;
	}	
	col = 0;
}

char Puzzle :: inttochar(int x)
{	return (char)(((int)'0') + x);	}

int Puzzle :: chtypetoint(chtype x)
{	char ch;
	ch = x & A_CHARTEXT;
	return (int)ch-(int)'0';
}

int Puzzle :: findbox(const int x, const int y)const
{
	if(x < 3)	// row 1
	{
		if(y < 3)	// box 1
		return 1;
		else if(y > 5)	// box 3
		return 3;
		else 		// box 2
		return 2;
	}

	else if(x > 5) 	// row 3
	{
		if(y < 3)	// box 7
		return 7;
		else if(y > 5)	// box 9
		return 9;
		else 		// box 8
		return 8;
	}

	else		// row 2 
	{
		if(y < 3)	// box 4
		return 4;
		else if(y > 5)	// box 6
		return 6;
		else 		// box 5
		return 5;
	}

}

/************************************************/
/*						*/
/*	Puzzle Solving Functions		*/
/*						*/
/************************************************/

void Puzzle :: elimrow(int x, int y)
{
	/* only eliminate if there isn't an answer in the cell */
	if(!cells[x][y].getanswer())
	/* eliminate all the possibilities by row */
	for(int i = 0; i < 9; i++)	
		if(cells[x][y].eliminate(cells[x][i].getanswer()))
		changed = true;
	
}


void Puzzle :: elimcol(int x, int y)
{
	/* only eliminate if there isn't an answer in the cell */
	if(!cells[x][y].getanswer()) 
	/* eliminate all the possibilities by column */
	for(int i = 0; i < 9; i++)
		if(cells[x][y].eliminate(cells[i][y].getanswer()))
		changed = true;
}

void Puzzle :: elimbox(int x, int y)
{
	/* only eliminate if there isn't an answer in the cell */
	if(!cells[x][y].getanswer()) 
	/* eliminate all the possibilities by box */
	switch(findbox(x, y))
	{
	case 1:
		for(int i=0;i<3;i++) 
		   for(int j=0;j<3;j++)
			if(cells[x][y].eliminate(cells[i][j].getanswer()))changed = true;
		break;
	case 2:
		for(int i=0;i<3;i++) 
		   for(int j=3;j<6;j++)
			if(cells[x][y].eliminate(cells[i][j].getanswer()))changed = true;
		break;
	case 3: 
		for(int i=0;i<3;i++) 
		   for(int j=6;j<9;j++)
			if(cells[x][y].eliminate(cells[i][j].getanswer()))changed = true;
		break;
	case 4: 
		for(int i=3;i<6;i++) 
		   for(int j=0;j<3;j++)
			if(cells[x][y].eliminate(cells[i][j].getanswer()))changed = true;
		break;
	case 5: 
		for(int i=3;i<6;i++) 
		   for(int j=3;j<6;j++)
			if(cells[x][y].eliminate(cells[i][j].getanswer()))changed = true;
		break;
	case 6: 
		for(int i=3;i<6;i++) 
		   for(int j=6;j<9;j++)
			if(cells[x][y].eliminate(cells[i][j].getanswer()))changed = true;
		break;
	case 7:
		for(int i=6;i<9;i++) 
		   for(int j=0;j<3;j++)
			if(cells[x][y].eliminate(cells[i][j].getanswer()))changed = true;
		break;
	case 8:
		for(int i=6;i<9;i++) 
		   for(int j=3;j<6;j++)
			if(cells[x][y].eliminate(cells[i][j].getanswer()))changed = true;
		break;
	case 9:
		for(int i=6;i<9;i++) 
		   for(int j=6;j<9;j++)
			if(cells[x][y].eliminate(cells[i][j].getanswer())) changed = true;
	}
}

bool Puzzle :: CompleteSolution()const
{

	for(int i=0;i<9;i++) 
	   for(int j=0;j<9;j++)
		if(cells[i][j].getanswer() == 0)
		return false;
	return true;



}





