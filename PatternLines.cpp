#include "PatternLines.h"

PatternLines::PatternLines()
{
    for(int outterLoop = 0; outterLoop < 5; outterLoop++)
    {
        for(int innerLoop = 0; innerLoop <= outterLoop; innerLoop++)
        {
            if(outterLoop == 0){
                this->patternLineOne[innerLoop] = nullptr;
            }
            else if(outterLoop == 1){
                this->patternLineTwo[innerLoop] = nullptr;
            }
            else if(outterLoop == 2){
                this->patternLineThree[innerLoop] = nullptr;
            }
            else if(outterLoop == 3){
                this->patternLineFour[innerLoop] = nullptr;
            }
            else if(outterLoop == 4){
                this->patternLineFive[innerLoop] = nullptr;
            }
        }
    }
}

PatternLines::~PatternLines()
{
    // Deconstructor
}

void PatternLines::emptyPatternLine(int patternLineNumber)
{
    for(int i = 0; i < getSize(getPatternLine(patternLineNumber)); i++)
    {
        getPatternLine(patternLineNumber)[i] = nullptr;
    }
}

bool PatternLines::isPatternLineEmpty(Tile* patternLineArray[])
{
    int counter = 0;
    int* counterPtr = nullptr;
    counterPtr = &counter;

    int arraySize = getSize(patternLineArray);
    
    for(int i = 0; i < arraySize; i++)
    {
        if(patternLineArray[i] == nullptr)
        {
            *counterPtr = *counterPtr + 1;
        }
    }

    if(counter == arraySize)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool PatternLines::isPatternLineFull(Tile* patternLineArray[])
{
    int counter = 0;
    int* counterPtr = nullptr;
    counterPtr = &counter;

    int arraySize = getSize(patternLineArray);
    
    for(int i = 0; i < arraySize; i++)
    {
        if(patternLineArray[i] != nullptr)
        {
            *counterPtr = *counterPtr + 1;
        }
    }
    
    if(counter == arraySize)
    {
        return true;
    }
    else
    {
        return false;
    }
}

char PatternLines::patternLineTileColour(Tile* patternLineArray[])
{
    char character = ' ';
    
    for(int i = 0; i < 1; i++)
    {
        if(patternLineArray[i] != nullptr)
        {
            character = patternLineArray[i]->getTile();
        }
    }

    return character;
}

int PatternLines::getSize(Tile* patternLineArray[])
{
    if(patternLineArray == patternLineOne)
    {
        return 1;
    }
    else if(patternLineArray == patternLineTwo)
    {
        return 2;
    }
    else if(patternLineArray == patternLineThree)
    {
        return 3;
    }
    else if(patternLineArray == patternLineFour)
    {
        return 4;
    }
    else
    {
        return 5;
    }
}

Tile **PatternLines::getPatternLine(int patternLineNumber)
{
    if(patternLineNumber == 1)
    {
        return this->patternLineOne;
    }
    else if(patternLineNumber == 2)
    {
        return this->patternLineTwo;
    }
    else if(patternLineNumber == 3)
    {
        return this->patternLineThree;
    }
    else if(patternLineNumber == 4)
    {
        return this->patternLineFour;
    }
    else
    {
        return this->patternLineFive;
    }
}

void PatternLines::displayPatternLines()
{
    for(int outterLoop = 0; outterLoop < 5; outterLoop++)
    {
        // Displaying pattern line number
        cout << (outterLoop + 1);
        cout << ": ";
        
        // Placing extra dots 
        for(int extraSpaces = (4 - outterLoop); extraSpaces > 0; extraSpaces--){
            cout << "  ";
        }
        
        // display pattern line
        for(int innerLoop = 0; innerLoop <= outterLoop; innerLoop++)
        {
            if(outterLoop == 0){
                if(patternLineOne[outterLoop - innerLoop] != nullptr){
                    cout << patternLineOne[outterLoop - innerLoop]->getTile() << " ";
                }
            }
            else if(outterLoop == 1){
                if(patternLineTwo[outterLoop - innerLoop] != nullptr){
                    cout << patternLineTwo[outterLoop - innerLoop]->getTile() << " ";
                }
            }
            else if(outterLoop == 2){
                if(patternLineThree[outterLoop - innerLoop] != nullptr){
                    cout << patternLineThree[outterLoop - innerLoop]->getTile() << " ";
                }
            }
            else if(outterLoop == 3){
                if(patternLineFour[outterLoop - innerLoop] != nullptr){
                    cout << patternLineFour[outterLoop - innerLoop]->getTile() << " ";
                }
            }
            else if(outterLoop == 4){
                if(patternLineFive[outterLoop - innerLoop] != nullptr){
                    cout << patternLineFive[outterLoop - innerLoop]->getTile() << " ";
                }
            }
        }
        cout << endl;
    }
}

std::string PatternLines::patternLineOneToString(){
    std::string str;
    if(!isPatternLineEmpty(patternLineOne)){
    str = patternLineOne[0]->getTile();
    } else{
        str = ".";
    }
    return str;
}

std::string PatternLines::patternLineTwoToString(){
    std::string str;
    if(!isPatternLineEmpty(patternLineTwo)){
        for(int i = 0; i < PATTERN_LINE_TWO_SIZE; i++){
            if(patternLineTwo[i] != nullptr){
                str = str + patternLineTwo[i]->getTile();
            } else{
                str = str + ".";
            }
        }
    } else{
        str = "..";
    }
    return str;
}

std::string PatternLines::patternLineThreeToString(){
    std::string str;
    if(!isPatternLineEmpty(patternLineThree)){
        for(int i = 0; i < PATTERN_LINE_THREE_SIZE; i++){
            if(patternLineThree[i] != nullptr){
                str = str + patternLineThree[i]->getTile();
            } else{
                str = str + ".";
            }
        }
    } else{
        str = "...";
    }
    return str;
}

std::string PatternLines::patternLineFourToString(){
    std::string str;
    if(!isPatternLineEmpty(patternLineFour)){
        for(int i = 0; i < PATTERN_LINE_FOUR_SIZE; i++){
            if(patternLineFour[i] != nullptr){
                str = str + patternLineFour[i]->getTile();
            } else{
                str = str + ".";
            }
        }
    } else {
        str = "....";
    }
    return str;
}

std::string PatternLines::patternLineFiveToString(){
    std::string str;
    if(!isPatternLineEmpty(patternLineFive)){
        for(int i = 0; i < PATTERN_LINE_FIVE_SIZE; i++){
            if(patternLineFive[i] != nullptr){
                str = str + patternLineFive[i]->getTile();
            } else {
                str = str + ".";
            }
        }
    } else{
        str = ".....";
    }
    return str;
}
