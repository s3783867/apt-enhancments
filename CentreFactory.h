#include "Factory.h"

#define CENTRE_FACTORY_MAX_SIZE         21

class CentreFactory
{
    public:

        // Constructor/Deconstructor
        CentreFactory();
        ~CentreFactory();

        // 2D Array of Factories of Tiles
        Tile* centreFactory[CENTRE_FACTORY_MAX_SIZE];

        /**
         * Checks if first player token has been taken
         */
        bool hasFirstPlayerTokenBeenTaken();

        /**
         * Searches the centre factory to see if it contains a particular tile
         */
        bool centreFactoryContainsTile(char tileColour);

        /**
         * Checks to see if the centre factory is empty
         */
        bool isCentreFactoryEmpty();

        /**
         * Restores centre factory to original condition
         */
        void refreshCentreFactory();

        /**
         * Display Centre Factory
         */
        void displayCentreFactory();

        /**
         * get centre factory in string form
         */
        string getCentreFactoryString();

    private:


};
