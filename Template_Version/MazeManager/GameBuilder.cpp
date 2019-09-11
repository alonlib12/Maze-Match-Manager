/*
 * GameBuilder.cpp
 *
 *  Created on: Jun 12, 2019
 *      Author: alon
 */

#include "GameBuilder.h"
#include "InputMazeParser.h"

using namespace std;

GameBuilder::GameBuilder(const std::list<std::string>& mazeFiles, const std::string& mazePath,
				const std::string& outputPath): mazeFiles(mazeFiles), mazePath(mazePath), outputPath(outputPath) {}

GameBuilder::~GameBuilder() {}

/* Returns a list of GameData objects.
 * Return value - list<GameData> */
std::list<GameData> GameBuilder::buildGameDataList() {
	std::list<GameData> gameList;
	for (auto& maze : mazeFiles) {
		string mazeFilePath = mazePath + maze;
		size_t suffixPos = maze.find_last_of(".");
		string gameName = maze.substr(0, suffixPos); //Remove suffix from maze file.
		struct params p = InputMazeParser(mazeFilePath.c_str()).parseMazeFile();
		if (p.validMaze) {
			string outputFilename = outputPath;
			if (outputPath != "")
				outputFilename = outputPath + maze + "_";
			GameData gd(gameName, p.maxSteps, p.rows, p.cols, p.maze, outputFilename.c_str());
			gameList.push_back(std::move(gd)); //Add new game to the list.
		}
	}
	return gameList;
}
