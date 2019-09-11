/*
 * Player.cpp
 *
 *  Created on: Jun 28, 2019
 *      Author: alon
 */

/* A class that holds a unique pointer to the chosen algorithm */
#include "Player.h"

Player::Player(GameData::InitData init, Id _playerId, int playerAlgorithm) {
	if (playerAlgorithm == 1)
		playerPtr = std::make_unique<Player1>(init, _playerId);
	else
		playerPtr = std::make_unique<Player2>(init, _playerId);
}
