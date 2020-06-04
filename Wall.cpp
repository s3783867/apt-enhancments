#include "Wall.h"

 Wall::Wall()
 {
    for(int outterLoop = 0; outterLoop < WALL_ROWS;  outterLoop++)
    {
        for(int innerLoop = 0; innerLoop < WALL_COLUMNS; innerLoop ++)
        {
            this->tile[outterLoop][innerLoop] = nullptr;
        }
    }
 }
        
Wall::~Wall()
{
    //  Deconstructor
}

int Wall::pointsToAdd(int xCo, int yCo)
{
    return moveLeft(xCo, yCo) + moveRight(xCo, yCo) + moveUp(xCo, yCo) + moveDown(xCo, yCo);
}

int Wall::moveLeft(int xCo, int yCo)
{
    pointsPointer = &tilePlacementPoints;

    *pointsPointer = *pointsPointer + 1;
    
    if(tile[yCo][xCo - 1] != nullptr && (xCo - 1) >= xMin)
    {
        moveLeft(xCo - 1, yCo); 
    }

    int addPoints = *pointsPointer;
    *pointsPointer = 0;

    return addPoints;
}

int Wall::moveRight(int xCo, int yCo)
{
    pointsPointer = &tilePlacementPoints;

    *pointsPointer = *pointsPointer + 1;

    if(tile[yCo][xCo + 1] != nullptr && (xCo + 1) <= xMax)
    {
        moveRight(xCo + 1, yCo); 
    }

    int addPoints = *pointsPointer;
    *pointsPointer = 0;

    return addPoints;
}

int Wall::moveUp(int xCo, int yCo)
{
    pointsPointer = &tilePlacementPoints;

    *pointsPointer = *pointsPointer + 1;

    if(tile[yCo - 1][xCo] != nullptr && (yCo - 1) >= yMin)
    {
        moveUp(xCo, yCo - 1); 
    }

    int addPoints = *pointsPointer;
    *pointsPointer = 0;

    return addPoints;
}

int Wall::moveDown(int xCo, int yCo)
{
    pointsPointer = &tilePlacementPoints;

    *pointsPointer = *pointsPointer + 1;

    if(tile[yCo + 1][xCo] != nullptr && (yCo + 1) <= yMax)
    {
        moveDown(xCo, yCo + 1); 
    }

    int addPoints = *pointsPointer;
    *pointsPointer = 0;

    return addPoints;
}

bool Wall::rowFilled()
{
    bool rowFilled = false;
    int counter = 0;
    
    // looping through wall
    for(int outterLoop = 0; outterLoop < WALL_ROWS;  outterLoop++)
    {
        // Searching each row to see if it is full
        for(int innerLoop = 0; innerLoop < WALL_COLUMNS; innerLoop ++)
        {
            if(tile[outterLoop][innerLoop] != nullptr)
            {
                counter++;
            }
        }

        // Increment if a full row is found
        if(counter == 5)
        {
            rowFilled = true;
        }
        
        // reset counter for next row
        counter = 0;
    }

    return rowFilled;
}

int Wall::verticalBonusPoints()
{
    int counter = 0;
    int fullColumns = 0;
    int pointPerFullColumn = 7;
    
    for(int outterLoop = 0; outterLoop < WALL_ROWS; outterLoop++)
    {
        for(int innerLoop = 0; innerLoop < WALL_COLUMNS; innerLoop++)
        {
            if(tile[innerLoop][outterLoop] != nullptr)
            {
                counter++;
            }
        }

        if(counter == WALL_ROWS)
        {
            fullColumns++;
        }

        counter = 0;
    }

    return (fullColumns * pointPerFullColumn);
}

int Wall::horizontalBonusPoints()
{
    int counter = 0;
    int fullRows = 0;
    int pointPerFullRow = 7;
    
    for(int outterLoop = 0; outterLoop < WALL_ROWS; outterLoop++)
    {
        for(int innerLoop = 0; innerLoop < WALL_COLUMNS; innerLoop++)
        {
            if(tile[outterLoop][innerLoop] != nullptr)
            {
                counter++;
            }
        }

        if(counter == WALL_COLUMNS)
        {
            fullRows++;
        }

        counter = 0;
    }

    return (fullRows * pointPerFullRow);
}

