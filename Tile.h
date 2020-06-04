#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

using std::stoi;
using std::for_each;
using std::ifstream;
using std::ofstream;
using std::istringstream;

enum tileOptions
{
    FirstPlayer,
    Red,
    Yellow,
    DarkBlue,
    LightBlue,
    Black,
    NoTile
};

typedef string tileType;

class Tile
{
    public:

        // Constructor/Deconstructor
        Tile();
        Tile(tileOptions tile);
        Tile(char tile);
        ~Tile();

        /**
         * Return a tile
         */
        char getTile();

    private:

        char tile;
};
