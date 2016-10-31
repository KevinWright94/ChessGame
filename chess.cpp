/*
 * chess.cpp
 *
 *  Created on: Oct 21, 2016
 *  Author: Kevin Wright
 */
#include"chess.h"

//sets the starting locations of the pieces and initializes the public string arrays.
void Chess::setBoard(){
	//initializing string arrays;
	pieceStr[0] = "none";pieceStr[1] = "pawn";	pieceStr[2] = "king"; pieceStr[3] = "queen";
	pieceStr[4] = "knight"; pieceStr[5] = "rook"; pieceStr[6] = "bishop";

	colorStr[0] = "NO COLOR"; colorStr[1] = "White"; colorStr[2] = "Black";

	whiteInCheck = false;
	blackInCheck = false;

	color setColor;
	int yVal;

	gameOver = false;
	curTurn = white;

	for (int y = 2; y < 6; y++){ // sets the middle of the board to be empty
		for (int x = 0; x < 8; x++){
			board[x][y].curPiece = none;
			board[x][y].curColor = noColor;
		}
	}
	for (int x = 0; x < 2; x++){
		if(x == 0){
			yVal = 7;
			setColor = black;
		}
		else{
			yVal = 0;
			setColor = white;
		}
		board[0][yVal].curPiece = rook;
		board[0][yVal].curColor = setColor;
		board[1][yVal].curPiece = knight;
		board[1][yVal].curColor = setColor;
		board[2][yVal].curPiece = bishop;
		board[2][yVal].curColor = setColor;
		board[3][yVal].curPiece = queen;
		board[3][yVal].curColor = setColor;
		board[4][yVal].curPiece = king;
		board[4][yVal].curColor = setColor;
		board[5][yVal].curPiece = bishop;
		board[5][yVal].curColor = setColor;
		board[6][yVal].curPiece = knight;
		board[6][yVal].curColor = setColor;
		board[7][yVal].curPiece = rook;
		board[7][yVal].curColor = setColor;
		if (yVal == 7)
			yVal--;
		else if(yVal == 0)
			yVal++;
		for (int xVal = 0; xVal < 8; xVal++){
			board[xVal][yVal].curPiece = pawn;
			board[xVal][yVal].curColor = setColor;
			board[xVal][yVal].pawnMoved = false;
		}
	}
}

//outputs the current state of the board to the console, using ASCII art.
void Chess::showBoard(){

	string pieceMap[7];
	pieceMap[0] = "      "; pieceMap[1] = "Pawn  ";	pieceMap[2] = "King  ";	pieceMap[3] = "Queen ";
	pieceMap[4] = "Knight"; pieceMap[5] = "Rook  "; pieceMap[6] = "Bishop";

	string colorMap[3];
	colorMap[0] = "      "; colorMap[1] = "White "; colorMap[2] = "Black ";


	cout << "CURRENT BOARD STATE:\n";
	cout << "--|------|------|------|------|------|------|------|------|\n";
	for (int y = 7; y >= 0; y--){
		cout << y+1 << " |";
		for (int x = 0; x < 8; x++){
			cout << colorMap[board[x][y].curColor] << "|";
		}
		cout << endl << "  |";
		for (int x = 0; x < 8; x++){
			cout << pieceMap[board[x][y].curPiece] << "|";
		}
		cout << endl;
		cout << "--|------|------|------|------|------|------|------|------|\n";
	}
		cout << "  | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    |\n";
}

//takes the color of the current player, and gets the user to input the x and y coordinates of a piece of that color
//returns the coordinates of the selected piece
Chess::loc Chess::selectPiece(color curPlayer){
	loc selected;
	color selectColor = noColor;
	while(selectColor != curPlayer){
		selected = getLoc();
		selectColor = board[selected.x][selected.y].curColor;
		if(selectColor != curPlayer || selected.x < 0 || selected.x > 7 || selected.y < 0 || selected.y > 7)
			cout << "\nNOT A VALID LOCATION: Please select a " << colorStr[curPlayer] << " Piece\n";
	}
	return selected;
}

