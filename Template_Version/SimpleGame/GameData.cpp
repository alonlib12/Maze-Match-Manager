/*
 * GameData.cpp
 *
 *  Created on: Jun 28, 2019
 *      Author: alon
 */


#include "GameData.h"

GameData::GameData(Id _gameId, InitData _numToBeFound, int _startPos, size_t _maxSteps, const std::vector<int> _numList):
    	gameId(_gameId), startPos(_startPos), numToBeFound(_numToBeFound), maxSteps(_maxSteps),
		numList(_numList) {}

/* Processes the player's move in the input game instance and returns feedback according to the game instance new state.
 * Return value - GameData::MoveFeedback */
GameData::MoveFeedback GameData::processMove(GameData::GameInstanceData& gameInstance, GameData::Move move) {
	gameInstance.currentLocation += move;
	gameInstance.steps++;
	int currentLocation = gameInstance.currentLocation;
	if ( static_cast<size_t>(currentLocation) >= 0 &&  static_cast<size_t>(currentLocation) < gameInstance.listSize)
		return numList[currentLocation];
	else {
		gameInstance.currentLocation -= move;
		return static_cast<GameData::MoveFeedback>(GameMoveFeedback::OUT_OF_BOUNDRIES);
	}
}
