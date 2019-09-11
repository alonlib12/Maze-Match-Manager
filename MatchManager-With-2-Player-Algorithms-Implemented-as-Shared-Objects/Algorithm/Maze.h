/*
 * Maze.h
 *
 *  Created on: May 10, 2019
 *      Author: alon
 */

#ifndef ALGORITHMS_MAZE_H_
#define ALGORITHMS_MAZE_H_

#include <unordered_map>
#include <map>
#include <climits>
#include "../Match/GameSymbols.h"
#include "../Match/AbstractAlgorithm.h"
/* A class that handles maze functionality */
typedef AbstractAlgorithm::Move Move;

class Maze {
private:
	std::unordered_map<int,std::unordered_map<int,mazeSymbols>> maze;
	std::map<int,int> coordinateMap;
	unsigned int vertivalLen;
	unsigned int horizontalLen;
	int normalizeHorizontal(int horizontal) const;
	int normalizeVertical(int vertical) const;
public:
	Maze():vertivalLen(UINT_MAX), horizontalLen(UINT_MAX) {maze[0][0] = mazeSymbols::pass;};
	bool isVisited(int verticalSteps, int horizontalSteps, Move move) const;
	bool isVisited(int vertical, int horizontal) const;
	void setNewVertivalLen(unsigned int _vertivalLen);
	void setNewHorizontalLen(unsigned int _horizontalLen);
	void insert(int verticalSteps, int horizontalSteps, mazeSymbols value);
	mazeSymbols getSymbol(int vertical, int horizontal) const;
};

#endif /* ALGORITHMS_MAZE_H_ */
