# ChessGame
Models a game of chess. With either 2 players, or 1 player against an AI.

Made by: Kevin Wright

Written in C++, using Eclipse and compiled Using G++.

Main.cpp:

initalizes the classes and handles the main gameplay loop at the most abstract level.

chess.h/chess.cpp:

Contains the Chess class which controls the data representation of the chess board, the pieces on it, and the funtions related to the operations of the game(i.e. checking if a piece can move from point a to b, or checking if a player is in check).

ai.h / ai.cpp:

contains the AI class which contains the functions related to the decision making process of the AI if the game is played single player. AI is a subclass of Chess so that it can use Chess's protected functions in its decision making process.
