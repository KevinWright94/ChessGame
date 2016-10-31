/*
 * chess.h
 *
 *  Created on: Oct 21, 2016
 *  Author: Kevin Wright
 */

#ifndef CHESS_H_
#define CHESS_H_

#include <string>
#include <iostream>
#include <cmath>

using namespace std;

class Chess{
public:
	enum piece {none, pawn, king, queen, knight, rook, bishop};

	string pieceStr[7];//array set in setBoard that contains string versions of the different piece types, enumerated above

	enum color {noColor, white, black};
	string colorStr[3];

	color curTurn; // color of current player
	bool gameOver;
	bool whiteInCheck;
	bool blackInCheck;

	struct loc{ //location: x and y coordinates
		int x;
		int y;
	};
	struct space{ //contents of a space of the chess board
		public:
			piece curPiece;
			color curColor;
			bool pawnMoved;//only used for pawns to determine if they can move 2 spaces or not.
	};

	space board[8][8]; //model of the chess board

	void setBoard();
	void showBoard();
	void turn(bool, loc, loc);
protected:
	loc selectPiece(color);
	loc getLoc();
	bool checkMove(loc, loc, piece);
	void movePiece(loc, loc);
	bool isCheck(loc, color);
	bool checkCheckMate(color);
	loc findKing(color);
};
#endif /* CHESS_H_ */
