/*
 * Algorithm_b.cpp
 *
 *  Created on: Mar 25, 2019
 *      Author: alon
 */

#include <algorithm>
#include "Algorithm_b.h"
#include "../Match/AlgorithmRegistration.h"
#include <climits>

using namespace std;
typedef AbstractAlgorithm::Move Move;

REGISTER_ALGORITHM (Algorithm_b)

const unsigned int STEPS_FOR_MOST_LIKELY_MOVE = 1;
const unsigned int STEPS_FOR_BOOKMARK = 5;
static const int INITIAL_VERTICAL_STEPS = 0;
static const int INITIAL_HORIZONTAL_STEPS = 0;
static const int NO_STEP = 0;
static const int ONE_STEP = 1;
static const int ONE_REVERSE_STEP = -1;
static const int WALL_WEIGHT = 1;
static const int NO_WALL_WEIGHT = 0;
static const int INITIAL_UNVISITED = 0;

Algorithm_b::Algorithm_b():
	verticalSteps(INITIAL_VERTICAL_STEPS),
	horizontalSteps(INITIAL_HORIZONTAL_STEPS),
	stepsTillBookmark(STEPS_FOR_BOOKMARK), //CHANGE TO STEPS_FOR_BOOKMARK
	vertivalLen(UINT_MAX),
	horizontalLen(UINT_MAX),
	stepsTillMostLikelyMove(STEPS_FOR_MOST_LIKELY_MOVE) {}

Algorithm_b::~Algorithm_b() {}

/* Returns a vector with all valid moves.
 * contains unvisited cells and visited cells that are not walls. */
vector<Move> Algorithm_b::possibleMovesList() const{
	vector<Move> possibleMoves;
	if (visited.isVisited(verticalSteps,horizontalSteps,Move::UP) && visited.getSymbol(verticalSteps+1, horizontalSteps) != mazeSymbols::wall)
		possibleMoves.push_back(Move::UP);
	else if (!visited.isVisited(verticalSteps,horizontalSteps,Move::UP))
		possibleMoves.push_back(Move::UP);
	if (visited.isVisited(verticalSteps,horizontalSteps,Move::DOWN) && visited.getSymbol(verticalSteps-1, horizontalSteps) != mazeSymbols::wall)
		possibleMoves.push_back(Move::DOWN);
	else if (!visited.isVisited(verticalSteps,horizontalSteps,Move::DOWN))
		possibleMoves.push_back(Move::DOWN);

	if (visited.isVisited(verticalSteps,horizontalSteps,Move::LEFT) && visited.getSymbol(verticalSteps, horizontalSteps-1) != mazeSymbols::wall)
		possibleMoves.push_back(Move::LEFT);
	else if (!visited.isVisited(verticalSteps,horizontalSteps,Move::LEFT))
		possibleMoves.push_back(Move::LEFT);

	if (visited.isVisited(verticalSteps,horizontalSteps,Move::RIGHT) && visited.getSymbol(verticalSteps, horizontalSteps+1) != mazeSymbols::wall)
		possibleMoves.push_back(Move::RIGHT);
	else if (!visited.isVisited(verticalSteps,horizontalSteps,Move::RIGHT))
		possibleMoves.push_back(Move::RIGHT);

	return possibleMoves;
}



vector<Move> Algorithm_b::unVisitedList() const{
	vector<Move> unVisitedMoves;
	if (!visited.isVisited(verticalSteps,horizontalSteps,Move::UP))
		unVisitedMoves.push_back(Move::UP);
	if (!visited.isVisited(verticalSteps,horizontalSteps,Move::DOWN))
		unVisitedMoves.push_back(Move::DOWN);
	if (!visited.isVisited(verticalSteps,horizontalSteps,Move::LEFT))
		unVisitedMoves.push_back(Move::LEFT);
	if (!visited.isVisited(verticalSteps,horizontalSteps,Move::RIGHT))
		unVisitedMoves.push_back(Move::RIGHT);

	return unVisitedMoves;
}


