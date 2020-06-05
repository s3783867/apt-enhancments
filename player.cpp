#include "player.h"

#include <iostream>
#include <string>
#include <limits>

Player::Player()
{
    for(int i = 0; i < MAX_PLAYERS;  i++)
    {
        this->players[i] = nullptr;
    }
}

Player::Player(string name, int points)
{
    this->name = name;
    this->points = points;
    
    this->patternLines = new PatternLines();
    this->floorLine = new FloorLine();
    this->wall = new Wall();
}

Player::~Player()
{
    //  Deconstructor
}

string Player::inputPlayerName()
{
    string playerName;
    
    cout << "> ";
    cin >> playerName;

    // CHECK FOR EXIT CALL
    if(playerName.compare("^D") == 0)
    {
        cout << endl << "Goodbye!" << endl;
        exit(1);
    }

    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
    cout << endl;

    return playerName;
}

string Player::validateName(string playerName)
{
    string validatedName = playerName;
    int playerNameLength = playerName.length();

    if(playerNameLength > 5){
        cout << "Invalid Input: Name can not be longer then 5 characters" << endl;
        validatedName = inputPlayerName();
        validatedName = validateName(validatedName);
    }
    
    for(int i = 0; i < playerNameLength; i++)
    {
        if(!isalpha(playerName[i]))
        {
            cout << endl << "Invalid Input: Please only use letters" << endl;
            validatedName = inputPlayerName();
            validatedName = validateName(validatedName);
        }
    }

    return validatedName;
}

void Player::createPlayers()
{
    
    string playerOneName = "";
    string playerTwoName = "";

    cout << "Enter a name for player 1" << endl;
    playerOneName = inputPlayerName();
    playerOneName = validateName(playerOneName);

    cout << "Enter a name for player 2" << endl;
    playerTwoName = inputPlayerName();
    playerTwoName = validateName(playerTwoName);

    Player* playerOne = new Player(playerOneName, 0);
    Player* playerTwo = new Player(playerTwoName, 0);

    this->players[0] = playerOne;
    this->players[1] = playerTwo;

    cout << "Let's play" << endl << endl;
}

string Player::isWinning(Player* playerOne, Player* playerTwo)
{
    string currentLeader = "It's a draw!";
    
    if(playerOne->getPoints() > playerTwo->getPoints())
    {
        currentLeader =  playerOne->getName() + "wins!";
    }
    else if (playerOne->getPoints() < playerTwo->getPoints())
    {
        currentLeader = playerTwo->getName() + "wins!";
    }

    return currentLeader;
}

string Player::getName()
{
    return name;
}

int Player::getPoints()
{
    return points;
}

PatternLines* Player::getPatternLines()
{
    return patternLines;
}

FloorLine* Player::getFloorLine()
{
    return floorLine;
}

Wall* Player::getWall()
{
    return wall;
}

void Player::setPoints(int points)
{
    this->points = points;
}

void Player::addPoints(int newPoints)
{
    this->points += newPoints;
}

void Player::subtractPoints(int newPoints)
{
    if(this->points < newPoints)
    {
        this->points = 0;
    }
    else
    {
        this->points -= newPoints;
    }
}