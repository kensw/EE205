CCC = g++
CCFLAGS = -ansi

sudoku: sudoku.o puzzle.o cell.o
	$(CCC) -o sudoku sudoku.o puzzle.o cell.o -lcurses

version1:
	rm -f puzzle.cc cell.h cell.cc
	ln -s puzzle_v1.cc puzzle.cc
	ln -s cell_v1.h cell.h
	ln -s cell_v1.cc cell.cc
	touch puzzle.cc cell.h cell.cc

version2:
	rm -f puzzle.cc cell.h cell.cc
	ln -s puzzle_v2.cc puzzle.cc
	ln -s cell_v2.h cell.h
	ln -s cell_v2.cc cell.cc
	touch puzzle.cc cell.h cell.cc

puzzle.o: puzzle.h

sudoku.o: puzzle.h

cell.o:	cell.h

clean:
	rm -f *.o

real_clean: clean
	rm -f sudoku

