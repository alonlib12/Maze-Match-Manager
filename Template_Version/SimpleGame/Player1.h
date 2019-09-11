/*
 * Player1.h
 *
 *  Created on: May 31, 2019
 *      Author: Alon Liberman
 */

#ifndef PLAYER1_H_
#define PLAYER1_H_

#include <string>
#include "AbstractPlayer.h"

class Player1 : public AbstractPlayer {
private:
	GameData::InitData init;
	Id playerId;
	GameMove curDirection;
public:
	Player1(GameData::InitData _init, Id _playerId);
    virtual GameData::Move move() const override { return static_cast<GameData::Move>(curDirection); }
    virtual Id id() const  override { return playerId; }
    void moveFeedback(GameData::MoveFeedback feedback) override;
};

#endif /* PLAYER1_H_ */
