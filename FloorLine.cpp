#include "FloorLine.h"

FloorLine::FloorLine()
{
    for(int i = 0; i < FLOOR_LINE_LENGTH;  i++)
    {
        this->deductions[i] = nullptr;
    }
}

FloorLine::~FloorLine()
{
    //  Deconstructor
}

bool FloorLine::hasFirstPlayerToken()
{   
    for(int i = 0; i < FLOOR_LINE_LENGTH; i++)
    {
        if (deductions[i] != nullptr)
        {
            if (deductions[i]->getTile() == 'F')
            {
                return true;
            }
        }
    } 

    return false;
}

int FloorLine::totalDeductionPoints()
{
    int tilesOnFloorLine = 0;
    int deductionPoints = 0;

    for(int i = 0; i < FLOOR_LINE_LENGTH; i++)
    {
        if(deductions[i] != nullptr)
        {
            tilesOnFloorLine++;
        }
    }

    deductionPoints = pointDeductionAlgorithm(tilesOnFloorLine);

    return deductionPoints;
}

int FloorLine::pointDeductionAlgorithm(int tilesOnFloorLine)
{
    int deduction = 0;

    if(tilesOnFloorLine >= 0 && tilesOnFloorLine <= 2)
    {
        deduction = tilesOnFloorLine;
    }
    else if(tilesOnFloorLine >= 3 && tilesOnFloorLine <= 5)
    {
        deduction = 4 + ((tilesOnFloorLine - 3) * 2);
    }
    else
    {
        deduction = 10 + ((tilesOnFloorLine - 6) * 3);
    }

    return deduction;
}

bool FloorLine::isFloorLineFull()
{
    int counter = 0;
    
    for(int i = 0; i < FLOOR_LINE_LENGTH; i++)
    {
        if(deductions[i] != nullptr)
        {
            counter = counter + 1;
        }
    }
    
    if(counter == FLOOR_LINE_LENGTH)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void FloorLine::displayFloorLine()
{
    for(int i = 0; i < FLOOR_LINE_LENGTH; i++)
    {
        if (deductions[i] != nullptr)
        {
            cout << printTile(deductions[i]->getTile());
            cout << " ";
        }
        else
        {
            cout << "\u25A2 ";
        }
    } 
}

std::string FloorLine::floorLineToString(){
    std::string str;
    for(int i =0; i < FLOOR_LINE_LENGTH; i++){
        if(deductions[i] != nullptr){
            str = str + deductions[i]->getTile();
        }
    }
    return str;
}
