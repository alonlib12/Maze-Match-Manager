/*
 * Maze.cpp
 *
 *  Created on: May 10, 2019
 *      Author: alon
 */

#include "Maze.h"
#include <algorithm>

using namespace std;
/* This method gets as input coordinates and move
 * and returns whether the result cell was visited.
 * Return value - bool */
bool Maze::isVisited(int vertical, int horizontal, Move move) const {
	switch(move) {
		case Move::UP:
			return isVisited(vertical+1, horizontal);
		case Move::DOWN:
			return isVisited(vertical-1, horizontal);
		case Move::LEFT:
			return isVisited(vertical, horizontal-1);
		case Move::RIGHT:
			return isVisited(vertical, horizontal+1);
		default:
			return false;
	}
}

bool Maze::isVisited(int vertical, int horizontal) const {
	int normalizedVer = normalizeVertical(vertical);
	int normalizedHor = normalizeHorizontal(horizontal);
	if (maze.find(vertical) != maze.cend() && maze.at(vertical).find(horizontal) != maze.at(vertical).cend())
		return true;
	for (map<int,int>::const_iterator itr = coordinateMap.begin(); itr != coordinateMap.end(); itr++) {
		int row = itr->first;
		int col = itr->second;
		if ( normalizedVer == normalizeVertical(row)  && normalizedHor == normalizeHorizontal(col)) {
			return true;
		}
	}

	return false;
}

void Maze::setNewVertivalLen(unsigned int _vertivalLen) {
	if (_vertivalLen != 0 && _vertivalLen != UINT_MAX) {
		vertivalLen = _vertivalLen;
	}
}
/* Inserts new value to maze in cell which located at [verticalSteps][horizontalSteps] */
void Maze::insert(int verticalSteps, int horizontalSteps, mazeSymbols value) {
	coordinateMap[verticalSteps] = horizontalSteps;
	maze[verticalSteps][horizontalSteps] = value;
	maze[normalizeVertical(verticalSteps)][normalizeHorizontal(horizontalSteps)] = value; //CHECK THIS
}

/* If maze vertical size is known then the method returns
 * horizontal mod vertical size else returns vertical.
 * Return value - int */
int Maze::normalizeVertical(int vertical) const {
	if (vertivalLen == UINT_MAX || vertivalLen == 0)
		return vertical;
	return ((int)vertivalLen + (vertical%(int)vertivalLen)) % (int)vertivalLen;
}
/* If maze horizontal size is known then the method returns
 * horizontal mod horizontal size else returns horizontal.
 * Return value - int */
int Maze::normalizeHorizontal(int horizontal) const {
	if (horizontalLen == UINT_MAX || horizontalLen == 0)
		return horizontal;
	return ((int)horizontalLen + (horizontal%(int)horizontalLen)) % (int)horizontalLen;
}

/* Returns maze cell value at location [vertical][horizontal]
 * Return value - mazeSymbol */
mazeSymbols Maze::getSymbol(int vertical, int horizontal) const {
	return maze.at(vertical).at(horizontal);
}

