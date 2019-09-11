COMP = g++-8.3.0
#put all your object files here
OBJS = main.o Algorithm_a.o Algorithm_b.o ArgumentParser.o FileUtilities.o GameBuilder.o GameData.o \
 GameInstance.o InputMazeParser.o Maze.o MazeOutput.o #objects should be placed here!
#The executabel filename DON'T CHANGE
EXEC = mazeManager
CPP_COMP_FLAG = -std=c++17 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG -pthread
CPP_LINK_FLAG = -lstdc++fs -pthread

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) $(CPP_LINK_FLAG) -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
main.o: main.cpp ArgumentParser.h GameManager.h GameData.h GameInstance.h \
 MazeOutput.h DataTypes.h GameSymbols.h AbstractAlgorithm.h Player.h \
 Algorithm_a.h Bookmark.h Maze.h Algorithm_b.h Match.h ReportOutput.h \
 GameBuilder.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Algorithm_a.o: Algorithm_a.cpp Algorithm_a.h AbstractAlgorithm.h \
 DataTypes.h GameSymbols.h Bookmark.h Maze.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Algorithm_b.o: Algorithm_b.cpp Algorithm_b.h AbstractAlgorithm.h \
 DataTypes.h GameSymbols.h Bookmark.h Maze.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
ArgumentParser.o: ArgumentParser.cpp ArgumentParser.h FileUtilities.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
FileUtilities.o: FileUtilities.cpp FileUtilities.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameBuilder.o: GameBuilder.cpp GameBuilder.h GameData.h GameInstance.h \
 MazeOutput.h DataTypes.h GameSymbols.h AbstractAlgorithm.h \
 InputMazeParser.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameData.o: GameData.cpp GameData.h GameInstance.h MazeOutput.h \
 DataTypes.h GameSymbols.h AbstractAlgorithm.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameInstance.o: GameInstance.cpp GameInstance.h MazeOutput.h DataTypes.h \
 GameSymbols.h AbstractAlgorithm.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
InputMazeParser.o: InputMazeParser.cpp GameSymbols.h InputMazeParser.h \
 FileUtilities.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Maze.o: Maze.cpp Maze.h GameSymbols.h AbstractAlgorithm.h DataTypes.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
MazeOutput.o: MazeOutput.cpp MazeOutput.h DataTypes.h GameSymbols.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)
