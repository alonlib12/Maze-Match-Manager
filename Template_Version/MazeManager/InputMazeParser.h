/*
 * InputMazeParser.h
 *
 *  Created on: Mar 21, 2019
 *      Author: Alon Liberman
 */

#ifndef SRC_HEADERS_INPUTMAZEPARSER_H_
#define SRC_HEADERS_INPUTMAZEPARSER_H_

/* A class for parsing maze files. */
#include <fstream>

class InputMazeParser {
private:
	std::string mazeFileName;
	std::ifstream mazeFile;
	std::string line; //current line
	bool badFileFormat;
	int endCounter; //$ counter.
	int playerPosCounter; //@ counter.
	unsigned int colSize;
	unsigned int rowSize;
	int readline(int lineNumber);
	void buildMaze(struct params& resultParams);
	void printMazeSymbolErrors();
	void readMazeLine();
	void printCharErrorsInMaze(int lineNumber);
	void rWhiteSpaceTrimLine();
	void parseMazeAttributes(struct params& resultParams);
	void invalidArgumentException(int lineNumber);
public:
	InputMazeParser(const char* mazeFileName);
	virtual ~InputMazeParser();
	struct params parseMazeFile();
};


#endif /* SRC_HEADERS_INPUTMAZEPARSER_H_ */
