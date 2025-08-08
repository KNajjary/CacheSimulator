#include "mainmemory.h"
#include <cmath>
#include <iostream>

using namespace std;


MainMemory::MainMemory()
{

}
int MainMemory::GetData(unsigned int start){

    for(unsigned int i=0; i<Cells.size(); i++){
        if(Cells[i].Address == start)
            return Cells[i].Data;
    }
    return 0;
}
void MainMemory::SetData(unsigned int start,int data){

    for(int i=0; i<Cells.size(); i++){
        if(  Cells[i].Address == start ){

            Cells[i].Data = data;
            return;
        }
    }
    Cells.push_back({.Address= start, .Data = data });
    return;
}
