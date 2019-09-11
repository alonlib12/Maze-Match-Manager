/*
 * GameManager.h
 *
 *  Created on: Mar 17, 2019
 *      Author: Alon Liberman
 */

#ifndef HEADERS_GAMEMANAGER_H_
#define HEADERS_GAMEMANAGER_H_

#include "GameData.h"

class GameManager {
public:
    GameData::InitData getInitData(GameData& game, GameData::GameInstanceData& gameInstance) {return game.getInitData(gameInstance);}
    GameData::MoveFeedback processMove(GameData& game, GameData::GameInstanceData& gameInstance, GameData::Move move) {
        return game.processMove(gameInstance, move);
    }
    /* Returns true if game ended due to success or failure, otherwise false.
	 * Return value - bool */
    bool endGame(GameData& game, GameData::GameInstanceData& gameInstance) {return game.endGame(gameInstance);}
    /* Returns the result score of the game. In case of failure returns -1.
	 * Return value - int */
    int score(GameData& game, GameData::GameInstanceData& gameInstance) {return game.getScore(gameInstance);}
};

#endif /* HEADERS_GAMEMANAGER_H_ */
