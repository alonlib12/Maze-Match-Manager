COMP = g++-5
#put all your object files here
SHARED_OBJS = Algorithm_a.so Algorithm_b.so
OBJS = Algorithm_a.o Algorithm_b.o Maze.o Bookmark.o
#The executabel filename DON'T CHANGE
EXEC = all
CPP_COMP_FLAG = -std=c++17 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG -fPIC
CPP_LINK_FLAG = -shared

$(EXEC): $(SHARED_OBJS)	
#First algorithm
Algorithm_a.so: Algorithm_a.o Maze.o
	$(COMP) $(CPP_LINK_FLAG) -o $@ $^
Algorithm_a.o: Algorithm_a.cpp Algorithm_a.h ../Match/GameSymbols.h \
 ../Match/AbstractAlgorithm.h ../Match/AlgorithmRegistration.h Bookmark.h Maze.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
#Second algorithm
Algorithm_b.so: Algorithm_b.o Maze.o
	$(COMP) $(CPP_LINK_FLAG) -o $@ $^
Algorithm_b.o: Algorithm_b.cpp Algorithm_b.h ../Match/GameSymbols.h \
 ../Match/AbstractAlgorithm.h ../Match/AlgorithmRegistration.h Bookmark.h Maze.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
#Maze module
Maze.o: Maze.cpp Maze.h ../Match/AbstractAlgorithm.h ../Match/GameSymbols.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(SHARED_OBJS)
