/*
 * AbstractAlgorithm.h
 *
 *  Created on: Apr 29, 2019
 *      Author: alon
 */

// AbstractAlgorithm.h

#ifndef ABSTRACTALGORITHM_H_
#define ABSTRACTALGORITHM_H_

#include <string>
#include "DataTypes.h"

using Move = DataTypes::Move;
using MoveFeedback = DataTypes::MoveFeedback;
using InitData = DataTypes::InitData;
using Id = DataTypes::Id;

class AbstractAlgorithm {
public:
	virtual ~AbstractAlgorithm(){}
	virtual Id id() const = 0;
	virtual Move move() = 0;
	virtual void moveFeedback(MoveFeedback feedback) = 0;
	virtual void hitWall() = 0;
	virtual void hitBookmark(int seq) = 0;
};


#endif /* ABSTRACTALGORITHM_H_ */
