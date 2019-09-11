/*
 * InputMazeParser.cpp
 *
 *  Created on: Mar 21, 2019
 *      Author: Alon Liberman
 */

#include <algorithm>
#include <iostream>
#include  "GameSymbols.h"
#include "InputMazeParser.h"
#include "FileUtilities.h"

using namespace std;

static const string MAX_STEPS_LINE_ERROR = "expected in line 2 - MaxSteps = <num>";
static const string ROWS_LINE_ERROR = "expected in line 3 - Rows = <num>";
static const string COLUMNS_LINE_ERROR = "expected in line 4 - Cols = <num>";
static const string MISSING_PLAYER_POS_ERROR = "Missing @ in maze";
static const string MISSING_END_ERROR = "Missing $ in maze";
static const string MORE_PLAYER_POS_ERROR = "More than one @ in maze";
static const string MORE_END_SIGN_ERROR = "More than one $ in maze";
static const string WRONG_CHARACTER_ERROR_PART1 = "Wrong character in maze: ";
static const string WRONG_CHARACTER_ERROR_PART2 = " in row ";
static const string WRONG_CHARACTER_ERROR_PART3 = ", col ";
static const string BAD_MAZE_ERROR = "Bad maze in maze file:";

static const int FAIL = 1;
static const int LINE_NAME = 1;
static const int LINE_MAX_STEPS = 2;
static const int LINE_ROWS = 3;
static const int LINE_COLUMNS = 4;
static const int MISSING_CHAR = 0;
static const int EXACT_NUMBER_OF_CHARS = 1;
static const int MORE_THAN_NEEDED_CHAR = 2;
static const int INITIAL_END_COUNTER = 0;
static const int INITIAL_PLAYER_POS_COUNTER = 0;
static const int INITIAL_COL_SIZE = 0;
static const int INITIAL_ROW_SIZE = 0;

InputMazeParser::InputMazeParser(const char* mazeFileName):
		mazeFileName(mazeFileName),
		mazeFile(mazeFileName),
		badFileFormat(false),
		endCounter(INITIAL_END_COUNTER),
		playerPosCounter(INITIAL_PLAYER_POS_COUNTER),
		colSize(INITIAL_COL_SIZE),
		rowSize(INITIAL_ROW_SIZE) {
	if (!mazeFile.is_open()) {
		badFileFormat = true;
	}
}

InputMazeParser::~InputMazeParser() {}

/* Parses the first four lines of the maze file and saves
 * the maze attributes to resultParams.
 * Return value - void. */
void InputMazeParser::parseMazeAttributes(struct params& resultParams) {
	getline(mazeFile,line); //maze name/description, ignore.
	getline(mazeFile,line); //maxSteps
	resultParams.maxSteps = readline(LINE_MAX_STEPS);
	getline(mazeFile,line); //Rows
	resultParams.rows = readline(LINE_ROWS);
	rowSize = resultParams.rows;
	getline(mazeFile,line); //Cols
	resultParams.cols = readline(LINE_COLUMNS);
	colSize = resultParams.cols;
}

/* Parses and error checks the input maze file.
 * If input file has no errors then this method returns struct params
 * with matching values of MaxSteps, Rows, Cols and maze.
 * If there are any errors then the method returns struct params without building the maze.  */
struct params InputMazeParser::parseMazeFile() {
	struct params resultParams;
	resultParams.validMaze = true;
	parseMazeAttributes(resultParams);
	if (badFileFormat) {
		resultParams.validMaze = false;
		return resultParams;
	}
	streampos beforeMazePos = mazeFile.tellg(); //Save current file position
	unsigned int rowCounter = 0;
	while (getline(mazeFile,line) && rowCounter < rowSize) { //Checks for errors in maze structure
		readMazeLine();
		rowCounter++;
	}
	printMazeSymbolErrors();
	FileUtilities::goToPosition(mazeFile,mazeFileName.c_str(),beforeMazePos); //Go to the position before reading the maze structure.
	int lineNumber = LINE_NAME;
	rowCounter = 0;
	while (getline(mazeFile,line) && rowCounter < rowSize) {
		printCharErrorsInMaze(lineNumber);
		lineNumber++;
		rowCounter++;
	}
	if (badFileFormat) { //If maze input file format is not good then do not build maze.
		resultParams.validMaze = false;
		return resultParams;
	}
	FileUtilities::goToPosition(mazeFile,mazeFileName.c_str(),beforeMazePos); //Go to the position before reading the maze structure.
	buildMaze(resultParams);
	return resultParams;
}

void InputMazeParser::buildMaze(struct params& resultParams) {
	resultParams.maze = vector< vector<mazeSymbols> >(resultParams.rows,vector<mazeSymbols>(resultParams.cols,mazeSymbols::pass));
		for (int i=0; i<resultParams.rows ; i++) {
			getline(mazeFile,line);
			size_t colMinLen = min(static_cast<size_t>(resultParams.cols), line.size());
			for (size_t j=0; j<colMinLen ; j++) {
				resultParams.maze[i][j] = (mazeSymbols)line[j];
			}
		}
}
/* Print Errors in case of invalid maze . */
void InputMazeParser::printMazeSymbolErrors(){
	if ( (playerPosCounter == MISSING_CHAR || endCounter == MISSING_CHAR) && !badFileFormat) {
		badFileFormat = true;
		cerr << mazeFileName << ": " << endl;
		cerr << BAD_MAZE_ERROR << endl;
	}
	if (playerPosCounter == MISSING_CHAR)
		cerr << MISSING_PLAYER_POS_ERROR << endl;
	if (endCounter == MISSING_CHAR)
		cerr << MISSING_END_ERROR << endl;
	if (playerPosCounter > EXACT_NUMBER_OF_CHARS)
			cerr << MORE_PLAYER_POS_ERROR << endl;
	if (endCounter > 1)
			cerr << MORE_END_SIGN_ERROR << endl;
}

