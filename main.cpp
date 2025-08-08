#include <iostream>
#include "cache.h"

using namespace std;

int main()
{
    int BlockS,Asso;
    string w,a;
    cin>>BlockS>>Asso>>w>>a;
    write_policy wpo;
    write_allocation_policy wap;
    if(w == "write-back")
        wpo = WriteBack;
    else if(w == "write-through")
        wpo = WriteThrough;
    
    if(a == "write-allocate")
        wap = WriteAllocate;
    else if(a == "no-write-allocate")
        wap = NoWriteAllocate;
    
    Cache c(BlockS,Asso,wpo,wap);
    MainMemory mem;
    int t,i=0;
    cin>>t;
    while(t>i){
        string in;
        cin>>in;
        if(in == "write"){
            int data;
            unsigned int ad;
            cin>>ad>>data;
            c.Write(ad,data,mem,i);

        }
        else if(in == "read"){
            unsigned int ad;
            cin>>ad;
            c.Read(ad,mem,i);

        }
        i++;
    }
    return 0;
}
