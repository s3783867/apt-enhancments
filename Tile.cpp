#include "Tile.h"

Tile::Tile(tileOptions tile)
{
    if(tile == FirstPlayer){
        this->tile = 'F';
    }
    else if(tile == Red){
        this->tile = 'R';
    }
    else if(tile == Yellow){
        this->tile = 'Y';
    }
    else if(tile == DarkBlue){
        this->tile = 'B';
    }
    else if(tile == LightBlue){
        this->tile = 'L';
    }
    else if(tile == Black){
        this->tile = 'U';
    }
    else{
        this->tile = '.';
    }
}

Tile::Tile(char tile){
    this->tile = tile;
}

Tile::~Tile()
{
    //  Deconstructor
}

char Tile::getTile()
{
    return tile;
}
