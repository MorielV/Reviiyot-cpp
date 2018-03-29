#include "Game.h"

Game::Game(char *ConfigurationFile) : players(), deck(), verbal(), n(), numOfTurns(0), nextPlayer(0), winners() {

    //create a <string> vector. each block holds a whole line.
    ifstream file(ConfigurationFile);        //to read from file
    if (!file)   // Test for error.
    {
        std::cerr << "Error opening file:\n";
        exit(1);
    }
    vector<string> lineVector;
    string line;
    while (getline(file, line)) {
        if (line[0] != '#' && line != "") {
            if (line[line.size() - 1] == ' ')
                line = line.substr(0, line.length() - 1);
            lineVector.push_back(line);
        }
    }

    verbal = stoi(lineVector[0]);                //initialize VERBAL parameter
    cout << verbal <<endl;
    n = stoi(lineVector[1]);                    //initialize N parameter
    deck = Deck(lineVector[2], n);            //initialize (and build) the deck

    string currentPlayerTypeAsString;
    int currentPlayerType;

    for (unsigned int i = 3; i < lineVector.size(); i++) {//initialize players
        string currentLine = lineVector[i];
        string currentPlayerName = "";
        int index = 0;
        while (currentLine[index] != ' ') {
            currentPlayerName = currentPlayerName + currentLine[index];
            index++;
        }
        currentPlayerTypeAsString = currentLine[index + 1];
        currentPlayerType = stoi(currentPlayerTypeAsString);

        if (currentPlayerType == 1) {
            players.push_back(new PlayerType1(currentPlayerName, i - 3,
                                              deck));    //i-3 is the position of the player (# on line - 3 first lines)
        } else if (currentPlayerType == 2) {
            players.push_back(new PlayerType2(currentPlayerName, i - 3,
                                              deck));    //i-3 is the position of the player (# on line - 3 first lines)
        } else if (currentPlayerType == 3) {
            players.push_back(new PlayerType3(currentPlayerName, i - 3,
                                              deck));    //i-3 is the position of the player (# on line - 3 first lines)
        } else if (currentPlayerType == 4) {
            players.push_back(new PlayerType4(currentPlayerName, i - 3,
                                              deck));    //i-3 is the position of the player (# on line - 3 first lines)
        }

    }


}

Game::Game(const Game &otherGame)
        : players(), deck(otherGame.deck), verbal(otherGame.verbal), n(otherGame.n), numOfTurns(otherGame.numOfTurns),
          nextPlayer(otherGame.nextPlayer), winners() {

    for (unsigned int i = 0; i < otherGame.players.size(); i++) {
        if (otherGame.players[i]->type == 1) {
            players.push_back(new PlayerType1(*otherGame.players[i]));
        } else if (otherGame.players[i]->type == 2) {
            players.push_back(new PlayerType2(*otherGame.players[i]));
        } else if (otherGame.players[i]->type == 3) {
            players.push_back(new PlayerType3(*otherGame.players[i]));
        } else if (otherGame.players[i]->type == 4) {
            players.push_back(new PlayerType4(*otherGame.players[i]));
        }

    }


}

Game::~Game() {
    clear();
}

Game &Game::operator=(const Game &otherGame) {
    clear();        //clear me

    this->n = otherGame.n;
    this->numOfTurns = otherGame.numOfTurns;
    this->verbal = otherGame.verbal;
    deck = otherGame.deck;    //operator = of deck
    this->players.resize(otherGame.players.size());

    //Copy Players vector
    for (unsigned int i = 0; i < otherGame.players.size(); i++) {
        if (otherGame.players[i]->type == 1) {
            players.push_back(new PlayerType1(*otherGame.players[i]));
        } else if (otherGame.players[i]->type == 2) {
            players.push_back(new PlayerType2(*otherGame.players[i]));
        } else if (otherGame.players[i]->type == 3) {
            players.push_back(new PlayerType3(*otherGame.players[i]));
        } else if (otherGame.players[i]->type == 4) {
            players.push_back(new PlayerType4(*otherGame.players[i]));
        }

    }
    return *this;
}

void Game::clear() {

    this->n = 0;
    this->numOfTurns = 0;
    this->verbal = 0;

    for (unsigned int i = 0; i < this->players.size(); i++) {    //delete players
        delete players[i];
    }


}

void Game::printState() {
    Game gameCopy(*this);

    //print deck state
    cout << "Deck: " + gameCopy.deck.toString() << endl;

    for (unsigned int i = 0; i < gameCopy.players.size(); i++) {
        cout << gameCopy.players[i]->toString() << endl;

    }

}

void Game::printNumberOfTurns() {
    cout << "Number of turns: " << this->numOfTurns << endl;
}

void Game::printTrace(int opponentIndex) {


    string asking = players[nextPlayer]->getName();
    string asked = players[opponentIndex]->getName();

    string askedCard = players[nextPlayer]->cardToSearch().toString();
    string askedValue = askedCard.substr(0, askedCard.length() - 1);            //get only the value part of the card

    cout << "Turn " << numOfTurns << endl;            //Turn numOfTurns
    printState();                            //print state
    cout << asking << " asked ";                //Bob Asked Alice for the value 2 (for example)
    cout << asked;
    cout << " for the value ";
    cout << askedValue << endl;
    cout << endl;
}

void Game::printWinner() {
    cout << "***** The Winner is: ";
    if (winners.size() > 1) {
        if (winners[1] > winners[0])
            cout << "the winners are: " + players[winners[0]]->getName() + " and " + players[winners[1]]->getName();
        else
            cout << "the winners are: " + players[winners[1]]->getName() + " and " + players[winners[0]]->getName();
    } else
        cout << players[winners[0]]->getName();
    cout << " *****" << endl;
}

void Game::init() {
//	NOT TODAYYY
}

void Game::play() {

    while (winners.size() == 0) {
        numOfTurns++;


        int opponentIndex = players[nextPlayer]->choosePlayer(
                players);        //returns the index of the opponent of nextPlayer

        if (verbal == 1)
            printTrace(opponentIndex);
        players[nextPlayer]->makeMove(players, deck, opponentIndex);    //make move of the player
        //check if there are winners
        if (players[nextPlayer]->getNumberOfCards() == 0)    //if nextPlayer's hand is empty
            winners.push_back(nextPlayer);
        if (players[opponentIndex]->getNumberOfCards() == 0)        //if the ASKED player's hand is empty
            winners.push_back(opponentIndex);

        if (nextPlayer == players.size() - 1)
            nextPlayer = 0;
        else
            nextPlayer++;


    }


}
