/*
 * GameData.h
 *
 *  Created on: Jun 8, 2019
 *      Author: alon
 */

#ifndef GAMEDATA_H_
#define GAMEDATA_H_

#include "GameInstance.h"
#include "DataTypes.h"

class GameData {
public:
    //--------------------------
    // required type traits
    //--------------------------
    using Id = DataTypes::Id;
    using InitData = DataTypes::InitData;
    using GameInstanceData = GameInstance;
    using Move = DataTypes::Move;
    using MoveFeedback = DataTypes::MoveFeedback;
    //--------------------------

    Id id() const { return gameId; }
    GameInstanceData newGameInstance() {
    	curPlayer++;
    	return GameInstanceData(maxSteps, rows, cols, maze, (filename+"player_"+curPlayer+".output").c_str());
    }
    MoveFeedback processMove(GameData::GameInstanceData& gameInstance, GameData::Move move);
    GameData::InitData getInitData(GameData::GameInstanceData& gameInstance) {return static_cast<InitData>(gameInstance.getInitData());}
    GameData(Id gameId, unsigned int maxSteps, unsigned int rows, unsigned int cols,
				std::vector< std::vector<mazeSymbols> > maze, const char* outputFilename);
	virtual ~GameData();
	bool endGame(GameData::GameInstanceData& gameInstance);
	int getScore(GameData::GameInstanceData& gameInstance) const;
private:
	Id gameId;
	unsigned int maxSteps;
	unsigned int rows;
	unsigned int cols;
	const std::vector< std::vector<mazeSymbols> > maze;
	std::string filename;
	char curPlayer;
	MoveFeedback handlePlayMoveResult(GameData::GameInstanceData& gameInstance, mazeSymbols symbol,
									  unsigned int prevXCoordinate, unsigned int prevYCoordinate);
};

#endif /* GAMEDATA_H_ */
