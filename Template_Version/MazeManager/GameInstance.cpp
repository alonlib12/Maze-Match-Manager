/*
 * GameInstance.cpp
 *
 *  Created on: Jun 8, 2019
 *      Author: alon
 */

#include "GameInstance.h"
#include <climits>
using namespace std;

static const int BOOKMARK_SIZE_INITIAL_VALUE = 0;
static const int STEPS_INITIAL_VALUE = 0;
static const unsigned int START_IDX = 0;
static const unsigned int END_IDX = UINT_MAX;

GameInstance::GameInstance(unsigned int maxSteps, unsigned int rows, unsigned int cols,
		std::vector< std::vector<mazeSymbols> > maze, const char* outputFilename):
	maxSteps(maxSteps),
	maze(maze),
	steps(STEPS_INITIAL_VALUE),
	ofile(outputFilename),
	filename(outputFilename),
	bookmarksSize(BOOKMARK_SIZE_INITIAL_VALUE) {
		/* Find the player and end position */
		for (unsigned int i=0; i<rows; i++) {
			for (unsigned int j=0; j<cols; j++) {
				if (maze[i][j] == mazeSymbols::playerPos) {
					xCurPos = i;
					yCurPos = j;
				}
			}
		}
}


GameInstance::~GameInstance(){}


/* Updates the player position on the maze board.
 * return value - void.  */
void GameInstance::adjustCoordinates(Move move) {
	switch(move) {
		case Move::UP:
			if (xCurPos == START_IDX)
				xCurPos = maze.size();
			xCurPos--;
			break;
		case Move::DOWN:
			if (xCurPos == maze.size() - 1)
				xCurPos = END_IDX;
			xCurPos++;
			break;
		case Move::RIGHT:
			if (yCurPos == maze[xCurPos].size() - 1)
				yCurPos = END_IDX;
			yCurPos++;
			break;
		case Move::LEFT:
			if (yCurPos == START_IDX)
				yCurPos = maze[xCurPos].size();
			yCurPos--;
			break;
		case Move::BOOKMARK:
			break;
	}
}
