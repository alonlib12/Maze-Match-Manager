/*
 * MazeOutput.cpp
 *
 *  Created on: Apr 1, 2019
 *      Author: alon
 */

#include "MazeOutput.h"

using namespace std;

MazeOutput::MazeOutput(const char* MazeOutputname):
	filename(MazeOutputname) {
		outputFile = make_shared<ofstream>(MazeOutputname);
	}


/* Writes input move to output file.
 * return value - void */
void MazeOutput::writeToOutput(Move move) const{
	if (filename == "")
		return;
	switch(move) {
		case Move::UP:
			*outputFile << "U" << endl;
			return;
		case Move::DOWN:
			*outputFile << "D" << endl;
			return;
		case Move::LEFT:
			*outputFile << "L" << endl;
			return;
		case Move::RIGHT:
			*outputFile << "R" << endl;
			return;
		case Move::BOOKMARK:
			*outputFile << "B" << endl;
	}
}

/* Writes game result to output file.
 * return value - void */
void MazeOutput::gameFinished(const string& successOrFail) const{
	if (filename == "") //In case no -output input argument.
			return;
	*outputFile << successOrFail << endl;
}
