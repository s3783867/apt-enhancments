#include "Factory.h"

Factory::Factory()
{
    tileBag = new TileBag();
    
    for(int outterLoop = 0; outterLoop < NUMBER_OF_FACTORIES;  outterLoop++)
    {
        for(int innerLoop = 0; innerLoop < FACTORY_SIZE;  innerLoop++)
        {
                this->factories[outterLoop][innerLoop] = nullptr;
        }
    }
}

Factory::~Factory()
{
    //  Deconstructor
}

bool Factory::factoryContainsTile(int factoryNumber, char tileColour)
{
    bool doesContainTile = false;

    for(int i = 0; i < FACTORY_SIZE; i++)
    {
        if(factories[factoryNumber - 1][i] != nullptr)
        {
            if(factories[factoryNumber - 1][i]->getTile() == tileColour)
            {
                doesContainTile = true;
            }
        }
    }

    return doesContainTile;
}

bool Factory::isFactoryEmpty(int factoryNumber)
{
    int counter = 0;

    for(int i = 0; i < FACTORY_SIZE;  i++)
    {
        if(factories[factoryNumber - 1 ][i] == nullptr)
        {
            counter++;
        }
    }

    if(counter == FACTORY_SIZE)
    {
        return true;
    }
    else
    {
        return false;
    } 
}

bool Factory::areFactoriesEmpty()
{
    int counter = 0;

    for(int outterLoop = 0; outterLoop < NUMBER_OF_FACTORIES;  outterLoop++)
    {
        for(int innerLoop = 0; innerLoop < FACTORY_SIZE;  innerLoop++)
        {
            if(factories[outterLoop][innerLoop] == nullptr)
            {
                counter++;
            }
        }
    }

    if(counter == (NUMBER_OF_FACTORIES * FACTORY_SIZE))
    {
        return true;
    }
    else
    {
        return false;
    } 
}

void Factory::emptyAFactory(int factoryNumber)
{
    for(int i = 0; i < FACTORY_SIZE; i ++)
    {
        factories[factoryNumber - 1][i] = nullptr;
    }
}

void Factory::refillFactories()
{
   if(tileBag->isTileBagEmpty())
   {
       tileBag->refillTileBag();
   }
   
   if(areFactoriesEmpty())
   {
        for(int outterLoop = 0; outterLoop < NUMBER_OF_FACTORIES;  outterLoop++)
        {
            for(int innerLoop = 0; innerLoop < FACTORY_SIZE;  innerLoop++)
            {
                factories[outterLoop][innerLoop] = tileBag->tileBagVector[0];
                tileBag->tileBagVector.erase(tileBag->tileBagVector.begin());
            }
        }
   }
}

void Factory::displayFactories()
{
    
    for(int outterLoop = 0; outterLoop < NUMBER_OF_FACTORIES;  outterLoop++)
    {
        // Factory Number
        cout << (outterLoop + 1);
        cout << ": ";

        // Print Factory Contents
        for(int innerLoop = 0; innerLoop < FACTORY_SIZE;  innerLoop++)
        {
            if(factories[outterLoop][innerLoop] != nullptr)
            {
                cout << printTile(factories[outterLoop][innerLoop]->getTile()) << " ";
            }
            else
            {
                cout << " ";
            }
        }

        cout << endl;
    }
}

std::string Factory::factoryToString(int factoryNumber){
    std::string str;
    if(!isFactoryEmpty(factoryNumber + 1)){
    for(int i = 0; i < FACTORY_SIZE; i++){
        str = str + factories[factoryNumber][i]->getTile();
        }
    }
    return str;
}

TileBag* Factory::getTileBag(){
    return this->tileBag;
}
