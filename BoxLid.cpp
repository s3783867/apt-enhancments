
#include "BoxLid.h"

BoxLid::BoxLid()
{
    boxLid = new LinkedList();
    boxLid->head = nullptr;
    boxLid->tail = nullptr;
}

BoxLid::~BoxLid()
{
    clear();
}

unsigned int BoxLid::size()
{
    Node* current = boxLid-> head;
    int counter = 0;
    while (current != nullptr)
    {
        current = current -> next;
        counter ++;
    }
    return counter;
}

char BoxLid::getValue(unsigned int index) {
   Node* current = boxLid->head;


   if (index < size()) {
      unsigned int counter = 0;
      while (counter < index) {
         ++counter;
         current = current->next;
      }
      // toReturn = current->value;
   } else {
      throw std::out_of_range("Index to big");
   }

   // return toReturn;
   return current->value;
}

void BoxLid::addTileBack(Tile* tile)
{
    Node* add = new Node();
    add -> value = tile->getTile();
    add -> next = nullptr;
    add->prev = boxLid->tail;

    //checks if list is empty:
    if (boxLid->head == nullptr)
    {
        add->prev = nullptr;
        boxLid->head = add;
        boxLid -> tail = add;
    }

    else
    {
        boxLid->tail->next = add;
        boxLid -> tail = add;
    }
}

void BoxLid::removeTileBack()
{
    if (boxLid->tail != nullptr)
    {
        Node* remove = boxLid->tail;
        boxLid->tail = boxLid->tail->prev;
        boxLid->tail->next = nullptr;
        delete remove;
       
    }
    else
    {
        throw std::logic_error("Deleting on empty list");
    }
    
}

void BoxLid::clear()
{
    while (boxLid->tail != nullptr)
    {
        removeTileBack();
    }
}

std::string BoxLid::printBoxLid(){
    int length = size();
    std::string boxLidString ="";
    for (int i=0; i<length;i++){
        boxLidString= boxLidString + getValue(i);
    }
    return boxLidString;
}
