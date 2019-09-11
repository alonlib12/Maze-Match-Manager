/*
 * ArgumentParser.h
 *
 *  Created on: May 1, 2019
 *      Author: Alon Liberman
 */
/* Description - A class that handles the input argument variables */
#ifndef MATCHMANAGER_ARGUMENTPARSER_H_
#define MATCHMANAGER_ARGUMENTPARSER_H_
/* A class that handles parsing of input arguments */
#include <string>
#include <list>

class ArgumentParser {
private:
	std::string mazePath;
	std::string algorithmPath;
	std::string outputPath;
	size_t numOfThreads;
	std::list<std::string> mazeFileNames;
	std::list<std::string> algorithmFileNames;
	bool validArgs;
	void parseInputArgs(int argc, const char* argv[]);
	void buildFileLists();
	void RemoveFilesWithoutExtension(const std::string& extension, std::list<std::string>& lst);

public:
	bool isValid() const {return validArgs;};
	const std::string& getAlgorithmPath() const {return algorithmPath;};
	const std::list<std::string>& getAlgorithmFileNames() const {return algorithmFileNames;};
	const std::list<std::string>& getMazeFileNames() const {return mazeFileNames;}
	const std::string& getMazePath() const {return mazePath;};
	const std::string& getOutputPath() const {return outputPath;};
	size_t getNumOfThreads() const {return numOfThreads;};
	ArgumentParser(int argc, const char* argv[]);
	virtual ~ArgumentParser();
};

#endif /* MATCHMANAGER_ARGUMENTPARSER_H_ */
