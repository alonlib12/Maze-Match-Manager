/*
 * AbstractPlayer.h
 *
 *  Created on: Jun 7, 2019
 *      Author: Alon Liberman
 */

#ifndef ABSTRACTPLAYER_H_
#define ABSTRACTPLAYER_H_

#include <string>
#include "GameData.h"

class AbstractPlayer {
public:
    virtual ~AbstractPlayer(){}
	using Id = std::string;
    enum class GameMove {RIGHT=1, LEFT=-1};
    virtual Id id() const = 0;
    virtual GameData::Move move() const = 0;
    virtual void moveFeedback(GameData::MoveFeedback feedback) = 0;
};

#endif /* ABSTRACTPLAYER_H_ */
