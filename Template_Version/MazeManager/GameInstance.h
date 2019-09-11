/*
 * GameInstance.h
 *
 *  Created on: Jun 8, 2019
 *      Author: Alon Liberman
 */

#ifndef GAMEINSTANCE_H_
#define GAMEINSTANCE_H_


#include <memory>
#include <unordered_map>
#include <string>
#include <vector>
#include "MazeOutput.h"
#include "AbstractAlgorithm.h"

static const int DEFAULT_INIT_DATA = 0;


class GameInstance {
private:
	unsigned int maxSteps;
	std::vector< std::vector<mazeSymbols> > maze;
	unsigned int xCurPos;
	unsigned int yCurPos;
	unsigned int steps;
	MazeOutput ofile;
	std::string filename;
	int bookmarksSize;
	std::unordered_map<unsigned int,std::unordered_map<unsigned int,int>> coordinatesToBookmarkSeq;
public:
	using MoveFeedback = DataTypes::MoveFeedback;
	using Move = DataTypes::Move;
	GameInstance(unsigned int maxSteps, unsigned int rows, unsigned int cols,
			std::vector< std::vector<mazeSymbols> > maze, const char* outputFilename);
	virtual ~GameInstance();
	void adjustCoordinates(Move move);
	unsigned int getXCurPos() const {return xCurPos;}
	unsigned int getYCurPos() const {return yCurPos;}
	void setXCurPos(unsigned int newX) {xCurPos = newX;}
	void setYCurPos(unsigned int newY) {yCurPos = newY;}
	void writeToOutput(Move move) {ofile.writeToOutput(move);}
	void upBookmarkByOne() {bookmarksSize++;}
	void upStepsByOne() {steps++;}
	mazeSymbols getMazeValue() const {return maze[xCurPos][yCurPos];}
	void setMazeValue(mazeSymbols value) {maze[xCurPos][yCurPos] = value;}
	void updateBookmarkMap() {coordinatesToBookmarkSeq[xCurPos][yCurPos] = bookmarksSize;}
	int getBookmarkMap() const {return coordinatesToBookmarkSeq.at(xCurPos).at(yCurPos);}
	int getInitData() {return DEFAULT_INIT_DATA;}
	unsigned int getSteps() const {return steps;};
	unsigned int getMaxSteps() const {return maxSteps;}
	bool isAtEndSymbol() {if (maze[xCurPos][yCurPos] == mazeSymbols::end ) return true; else return false;}
	void gameFinished(const std::string& gameResult) {ofile.gameFinished(gameResult);}
};

#endif /* GAMEINSTANCE_H_ */
