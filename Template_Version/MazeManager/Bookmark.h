/*
 * Bookmark.h
 *
 *  Created on: May 9, 2019
 *      Author: Alon Liberman
 */

#ifndef ALGORITHMS_BOOKMARK_H_
#define ALGORITHMS_BOOKMARK_H_

/* A class that handles bookmark functionality */
class Bookmark {
private:
	const int verticalSteps;
	const int horizontalSteps;
public:
	Bookmark(int _verticalSteps, int _horizontalSteps):
		verticalSteps(_verticalSteps), horizontalSteps(_horizontalSteps) {};
	unsigned int calcVerticalLen(int playerVerticalSteps) const {
		return abs(verticalSteps - playerVerticalSteps);
	};
	unsigned int calcHorizontalLen(int playerHorizontalSteps) const {
		return abs(horizontalSteps - playerHorizontalSteps);
	};
};

#endif /* ALGORITHMS_BOOKMARK_H_ */
