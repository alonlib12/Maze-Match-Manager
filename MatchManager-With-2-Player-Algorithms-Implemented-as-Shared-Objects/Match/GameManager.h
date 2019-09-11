/*
 * GameManager.h
 *
 *  Created on: Mar 17, 2019
 *      Author: Alon Liberman
 */

#ifndef HEADERS_GAMEMANAGER_H_
#define HEADERS_GAMEMANAGER_H_

#include <memory>
#include "AbstractAlgorithm.h"
#include "MazeOutput.h"
#include <unordered_map>
typedef AbstractAlgorithm::Move Move;

class GameManager {
private:
	unsigned int maxSteps;
	std::vector< std::vector<mazeSymbols> > maze;
	unsigned int xCurPos;
	unsigned int yCurPos;
	unsigned int steps;
	MazeOutput ofile;
	std::string filename;
	std::unique_ptr<AbstractAlgorithm>& player;
	int bookmarksSize;
	std::unordered_map<unsigned int,std::unordered_map<unsigned int,int>> coordinatesToBookmarkSeq;
	const std::string& algName;
	const std::string& mazeName;
	void adjustCoordinates(Move move);
	bool handlePlayMoveResult(mazeSymbols symbol, unsigned int prevXCoordinate, unsigned int prevYCoordinate);
public:
	GameManager(unsigned int maxSteps, unsigned int rows, unsigned int cols,
			std::vector< std::vector<mazeSymbols> > maze, const char* outputFilename,
			std::unique_ptr<AbstractAlgorithm>& player,const std::string& algName,const std::string& mazeName);
	virtual ~GameManager();
	bool play();
	unsigned int getSteps() const {return steps;};
	unsigned int getMaxSteps() const {return maxSteps;};
	std::string getAlgName() const {return algName;};
	std::string getMazeName() const {return mazeName;};
};

#endif /* HEADERS_GAMEMANAGER_H_ */
