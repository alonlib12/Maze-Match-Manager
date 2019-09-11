/*
 * OutputFile.h
 *
 *  Created on: Apr 1, 2019
 *      Author: Alon Liberman
 */

#ifndef SRC_HEADERS_OUTPUTFILE_H_
#define SRC_HEADERS_OUTPUTFILE_H_
/* A class for managing game output */
#include <fstream>
#include <memory>
#include  "GameSymbols.h"
#include "AbstractAlgorithm.h"
typedef AbstractAlgorithm::Move Move;

class MazeOutput {
private:
	std::string filename;
	std::shared_ptr<std::ofstream> outputFile;
public:
	MazeOutput(const char* MazeOutputname);
	void writeToOutput(Move move) const;
	void gameFinished(const std::string& successOrFail) const;
};

#endif /* SRC_HEADERS_OUTPUTFILE_H_ */
