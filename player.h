#include "Wall.h"

#define MAX_PLAYERS                2

class Player
{
    public:
        
        // COnstructor/Deconstructor
        Player();
        Player(string name, int points);
        ~Player();

        PatternLines* getPatternLines();
        FloorLine* getFloorLine();
        Wall* getWall();        
        
        // Array of players
        Player* players[MAX_PLAYERS];

        /**
         * Create two players for the game
         */
        void createPlayers(); 

        /**
         * Helper method to simplify player name input
         */
        string inputPlayerName();

        /**
         * Helper method to simplify player name validation
         */
        string validateName(string playerName);

        /**
         * Indicates who is currently winning
         */
        string isWinning(Player* playerOne, Player* playerTwo);

        /**
         * Return the player name
         */
        string getName();

        /**
         * Return the player points
         */
        int getPoints();

        /**
         * Set the player points
         */
        void setPoints(int points);

        /**
         * Add points to players current score
         */
        void addPoints(int newPoints);

        /**
         * Subtract points to players current score
         */
        void subtractPoints(int newPoints);

    private:
        
        string name;
        int points;

        PatternLines* patternLines;
        FloorLine* floorLine;
        Wall* wall;
};
