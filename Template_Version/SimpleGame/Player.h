/*
 * Player.h
 *
 *  Created on: Jun 7, 2019
 *      Author: Alon Liberman
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <memory>
#include "Player1.h"
#include "Player2.h"

class Player {
private:
	std::unique_ptr<AbstractPlayer> playerPtr;
public:
	using Id = AbstractPlayer::Id;
	Player(GameData::InitData init, Id _playerId, int playerAlgorithm);
	Id id() const {return playerPtr->id();}
	GameData::Move move() const {return playerPtr->move();}
	void moveFeedback(GameData::MoveFeedback feedback) {playerPtr->moveFeedback(feedback);}
};


#endif /* PLAYER_H_ */
