/*
 * MatchManager.cpp
 *
 *  Created on: Apr 30, 2019
 *      Author: Alon Liberman
 */

#include <iostream>
#include "MatchManager.h"
#include "InputMazeParser.h"
#include <memory>


using namespace std;

static const int ALGORITHM_FAILED = -1;
static const unsigned int PADDING_SIZE = 10;
static const size_t INITIAL_AVILABLE_INDEX = 0;
static const string MAZE_SUFFIX = ".maze";

MatchManager::MatchManager(const list<function<unique_ptr<AbstractAlgorithm>()>>& algorithmFactories,const list<string>& _algorithmNames,
			 const list<string> mazeFiles, const string& mazePath, const std::string& outputPath, size_t numOfThreads):
		mazeFileNames(mazeFiles),
		algorithmNames(_algorithmNames),
		numOfThreads(numOfThreads),
		availableGameIdx(INITIAL_AVILABLE_INDEX) {
	buildGameManagers(algorithmFactories, mazePath, outputPath);
}

/* Creates a new game manager For each algorithm factory and maze file
 * and adds it to the managers list.
 * Return value - void.   */
void MatchManager::buildGameManagers(const list<function<unique_ptr<AbstractAlgorithm>()>>& algorithmFactories, const string& mazePath, const std::string& outputPath) {
	auto algNamesItr = algorithmNames.rbegin();
	for ( auto  algorithmFactoryFunc = algorithmFactories.rbegin(); algorithmFactoryFunc!=algorithmFactories.rend();algorithmFactoryFunc++) {
		if (algNamesItr == algorithmNames.rend())
			break;
		list<string>::const_iterator next;
		for ( list<string>::const_iterator mazefileItr  = mazeFileNames.begin(); mazefileItr != mazeFileNames.end();) {
			next = ++mazefileItr;
			--mazefileItr;
			string mazeFilePath = mazePath + *mazefileItr;
			struct params p = InputMazeParser(mazeFilePath.c_str()).parseMazeFile();
			if (p.validMaze) {
				string outputFilename="";
				if (outputPath != "")
					outputFilename = outputPath + *mazefileItr + *algNamesItr + ".output";
				algorithms.push_back((*algorithmFactoryFunc)());
				managers.push_back(GameManager(p.maxSteps, p.rows, p.cols, p.maze,outputFilename.c_str() ,
						algorithms.back(),*algNamesItr,*mazefileItr));
				mazefileItr = next;
			}
			else if (mazefileItr == mazeFileNames.begin()) {//Current maze is not valid.
				mazeFileNames.erase(mazefileItr);
				mazefileItr = mazeFileNames.begin();
			}
			else { //Current maze is not valid.
				mazeFileNames.erase(mazefileItr);
				mazefileItr = next;
			}
		}
		algNamesItr++;
	}
}

void MatchManager::threadHandler() {
	size_t localIdx = availableGameIdx++;
	while ( localIdx  < managers.size() ) {
		list<GameManager>::iterator gameManagerItr = managers.begin();
		advance(gameManagerItr,localIdx);
		gameManagerItr->play();
		algAndMazeToStepsMap[gameManagerItr->getAlgName()][gameManagerItr->getMazeName()] = gameManagerItr->getSteps();
		algAndMazeToMaxStepsMap[gameManagerItr->getAlgName()][gameManagerItr->getMazeName()] = gameManagerItr->getMaxSteps();
		localIdx = availableGameIdx++;
	}
}

/* Plays each game manager and prints the result to the screen
 * Return value - void. */
void MatchManager::play() {
	vector<unique_ptr<thread>> threads(numOfThreads);
	printMazeFilesToScreen();
	if (numOfThreads > 1) {
		for (size_t i=0 ; i<numOfThreads ; i++) {
				threads[i] = make_unique<thread>(&MatchManager::threadHandler, this); // create and run the thread
		}
		// ===> join all the threads to finish nicely (i.e. without crashing / terminating threads)
		for(size_t i=0 ; i<numOfThreads ; i++) {
			threads[i]->join();
		}
	}
	else //If input -num_threads equals 1 then use the main thread to call gamemanagers.
		threadHandler();
	for (const string& algorithmName : algorithmNames) {
		cout << "|" << algorithmName << " |" ;
		for (const string& mazeFile : mazeFileNames) {
			printGameReusltToScreen(algAndMazeToStepsMap[algorithmName][mazeFile],algAndMazeToMaxStepsMap[algorithmName][mazeFile]);
		}
		cout << endl;
	}
}
/* Prints all the maze file names to the screen.
 * Return value - void. */
void MatchManager::printMazeFilesToScreen() const {
	cout << "-------------" ;
	for (size_t i=0 ; i<mazeFileNames.size(); i++) {
			cout << "------------" ;
	}
	cout << endl;
	cout << "|             ";
	for (const string& mazeFileName : mazeFileNames) {
		string mazefileNameWithoutSuffix = mazeFileName.substr(0, mazeFileName.rfind(MAZE_SUFFIX));
		cout << "|" << mazefileNameWithoutSuffix ;
		padWithSpaces(mazefileNameWithoutSuffix);
	}
	cout << "|" << endl;
}


void MatchManager::printGameReusltToScreen(unsigned int steps, unsigned int maxSteps) {
	if (steps < maxSteps) {
		padWithSpaces(to_string(steps));
		cout << steps << "|" ;
	}
	else {
		padWithSpaces(to_string(ALGORITHM_FAILED));
		cout << ALGORITHM_FAILED << "|" ;
	}
}

void MatchManager::padWithSpaces(const string& str) const {
	if (PADDING_SIZE < str.size())
		return;
	size_t spacesLen = PADDING_SIZE - str.size();
	for (size_t i=0; i<spacesLen; i++) {
		cout << " ";
	}
}

MatchManager::~MatchManager() {}

