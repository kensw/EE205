/* file: cell_inl_v2.h */
#include "cell.h"

/********************************************************/
/*							*/
/*	Mutators	`				*/
/*							*/
/********************************************************/

inline void Cell :: nincrement()
{	ncount++;	}

inline void Cell :: nclear()
{	ncount = 0;	}

inline void Cell :: hide()
{	number = 0;
	fgiven = false;
}

inline void Cell :: setanswer(int x)
{	answer = x;	}

inline void Cell :: setnumber(int x)
{	number = x;	}

inline void Cell :: reveal()
{	number = answer;
	fgiven = true;
}

/********************************************************/
/*							*/
/*	Accessors	`				*/
/*							*/
/********************************************************/

inline int Cell :: getncount() const
{	return ncount;	}

inline bool Cell :: isgiven() const
{	return fgiven;	}

inline int Cell :: getanswer() const
{	return answer;	}

inline bool Cell :: iscorrect() const
{	return number == answer;	}

inline int Cell :: getnumber() const
{	return number;	}

inline bool Cell :: possibility(const int x) const
{
	return possible[x];
}

