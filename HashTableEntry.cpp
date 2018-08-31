//
// Created by David on 17/9/2017.
//

#include "HashTableEntry.h"
#include "string.h"

HashTableEntry::HashTableEntry(int p,int a)
{
    primerBloqueLLave=p;
    actualBloqueLLave=a;
}

char * HashTableEntry::toChar()
{
    int pos=0;
    char * data = new char[8];
    memcpy(&data[pos],&primerBloqueLLave,4);
    pos+=4;
    memcpy(&data[pos],&actualBloqueLLave,4);
    pos+=4;
    return data;
}
void HashTableEntry::initFromChar(char * data)
{
    int pos=0;
    memcpy(&primerBloqueLLave,&data[pos],4);
    pos+=4;
    memcpy(&actualBloqueLLave,&data[pos],4);
    pos+=4;
}