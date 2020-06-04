#include "TileBag.h"

#define BAG_ARRAY_MAX_SIZE  100 

//class for nodes in the linked list:
class Node
{
    public:
        //tileType* value;
        char value;
        Node* next;
        Node* prev;
};

//linked list class for boxlid:
class LinkedList
{
    public:
        Node* head;
        Node* tail;
};


class BoxLid
{
    public:
        
        BoxLid();
        ~BoxLid();

        //returns the size of the boxlid:
        unsigned int size();

        char getValue(unsigned int index);

        //adds a tile to the back of the boxlid:
        void addTileBack(Tile* tile);

        //removes a tile from the back of the boxlid:
        void removeTileBack();

        //clears the boxlid:
        void clear();

        // Print box lid
        std::string printBoxLid();

    private:

        LinkedList* boxLid;
};