//prompts the player to input x and y coordinates for a piece, and returns them as a loc
Chess::loc Chess::getLoc(){
	loc selected;
	cout << "X Location: ";
	cin >> selected.x;
	cout << "Y Location: ";
	cin >> selected.y;
	selected.x--; //decrement to have user selection 1,1 go to array [0][0]
	selected.y--;
	return selected;
}

//takes a starting point, ending point, and movement type for a piece and returns a boolean value on if the move is a valid move
//for the given piece type.
bool Chess::checkMove(loc selected, loc dest, piece movType){
	bool canMove = false;
	bool movCheck = true;
	color myColor = board[selected.x][selected.y].curColor;
	color opColor;
	bool opCheck;

	if (myColor == white)
		opColor = black;
	else
		opColor = white;
	if(opColor  == black)
		opCheck = blackInCheck;
	else
		opCheck = whiteInCheck;

	if (dest.x < 0 || dest.y < 0 || dest.x > 7 || dest.y > 7){// return false if destination is out of bounds
		cout << "ERROR: out of bounds selection: ("<< dest.x <<", " << dest.y <<")\n";
		return false;
	}
	if (movType == pawn){
		if(myColor == white){
			if(dest.y == selected.y+1 && dest.x == selected.x && board[dest.x][dest.y].curPiece == none){
				canMove = true;
			}
			else if(dest.y == selected.y+2 && dest.x == selected.x && board[dest.x][dest.y].curPiece == none && board[selected.x][selected.y+1].curPiece == none && board[selected.x][selected.y].pawnMoved == false){
				canMove = true;
			}
			else if ((dest.x == selected.x+1 || dest.x == selected.x-1) && dest.y == selected.y+1 && board[dest.x][dest.y].curColor == opColor){
				canMove = true;
			}
		}
		if(myColor == black){
			if(dest.y == selected.y-1 && dest.x == selected.x && board[dest.x][dest.y].curPiece == none){
				canMove = true;
			}
			else if(dest.y == selected.y-2 && dest.x == selected.x && board[dest.x][dest.y].curPiece == none && board[selected.x][selected.y-1].curPiece == none  && board[selected.x][selected.y].pawnMoved == false){
				canMove = true;
			}
			else if((dest.x == selected.x+1 || dest.x == selected.x-1) && dest.y == selected.y-1 && board[dest.x][dest.y].curColor == opColor){
				canMove = true;
			}
		}
	}
	else if (movType == rook){
		movCheck = true; // set flag to true, becomes false if the path of the piece goes over another piece of your color
		if (dest.x == selected.x){
			if (dest.y < selected.y){
				for (int y = dest.y+1; y < selected.y; y++){
					if (board[dest.x][y].curPiece != none){
						movCheck = false;
					}
				}
			}
			if (dest.y > selected.y){
				for (int y = selected.y+1; y < dest.y; y++){
					if (board[dest.x][y].curPiece != none){
						movCheck = false;
					}
				}
			}
			if(board[dest.x][dest.y].curColor == myColor){
				movCheck = false;
			}
			if (movCheck)
				canMove = true;
		}
		else if (dest.y == selected.y){
			if (dest.x < selected.x){
				for (int x = dest.x+1; x < selected.x; x++){
					if (board[x][dest.y].curPiece != none){
						movCheck = false;
					}
				}
			}
			if (dest.x > selected.x){
				for (int x = selected.x+1; x < dest.x; x++){
					if (board[x][dest.y].curPiece != none){
						movCheck = false;
					}
				}
			}
			if(board[dest.x][dest.y].curColor == myColor){
				movCheck = false;
			}
			if (movCheck)
				canMove = true;
		}
	}
	else if(movType == bishop){
		if(abs(dest.x - selected.x) == abs(dest.y - selected.y)){
			for (int dif = 1; dif < abs(dest.x - selected.x); dif++){
				int xDif = dif;
				int yDif = dif;
				if (dest.x < selected.x)
					xDif = 0 - xDif;
				if (dest.y < selected.y)
					yDif = 0 - yDif;
				if(board[selected.x+xDif][selected.y+yDif].curPiece != none){
					movCheck = false;
				}
			}
			if (movCheck && board[dest.x][dest.y].curColor != myColor)
				canMove = true;
		}
	}
	else if (movType == knight){
		if (((dest.x == selected.x+1 || dest.x == selected.x-1) && (dest.y == selected.y+2 || dest.y == selected.y-2)) ||
		    ((dest.x == selected.x+2 || dest.x == selected.x-2) && (dest.y == selected.y+1 || dest.y == selected.y-1))){
			if(board[dest.x][dest.y].curColor != myColor)
				canMove = true;
		}
	}
	else if (movType == king){
		if (dest.x > (selected.x-2) && dest.x < (selected.x+2) && dest.y > (selected.y-2) && dest.y < (selected.y+2)){
			if (board[dest.x][dest.y].curColor != myColor)
				canMove = true;
		}
	}
	else if (movType == queen){
		if (dest.y == selected.y || dest.x == selected.x){
			canMove = checkMove(selected, dest, rook); // recursive call to test queens movement as a rook
		}
		if (abs(dest.x - selected.x) == abs(dest.y - selected.y)){
			canMove = checkMove(selected, dest, bishop); //recursive call to test queens movement as a bishop
		}

	}
	if(canMove && !opCheck){ // if can move and opponent isn't in check
		space save = board[dest.x][dest.y]; //saves the contents of the destination on the board
		movePiece(selected, dest);

		if(isCheck(findKing(myColor), myColor)){ //if completing the current move puts you in check, its not a valid move
			canMove = false;
		}
		movePiece(dest, selected); //moves the selected piece back to where it started
		board[dest.x][dest.y] = save; //returns the original contents of the destination to the board
	}
	return canMove;
}

