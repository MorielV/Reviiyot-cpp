#include "Player.h"

//Player functions-------------------------------------------------------------------------------
//player copy Constructor
Player::Player(const Player& otherPlayer):Hand(otherPlayer),name(otherPlayer.name),type(otherPlayer.type),position(otherPlayer.position){}//Player copy constructor
//player constructor
Player::Player(const string &playerName,int type,int playerPosition,Deck &deck):Hand(deck),name(playerName),type(type),position(playerPosition){}
string Player::getName(){	//returns the name of the player
	return name;
}
string Player::toString(){	//returns the name of the player + his hand
	return getName()+": "+Hand::toString();
}
void Player::makeMove( vector<Player*>& players,Deck &deck,int opponentIndex){

	Card &card=this->cardToSearch();
	bool isFigure=card.isFigure;						//indicates if the needed card is FigureCard or NumericCard
	string cardToSearch=card.toString();
	cardToSearch=cardToSearch.substr(0,cardToSearch.length()-1);	//get rid of the last Char-dont care about shape
	int askFrom=opponentIndex;								//the index of the player we need to ask- in the vector
	int boolCounter=0;
	//create all possible kinds of this card
	Card *club;
	Card *diamond;
	Card *heart;
	Card *spade;
	if(isFigure){
		club=new FigureCard(cardToSearch+"C");
		diamond=new FigureCard(cardToSearch+"D");
		heart=new FigureCard(cardToSearch+"H");
		spade=new FigureCard(cardToSearch+"S");
	}
	else{
		club=new NumericCard(cardToSearch+"C");
		diamond=new NumericCard(cardToSearch+"D");
		heart=new NumericCard(cardToSearch+"H");
		spade=new NumericCard(cardToSearch+"S");
		}

		bool gotClub=players[askFrom]->removeCard(*club);		//ask the player for the CLUB card
		bool gotDiamond=players[askFrom]->removeCard(*diamond);	//ask the player for the DIAMOND card
		bool gotHeart=players[askFrom]->removeCard(*heart);		//ask the player for the HEART card
		bool gotSpade=players[askFrom]->removeCard(*spade);		//ask the player for the SPADE card

		if(gotClub){
			this->addCard(*club);
			boolCounter++;

		}
		if(gotDiamond){
			this->addCard(*diamond);
			boolCounter++;
		}
		if(gotHeart){
			this->addCard(*heart);
			boolCounter++;
		}
		if(gotSpade){
			this->addCard(*spade);
			boolCounter++;
		}
		delete club;					//delete the cards we used for this turn.
		delete diamond;					//
		delete heart;					//
		delete spade;					//

		if(deck.getNumberOfCards()!=0){	//IF THERE ARE STILL CARDS IN THE DECK!
			if(boolCounter==0){				//if the OPPONENT had no cards for me AND the deck still has cards
				Card *toAdd=deck.fetchCard();
				this->addCard(*toAdd);
				delete toAdd;
				this->fourOfAKind();		//if we have fours, delete them

			}
			else {							// if the OPPONENT lost K cards, he needs to draw K more from the deck
				if(players[askFrom]->getNumberOfCards()!=0){	//if the OPPONENT'S hand is NOT EMPTY-He can draw
					for(int i=0; i<boolCounter && deck.getNumberOfCards()!=0;i++){	//draw K cards (or less of the deck is almost empty
						Card *toAdd=deck.fetchCard();
						players[askFrom]->addCard(*toAdd);
						delete toAdd;
						players[askFrom]->fourOfAKind();	////if the opponent has fours, delete them
						this->fourOfAKind();			//if we have fours, delete them

					 }
				 }

			}
	}
		else{							//no one Drew any cards, just check if they have fourOfAKind
			this->fourOfAKind();		//if we have fours, delete them
			players[askFrom]->fourOfAKind();	////if the opponent has fours, delete them
		}


}





