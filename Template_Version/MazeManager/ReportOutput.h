/*
 * ReportOutput.h
 *
 *  Created on: Jun 11, 2019
 *      Author: Alon Liberman
 */

#ifndef REPORTOUTPUT_H_
#define REPORTOUTPUT_H_
#include <functional>
#include <iostream>
/* A class that handles the printing of match results */
static const size_t PADDING_SIZE = 10;
static const std::string EMPTY_STRING = "";
static const std::string OPENING_STRING = "          |";

template<typename GameManager, typename GameData, typename Player, typename PlayerFactory = std::function<Player(typename GameData::InitData)>>
class ReportOutput {
private:
	using Report = std::vector<std::pair<typename GameData::Id, std::vector<std::pair<typename Player::Id, int>>>>;
	Report& report;
public:
	ReportOutput(Report& report): report(report) {}
	virtual ~ReportOutput() {}
	/* Prints spaces to pad input string to 10 characters and returns empty string.
	 * Return value - string */
	std::string padWithSpaces(const std::string& str) const {
		if (PADDING_SIZE < str.size())
				return EMPTY_STRING;
		size_t spacesLen = PADDING_SIZE - str.size();
		for (size_t i=0; i<spacesLen; i++) {
				std::cout << " ";
		}
		return EMPTY_STRING;
	}
	/* Converts the input integer to string and Prints spaces to pad the input to 10 characters.
	 * Return value - string */
	std::string padWithSpaces(int i) const {
		std::string str = std::to_string(i);
		return padWithSpaces(str);
	}
	/* Prints in a readable format the match results that are saved in private member report.
	 * Return value - void */
	void printReport() {
		if (report.empty())
			return;
		std::cout << OPENING_STRING;
		auto& gameReport = report.front();
		for (auto& playerId : gameReport.second) {
			std::cout << playerId.first << padWithSpaces(playerId.first) << "|";
		}
		std::cout << std::endl;
		for (auto& game : report) {
			std::cout << game.first << padWithSpaces(game.first) << "|";
			for (auto& player : game.second) {
				std::cout << player.second << padWithSpaces(player.second) << "|";
			}
			std::cout << std::endl;
		}
	}
};

#endif /* REPORTOUTPUT_H_ */
