/*
 * GameManager.h
 *
 *  Created on: May 31, 2019
 *      Author: Alon Liberman
 */

#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "GameData.h"

class GameManager {
public:
    GameData::InitData getInitData(GameData& game, GameData::GameInstanceData& gameInstance) {
        return game.getInitData(gameInstance);
    }
    GameData::MoveFeedback processMove(GameData& game, GameData::GameInstanceData& gameInstance, GameData::Move move) {
        return game.processMove(gameInstance, move);
    }
    bool endGame(GameData& game, GameData::GameInstanceData& gameInstance);
    int score(GameData& game, GameData::GameInstanceData& gameInstance);
};

#endif /* GAMEMANAGER_H_ */
