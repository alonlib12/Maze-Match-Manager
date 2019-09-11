/*
 * GameBuilder.h
 *
 *  Created on: Jun 12, 2019
 *      Author: Alon Liberman
 */

#ifndef GAMEBUILDER_H_
#define GAMEBUILDER_H_
/* A class that builds a list of GameData objects. */
#include <string>
#include <list>
#include "GameData.h"

class GameBuilder {
private:
	const std::list<std::string>& mazeFiles;
	const std::string& mazePath;
	const std::string& outputPath;
public:
	GameBuilder(const std::list<std::string>& mazeFiles, const std::string& mazePath,
				const std::string& outputPath);
	virtual ~GameBuilder();
	std::list<GameData> buildGameDataList();
};

#endif /* GAMEBUILDER_H_ */