/* Parses maxSteps, Rows and Cols from input file and prints errors if the input file has bad format.
 * Input - int lineNumber.
 * return value - int lineValue (MaxSteps, Rows or Cols)  */
int InputMazeParser::readline(int lineNumber) {
	size_t pos;
	size_t idx;
	int lineValue;
	rWhiteSpaceTrimLine();
	try {
		switch(lineNumber) {
			case LINE_MAX_STEPS: {
				if(line.find("MaxSteps") == string::npos)
					throw invalid_argument("Wrong line");
				break;
			}
			case LINE_ROWS: {
				if(line.find("Rows") == string::npos)
					throw invalid_argument("Wrong line");
				break;
			}
			case LINE_COLUMNS: {
				if(line.find("Cols") == string::npos)
					throw invalid_argument("Wrong line");
				break;
			}
		}
		pos = line.find("=");
		lineValue = stoi(line.substr(pos+1),&idx);
		if (line.substr(pos+1).size() != idx)
			throw invalid_argument("Not a valid number");
		if (lineValue < 0)
			throw invalid_argument("Negative value");
	}
	catch(const std::invalid_argument& ia) {
		invalidArgumentException(lineNumber);
		return FAIL;
	}
	catch (const std::out_of_range& oor	) {
		badFileFormat = true;
		cerr << "Out of Range error: " << oor.what() << endl;
		return FAIL;
	}
	return lineValue;
}


void InputMazeParser::invalidArgumentException(int lineNumber) {
	if (!badFileFormat) {
		badFileFormat = true;
		cerr << mazeFileName << ": " << endl;
		cerr << "Bad maze file header:" << endl;
	}
	switch(lineNumber) {
		case LINE_MAX_STEPS: {
			cerr << MAX_STEPS_LINE_ERROR << endl;
			break;
		}
		case LINE_ROWS: {
			cerr << ROWS_LINE_ERROR << endl;
			break;
		}
		case LINE_COLUMNS: {
			cerr << COLUMNS_LINE_ERROR << endl;
			break;
		}
	}
	cerr << "got: " << line << endl;
}

/* Erases spaces , '\r' and tabs from the end of the line.
 * Return value - void. */
void InputMazeParser::rWhiteSpaceTrimLine() {
	line.erase(line.find_last_not_of(" \n\r\t")+1);
}

/* Checks for error in maze.
 * return value - void. */
void InputMazeParser::readMazeLine() {
	unsigned int colMinLen = min(colSize,static_cast<unsigned int>(line.size()));
	for (unsigned int i=0 ; i<colMinLen ; i++) {
		if (line[i] == (char)mazeSymbols::playerPos) // line[i] == '@'.
			playerPosCounter++;
		else if (line[i] == (char)mazeSymbols::end) //line[i] == '$'.
			endCounter++;
		else if (line[i] != (char)mazeSymbols::pass && line[i] != (char)mazeSymbols::wall && !badFileFormat) {
			badFileFormat = true;
			cerr << mazeFileName << ": " << endl;
			cerr << BAD_MAZE_ERROR << endl;
		}
		if ( (endCounter == MORE_THAN_NEEDED_CHAR || playerPosCounter == MORE_THAN_NEEDED_CHAR) && !badFileFormat) {
			badFileFormat = true;
			cerr << mazeFileName << ": " << endl;
			cerr << BAD_MAZE_ERROR << endl;
		}
	}
}

/* Prints invalid char errors if exists in maze.
 * return value - void. */
void InputMazeParser::printCharErrorsInMaze(int lineNumber) {
	for (unsigned int col = 0; col<colSize && col<line.size(); col++) {
		if (line[col] == (char)mazeSymbols::tab) { //If line[col] is tab.
			if (!badFileFormat) {
				badFileFormat = true;
				cerr << mazeFileName << ": " << endl;
				cerr << BAD_MAZE_ERROR << endl;
			}
			cerr << WRONG_CHARACTER_ERROR_PART1 << "TAB" << WRONG_CHARACTER_ERROR_PART2 << lineNumber << WRONG_CHARACTER_ERROR_PART3 << col+1 << endl;
		}
		else if (line[col] != (char)mazeSymbols::end && line[col] != (char)mazeSymbols::pass && line[col] != (char)mazeSymbols::playerPos && line[col] != (char)mazeSymbols::wall) { //If line[col] is not a valid char.
			if (!badFileFormat) {
				badFileFormat = true;
				cerr << mazeFileName << ": " << endl;
				cerr << BAD_MAZE_ERROR << endl;
			}
			cerr << WRONG_CHARACTER_ERROR_PART1 << line[col] << WRONG_CHARACTER_ERROR_PART2 << lineNumber << WRONG_CHARACTER_ERROR_PART3 << col+1 << endl;
		}
	}
}
