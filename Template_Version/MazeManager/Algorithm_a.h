/*
 * Algorithm_a.h
 *
 *  Created on: Mar 25, 2019
 *      Author: alon
 */

#ifndef SRC_HEADERS_Algorithm_a_H_
#define SRC_HEADERS_Algorithm_a_H_

#include <unordered_map>
#include <stack>
#include "AbstractAlgorithm.h"
#include "Bookmark.h"
#include "Maze.h"


class Algorithm_a: public AbstractAlgorithm {
private:
	Id playerId;
	InitData init;
	Maze visited;
	std::stack<Move> prevMoves;
	int verticalSteps;
	int horizontalSteps;
	int stepsTillBookmark;
	unsigned int vertivalLen;
	unsigned int horizontalLen;
	std::vector<Bookmark> bookmarks;
	unsigned int stepsTillMostLikelyMove;
	bool isDeadEnd() const;
	Move revereseMove(Move move) const;
	void addMove(Move move);
	std::vector<Move> possibleMovesList() const;
	Move mostLikelyDirection(const std::vector<Move>& possibleMoves) const;
	unsigned int countUnvisited(Move move) const;
	unsigned int countUnvisited(const std::vector<int>& v, const std::vector<int>& h, Move move) const;
	bool isWall(int vertical, int horizontal) const ;
	int probabilityOfWall(Move move) const ;
	int probabilityOfWall(const std::vector<int>& v, const std::vector<int>& h) const;
	std::vector<Move> unVisitedList() const;
	Move bookmarkMove();
	Move likelyMove(const std::vector<Move>& unVisitedMoves);
public:
	Algorithm_a(InitData init, Id _playerId);
	virtual ~Algorithm_a();
	Move move() override;
	Id id() const override {return playerId;}
	void moveFeedback(MoveFeedback feedback) override;
	void hitWall() override;
	void hitBookmark(int seq) override;
};

#endif /* SRC_HEADERS_Algorithm_a_H_ */
