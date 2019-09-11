/*
 * GameSymbols.h
 *
 *  Created on: Mar 19, 2019
 *      Author: Alon Liberman
 */

#ifndef SRC_HEADERS_GAMESYMBOLS_H_
#define SRC_HEADERS_GAMESYMBOLS_H_

#include <vector>

enum class mazeSymbols: char {wall = '#', pass = ' ', playerPos = '@', end = '$', tab = 9, bookmark = 'B'};
enum class GameMove { UP, RIGHT, DOWN, LEFT, BOOKMARK };

struct params {
	int maxSteps;
	int rows;
	int cols;
	std::vector< std::vector<mazeSymbols> > maze;
	bool validMaze;
};

#endif /* SRC_HEADERS_GAMESYMBOLS_H_ */

