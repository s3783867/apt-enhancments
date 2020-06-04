#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <thread>
#include <chrono>

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

enum class ansi_color_code: int{
    red=31,
    yellow=33,
    blue=34,
    magenta=35,
    white=37,
    bright_black = 90,
    bright_cyan=96,
};

template<ansi_color_code color,typename printable>
    std::string print_as_color(printable const& value){
    std::stringstream sstr;
    sstr<<"\033[1;"<<static_cast<int>(color)<<"m"<<value<<"\033[0m";
    return sstr.str();
}

template<typename printable>
    std::string printTile(printable const& tile){
    std::string colouredTile;
    if(tile=='R'){
        colouredTile = print_as_color<ansi_color_code::red>(tile);
    }else if(tile=='B'){
        colouredTile = print_as_color<ansi_color_code::blue>(tile);
    }else if(tile=='L'){
        colouredTile = print_as_color<ansi_color_code::bright_cyan>(tile);
    }else if(tile=='Y'){
        colouredTile = print_as_color<ansi_color_code::yellow>(tile);
    }else if(tile=='U'){
        colouredTile = print_as_color<ansi_color_code::bright_black>(tile);
    }else {
        colouredTile = print_as_color<ansi_color_code::magenta>(tile);
    }
 return colouredTile;
}


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
