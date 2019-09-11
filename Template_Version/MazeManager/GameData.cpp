/*
 * GameData.cpp
 *
 *  Created on: Jun 8, 2019
 *      Author: Alon Liberman
 */

#include "GameData.h"

using namespace std;

static const int FAIL = -1;
static const char INITIAL_CURRENT_PLAYER = 'a' - 1;

GameData::GameData(Id gameId, unsigned int maxSteps, unsigned int rows, unsigned int cols,
		std::vector< std::vector<mazeSymbols> > maze, const char* outputFilename):
	gameId(gameId),
	maxSteps(maxSteps),
	rows(rows),
	cols(cols),
	maze(maze),
	filename(outputFilename),
	curPlayer(INITIAL_CURRENT_PLAYER){}

GameData::~GameData() {}


/* This method manages the player and the maze board.
 * If the player succeeded to find the exit of the maze whithin the MaxSteps limit then return true,
 * else return false.
 * return value - bool. */
GameData::MoveFeedback GameData::processMove(GameData::GameInstanceData& gameInstance, GameData::Move move) {
	unsigned int prevXCoordinate = gameInstance.getXCurPos(); //Save current location.
	unsigned int prevYCoordinate = gameInstance.getYCurPos();
	gameInstance.adjustCoordinates(static_cast<Move>(move));
	mazeSymbols symbol = gameInstance.getMazeValue(); //Get the char in current position (wall, pass, bookmark or end)
	gameInstance.writeToOutput(static_cast<Move>(move));
	if (static_cast<Move>(move) == Move::BOOKMARK) {
		gameInstance.upBookmarkByOne(); //bookmarksSize is initialized to -1 so the first bookmarksSize++ equals to 0
		gameInstance.setMazeValue(mazeSymbols::bookmark); //Update game board.
		gameInstance.updateBookmarkMap();
	}
	gameInstance.upStepsByOne();
	return handlePlayMoveResult(gameInstance, symbol, prevXCoordinate, prevYCoordinate);
}



/* Handles the result of the player's move: hit bookmark, hit wall and if player got to the maze's end.
 * If current maze cell is the end then return true, otherwise false.
 * return value - bool.  */
GameData::MoveFeedback GameData::handlePlayMoveResult(GameData::GameInstanceData& gameInstance, mazeSymbols symbol,
											unsigned int prevXCoordinate, unsigned int prevYCoordinate) {
	switch(symbol) {
		case mazeSymbols::wall:
			gameInstance.setXCurPos(prevXCoordinate);
			gameInstance.setYCurPos(prevYCoordinate);
			return static_cast<MoveFeedback>(GameMoveFeedback::HIT_WALL);
		case mazeSymbols::bookmark:
			return static_cast<MoveFeedback>(gameInstance.getBookmarkMap());
		default:
			return static_cast<MoveFeedback>(GameMoveFeedback::OK);
	}
}


bool GameData::endGame(GameData::GameInstanceData& gameInstance) {
	if (gameInstance.getSteps() >= gameInstance.getMaxSteps())
		return true;
	else
		return gameInstance.isAtEndSymbol();
}

int GameData::getScore(GameData::GameInstanceData& gameInstance) const {
	if (gameInstance.getSteps() < gameInstance.getMaxSteps()) {
		gameInstance.gameFinished("!");
		return gameInstance.getSteps();
	}

	else {
		gameInstance.gameFinished("X");
		return FAIL;
	}
}
