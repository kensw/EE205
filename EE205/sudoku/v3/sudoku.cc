
#include "puzzle.h"

main()
{
	Puzzle a;
	chtype c, n;
	bool playmore = true;

	a.make();

	while(playmore)
	{	c = getchar();
		a.clearmessage();
		switch(c)
		{   
/* move up */	    case 'w':
		    case 'k': a.moveup();
				break;
/* move left */	    case 'a':
		    case 'h': a.moveleft();
				break;
/* move down */	    case 's':
		    case 'j': a.movedown();
				break;
/* move right */    case 'd':
		    case 'l': a.moveright();
				break;
/* insert note */   case 'n': n = getchar();
			      a.insertnote(n);
				break;
/* request hint */  case 'H': a.hint();
				break;
/*submit solution*/ case 'S': if(a.submit())
			      {		a.message("Congrats! Would you like to play again (y)es or (n)o?");
					c = getchar();
					/* if they have a need for the extreme, make a new puzzle */
					if(c == 'y' || c == 'Y')
					{	a.clear();
						a.make();
						break;
					}
					else
						playmore = false;
			      }
			      else 
				a.message("It isn't completely correct, wrong answers are highlighted");
				break;
/*request solution*/case 'G': a.giveup();
				a.message("Sorry that was too extreme for you.  Would you like to play again? (y)es or (n)o?");
				c = getchar();
				/* if they have a need for the extreme, make a new puzzle */
				if(c == 'y' || c == 'Y')
				{	a.clear();
					a.make();
					break;
				}

		    case 'Q': playmore = false;
				break;
/* delete entry */  case 8:	a.insert(' ');
				break;
		    case ' ':
/* insert number */ case '1':
		    case '2':
		    case '3':
		    case '4':
		    case '5':
		    case '6':
		    case '7':
		    case '8':
		    case '9': a.insert(c);
				break;
/* invalid commands */ default: a.message("Invalid Command");
		}
	}
}
