/*
 * main.cpp
 *
 *  Created on: May 31, 2019
 *      Author: Alon Liberman
 */

#include "ArgumentParser.h"
#include "GameManager.h"
#include "Player.h"
#include "Match.h"
#include "ReportOutput.h"
#include "GameBuilder.h"



using namespace std;

static const int SUCCESS = 0;
static const int FAILURE = 1;


int main(int argc, const char* argv[]) {
	ArgumentParser argParser(argc,argv); //Parse input arguments
	if (!argParser.isValid())
		return FAILURE;
	using MyMatch = Match<GameManager, GameData, Player>;
    GameManager g;
    MyMatch match(g);
    match.addPlayer([](int init){return Player(init,"player_a",1);});
    match.addPlayer([](int init){return Player(init,"player_b",2);});
    match.addPlayer([](int init){return Player(init,"player_c",2);});
    //build Game List from input arguments
    GameBuilder builder(argParser.getMazeFileNames(), argParser.getMazePath(), argParser.getOutputPath());
    list<GameData> gameList = builder.buildGameDataList();
    for (GameData& gd : gameList) {
    	match.addGame(gd);
    }
    MyMatch::Report report = match.runMatch(argParser.getNumOfThreads());
    /* Print report match results */
    ReportOutput<GameManager, GameData, Player> reportResults(report);
    reportResults.printReport();
    return SUCCESS;
}
