#include "FloorLine.h"

#define WALL_ROWS               5
#define WALL_COLUMNS            5

class Wall
{
    public:

        // Constructor/Deconstructor
        Wall();
        ~Wall();

        /** 
         * 2D Wall of tile objects
         * A fixed size wall: 5 x 5
         */
        Tile* tile[WALL_ROWS][WALL_COLUMNS];
        
        /**
         * Adds the corresponding amount of points at the end of each round
         */
        int pointsToAdd(int xCo, int yCo);
        
        /**
         * Helper method for recursively adding points correctly
         */
        int moveLeft(int xCo, int yCo);
        int moveRight(int xCo, int yCo);
        int moveUp(int xCo, int yCo);
        int moveDown(int xCo, int yCo);

        /**
         * Checks to see if a row is full to end the game
         */
        bool rowFilled();

        /**
         * Calculates total bonus points for full vertical lines on wall
         */
        int verticalBonusPoints();

        /**
         * Calculates total bonus points for full horizontal lines on wall
         */
        int horizontalBonusPoints();

        /**
         * Checks if a colour can be round in all rows
         */
        int colourInAllRows(char tileColour);

        /**
         * Calculates total bonus points for five of the same colour on wall
         */
        int sameColourbonusPoints();

        /**
         * Loops through a wall and checks what the correct colour for that position is given the pattern line number
         */
        int getWallPositionForTileColour(int patternLineNumber, char tileColour);

        /**
         * Loops through a wall and checks what the correct colour for that position is given the pattern line number and wall number
         */
        char getTileColourForWallPosition(int patternLineNumber, int wallPositionNumber);

        /**
         * Display Walls
         */
        void displayWall();
        /**
         * turns wall into string format
         */
        string wallToString();

    private:

        int* pointsPointer = nullptr;
        int tilePlacementPoints = 0;
        
        int xMin = 0, xMax = 5, yMin = 0, yMax = 5;
};
