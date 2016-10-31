/*
 * ai.cpp
 *
 *  Created on: Oct 21, 2016
 *      Author: Kevin
 */

#include"ai.h"

//Takes an enumerated piece and returns an int value for the importance of the piece
int AI::pieceVal(Chess::piece p){
	int value;
	switch(p){
	case Chess::pawn:
		value = 1;
		break;
	case Chess::bishop:
		value = 2;
		break;
	case Chess::knight:
		value = 2;
		break;
	case Chess::rook:
		value = 3;
		break;
	case Chess::queen:
		value = 4;
		break;
	case Chess::king:
		value = 5;
		break;
	case Chess::none:
		value = 0;
		break;
	}
	return value;
}

//takes the location of an AI controlled black piece, and returns true if the piece can be taken by a white piece in the next turn
bool AI::danger(loc blackL){ //find what can attack current piece
	bool inDanger = false;
	for (int wx = 0; wx < 8; wx++){
		for (int wy = 0; wy < 8; wy++){
			if (board[wx][wy].curColor == white){
				loc whiteL;
				whiteL.x = wx;
				whiteL.y = wy;
				//cout <<"Danger: checkMove(" << whiteL.x << ", " << whiteL.y << ") to (" << blackL.x << ", " << blackL.y << ")\n";
				if (checkMove(whiteL, blackL, board[whiteL.x][whiteL.y].curPiece)){
					inDanger = true;
				}
			}
		}
	}
	return inDanger;
}

//takes the location of an AI controlled black piece, and returns the int value of the best white piece that the
//black piece is in position take in the next turn
int AI::bestAttack(loc blackL){

	int bestAttackValue = 0;

	for (int wx = 0; wx < 8; wx++){
		for (int wy = 0; wy < 8; wy++){
			if (board[wx][wy].curColor == white){
				loc whiteL;
				whiteL.x = wx;
				whiteL.y = wy;
				//cout <<"bestAttack: checkMove(" << blackL.x << ", " << blackL.y << ") to (" << whiteL.x << ", " << whiteL.y << ")\n";
				if (checkMove(blackL, whiteL, board[blackL.x][blackL.y].curPiece) && pieceVal(board[whiteL.x][whiteL.y].curPiece) >= bestAttackValue){
					bestAttackValue = pieceVal(board[whiteL.x][whiteL.y].curPiece);
				}
			}
		}
	}
	//cout << "BESTVICLOc = (" << bestVicLoc.x << ", " << bestVicLoc.y << ") from ("<< blackL.x << ", " << blackL.y << ")\n";
	return bestAttackValue;
}

//tests all possible moves for black to take in the next turn, and returns the one that has the highest 'value'
//found by subtracting points for the danger black pieces are put in and adding points for the risk white pieces are placed in by black pieces
AI::move AI::bestMove(){
	vector<move> bestMove;
	move curMove;
	loc curLoc;

	move returnMove;
	loc blackPiece;
	space saveSpace; //saves the contents of a space before attempting a move that overrides it
	int bestMoveVal = -1000;
	int currentMoveVal = 0;
	int moveIndex;

	for(int ox = 0; ox < 8; ox++){
		for(int oy = 0; oy < 8; oy++){
			if(board[ox][oy].curColor == black){ //finds current black Pieces
				blackPiece.x = ox;
				blackPiece.y = oy;
				for(int x = 0; x < 8; x++){ //for each black piece found, find all moves
					for(int y = 0; y < 8; y++){

						curLoc.x = x;
						curLoc.y = y;
						//cout <<"BestMove: checkMove(" << blackPiece.x << ", " << blackPiece.y << ") to (" << curLoc.x << ", " << curLoc.y << ")\n";
						if(checkMove(blackPiece, curLoc, board[blackPiece.x][blackPiece.y].curPiece)){
							currentMoveVal = 0;
							if(board[curLoc.x][curLoc.y].curColor == white){
								currentMoveVal += pieceVal(board[curLoc.x][curLoc.y].curPiece); //double points for actually taking a piece
								currentMoveVal *= 2;
								//cout << "Taken Piece\n";
							}

							//emulates a move to score its value, and then returns pieces to their starting positions
							saveSpace = board[curLoc.x][curLoc.y];
							movePiece(blackPiece, curLoc);

							currentMoveVal += scoreBoard();

							movePiece(curLoc, blackPiece);
							board[curLoc.x][curLoc.y] = saveSpace;

							if(currentMoveVal == bestMoveVal){
								curMove.from = blackPiece;
								curMove.to = curLoc;
								returnMove = curMove;
								bestMove.push_back(curMove);
							}

							if(currentMoveVal > bestMoveVal){

								curMove.from = blackPiece;
								curMove.to = curLoc;
								returnMove = curMove;
								bestMove.clear();
								bestMove.push_back(curMove);
								bestMoveVal = currentMoveVal;
							}
						}
					}
				}
			}
		}
	}
	if (bestMove.size() > 0){ //if bestMoves has at least 1 move, return random move from bestMoves
		std::srand(std::time(0));
		int randInt = std::rand()+ 1;
		moveIndex = (randInt % bestMove.size());
		returnMove = bestMove[moveIndex];
	}
	else{ //return invalid move if no possible moves found, probably means AI is in check mate
		returnMove.from.x = -1;
		returnMove.from.y = -1;
		returnMove.to.x = -1;
		returnMove.to.y = -1;
	}

	return returnMove;
}

// scores a potential move the AI can make.scores them based on the value of potential future moves, and potential dangers.
int AI::scoreBoard(){
	int val = 0;
	loc blackP;

	for(int x = 0; x < 8; x++){
		for(int y = 0; y < 8; y++){
			if(board[x][y].curColor == black){
				blackP.x = x;
				blackP.y = y;
				if(danger(blackP) && board[blackP.x][blackP.y].curPiece != queen){
					val -= pieceVal(board[blackP.x][blackP.y].curPiece);
				}
				else if(danger(blackP) && board[blackP.x][blackP.y].curPiece == queen){
					val -= (pieceVal(board[blackP.x][blackP.y].curPiece)* 2);//minus double points for putting queen in danger to dissuade AI from endangering it
				}
				val += bestAttack(blackP);
			}
		}
	}

	return val;
}

