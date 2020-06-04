#include "CentreFactory.h"

CentreFactory::CentreFactory()
{
    
}

CentreFactory::~CentreFactory()
{
    //  Deconstructor
}

bool CentreFactory::hasFirstPlayerTokenBeenTaken()
{
    if(centreFactory[0] == nullptr)
    {
        return true;
    }
    else if(centreFactory[0]->getTile() == 'F')
    {
        return false;
    }
    else
    {
        return true;
    }
    
}

bool CentreFactory::centreFactoryContainsTile(char tileColour)
{
    bool doesContainTile = false;

    for(int i = 0; i < CENTRE_FACTORY_MAX_SIZE; i++)
    {
        if(centreFactory[i] != nullptr)
        {
            if(centreFactory[i]->getTile() == tileColour)
            {
                doesContainTile = true;
            }
        }
    }

    return doesContainTile;
}

bool CentreFactory::isCentreFactoryEmpty()
{
    int counter = 0;

    for(int outterLoop = 0; outterLoop < CENTRE_FACTORY_MAX_SIZE;  outterLoop++)
    {
        if(centreFactory[outterLoop] == nullptr)
        {
            counter++;
        } 
    }

    if(counter == CENTRE_FACTORY_MAX_SIZE)
    {
        return true;
    }
    else
    {
        return false;
    } 
}

void CentreFactory::refreshCentreFactory()
{
    for(int i = 0; i < CENTRE_FACTORY_MAX_SIZE; i++)
    {
        centreFactory[i] = nullptr;
    }

    centreFactory[0] = new Tile(FirstPlayer);
}

void CentreFactory::displayCentreFactory()
{
    cout << "0: ";
    
    for(int i = 0; i < CENTRE_FACTORY_MAX_SIZE; i++)
    {
        if(centreFactory[i] != nullptr)
        {
            cout << centreFactory[i]->getTile() << " ";
        }
    }
    cout << endl;
}

std::string CentreFactory::getCentreFactoryString(){
    std::string centreFactoryString;
    if(!isCentreFactoryEmpty()){
    for(int i = 0; i < CENTRE_FACTORY_MAX_SIZE; i++){
        if(centreFactory[i] != nullptr){
        centreFactoryString = centreFactoryString + centreFactory[i]->getTile();
        }
    }
    }
    
    return centreFactoryString;
}