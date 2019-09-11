/*
 * GameManager.cpp
 *
 *  Created on: Jun 28, 2019
 *      Author: alon
 */



#include "GameManager.h"


static const int START_POSITION_LOWER_BOUNDRY = 0;
static const int FAIL = -1;

/* Returns true if game ended due to success or failure, otherwise false.
 * Return value - bool */
bool GameManager::endGame(GameData& game, GameData::GameInstanceData& gameInstance) {
	if (gameInstance.startPos < START_POSITION_LOWER_BOUNDRY || gameInstance.startPos >= static_cast<int>(gameInstance.listSize))
	return true;
	if (gameInstance.steps >= game.getMaxSteps())
		return true;
	if (game.isNumFound(gameInstance))
		return true;
	return false;
}
/* Returns the result score of the game. In case of failure returns -1.
 * Return value - int */
int GameManager::score(GameData& game, GameData::GameInstanceData& gameInstance) {
	if (gameInstance.startPos < START_POSITION_LOWER_BOUNDRY || gameInstance.startPos >= static_cast<int>(gameInstance.listSize))
	return FAIL;
	if (gameInstance.steps >= game.getMaxSteps())
		return FAIL;
	return gameInstance.steps;
}
