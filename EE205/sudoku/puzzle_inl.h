#include "puzzle.h"


inline int Puzzle :: realrow(int i)
{
	return (i-2)/3;
}

inline int Puzzle :: realcol(int i)
{
	return (i-4)/7;
}


inline int Puzzle :: fakerow(int i)
{
	return 3*i+2;
}

inline int Puzzle :: fakecol(int i)
{
	return 7*i+4;
}
