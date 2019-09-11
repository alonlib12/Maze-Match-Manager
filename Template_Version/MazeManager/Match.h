/*
 * Match.h
 *
 *  Created on: Jun 1, 2019
 *      Author: Alon Liberman
 */

#ifndef MATCH_H_
#define MATCH_H_
#include <mutex>
#include <functional>
#include <vector>
#include <atomic>
#include <thread>
#include <memory>
static const size_t INITIAL_AVAILABLE_IDX = 0;

//-----------------
// Match Manager
//-----------------
template<typename GameManager, typename GameData, typename Player, typename PlayerFactory = std::function<Player(typename GameData::InitData)>>
class Match {
    GameManager game_manager;
    std::vector<GameData> games;
    std::vector<PlayerFactory> players;
    std::atomic<std::size_t> availableIdx;
    std::mutex addScoreMutex;
    std::mutex addGameMutex;
public:
    explicit Match(GameManager gm): game_manager{std::move(gm)}, availableIdx(INITIAL_AVAILABLE_IDX) {}
    void addGame(GameData gd) {
        games.push_back(std::move(gd));//
    }
    void addPlayer(PlayerFactory p) {
        players.push_back(std::move(p));
    }
    using Report = std::vector<std::pair<typename GameData::Id, std::vector<std::pair<typename Player::Id, int>>>>;

    /* A thread function for playing the available games with available players.
     * Uses atomic integer to make sure that only one thread handles each game and player pair.
	 * Return value - void */
    void threadHandler(Report& report) {
		size_t localIdx = availableIdx++;
		size_t localGameIdx = localIdx / players.size();
		size_t localPlayerIdx = localIdx % players.size();
		while ( localIdx < games.size()*players.size() ) {
			typename std::vector<GameData>::iterator gameItr = games.begin();
			advance(gameItr,localGameIdx);
			typename std::vector<PlayerFactory>::iterator playerFactoryItr = players.begin();
			advance(playerFactoryItr,localPlayerIdx);
			{ //Locking before adding game
				std::lock_guard<std::mutex> lock(addGameMutex);
				if (localGameIdx == report.size())
					report.emplace_back(gameItr->id(), std::vector<std::pair<typename Player::Id, int>>{});
			}
			// gameInstance is per player
			typename GameData::GameInstanceData gameInstance = gameItr->newGameInstance();
			typename GameData::InitData gameInitData = game_manager.getInitData(*gameItr, gameInstance);
			Player player = (*playerFactoryItr)(gameInitData);
			while(!game_manager.endGame(*gameItr, gameInstance)) {
				typename GameData::Move move = player.move();
				typename GameData::MoveFeedback feedback = game_manager.processMove(*gameItr, gameInstance, move);
				player.moveFeedback(feedback);
			}
			{ //Get next game and player
				std::lock_guard<std::mutex> lock(addScoreMutex);
				report[localGameIdx].second.emplace_back(player.id(), game_manager.score(*gameItr, gameInstance));
			}
			localIdx = availableIdx++; //Get the next game and player
			localGameIdx = localIdx / players.size();
			localPlayerIdx = localIdx % players.size();
		}
    }



    Report runMatch(size_t numOfThreads) {
        Report report;
        std::vector<std::unique_ptr<std::thread>> threads(numOfThreads);
		if (numOfThreads > 1) {
			for (size_t i=0 ; i<numOfThreads ; i++) {
				threads[i] = std::make_unique<std::thread>(&Match::threadHandler, this, std::ref(report)); // create and run the thread
			}
			// ===> join all the threads to finish nicely (i.e. without crashing / terminating threads)
			for(size_t i=0 ; i<numOfThreads ; i++) {
					threads[i]->join();
			}
		}
		else //If input -num_threads equals 1 then use the main thread only.
			threadHandler(report);
        return report;
    }
};

#endif /* MATCH_H_ */
