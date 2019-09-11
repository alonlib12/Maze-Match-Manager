COMP = g++-8.3.0
#put all your object files here
OBJS = main.o Player2.o GameData.o GameInstance.o GameManager.o Player1.o Player.o#objects should be placed here!
#The executabel filename DON'T CHANGE
EXEC = simpleGame
CPP_COMP_FLAG = -std=c++17 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG
CPP_LINK_FLAG = -lstdc++fs

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) $(CPP_LINK_FLAG) -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
main.o: main.cpp GameManager.h GameData.h GameInstance.h Player.h \
 Player1.h AbstractPlayer.h Player2.h ../Common/Match.h ReportOutput.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Player2.o: Player2.cpp Player2.h AbstractPlayer.h GameData.h \
 GameInstance.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameData.o: GameData.cpp GameData.h GameInstance.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameInstance.o: GameInstance.cpp GameInstance.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameManager.o: GameManager.cpp GameManager.h GameData.h GameInstance.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Player1.o: Player1.cpp Player1.h AbstractPlayer.h GameData.h \
 GameInstance.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Player.o: Player.cpp Player.h Player1.h AbstractPlayer.h GameData.h \
 GameInstance.h Player2.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)
