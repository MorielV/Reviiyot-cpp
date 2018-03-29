#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include<vector>
#include "Player.h"
#include "Deck.h"
#include <fstream>
using namespace std;

class Game {
private:
	vector <Player *> players;  //The list of the players
	Deck deck;                 //The deck of the game
	int verbal;
	int n;
	int numOfTurns;
	unsigned int nextPlayer;
	vector <int> winners;
public:
	Game &operator=(const Game &otherGame);
	~Game();
	void clear();
	Game(char* configurationFile);
	Game(const Game &otherGame);
	void init();
	void play();
	void printState();        //Print the state of the game as described in the assignment.
	void printWinner();       //Print the winner of the game as describe in the assignment.
    void printNumberOfTurns(); //Print the number of played turns at any given time.
    void printTrace(int opponentIndex);	//param- the opponents index
};

#endif
