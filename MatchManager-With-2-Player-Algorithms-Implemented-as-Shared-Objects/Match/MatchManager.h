/*
 * MatchManager.h
 *
 *  Created on: Apr 30, 2019
 *      Author: Alon Liberman
 */

#ifndef MATCHMANAGER_MATCHMANAGER_H_
#define MATCHMANAGER_MATCHMANAGER_H_

/* A class for managing multiple maze file and algorithms. */

#include <list>
#include <string>
#include <thread>
#include <atomic>
#include "GameManager.h"

class MatchManager {
private:
	std::list<GameManager> managers;
	std::list<std::unique_ptr<AbstractAlgorithm>> algorithms;
	std::list<std::string> mazeFileNames;
	const std::list<std::string>& algorithmNames;
	size_t numOfThreads;
	std::atomic<std::size_t> availableGameIdx;
	std::unordered_map<std::string,std::unordered_map<std::string,unsigned int>> algAndMazeToStepsMap;
	std::unordered_map<std::string,std::unordered_map<std::string,unsigned int>> algAndMazeToMaxStepsMap;
	void buildGameManagers(const std::list<std::function<std::unique_ptr<AbstractAlgorithm>()>>& algorithmFactories,
			 	 	 	   const std::string& mazePath, const std::string& outputPath);
	void printMazeFilesToScreen() const;
	void padWithSpaces(const std::string& filename) const;
	void threadHandler();
	void printGameReusltToScreen(unsigned int steps, unsigned int maxSteps);
public:
	MatchManager(const std::list<std::function<std::unique_ptr<AbstractAlgorithm>()>>& algorithmFactories,
				 const std::list<std::string>& algorithmNames,
				 const std::list<std::string> mazeFiles, const std::string& mazePath, const std::string& outputPath, size_t numOfThreads);
	void play();
	virtual ~MatchManager();
};

#endif /* MATCHMANAGER_MATCHMANAGER_H_ */
