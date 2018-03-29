#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>

#include <Hand.h>

using namespace std;

class Player : public Hand {
private:
	const string name;
public:
	const int type;
	int position;
	Player(const string &name, int type,  int position,Deck &deck);
	string toString();	 											//to make Class Player abstract
	string getName();  												//Returns the name of the player
	virtual Card &cardToSearch()=0; 								// Abstract function that find the card you need to ask for
	virtual int choosePlayer(const vector<Player*> &players)=0;	 	//Abstract function that choose the player you need to ask for cards
	void makeMove( vector<Player*>& players, Deck &deck,int opponentIndex);			//make a move (ask a player for the card you need) -Returns INT as in the index of the player we played with
	Player(const Player& otherPlayer);								//Player copy constructor

};

class PlayerType1 : public Player {  //For strategy 1
public:
	//constructor
	PlayerType1(string &playerName, int playerPosition,Deck &deck);
	//copy constructor
	PlayerType1(Player &otherPlayer);
	//what is the wanted value-according to our hand
	Card &cardToSearch();
	int choosePlayer(const vector<Player*> &players);

};

class PlayerType2 : public Player {  //For strategy 2
public:
	//constructor
	PlayerType2(string &playerName, int playerPosition,Deck &deck);
	//copy constructor
		PlayerType2(Player &otherPlayer);
	//what is the wanted value-according to our hand
	Card &cardToSearch();
	int choosePlayer(const vector<Player*> &players);


//...
};

class PlayerType3 : public Player {  //For strategy 3
	public:
		PlayerType3(string &playerName, int playerPosition,Deck &deck);
		//copy constructor
		PlayerType3(Player &otherPlayer);
		Card &cardToSearch();
		int choosePlayer(const vector<Player*> &players);

	private:
		int lastAsked3;			//the last player we asked for a card
};


class PlayerType4 : public Player {  //For strategy 4
public:
		PlayerType4(string &playerName, int playerPosition,Deck &deck);
		//copy constructor
		PlayerType4(Player &otherPlayer);
		Card &cardToSearch();
		int choosePlayer(const vector<Player*> &players);


	private:
		int lastAsked4;			//the last player we asked for a card};
};




#endif
