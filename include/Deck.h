#ifndef DECK_H_
#define DECK_H_
#include <vector>
#include <iostream>
#include<string>
#include "Card.h"

using namespace std;

class Deck {
private:
	// Declare here the collection of "Card *" of the deck
	vector<Card*> myDeck;
	string deckAsString;
	void clear();
public:
	int n;
	Deck(const string &stringInput,const int n);	//Deck Constructor
	Deck(const Deck &otherDeck);							//Deck Copy constructor
	Deck();											//empty
	vector<Card*> clone()const;							//clone a deck
	virtual ~Deck();								//Deck Destructor
	Deck &operator=(const Deck& otherDeck);			//"=" operator
	Card* fetchCard();   							//Returns the top card of the deck and remove it from the deck
	int getNumberOfCards(); 						// Get the number of cards in the deck
	string toString();								// Return the cards in top-to-bottom order in a single line, cards are separated by a space ex: "12S QD AS 3H"

};

#endif
