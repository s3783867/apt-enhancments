#include "CentreFactory.h"

#define     PATTERN_LINE_ONE_SIZE             1
#define     PATTERN_LINE_TWO_SIZE             2
#define     PATTERN_LINE_THREE_SIZE           3
#define     PATTERN_LINE_FOUR_SIZE            4
#define     PATTERN_LINE_FIVE_SIZE            5

class PatternLines
{
    public:

        // Constructor/Deconstructor
        PatternLines();
        ~PatternLines();

        /**
         * 
         */
        void emptyPatternLine(int patternLineNumber);

        /**
         * Checks to see if pattern line is empty
         */
        bool isPatternLineEmpty(Tile* patternLineArray[]);

        /**
         * Checks to see if pattern line is full
         */
        bool isPatternLineFull(Tile* patternLineArray[]);

        /**
         * Checks to see current tile colour in the pattern line
         */
        char patternLineTileColour(Tile* patternLineArray[]);
        
        /**
         * Returns size of pattern line
         */
        int getSize(Tile* patternLineArray[]);

        /**
         * Returns a pattern line
         */ 
        Tile **getPatternLine(int patternLineNumber);

        /**
         * Display Pattern Lines
         */
        void displayPatternLines();
        
        /**
         * Convert Pattern Line to string
         */
        string patternLineOneToString();
        string patternLineTwoToString();
        string patternLineThreeToString();
        string patternLineFourToString();
        string patternLineFiveToString();

    private:
        
        // 5 1D Array's of Tiles 
        Tile* patternLineOne[PATTERN_LINE_ONE_SIZE];
        Tile* patternLineTwo[PATTERN_LINE_TWO_SIZE];
        Tile* patternLineThree[PATTERN_LINE_THREE_SIZE];
        Tile* patternLineFour[PATTERN_LINE_FOUR_SIZE];
        Tile* patternLineFive[PATTERN_LINE_FIVE_SIZE];

};
