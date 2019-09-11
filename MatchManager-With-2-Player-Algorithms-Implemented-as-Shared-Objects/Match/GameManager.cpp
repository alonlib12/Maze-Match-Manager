/*
 * GameManager.cpp
 *
 *  Created on: Mar 17, 2019
 *      Author: Alon Liberman
 */

#include "GameManager.h"
#include  "GameSymbols.h"
#include <climits>
using namespace std;

static const int BOOKMARK_SIZE_INITIAL_VALUE = 0;
static const int STEPS_INITIAL_VALUE = 0;
static const unsigned int START_IDX = 0;
static const unsigned int END_IDX = UINT_MAX;

GameManager::GameManager(unsigned int maxSteps, unsigned int rows, unsigned int cols,
		std::vector< std::vector<mazeSymbols> > maze, const char* outputFilename,
		unique_ptr<AbstractAlgorithm>& player,const string& algName, const string& mazeName):
	maxSteps(maxSteps),
	maze(maze),
	steps(STEPS_INITIAL_VALUE),
	ofile(outputFilename),
	filename(outputFilename),
	player(player),
	bookmarksSize(BOOKMARK_SIZE_INITIAL_VALUE),
	algName(algName),
	mazeName(mazeName) {
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


GameManager::~GameManager(){}

/* This method manages the player and the maze board.
 * If the player succeeded to find the exit of the maze whithin the MaxSteps limit then return true,
 * else return false.
 * return value - bool. */
bool GameManager::play() {
	while(steps < maxSteps) {
		Move move = player->move();
		unsigned int prevXCoordinate = xCurPos; //Save current location.
		unsigned int prevYCoordinate = yCurPos;
		adjustCoordinates(move);
		mazeSymbols symbol = maze[xCurPos][yCurPos]; //Get the char in current position (wall, pass, bookmark or end)
		ofile.writeToOutput(move);
		if (move == Move::BOOKMARK) {
			bookmarksSize++; //bookmarksSize is initialized to -1 so the first bookmarksSize++ equals to 0
			maze[xCurPos][yCurPos] = mazeSymbols::bookmark; //Update game board.
			coordinatesToBookmarkSeq[xCurPos][yCurPos] = bookmarksSize;
		}
		steps++;
		if (handlePlayMoveResult(symbol, prevXCoordinate, prevYCoordinate))
			return true;
	}
	ofile.gameFinished("X");
	return false;
}

/* Handles the result of the player's move: hit bookmark, hit wall and if player got to the maze's end.
 * If current maze cell is the end then return true, otherwise false.
 * return value - bool.  */
bool GameManager::handlePlayMoveResult(mazeSymbols symbol, unsigned int prevXCoordinate, unsigned int prevYCoordinate) {
	switch(symbol) {
		case mazeSymbols::wall:
			player->hitWall();
			xCurPos = prevXCoordinate;
			yCurPos = prevYCoordinate;
			break;
		case mazeSymbols::pass:
			break;
		case mazeSymbols::end:
			ofile.gameFinished("!");
			return true; //Solved maze
		case mazeSymbols::bookmark:
			player->hitBookmark(coordinatesToBookmarkSeq[xCurPos][yCurPos]); //Check this. input parameter of hitBookmark is not clear.
			break;
		case mazeSymbols::playerPos:
			break;
		default:
			break;
	}
	return false;
}


/* Updates the player position on the maze board.
 * return value - void.  */
void GameManager::adjustCoordinates(Move move) {
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
