CCC = g++
CCFLAGS = -ansi

sudoku: sudoku.o puzzle.o cell.o 
	$(CCC) -o sudoku sudoku.o puzzle.o cell.o -lcurses 

testpos: testpossible.o cell.o
	$(CCC) -o testpos testpossible.o cell.o

testpossible.o: cell.h

puzzle.o: puzzle.h cell.h

sudoku.o: puzzle.h cell.h

cell.o:	cell.h 

clean:
	rm -f *.o

real_clean: clean
	rm -f sudoku
	rm -f testpos
