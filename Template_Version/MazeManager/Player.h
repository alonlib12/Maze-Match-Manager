/*
 * Player.h
 *
 *  Created on: Jun 7, 2019
 *      Author: Alon Liberman
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <memory>
#include "AbstractAlgorithm.h"
#include "GameData.h"
#include "DataTypes.h"
#include "Algorithm_a.h"
#include "Algorithm_b.h"

class Player {
private:
	std::unique_ptr<AbstractAlgorithm> playerPtr;
public:
	using Id = DataTypes::Id;
	Player(GameData::InitData init, Id _playerId, int playerAlgorithm) {
		if (playerAlgorithm == 1)
			playerPtr = std::make_unique<Algorithm_a>(init, _playerId);
		else //Todo Algorithm_b
			playerPtr = std::make_unique<Algorithm_b>(init, _playerId);
	}
	Id id() const {return playerPtr->id();}
	GameData::Move move() const {return playerPtr->move();}
	void moveFeedback(GameData::MoveFeedback feedback) {playerPtr->moveFeedback(feedback);}
};


#endif /* PLAYER_H_ */
