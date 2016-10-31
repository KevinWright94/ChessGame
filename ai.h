/*
 * ai.h
 *
 *  Created on: Oct 21, 2016
 *  Author: Kevin Wright
 */

#ifndef AI_H_
#define AI_H_
#include"chess.h"
#include<iostream>
#include<vector>
#include<cstdlib>
#include <ctime>

class AI : public Chess{
public:
	struct move{
		loc to;
		loc from;
	};
	move bestMove();
private:
	bool danger(loc);
	int bestAttack(loc);
	int pieceVal(piece);

	int scoreBoard();
};
#endif /* AI_H_ */
