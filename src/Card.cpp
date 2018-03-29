#include "Card.h"

//Card functions implementations
//-----------------------------
//Set the shape for a card
Card::Card(): shape(), isFigure(){

}
void Card::setShape(char shapeAsChar){
	//shapeAsChar-the last Char of the card is the Shape!

	if(shapeAsChar=='D')
		shape=Diamond;
	else if(shapeAsChar=='H')
		shape=Heart;
	else if(shapeAsChar=='S')
		shape=Spade;
	else if(shapeAsChar=='C')
		shape=Club;
}
Shape Card::getShape(){		//returns shape
	return shape;
}
int Card::compareTo(Card &cardB){//compare Two cards (returns int)

	int ans;

	if(!this->isFigure&&cardB.isFigure)//case of NumericCard<FigureCard ALWAYS
		ans= -1;
	else if(this->isFigure&&!cardB.isFigure)//case of FigureCard>NumericCard
		ans= 1;
	else{															//if Both are the same Type	 -	ans <- the difference between them
		ans= this->getValue()-cardB.getValue();
		if(ans==0)
				return this->getShape()-cardB.getShape();

		}
		return ans;
}
int Card::compareByValue(Card &cardB){
	int ans;

		if(!this->isFigure&&cardB.isFigure)//case of NumericCard<FigureCard ALWAYS
			ans= -1;
		else if(this->isFigure&&!cardB.isFigure)//case of FigureCard>NumericCard
			ans= 1;
		else															//if Both are the same Type	 -	ans <- the difference between them
			ans= this->getValue()-cardB.getValue();

			return ans;
}
//FigureCard function implementations
//--------------------------------------
//FigureCard Constructor
FigureCard::FigureCard(const string & cardAsString) :figure(), stringRep(cardAsString){

	isFigure=true;
	//the first char of the string is the value (in figure cards)
	char figureChar=cardAsString[0];
	if(figureChar=='J')
		figure=Jack;
	else if(figureChar=='Q')
		figure=Queen;
	else if(figureChar=='K')
		figure=King;
	else if(figureChar=='A')
		figure=Ace;
	setShape(cardAsString[cardAsString.length()-1]);

}

string FigureCard::toString(){
	return stringRep;
}
//get value part of the Card
int FigureCard::getValue(){
	return figure;
}
Figure FigureCard:: getFigure(){

	return figure;

}
//NumericCard function implementations
//--------------------------------------
//Numeric card Constructor
NumericCard::NumericCard(const string & cardAsString) : number() ,stringRep(cardAsString){
	isFigure=false;
	//the String representation of the card is the parameter

	string value=cardAsString.substr(0,cardAsString.length()-1);
	int numericValue=std::stoi(value);

	number=numericValue;				//set value for this card
	setShape(cardAsString[cardAsString.length()-1]);//
}
string NumericCard::toString(){
	return stringRep;
}
//get value part of the Card
int NumericCard::getValue(){
	return number;
}
// Static function, used to determine (By string) if a Card is a Numeric Card or a value Card                  -----------------------------------------
