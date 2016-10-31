/*
 * Main.cpp
 *
 *  Created on: Oct 21, 2016
 *  Author: Kevin Wright
 */
#include<iostream>
#include<string>
#include<cmath>

#include"chess.h"
#include"ai.h"

using namespace std;

int main(){
	string test;
	AI::move aiBestMove;
	Chess* game;
	AI *blackAI;
	game = blackAI = new AI;
	game->setBoard();
	char inchar;


	cout << "Please select number of Players:\n1: One Player 2: Two Players\n";
	cin >> inchar;
	while(inchar != '1' && inchar != '2'){
		cout << "Not a valid response, Please select '1' or '2' for the number of players:\n";
		cin >> inchar;
	}
	while (game->gameOver != true){
		game->showBoard();
		game->turn(true, aiBestMove.from, aiBestMove.to);
		game->showBoard();
		if(inchar == '1'){
			aiBestMove = blackAI->bestMove();
			game->turn(false, aiBestMove.from, aiBestMove.to);
		}
		else{
			game->turn(true, aiBestMove.from, aiBestMove.to);
		}

	}
	return 0;
}
