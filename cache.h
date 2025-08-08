#include <string>
#include <vector>
#include "set.h"
#include "mainmemory.h"

using namespace std;

#ifndef CACHE_H
#define CACHE_H

enum write_policy{
    WriteBack,
    WriteThrough
};
enum write_allocation_policy{
    WriteAllocate,
    NoWriteAllocate
};

class Cache
{
    const unsigned int BlocksCount; // 16 fixed
    const unsigned int Associativity;
    const unsigned int BlockSize; // input
    const unsigned int SetsCount;
    unsigned int TagBitsCount,IndexBitsCount,OffsetBitsCount;
    const write_policy WritePolicy;
    const write_allocation_policy AllocPolicy;
    Set* Sets;

    friend class MainMemory;
public:
    Cache(unsigned int,unsigned  int, write_policy, write_allocation_policy);
    void Write(unsigned int , int,MainMemory&,int);
    void Read(unsigned int,MainMemory&,int);
    unsigned int FindTag(unsigned int ad);
    unsigned int FindOffset(unsigned int ad);
    unsigned int FindIndex(unsigned int ad);
    unsigned int MakeAdderss(unsigned int tag, unsigned int index, unsigned int offset);
    bool RequestData(unsigned int ad,Block *&b); //returns false if not found
    Block* FindeLRU(unsigned int index);
    void EvictBlock(Block * blk, unsigned int index, MainMemory &mem);
    //all ints are in base 10

};

#endif // CACHE_H
