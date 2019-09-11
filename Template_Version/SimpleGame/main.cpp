/*
 * main.cpp
 *
 *  Created on: May 31, 2019
 *      Author: Alon Liberman
 */


#include "GameManager.h"
#include "GameData.h"
#include "Player.h"
#include "../Common/Match.h"
#include "ReportOutput.h"



using namespace std;

static const size_t SUCCESS = 0;

int main() {
    using MyMatch = Match<GameManager, GameData, Player>;
    GameManager g;
    MyMatch match(g);
    match.addPlayer([](int init){return Player(init,"player1",1);});
    match.addPlayer([](int init){return Player(init,"player2",2);});
    /*GameData( GameId, number to be found, start position, max steps, list of numbers)*/
    GameData gd("game1", 5, 0, 10, {-1, 0, 5, 9, 11});
    GameData gd2("game2", 5 , 4, 7, {-1, 0, 4 , 5, 7, 9, 11});
    GameData gd3("game3", 20 , 10, 7, {-1, 0, 4 , 5, 7, 9, 11});
    GameData gd4("game3", 20 , 10, 7, {});
    match.addGame(gd);
    match.addGame(gd2);
    match.addGame(gd3);
    match.addGame(gd4);
    MyMatch::Report report = match.runMatch();
    /* Print report match results */
    ReportOutput<GameManager, GameData, Player> reportResults(report);
    reportResults.printReport();
	return SUCCESS;
}
