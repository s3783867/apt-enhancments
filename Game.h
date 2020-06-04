#include "player.h"

class Game
{
    public:
        
        // Constructor/Deconstructor
        Game();
        ~Game();

        /**
         * Generates all constructors for new game
         */
        void newGame();
        
        /**
         * Plays one turn of Azul, for this player
         * 
         * On one line of input player indicates:
         *  1. An available factory or Centre Factory to select
         *  2. Colour they wish to pick
         *  3. Pattern line to place colour
         * 
         * Then, check if turn is valid
         */
        void playerTurn(Player* player);
        
        /**
         * Checks to see if a players turn is successful
         * 
         * If a turn is valid print "Turn successful"
         * Otherwise print "Turn unsuccessful" and ask player to redo their turn
         */
        bool isTurnValid(Player* player);


        bool getTurn();

        /**
         * Simulates a round of a game
         */
        void aRound();

        /**
         * Displays a built mosiac
         */
        void displayMosaic(Player* player);

        /**
         * Checks and moves a tile to the wall if possible
         */
        void moveTileToWall(Player* player, int lineNumber);

        /**
         * Helper method to attempt moving tile across to wall for each pattern line 
         */
        void movePatternLinesToWall(Player* player);

        /**
         * Loads a previous Game
         */
        void loadGame(string filename);

        
        /**
         * Saves Current Game
         */
        void saveGame(string filename);

        /**
         * Deletes Current Game
         */
        void deleteGame();

        /**
         * Checks if tile is valid
         */
        bool isTileValid(Tile* tile);
    
    private:

        Player* players;
        BoxLid* boxLid;
        Factory* factory;
        CentreFactory* centreFactory;

        string action, fileName;
        int factoryNumber, patternLineNumber;
        char tileColour, breakAction;

        int playerIterator = 0;

};