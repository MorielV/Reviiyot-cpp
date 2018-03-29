#ifndef HAND_H_
#define HAND_H_

#include <iostream>
#include <vector>
#include "Card.h"
#include "Deck.h"

using namespace std;

class Hand {
private:

	vector<Card*>myHand;
public:
	Hand(Deck &deck);
	Hand(const Hand& otherHand);
	vector<Card*>& getHandVector();//returns a reference to the vector
	Hand &operator=(const Hand& otherDeck);			//"=" operator
	void clear();
	vector<Card*> clone ()const;	//function that clones a vector of cards

	bool addCard(Card &card);
	bool removeCard(Card &card);
	void fourOfAKind();		//removes four of a kind from a hand, if it exists
	int getNumberOfCards(); // Get the number of cards in hand
	string toString(); // Return a list of the cards, separated by space, in one line, in a sorted order, ex: "2S 5D 10H"
	virtual ~Hand();
};

#endif
