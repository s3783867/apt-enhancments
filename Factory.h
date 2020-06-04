#include "BoxLid.h"

#define NUMBER_OF_FACTORIES     5
#define FACTORY_SIZE            4

class Factory
{
    public:

        // Constructor/Deconstructor
        Factory();
        ~Factory();

        // 2D Array of Factories of Tiles
        Tile* factories[NUMBER_OF_FACTORIES][FACTORY_SIZE];


        /**
         * Searches a factory for a sepcific tile colour
         */
        bool factoryContainsTile(int factoryNumber, char tileColour);
        
        /**
         * Checks if a singular factory is empty
         */
        bool isFactoryEmpty(int factoryNumber);

        /**
         * Checks if all factories are empty
         */
        bool areFactoriesEmpty();

        /**
         * Empty a factory after it has been selected
         */
        void emptyAFactory(int factoryNumber);

        /**
         * Refills a factory with new tiles
         */ 
        void refillFactories();

        string factoryToString(int factoryNumber);
        
        

        /**
         * Display Factories
         */ 
        void displayFactories();

        TileBag* getTileBag();

    private:
    
        TileBag* tileBag;

};