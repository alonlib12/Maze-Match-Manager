/*
 * GameData.h
 *
 *  Created on: May 31, 2019
 *      Author: Alon Liberman
 */

#ifndef GAMEDATA_H_
#define GAMEDATA_H_

#include <string>
#include <vector>
#include <climits>
#include "GameInstance.h"


class GameData {
public:
    //--------------------------
    // required type traits
    //--------------------------
    using Id = std::string;
    using InitData = int; //number to find
    using GameInstanceData = GameInstance;
    using Move = int;
    using MoveFeedback = long long int;
    //--------------------------
    enum class GameMoveFeedback : MoveFeedback {OUT_OF_BOUNDRIES=UINT_MAX};
    Id id() const { return gameId; }
    GameData(Id _gameId, InitData _numToBeFound, int _startPos, size_t _maxSteps, const std::vector<int> _numList);
    InitData getInitData(GameData::GameInstanceData& gameInstance) const {return gameInstance.getInitData();}
    GameInstanceData newGameInstance() const { return GameInstance(startPos, numToBeFound, numList); }
    MoveFeedback processMove(GameData::GameInstanceData& gameInstance, GameData::Move move);
    size_t getMaxSteps() const {return maxSteps;};
    bool isNumFound(GameData::GameInstanceData& gameInstance) const {
    	return numToBeFound == numList[gameInstance.currentLocation];
    };

private:
	Id gameId;
	int startPos;
	InitData numToBeFound;
	size_t maxSteps;
	const std::vector<InitData> numList;
};

#endif /* GAMEDATA_H_ */
