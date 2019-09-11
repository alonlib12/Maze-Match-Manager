/*
 * GameInstance.h
 *
 *  Created on: Jun 1, 2019
 *      Author: Alon Liberman
 */

#ifndef GAMEINSTANCE_H_
#define GAMEINSTANCE_H_

#include <vector>

struct GameInstance {
	std::size_t listSize;
	const std::vector<int>& numList;
	int currentLocation;
	int numToBeFound;
	std::size_t steps;
	int startPos;
	GameInstance(int _startPos, int _numToBeFound, const std::vector<int>& _numList);
	int getInitData() const {return numToBeFound;}
};

#endif /* GAMEINSTANCE_H_ */
