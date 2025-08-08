#include "cache.h"
#include <cmath>
#include "functions.cpp"
#include <iostream>
#include "mainmemory.h"

using namespace std;

Cache::Cache(unsigned int a1,unsigned  int a2, write_policy a3, write_allocation_policy a4)
    : BlocksCount(16),
    BlockSize(a1),
    Associativity(a2),
    SetsCount(BlocksCount/Associativity),
    WritePolicy(a3),
    AllocPolicy(a4)

{

    Sets = new Set [SetsCount];
    unsigned int i;
    for(i=0; i<SetsCount; i++){
        Sets[i] = Set(i,Associativity,BlockSize);
    }
    TagBitsCount=0;
    IndexBitsCount=0;
    OffsetBitsCount=0;
    while(pow(2,OffsetBitsCount)<BlockSize)
        OffsetBitsCount++;
    while(pow(2,IndexBitsCount)<SetsCount)
        IndexBitsCount++;
    TagBitsCount = 32-(OffsetBitsCount+IndexBitsCount);




}
unsigned int Cache::FindTag(unsigned int ad)
{

    unsigned int dec ;
    dec = ad / (BlockSize*SetsCount);
    return dec;
}
unsigned int Cache::FindOffset(unsigned int ad)
{
    unsigned int dec ;
    dec = ad % BlockSize;
    return dec;

}
unsigned int Cache::FindIndex(unsigned int ad)
{

    unsigned int dec ;
    dec = (ad/BlockSize) % SetsCount ;
    return dec;

}
void Cache::Write(unsigned int ad, int data,MainMemory &mem,int t){
    unsigned int index = FindIndex(ad);
    unsigned int tag = FindTag(ad);
    unsigned int byteOffset = FindOffset(ad);
    Block * blk =nullptr;
    if(RequestData(ad,blk)){
        //hit

        blk->SetData(data);
        cout<<"hit"<<endl;

        if(WritePolicy == WriteThrough){
            mem.SetData(ad,data);
            cout<<"mem_write addr "<<ad<<endl;
        }
        else if(WritePolicy == WriteBack){
            blk->SetDirty(true);
        }
        blk->SetTime(t);
        return;

    }
    // else miss
    cout<<"miss"<<endl;
    if(AllocPolicy == NoWriteAllocate){
        //directly update mem
        cout<<"mem_write addr "<<ad<<endl;
        mem.SetData(MakeAdderss(tag,index,0),data);
        return;


    }

    if(AllocPolicy == WriteAllocate){
        //find LRU
        Block * LRU = FindeLRU(index);
        EvictBlock(LRU,index,mem);
        //write on  LRU
        unsigned int startAd =MakeAdderss(tag,index,0) ,
            endAd = MakeAdderss(tag,index,BlockSize-1);

        int  Bdata = data;
        LRU->SetBlock(tag,Bdata);
        LRU->SetTime(t);
        if(WritePolicy == WriteThrough){
            mem.SetData(MakeAdderss(tag,index,0),data);
            cout<<"mem_write addr "<<ad<<endl;
        }
        else if(WritePolicy == WriteBack){
            LRU->SetDirty(true);
        }



    }
    return;

}
void Cache::EvictBlock(Block * blk,unsigned int index,MainMemory &mem){
    if(!blk->GetValid())return;
    //if valid, evict
    unsigned int startAd =MakeAdderss(blk->GetTag(),index,0) ,
        endAd = MakeAdderss(blk->GetTag(),index,BlockSize-1);

    if(blk->GetDirty()){
        cout<<"evict addr "<<startAd<<" "<<endAd<<" dirty True"<<endl;

        if(WritePolicy == WriteBack)
        {
            //update mem befor eviction

            mem.SetData(startAd,blk->GetData());
            cout<<"mem_write addr "<<startAd<<" "<<endAd<<endl;

        }
    }
    else
        cout<<"evict addr "<<startAd<<" "<<endAd<<" dirty False"<<endl;
    return;

}
Block* Cache::FindeLRU(unsigned int index){
    Block *LRU = Sets[index].GetBlock(0);
    int least = Sets[index].GetBlock(0)->GetTime();

    for(unsigned int i=0; i<Associativity; i++){
        Block * currBl = Sets[index].GetBlock(i);
        if(!currBl->GetValid())
        {
            // not valid
            LRU = currBl;
            return LRU;
        }
        if(least > currBl->GetTime())
        {
            least = currBl->GetTime();
            LRU = currBl;

        }
    }
    return LRU;
}
unsigned int Cache::MakeAdderss(unsigned int tag,unsigned int index,unsigned int offset){
    return binaryS_to_decimalInt(decimalInt_to_binaryS(tag,TagBitsCount)+decimalInt_to_binaryS(index,IndexBitsCount)+decimalInt_to_binaryS(offset,OffsetBitsCount));
}
void Cache::Read(unsigned int ad,MainMemory &mem,int t){
    unsigned int index,tag,byteOffset;
    index = FindIndex(ad);
    tag = FindTag(ad);
    byteOffset = FindOffset(ad);
    Block *blk =nullptr;
    if(RequestData(ad,blk))//hit
    {
        int data = blk->GetData();
        cout<<"hit data "<<data<<endl;
        blk->SetTime(t);

    }
    else //miss
    {
        cout<<"miss data "<<mem.GetData(MakeAdderss(tag,index,0))<<endl;
        Block * LRU;
        LRU = FindeLRU(index);
        EvictBlock(LRU,index,mem);
        int  data = mem.GetData(MakeAdderss(tag,index,0));

        LRU->SetBlock(tag,data);
        LRU->SetTime(t);
    }

    return;



}
bool Cache::RequestData(unsigned int ad,Block *&b){
    unsigned int index = FindIndex(ad);
    unsigned int tag = FindTag(ad);
    unsigned int i;
    for(i=0; i<Associativity; i++){
        Block * currBl = Sets[index].GetBlock(i);
        if(currBl->GetValid() && currBl->GetTag()==tag)
        {
            //hit
            b = currBl;
            return true;

        }
    }
    b = nullptr;
    return false;
}