unsigned int Algorithm_b::countUnvisited(const vector<int>& v, const vector<int>& h, Move move) const {
	unsigned int unvisited = INITIAL_UNVISITED;
	unvisited += visited.isVisited(verticalSteps+v[0],horizontalSteps+h[0],move)? NO_WALL_WEIGHT : WALL_WEIGHT;
	unvisited += visited.isVisited(verticalSteps+v[1],horizontalSteps+h[1],move)? NO_WALL_WEIGHT : WALL_WEIGHT;
	unvisited += visited.isVisited(verticalSteps+v[2],horizontalSteps+h[2],move)? NO_WALL_WEIGHT : WALL_WEIGHT;
	unvisited += visited.isVisited(verticalSteps+v[3],horizontalSteps+h[3],move)? NO_WALL_WEIGHT : WALL_WEIGHT;
	unvisited += visited.isVisited(verticalSteps+v[4],horizontalSteps+h[4],move)? NO_WALL_WEIGHT : WALL_WEIGHT;
	unvisited += visited.isVisited(verticalSteps+v[5],horizontalSteps+h[5],move)? NO_WALL_WEIGHT : WALL_WEIGHT;
	return unvisited;
}




/* Computes the number of unvisited cells at a certain direction.
 * Return value - unsigned int */
unsigned int Algorithm_b::countUnvisited(Move move) const{
	unsigned int unvisited = INITIAL_UNVISITED;
	vector<int> v;
	vector<int> h;
	switch(move) {
		case Move::UP:
			v = {NO_STEP,NO_STEP,NO_STEP,ONE_STEP,ONE_STEP,ONE_STEP};
			h = {NO_STEP,ONE_REVERSE_STEP,ONE_STEP,NO_STEP,ONE_REVERSE_STEP,ONE_STEP};
			return countUnvisited(v,h,move);
		case Move::DOWN:
			v = {NO_STEP,NO_STEP,NO_STEP,ONE_REVERSE_STEP,ONE_REVERSE_STEP,ONE_REVERSE_STEP};
			h = {NO_STEP,ONE_REVERSE_STEP,ONE_STEP,NO_STEP,ONE_REVERSE_STEP,ONE_STEP};
			return countUnvisited(v,h,move);
		case Move::RIGHT:
			v = {NO_STEP,ONE_REVERSE_STEP,ONE_STEP,NO_STEP,ONE_REVERSE_STEP,ONE_STEP};
			h = {NO_STEP,NO_STEP,NO_STEP,ONE_STEP,ONE_STEP,ONE_STEP};
			return countUnvisited(v,h,move);
		case Move::LEFT:
			v = {NO_STEP,ONE_REVERSE_STEP,ONE_STEP,NO_STEP,ONE_REVERSE_STEP,ONE_STEP};
			h = {NO_STEP,NO_STEP,NO_STEP,ONE_REVERSE_STEP,ONE_REVERSE_STEP,ONE_REVERSE_STEP};
			return countUnvisited(v,h,move);
		case Move::BOOKMARK:
			break;
	}
	return unvisited;
}

/* Returns the Move which has the most unvisited cells
 * Return value - Move */
Move Algorithm_b::mostLikelyDirection(const vector<Move>& possibleMoves) const {
	int mostLikelyMove = INT_MIN;
	Move maxMove;
	for (Move move : possibleMoves) {
		if (mostLikelyMove < static_cast<int>(countUnvisited(move)) ) {
			mostLikelyMove = static_cast<int>(countUnvisited(move));
			maxMove = move;
		}
	}
	return maxMove;
}

/* Sets bookmark in member variables and returns bookmark move.
 * Return value - Moves */
Move Algorithm_b::bookmarkMove() {
	bookmarks.push_back(Bookmark(verticalSteps, horizontalSteps));
	stepsTillBookmark = STEPS_FOR_BOOKMARK;
	visited.insert(verticalSteps,horizontalSteps,mazeSymbols::bookmark);
	addMove(Move::BOOKMARK);
	return Move::BOOKMARK;
}

/* Returns the most likely move to do from the unVisitedMoves list.
 * Return value - Moves */
Move Algorithm_b::likelyMove(const vector<Move>& unVisitedMoves) {
	stepsTillMostLikelyMove = STEPS_FOR_MOST_LIKELY_MOVE;
	Move moveResult = mostLikelyDirection(unVisitedMoves);
	addMove(moveResult);
	return moveResult;
}


/* Picks a random move that the player has not
 * visited yet. If the player has visited all the possible next positions
 * then it keeps returning back the steps it did until it finds a position
 * it has not visited.
 * Return value - Moves */
