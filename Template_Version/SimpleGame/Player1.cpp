/*
 * Player1.cpp
 *
 *  Created on: Jun 28, 2019
 *      Author: alon
 */


#include "Player1.h"

Player1::Player1(GameData::InitData _init, Id _playerId):
	init(_init), playerId(_playerId), curDirection(GameMove::RIGHT) {}


/* Changes the player move direction if it is beyond the list boundaries, otherwise do nothing.
 * Return value - void */
void Player1::moveFeedback(GameData::MoveFeedback feedback) {
	if ( feedback == static_cast<GameData::MoveFeedback>(GameData::GameMoveFeedback::OUT_OF_BOUNDRIES) )
		curDirection = GameMove::LEFT;
	else
		return;
}
