#include "Deck.h"
//Deck constructor
Deck::Deck(const string & stringInput, int n) :myDeck((n + 3) * 4), deckAsString(stringInput),n(n) {
	int index=0;
	string currentCard; //current card we work on.

	if(deckAsString[deckAsString.size()-1]==' '){//if there are SPACES at the end of the deck

		int k=deckAsString.size()-1;
		int numOfSpaces=1;
		while(deckAsString[k]==' '){
			numOfSpaces++;
			k--;
		}
		deckAsString=deckAsString.substr(0,deckAsString.length()-numOfSpaces);
	}


	for (int i = stringInput.length()-1; i>=-1; i--) {

		if (i!=-1 && stringInput[i] != ' ') { //while we don't reach a SPACE char
			currentCard =  stringInput[i] + currentCard;
			}
		else {

			if (currentCard[0]>='0' && currentCard[0]<='9'){ //if the first character of the string is a number
				myDeck[index]=new NumericCard(currentCard);//create a Numeric Card
				currentCard="";
				index++;
			}
			else{
				myDeck[index]=new FigureCard(currentCard); //else-create a figure Card
				currentCard="";
				index++;
			}
		}
	}

}
Deck::Deck(): myDeck(),deckAsString(), n(0){}
Deck::Deck(const Deck &otherDeck):myDeck(),deckAsString(otherDeck.deckAsString), n(otherDeck.n){
	myDeck=otherDeck.clone();
}

vector<Card*> Deck::clone() const{						//clones a Vector of card pointers

	vector<Card*> clonedVector(myDeck.size());		//vector of clone (same size)
	for (unsigned int i=0; i<myDeck.size(); i++){
		if(myDeck[i]->isFigure)
			clonedVector[i]=new FigureCard(myDeck[i]->toString());
		else
			clonedVector[i]=new NumericCard(myDeck[i]->toString());
	}
	return clonedVector;

}
Deck::~Deck(){
	clear();

}
void Deck::clear(){
	for(unsigned int i=0; i<myDeck.size(); i++)	//delete each and every Card (pointer)
		delete myDeck[i];
	this->deckAsString="";
}
Deck & Deck::operator=(const Deck& otherDeck){		//"=" operator

	clear();
	this->deckAsString=otherDeck.deckAsString;
	this->myDeck=otherDeck.clone();

	return *this;
}
Card* Deck::fetchCard(){

	Card* toReturn=myDeck[myDeck.size()-1]; //toReturn will point the the Card FROM THE TOP
	myDeck.pop_back();						//Erase from Vector(the Deck)

	//---remove the card from the string (deckAsString field)
	unsigned int index=0;			//start iterating from the end
	while(deckAsString[index]!=' '&&index<deckAsString.length()){
		index++;
	}
	if(index>=deckAsString.length())
			deckAsString="";
	else
			deckAsString=deckAsString.substr(index+1, deckAsString.length()-1-index);
	return toReturn;
}
int Deck::getNumberOfCards(){
	return myDeck.size();
}
string Deck::toString(){
	return deckAsString;
}





