#include "block.h"
#include <iostream>
#include <ctime>

using namespace std;

Block::Block()
    : BlockSize(0)
{
    Valid = false;
    Data = 0;
    Dirty = false;
    Tag =0;
    //time(&LastAccessTime);
    LastAccessTime = 0;//clock();

}
Block::Block(unsigned int bsiz)
    : BlockSize(bsiz)
{
    Valid = false;
    Data = 0;
    Dirty = false;
    Tag =0;

    //time(&LastAccessTime);
    LastAccessTime = 0;//clock();

}
Block::Block(Block const &b)
    : BlockSize(b.BlockSize)
{
    Tag = b.Tag;
    //Data = b.Data;
    Data = b.Data;
    Valid = b.Valid;
    Dirty = b.Dirty;
    LastAccessTime = b.LastAccessTime;
}
void Block::SetBlock(unsigned int tag,int  data){

    Data = data;

    Tag = tag;
    Valid = true;
    //LastAccessTime = time;
    Dirty = false;

}
void Block::SetBlockSize(unsigned int s){
    BlockSize = s;


}
void Block::SetData(int data){
    //time(&LastAccessTime);
    Data=data;
    Valid = true;
}
int Block::GetData() const
{
    return Data;

}
unsigned int Block::GetTag() const{
    return Tag;
}
bool Block::GetValid() const{
    return Valid;
}
int Block::GetTime() const{
    return LastAccessTime;
}
void Block::SetDirty(bool d){
    Dirty  = d;
}
bool Block::GetDirty() const
{
    return Dirty;
}
void Block::SetTime(int t){
    LastAccessTime = t;
}
