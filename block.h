#include <ctime>

#ifndef BLOCK_H
#define BLOCK_H

class Block
{
    unsigned int BlockSize;
    unsigned int Tag;
    int  Data;
    bool Valid,Dirty;
    int LastAccessTime;
public:
    Block(unsigned int);
    Block();
    Block(Block const &b);
    void SetData(int data);
    void SetBlock(unsigned int,int );
    void SetBlockSize(unsigned int);
    void SetDirty(bool);
    bool GetDirty() const;
    int GetData() const;
    unsigned int GetTag() const;
    bool GetValid() const;
    int GetTime() const;
    void SetTime(int);
};

#endif // BLOCK_H
