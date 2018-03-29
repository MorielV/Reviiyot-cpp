#include "Hand.h"

//Hand constructor
Hand::Hand(Deck &deck):myHand(){
	for(int i=0; i<7; i++){		//add 7 cards from the deck
		Card *toAdd=(deck.fetchCard());
		bool cardWasAdded=addCard(*(toAdd));
		delete toAdd;					//delete card (that was in the deck) from memory-it was RECREATED in a hand
		if(!cardWasAdded)
			throw new runtime_error("Error adding card to Hand");
	}
			fourOfAKind();		//check if there are 4 of a kind in the hand. if so-delete them

}
//Hand copy constructor
Hand::Hand(const Hand& otherHand):myHand(otherHand.myHand.size()){
	myHand=otherHand.clone();

}
//Hand Destructor
Hand::~Hand(){
clear();
};
 vector<Card*>& Hand::getHandVector(){
	return myHand;
}

Hand & Hand::operator=(const Hand& otherHand){

	if(this==&otherHand)
			return *this;
		clear();
		this->myHand=otherHand.clone();
		return *this;





}
 void Hand::clear(){
	for(unsigned int i=0; i<myHand.size(); i++)	//delete each and every Card (pointer)
			delete myHand[i];

}
 vector<Card*> Hand::clone() const{
	vector<Card*> clonedVector(myHand.size());		//vector of clone (same size)
		for (unsigned int i=0; i<myHand.size(); i++){
			if(myHand[i]->isFigure)
				clonedVector[i]=new FigureCard(myHand[i]->toString());
			else
				clonedVector[i]=new NumericCard(myHand[i]->toString());
		}
		return clonedVector;
}
int Hand::getNumberOfCards(){	 //return number of cards in hand
	return myHand.size();
}
bool Hand::addCard(Card &card){
	Card* toAdd;
	string cardAsString=card.toString();
	if(card.isFigure)	//if its a Figure Card-Create one and add to Vector
		 toAdd=new FigureCard(cardAsString);
	else				//if its a Numeric Card - create one and add to vector
		toAdd=new NumericCard(cardAsString);
	//add card at the appropriate place in the vector ! (to keep it sorted)
	unsigned int index=0;
	while(index<myHand.size()&&myHand[index]->compareTo(*toAdd)<0)	//while we compare to a card "smaller" than toAdd
		index++;
	if(index<myHand.size()&&myHand[index]->toString()==toAdd->toString())				//if trying to add a card you already have- illegal
		return false;
	else
		myHand.insert(myHand.begin()+index, toAdd);


	return true;





}
bool Hand::removeCard(Card &card){//removes a certain card

	string toRemoveString=card.toString();	//the string of the Card That's to be removed
	bool cardWasFound=false;
	int removeFromIndex;
	for (unsigned int i=0; i<myHand.size()&&!cardWasFound; i++)	//look for the card by comparing Strings.
		if(toRemoveString==myHand[i]->toString()){
			cardWasFound=true;
			removeFromIndex=i;
	}
	//now cardWasFound is true IFF we found the card
	if(cardWasFound){
		delete myHand[removeFromIndex];			//delete the card
		myHand.erase(myHand.begin()+removeFromIndex);	//remove card from vector
	}
	return cardWasFound;





}
void Hand::fourOfAKind(){		  //removes four of a kind from a hand, if it exists

	int index=myHand.size()-1;
	bool found=false;
	int fourIndex=-1;			//index of the first card in the 4 of a kind sequence

	while(!found && index>=3){
		if(myHand[index-3]->compareByValue(*myHand[index])==0){
			found=true;
			fourIndex=index-3;
		}
		index--;
	}
	if(fourIndex!=-1){
		for(int i=fourIndex;i<=fourIndex+3; i++ ){
				delete myHand[i];				//delete the card
			}
		myHand.erase(myHand.begin()+fourIndex,myHand.begin()+fourIndex+4);	//erase the empty blocks of the vector
		}

}
string Hand::toString(){
	string toReturn="";
	for(unsigned int i=0; i<myHand.size(); i++){
	if(i==myHand.size()-1)
		toReturn=toReturn+myHand[i]->toString();
	else
		toReturn=toReturn+myHand[i]->toString()+" ";
	}
	return toReturn;
}


