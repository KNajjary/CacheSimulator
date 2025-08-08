#include "set.h"
#include <iostream>

using namespace std;


Set::Set()
    : Size(0),
    Index(0),
    BlockSize(0)
{
    Blocks = nullptr;


}
Set::Set(unsigned int ind, unsigned int siz, unsigned int bsiz)
    : Size(siz),
    Index(ind),
    BlockSize(bsiz)
{
    Blocks = new Block [Size];
    unsigned int i;
    for(i=0; i<Size; i++){
        Blocks[i].SetBlockSize(BlockSize );
    }

}
Set::Set( unsigned int siz, unsigned int bsiz)
    : Size(siz),
    Index(-1),
    BlockSize(bsiz)
{
    Blocks = new Block [Size];

    for(unsigned int i=0; i<Size; i++){
        Blocks[i].SetBlockSize(BlockSize );
    }


}

void Set::SetBlockSize(unsigned int s){
    BlockSize = s;
    for(unsigned int i=0; i<Size; i++){
        Blocks[i].SetBlockSize(BlockSize );
    }

}
void Set::SetIndex(unsigned int ind){
    Index = ind;
}
unsigned int Set::GetIndex() const
{
    return Index;
}
Block* Set::GetBlock(unsigned int i)
{
    if(i<Size)return &Blocks[i];
    cout<<"Block index out of set size";
    return nullptr;

}