int Wall::colourInAllRows(char tileColour)
{
    bool bonusPoints = 0;
    int counter = 0;
    
    for(int outterLoop = 0; outterLoop < WALL_ROWS; outterLoop++)
    {
        for(int innerLoop = 0; innerLoop < WALL_COLUMNS; innerLoop++)
        {
            if(tile[outterLoop][innerLoop] != nullptr)
            {
                if(tile[outterLoop][innerLoop]->getTile() == tileColour)
                {
                    counter++;
                }
            }
        }
    }

    if(counter == 5)
    {
        bonusPoints = 5;
    }

    return bonusPoints;
}

int Wall::sameColourbonusPoints()
{
    
    return colourInAllRows('R') + colourInAllRows('Y') + colourInAllRows('B') + colourInAllRows('L') + colourInAllRows('U');
}

int Wall::getWallPositionForTileColour(int patternLineNumber, char tileColour)
{
        if(tileColour == 'Y')
        {
            return patternLineNumber;
        }
        else if(tileColour == 'R')
        {
            return (patternLineNumber + 1) % 5;
        }
        else if(tileColour == 'U')
        {
            return (patternLineNumber + 2) % 5;
        }
        else if(tileColour == 'L')
        {
            return (patternLineNumber + 3) % 5;
        }
        else
        {
            return (patternLineNumber + 4) % 5;
        }
}

char Wall::getTileColourForWallPosition(int patternLineNumber, int wallPositionNumber)
{
    char colour = '.';
    
    if(patternLineNumber == 1)
    {
        if(wallPositionNumber == 0)
        {
            colour = 'b';
        }
        else if(wallPositionNumber == 1)
        {
            colour = 'y';
        }
        else if(wallPositionNumber == 2)
        {
            colour = 'r';
        }
        else if(wallPositionNumber == 3)
        {
            colour = 'u';
        }
        else
        {
            colour = 'l';
        }
    }

    else if(patternLineNumber == 2)
    {
        if(wallPositionNumber == 0)
        {
            colour = 'l';
        }
        else if(wallPositionNumber == 1)
        {
            colour = 'b';
        }
        else if(wallPositionNumber == 2)
        {
            colour = 'y';
        }
        else if(wallPositionNumber == 3)
        {
            colour = 'r';
        }
        else
        {
            colour = 'u';
        }
    }

    else if(patternLineNumber == 3)
    {
        if(wallPositionNumber == 0)
        {
            colour = 'u';
        }
        else if(wallPositionNumber == 1)
        {
            colour = 'l';
        }
        else if(wallPositionNumber == 2)
        {
            colour = 'b';
        }
        else if(wallPositionNumber == 3)
        {
            colour = 'y';
        }
        else
        {
            colour = 'r';
        }
    }

    else if(patternLineNumber == 4)
    {
        if(wallPositionNumber == 0)
        {
            colour = 'r';
        }
        else if(wallPositionNumber == 1)
        {
            colour = 'u';
        }
        else if(wallPositionNumber == 2)
        {
            colour = 'l';
        }
        else if(wallPositionNumber == 3)
        {
            colour = 'b';
        }
        else
        {
            colour = 'y';
        }
    }

    else
    {
        if(wallPositionNumber == 0)
        {
            colour = 'y';
        }
        else if(wallPositionNumber == 1)
        {
            colour = 'r';
        }
        else if(wallPositionNumber == 2)
        {
            colour = 'u';
        }
        else if(wallPositionNumber == 3)
        {
            colour = 'l';
        }
        else
        {
            colour = 'b';
        }
    }

    return colour;
}

void Wall::displayWall()
{
    for(int outterLoop = 0; outterLoop < WALL_ROWS;  outterLoop++)
    {
        for(int innerLoop = 0; innerLoop < WALL_COLUMNS; innerLoop ++)
        {
            if(tile[outterLoop][innerLoop] != nullptr)
            {
                cout << " " <<tile[outterLoop][innerLoop]->getTile();
            }
            else
            {
                cout << " .";
            }
        }
        cout << endl;
    }
}

string Wall::wallToString(){
    string wall = "byrullbyruulbyrrulbyyrulb";
    int count = 0;
    for(int i = 0; i < WALL_ROWS; i++){
        for(int j = 0; j < WALL_COLUMNS; j++){
            if(tile[i][j] != nullptr){
                wall[count] = tile[i][j]->getTile();
            }
        count++;
        }
    }
    return wall;
}