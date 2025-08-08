#include <vector>

using namespace std;

#ifndef MAINMEMORY_H
#define MAINMEMORY_H

struct Cell{
    unsigned int Address;
    int Data;
};

class MainMemory
{
    vector <Cell> Cells;
public:
    MainMemory();
    int GetData(unsigned int start);
    void SetData(unsigned int start, int data);
};

#endif // MAINMEMORY_H
