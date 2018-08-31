//
// Created by David on 17/9/2017.
//

#include "Idx_Entry.h"
#include <stdio.h>
#include <string.h>

Idx_Entry::Idx_Entry(char *i, int nB, int nRR)
{
    strncpy(id,i,20);
    numeroBloque=nB;
    numeroRR=nRR;
}

char * Idx_Entry::toChar()
{
    int pos=0;
    char * data = new char[28];
    memcpy(&data[pos],id,20);
    pos+=20;
    memcpy(&data[pos],&numeroBloque,4);
    pos+=4;
    memcpy(&data[pos],&numeroRR,4);
    pos+=4;
    return data;
}

void Idx_Entry::initFromChar(char *data)
{
    int pos=0;
    memcpy(id,&data[pos],20);
    pos+=20;
    memcpy(&numeroBloque,&data[pos],4);
    pos+=4;
    memcpy(&numeroRR,&data[pos],4);
    pos+=4;
}