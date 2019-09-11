/*
 * Player2.cpp
 *
 *  Created on: Jun 6, 2019
 *      Author: Alon Liberman
 */

#include "Player2.h"

/* Changes the player move direction if it is beyond the list boundaries.
 * If current cell value is bigger than numToFind then change move directrion to Left, otherwise right.
 * Return value - void */
 void Player2::moveFeedback(GameData::MoveFeedback feedback) {
	if ( feedback == static_cast<GameData::MoveFeedback>(GameData::GameMoveFeedback::OUT_OF_BOUNDRIES) )
		changeDirection();
	else if ( static_cast<int>(feedback) > numToFind )
		curDirection = GameMove::LEFT;
	else if ( static_cast<int>(feedback) < numToFind )
		curDirection = GameMove::RIGHT;
 }


 /* Switches the current move direction.
  * Return value - void */
 void Player2::changeDirection() {
	 if (curDirection == GameMove::RIGHT)
		 curDirection = GameMove::LEFT;
	 else
		 curDirection = GameMove::RIGHT;
 }
