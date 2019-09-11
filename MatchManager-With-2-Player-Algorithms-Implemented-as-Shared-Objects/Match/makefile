COMP = g++-5
#put all your object files here
OBJS = MatchManager.o GameManager.o InputMazeParser.o MazeOutput.o  main.o \
AlgorithmRegistrar.o AlgorithmRegistration.o ArgumentParser.o FileUtilities.o #objects should be placed here! 
#The executabel filename DON'T CHANGE
EXEC = matchManager
CPP_COMP_FLAG = -std=c++17 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG
CPP_LINK_FLAG = -ldl -lpthread -export-dynamic#(-rdynamic)

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) $(CPP_LINK_FLAG) -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
main.o: main.cpp FileUtilities.h GameManager.h AbstractAlgorithm.h \
 MazeOutput.h GameSymbols.h MatchManager.h ArgumentParser.h \
 InputMazeParser.h AlgorithmRegistrar.h DLClass.h AlgorithmRegistration.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
MazeOutput.o: MazeOutput.cpp MazeOutput.h GameSymbols.h AbstractAlgorithm.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
InputMazeParser.o: InputMazeParser.cpp GameSymbols.h InputMazeParser.h FileUtilities.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameManager.o: GameManager.cpp GameManager.h AbstractAlgorithm.h MazeOutput.h GameSymbols.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
AlgorithmRegistrar.o: AlgorithmRegistrar.cpp AlgorithmRegistrar.h AbstractAlgorithm.h DLClass.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
AlgorithmRegistration.o: AlgorithmRegistration.cpp \
 AlgorithmRegistration.h AbstractAlgorithm.h AlgorithmRegistrar.h DLClass.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
MatchManager.o: MatchManager.cpp MatchManager.h GameManager.h \
 AbstractAlgorithm.h MazeOutput.h GameSymbols.h ArgumentParser.h InputMazeParser.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
ArgumentParser.o: ArgumentParser.cpp ArgumentParser.h FileUtilities.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
FileUtilities.o: FileUtilities.cpp FileUtilities.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)
