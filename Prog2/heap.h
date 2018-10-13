#ifndef _HEAP_H
#define _HEAP_H

#include <vector>
#include <string>
#include <hash.h>
using namespace std;

class heap
{
  public:
    heap(int capacity);

    // an average-case constant time algorithm
    int insert(const string &id, int key, void *pv = nullptr);

    // ALL OTHER BELOW USE worst-case logarithmic time algorithms

    // removes the item with the lowest key from the heap
    int deleteMin();

    // providing both increaseKey and decreaseKey functionality
    int setKey();

    // delete an item with a specified id from the heap
    int remove();

  private:
    class node
    { // An inner class within heap
      public:
        std::string id; // The id of this node
        int key;        // The key of this node
        void *pData;    // A pointer to the actual data
    };

    int capacity;
    int size;
    std::vector<node> data; // The actual binary heap
    hashTable *mapping;     // maps ids to node pointers

    void percolateUp(int posCur);
    void percolateDown(int posCur);
    int getPos(node *pn);
};

#endif