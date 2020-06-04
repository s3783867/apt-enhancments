#include "PatternLines.h"

#define FLOOR_LINE_LENGTH           7

class FloorLine
{
    public:

        /**
         * Constructor
         */
        FloorLine();
        
        /**
         * Deconstructor
         */ 
        ~FloorLine();

         /** 
         * 1D Wall of tile objects
         */
        Tile* deductions[FLOOR_LINE_LENGTH];

        /**
         * Checks if a floor line contains the first player tile
         */
        bool hasFirstPlayerToken();

        /**
         * Calculates total amount of deduction points for the round
         */
        int totalDeductionPoints();

        /**
         * Helper method: Algoithm that dicates amounts of 
         * points to deduct based on the amount of tiles in floor line
         */
        int pointDeductionAlgorithm(int tilesOnFloorLine);

        /**
         * Checks to see if floor line is full
         */
        bool isFloorLineFull();

        /**
         * Display Floor Line
         */
        void displayFloorLine();
        /**
         * Turns floor line into string format
         */
        std::string floorLineToString();

    private:
    
        BoxLid* boxLid = new BoxLid();

};
