/*
 * Player2.h
 *
 *  Created on: Jun 6, 2019
 *      Author: alon
 */

#ifndef PLAYER2_H_
#define PLAYER2_H_


#include <string>
#include "AbstractPlayer.h"

class Player2 : public AbstractPlayer {
private:
	Id playerId;
	GameMove curDirection;
	GameData::InitData numToFind;
	void changeDirection();
public:
    Player2(GameData::InitData init, Id _playerId): playerId(_playerId), curDirection(GameMove::RIGHT), numToFind(init) {}
    virtual ~Player2(){}
    virtual GameData::Move move() const override { return static_cast<GameData::Move>(curDirection); }
	virtual Id id() const  override { return playerId; }
    virtual void moveFeedback(GameData::MoveFeedback feedback) override;
};

#endif /* PLAYER2_H_ */
