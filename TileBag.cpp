#include "TileBag.h"

TileBag::TileBag()
{
    
}

TileBag::~TileBag()
{
    //  Deconstructor
}

bool TileBag::isTileBagEmpty()
{
    return tileBagVector.empty();
}

void TileBag::refillTileBag()
{    
    if(isTileBagEmpty())
    {
        for(int i = 0; i < 100; i++)
        {
            if(i < 20){
                tileBagVector.push_back(new Tile(Red));
            }
            else if(i < 40){
                tileBagVector.push_back(new Tile(Yellow));
            }
            else if(i < 60){
                tileBagVector.push_back(new Tile(DarkBlue));
            }
            else if(i < 80){
                tileBagVector.push_back(new Tile(LightBlue));
            }
            else{
                tileBagVector.push_back(new Tile(Black));
            }        
        }

        shuffleTileBag(100);
    }
}

void TileBag::swap(Tile* a, Tile* b)
{
    Tile temp = *a;  
    *a = *b;  
    *b = temp;
}

void TileBag::shuffleTileBag(int n)
{    
    // Use a different seed value so that  
    // we don't get same result each time 
    // we run this program  
    srand (time(NULL));  
  
    // Start from the last element and swap  
    // one by one. We don't need to run for  
    // the first element that's why i > 0  
    for (int i = n - 1; i > 0; i--)  
    {  
        // Pick a random index from 0 to i  
        int j = rand() % (i + 1);  
  
        // Swap arr[i] with the element  
        // at random index  
        swap(tileBagVector[i], tileBagVector[j]);  
    } 
}

int  TileBag::numberOfTilesInBag()
{
    return tileBagVector.size();
}

void TileBag::displayTileBag()
{
    int tileBagSize = numberOfTilesInBag();
    for(int i = 0; i < tileBagSize; i++)
    {
        cout << tileBagVector[i]->getTile() << " ";
    }
}

string TileBag::tileBagToString(){
    string tileBagStr;
    int tileBagSize = numberOfTilesInBag();
    for(int i =0; i < tileBagSize; i++){
        tileBagStr = tileBagStr + tileBagVector[i]->getTile();
    }
    return tileBagStr;
}