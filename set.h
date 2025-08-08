#include "block.h"
#include <vector>
#include <queue>

using namespace std;

#ifndef SET_H
#define SET_H

class Set
{
    Block *Blocks;
    unsigned int Index;
    unsigned int Size,BlockSize;

public:
    Set();
    Set(unsigned int ind,unsigned  int siz,unsigned  int bsiz);
    Set(unsigned int siz, unsigned int bsiz);
    void SetIndex(unsigned int ind);
    void SetBlockSize(unsigned int s);
    unsigned int GetIndex() const;
    Block* GetBlock(unsigned int) ;
};

#endif // SET_H
