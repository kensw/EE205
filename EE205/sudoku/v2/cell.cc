/* file: cell_v2.cc */

#include "cell.h"
#include <stdio.h>

/********************************************************/
/*							*/
/*	Constructors	`				*/
/*							*/
/********************************************************/

Cell::Cell() : ncount(0), number(0), answer(0), fgiven(false)
{

	for(int i = 0; i < 10; i++)
		possible[i] = true;

}

void Cell :: resetposs()
{	for(int i = 0; i < 10; i++)
		possible[i] = true;
}

bool Cell::eliminate(const int x)
{
	if(!possible[x])
	return false;
	
	possible[x] = false;

	for(int i = 1 ; i < 10 ; i++)	
	{
		if(probability(i) == 1)
		setanswer(i);
	}
	return true;
}

float Cell :: probability(const int x) const
{
	float sum = 0;
	for(int i = 1 ; i < 10 ; i++)
	{
		sum = sum + (float)possible[i];
	}

	return (float)possible[x]/sum;
}