//takes the starting location and ending location of a move, and moves the contents of
//the 'from' space to the 'to' space and then empties the starting space
void Chess::movePiece(loc from, loc to){
	board[to.x][to.y].curColor = board[from.x][from.y].curColor;
	board[to.x][to.y].curPiece = board[from.x][from.y].curPiece;
	board[to.x][to.y].pawnMoved = board[from.x][from.y].pawnMoved;

	board[from.x][from.y].curColor = noColor;
	board[from.x][from.y].curPiece = none;
	board[from.x][from.y].pawnMoved = false;
}

//takes the location of the king and the color of the player, returns true if the king is in danger of being taken by an opponent piece
bool Chess::isCheck(loc kingLoc, color player){
	bool canMove = false;
	bool check = false;
	loc testLoc;
	color opColor;

	if (player == white)
		opColor = black;
	else
		opColor = white;

	for (int x = 0;x < 8; x++){ //check if any enemy pieces can move to current location
		for (int y = 0; y < 8; y++){
			testLoc.x = x;
			testLoc.y = y;
			if(board[testLoc.x][testLoc.y].curColor == opColor){
				canMove = checkMove(testLoc, kingLoc, board[testLoc.x][testLoc.y].curPiece);// check if piece at testLoc can move to current location;
				if (canMove)
					check = true;
			}
		}
	}
	if(player == white && check  == true){ //sets flags for the current player's check status
		whiteInCheck = true;
	}
	else if(player == black && check  == true){
		blackInCheck = true;
	}
	else if(player == black && check  == false){
		blackInCheck = false;
	}
	else if(player == white && check  == false){
		whiteInCheck = false;
	}
	return check;
}

