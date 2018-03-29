#ifndef CARD_H_
#define CARD_H_

#include <iostream>
#include <string>
using namespace std;


enum Shape {
	Club,
	Diamond,
	Heart,
	Spade
};

enum Figure {
	Jack,
	Queen,
	King,
	Ace
};

class Card {
private:
  Shape shape;
public:
  	bool isFigure;
  	Card();
  	int compareByValue(Card &cardB);
  	int compareTo(Card &cardB);				 //Compares between 2 cards, returns an INT accordingly
	void setShape(char shapeAsChar);		 //set shape for card
	Shape getShape();
	virtual int getValue()	= 0 ;
	virtual string toString() = 0;			 //Returns the string representation of the card "<value><shape>" exp: "12S" or "QD"
	virtual ~Card() {}
};

class FigureCard : public Card {
private:

	Figure figure;
	string stringRep;
public:
	Figure getFigure();
	int getValue();
	FigureCard(const string & cardAsString);
	virtual string toString() override;
	virtual ~FigureCard() {};
};

class NumericCard : public Card {
private:
	int number;
    string stringRep;

public:
    int getValue();
	NumericCard(const string & cardAsString);
	virtual string toString() override;
	virtual ~NumericCard() {}
};




#endif
