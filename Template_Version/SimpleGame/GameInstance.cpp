/*
 * GameInstance.cpp
 *
 *  Created on: Jun 28, 2019
 *      Author: alon
 */




#include "GameInstance.h"

using namespace std;

static const size_t INITIAL_STEPS = 0;

GameInstance::GameInstance(int _startPos, int _numToBeFound, const std::vector<int>& _numList):
	numList(_numList), currentLocation(_startPos), numToBeFound(_numToBeFound),
	steps(INITIAL_STEPS),startPos(_startPos) {
	listSize = numList.size();
}
