/*
 * DataTypes.h
 *
 *  Created on: Jun 9, 2019
 *      Author: alon
 */

#ifndef DATATYPES_H_
#define DATATYPES_H_

#include "GameSymbols.h"



class DataTypes {
public:
	using Move = GameMove;
	using MoveFeedback = int;
	using Id = std::string;
	using InitData = int;
};

enum class GameMoveFeedback : DataTypes::MoveFeedback {HIT_WALL=-2, HIT_BOOKMARK=2, OK=-1};

#endif /* DATATYPES_H_ */