//takes the color of a player, and returns true if they have no possible moves that can get them out of check
bool Chess::checkCheckMate(color player){
	bool isCM = true;
	loc selected;
	loc curLoc;
	for(int ox = 0; ox < 8; ox++){
		for (int oy = 0; oy < 8; oy++){
			if(board[ox][oy].curColor == player){
				selected.x = ox;
				selected.y = oy;
				for(int ix = 0; ix < 8; ix++){
					for (int iy = 0; iy < 8; iy++){
						curLoc.x = ix;
						curLoc.y = iy;
						if(checkMove(selected, curLoc, board[selected.x][selected.y].curPiece)){
							isCM = false;
							//cout << "not CheckMate Can Move : " << colorStr[board[selected.x][selected.y].curColor] << " "
							//	 << pieceStr[board[selected.x][selected.y].curPiece]<< endl;
						}
					}
				}
			}
		}
	}
	return isCM;
}

//turn runs through the events of a turn of the game and changes the current player at the end of the turn.
//isPlayer determines if the current turn is being made by a user, or the AI.
//the from and to locations are only used if the current player is an AI, who's move has already been determined.
void Chess::turn(bool isPlayer, loc from, loc to){
	bool canMove = false;
	bool inCheck = false;
	char selectChar;
	bool selectNew;

	loc destination;
	loc startLoc;
	if (!gameOver){
		loc kingLoc = findKing(curTurn);
		cout << "NEW TURN: " <<colorStr[curTurn] << "'s turn\n";

		inCheck = isCheck(kingLoc, curTurn);

		if (inCheck){
			cout <<"IN CHECK:\n";
		}
		if (checkCheckMate(curTurn)){
			gameOver = true;
			cout <<"GAME OVER: " << colorStr[curTurn] << " LOSES\n";
			return;
		}
		if(isPlayer){
			startLoc = selectPiece(curTurn);
		}
		else{
			startLoc = from;
		}
		cout << "Selected " << colorStr[board[startLoc.x][startLoc.y].curColor] << " " << pieceStr[board[startLoc.x][startLoc.y].curPiece] << endl;
		cout << "Move to...\n";
		if(isPlayer)
			destination = getLoc();
		else{
			destination = to;
		}
		cout << "from ("<< startLoc.x+1 <<", " << startLoc.y+1 <<") to ("<< destination.x+1 <<", " <<destination.y+1<< ")\n";
		while (canMove == false){
			canMove = checkMove(startLoc, destination, board[startLoc.x][startLoc.y].curPiece);
			if (canMove == false){
				cout << "INVALID MOVEMENT: please retry selection\n";
				cout << "Select new Piece?\n1:Yes\n0:No\n";
				cin >> selectChar;
				while (selectChar != '0' && selectChar != '1'){
					cout << "INVALID INPUT: please select 1 or 0: \n";
					cin >> selectChar;
				}
				if (selectChar == '1')
					selectNew = true;
				else
					selectNew = false;
				if (selectNew){
					startLoc = selectPiece(curTurn);
					cout << "Selected " << colorStr[board[startLoc.x][startLoc.y].curColor] << " " << pieceStr[board[startLoc.x][startLoc.y].curPiece] << endl;
				}
				cout << "Move to...\n";
				destination = getLoc();
			}
			else{
				movePiece(startLoc, destination);
				if(board[destination.x][destination.y].curPiece == pawn){
					board[destination.x][destination.y].pawnMoved = true;
				}
				//moved = true;
			}
		}
		if (curTurn == white) //swap color for next turn
			curTurn = black;
		else
			curTurn = white;
	}
	return;
}

//takes the color of a player, and returns the location of that players king
Chess::loc Chess::findKing(color curTurn){
	loc kingLoc;
	for (int x = 0; x < 8; x++){ // find the current players king
			for (int y = 0; y < 8; y++){
				if (board[x][y].curColor == curTurn && board[x][y].curPiece == king){
					kingLoc.x = x;
					kingLoc.y = y;
				}
			}
		}
	return kingLoc;
}