Move Algorithm_b::move() {
	vector<Move> possibleMoves = possibleMovesList();
	vector<Move> unVisitedMoves = unVisitedList();
	stepsTillMostLikelyMove--;
	stepsTillBookmark--;
	//Set bookmark if needed.
	if (stepsTillBookmark == 0 && visited.getSymbol(verticalSteps,horizontalSteps) != mazeSymbols::bookmark) {
		return bookmarkMove();
	}
	if (isDeadEnd() && prevMoves.size() > 0) {
		Move lastMove = prevMoves.top(); prevMoves.pop();
		addMove(revereseMove(lastMove));
		return revereseMove(lastMove);
	}
	std::random_device rd;
	std::default_random_engine rng(rd());
	std::uniform_int_distribution<> randoffset(0,possibleMoves.size()-1);
	//Return most likely move if needed.
	if (stepsTillMostLikelyMove == 0 && unVisitedMoves.size() > 0) {
		return likelyMove(unVisitedMoves);
	}
	Move moveResult = possibleMoves[randoffset(rng)%possibleMoves.size()];
	//Check if current place is junction and save the coordinates
	while(possibleMoves.size() > 1 && visited.isVisited(verticalSteps,horizontalSteps,moveResult)) {
		vector<Move>::iterator pos = find(possibleMoves.begin(), possibleMoves.end(), moveResult);
		possibleMoves.erase(pos);
		moveResult = possibleMoves[randoffset(rng)%possibleMoves.size()];
	}
	addMove(moveResult);
	return moveResult;
}

/* Returns the reverse move of the input move.
 * Input - Moves move.
 * Return value - Moves */
Move Algorithm_b::revereseMove(Move move) const{
	switch(move) {
		case Move::UP:
			return Move::DOWN;
		case Move::DOWN:
			return Move::UP;
		case Move::LEFT:
			return Move::RIGHT;
		case Move::RIGHT:
			return Move::LEFT;
		default:
			return Move::UP;
	}
}

/* Returns true if player has visited all possible next positions.
 * Return value - bool */
bool Algorithm_b::isDeadEnd() const{
	return visited.isVisited(verticalSteps,horizontalSteps,Move::UP) && visited.isVisited(verticalSteps,horizontalSteps,Move::DOWN) && visited.isVisited(verticalSteps,horizontalSteps,Move::LEFT) && visited.isVisited(verticalSteps,horizontalSteps,Move::RIGHT);
}

/* Saves the current move and maze char (pass, wall, end or start).
 * Return value - void. */
void Algorithm_b::addMove(Move move) {
	if (!isDeadEnd() && move != Move::BOOKMARK)
		prevMoves.push((Move)move);

	switch(move) {
		case Move::UP:
			verticalSteps++;
			break;
		case Move::DOWN:
			verticalSteps--;
			break;
		case Move::LEFT:
			horizontalSteps--;
			break;
		case Move::RIGHT:
			horizontalSteps++;
			break;
		case Move::BOOKMARK:
			visited.insert(verticalSteps,horizontalSteps,mazeSymbols::bookmark);
			return;
	}

	if (!visited.isVisited(verticalSteps,horizontalSteps))
		visited.insert(verticalSteps,horizontalSteps,mazeSymbols::pass);
}

/* This method is called by the game manager to notify the player that
 * the move it made is to a wall.
 * Return value - void. */
void Algorithm_b::hitWall() {
	visited.insert(verticalSteps,horizontalSteps,mazeSymbols::wall);
	Move lastMove = prevMoves.top(); prevMoves.pop();
	switch(lastMove) {
		case Move::UP:
			verticalSteps--;
			break;
		case Move::DOWN:
			verticalSteps++;
			break;
		case Move::LEFT:
			horizontalSteps++;
			break;
		case Move::RIGHT:
			horizontalSteps--;
			break;
		default:
			break;
	}
}

/* This method is called by the game manager to notify the player that
 * it hit a bookmark. The player then updates the maze borders.
 * Return value - void. */
void Algorithm_b::hitBookmark(int seq) {
	if ( visited.isVisited(verticalSteps,horizontalSteps) && visited.getSymbol(verticalSteps,horizontalSteps) == mazeSymbols::bookmark )
		return;
	if (min(bookmarks[seq-1].calcVerticalLen(verticalSteps), vertivalLen) != 0)
		vertivalLen = min(bookmarks[seq-1].calcVerticalLen(verticalSteps), vertivalLen);
	if (min(bookmarks[seq-1].calcHorizontalLen(horizontalSteps), horizontalLen) != 0)
		horizontalLen = min(bookmarks[seq-1].calcHorizontalLen(horizontalSteps), horizontalLen);
	visited.insert(verticalSteps,horizontalSteps,mazeSymbols::bookmark);
}

