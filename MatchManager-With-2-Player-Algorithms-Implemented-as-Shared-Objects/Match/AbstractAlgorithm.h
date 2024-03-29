/*
 * AbstractAlgorithm.h
 *
 *  Created on: Apr 29, 2019
 *      Author: alon
 */

// AbstractAlgorithm.h

#pragma once

class AbstractAlgorithm {
public:
virtual ~AbstractAlgorithm(){}

enum Move { UP, RIGHT, DOWN, LEFT, BOOKMARK };

    virtual Move move() = 0;
    virtual void hitWall() = 0;
    virtual void hitBookmark(int seq) = 0;
};