// PlayerType 1-----------------------------------------------------------------------------------
//constructor -calls Class Player 's constructor first.
PlayerType1::PlayerType1(string &playerName, int playerPosition,Deck &deck):Player(playerName,1 ,playerPosition, deck){}
PlayerType1::PlayerType1(Player &otherPlayer):Player(otherPlayer){};
Card &PlayerType1::cardToSearch(){//returns the card we have the most of

	vector<Card*> myHand=Hand::getHandVector(); //get access to the Hand vector


	int bestIndex=0;
	int temp=1;
	int currentBestShows=0;

	for(unsigned int i=0; i<myHand.size(); i++, temp++){
		if(i==myHand.size()-1	||	(myHand[i]->compareByValue(*myHand[i+1]))!=0){	//if the current value DIFFERS from the next card in hand (comapre By Value)

			if(currentBestShows<=temp){			//if TEMP got bigger than last Biggest num of shows
				bestIndex=i;				// i points to the "best place" at the moment
				currentBestShows=temp;

			}
				temp=0;
		}

	}
	//return a pointer to the needed Card.
	return *myHand[bestIndex];






}
int PlayerType1::choosePlayer(const vector<Player*> &players){//returns player position of the player we ASK for a card
	int bestPosition=players.size()-1;								//the index of the player with the most cards (AT THE MOMENT)
	int biggestNumOfCards=0;
	for(int i=players.size()-1; i>=0; i--){
		if(players[i]->getNumberOfCards()	>	biggestNumOfCards && this->position!=i){	//if we look at a player with more cards than we last saw
			biggestNumOfCards=players[i]->getNumberOfCards();		//new Highest num of cards
			bestPosition=i;											//the index of that player
		}
	}
	return bestPosition;




}






// PlayerType 2-----------------------------------------------------------------------------------
//constructor -calls Class Player 's constructor first.
PlayerType2::PlayerType2(string &playerName, int playerPosition,Deck &deck):Player(playerName, 2,playerPosition,deck){}
PlayerType2::PlayerType2(Player &otherPlayer):Player(otherPlayer){};
Card &PlayerType2::cardToSearch(){//returns the card we have the least


	vector<Card*> myHand=Hand::getHandVector(); //get access to the Hand vector


	int bestIndex=0;
	int temp=1;
	int currentBestShows=myHand.size();

	for(int i=myHand.size()-1; i>=0; i--, temp++){
		if(i==0	||	(myHand[i]->compareByValue(*myHand[i-1]))!=0){	//if the current value DIFFERS from the next card in hand (comapre By Value)

			if(temp<=currentBestShows){						//if TEMP got smaller than last Smallest num of shows
				bestIndex=i;								// i points to the "best place" at the moment
				currentBestShows=temp;

			}
				temp=0;
		}

	}
	//return a pointer to the needed Card.
	return *myHand[bestIndex];






}
int PlayerType2::choosePlayer(const vector<Player*> &players){//returns player position of the player we ASK for a card


	int bestPosition=players.size()-1;								//the index of the player with the most cards (AT THE MOMENT)
	int biggestNumOfCards=0;
	for(int i=players.size()-1; i>=0; i--){
		if(players[i]->getNumberOfCards()	>	biggestNumOfCards && this->position!=i){	//if we look at a player with more cards than we last saw
			biggestNumOfCards=players[i]->getNumberOfCards();		//new Highest num of cards
			bestPosition=i;											//the index of that player
		}
	}
	return bestPosition;




}






//PlayerType 3------------------------------------------------------------------------------------
//constructor -calls Class Player 's constructor first.
PlayerType3::PlayerType3(string &playerName, int playerPosition,Deck &deck):Player(playerName,3,playerPosition,deck), lastAsked3(-1){}
PlayerType3::PlayerType3(Player &otherPlayer):Player(otherPlayer),lastAsked3(){};

Card &PlayerType3::cardToSearch(){				//returns the card with the highest value
	vector<Card*> myHand=Hand::getHandVector(); //get access to the Hand vector
	return *myHand[myHand.size()-1];
}
int PlayerType3::choosePlayer(const vector<Player*> &players){//returns the position of the player we want to ask from.

	int numOfPlayers=players.size();	//number of players in game
	lastAsked3++;
	if(lastAsked3 == numOfPlayers)
		lastAsked3=0;
	 if(lastAsked3 == position){
			if(lastAsked3+1==numOfPlayers)
				lastAsked3=0;
			else
				lastAsked3++;

	}

	return lastAsked3;
}




//PlayerType4--------------------------------------------------------------------------------------
//constructor -calls Class Player 's constructor first.
PlayerType4::PlayerType4(string &playerName, int playerPosition,Deck &deck):Player(playerName,4,playerPosition,deck), lastAsked4(-1){}
PlayerType4::PlayerType4(Player &otherPlayer):Player(otherPlayer),lastAsked4(){};

int PlayerType4::choosePlayer(const vector<Player*> &players){//returns the position of the player we want to ask from.

	int numOfPlayers=players.size();	//number of players in game
	lastAsked4++;
	if(lastAsked4 == numOfPlayers)
		lastAsked4=0;
	 if(lastAsked4 == position){
			if(lastAsked4+1==numOfPlayers)
				lastAsked4=0;
			else
				lastAsked4++;
	 }
		return lastAsked4;


}
Card &PlayerType4::cardToSearch(){				//returns the card with the lowest value
	vector<Card*> myHand=Hand::getHandVector(); //get access to the Hand vector
	return *myHand[0];
}


