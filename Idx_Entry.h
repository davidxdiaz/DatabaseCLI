//
// Created by David on 17/9/2017.
//

#ifndef PROYECTOED2_MASTER_IDX_ENTRY_H
#define PROYECTOED2_MASTER_IDX_ENTRY_H


class Idx_Entry {
public:
    Idx_Entry(char * id,int nB,int nRR);
    char id[20];
    int numeroBloque;
    int numeroRR;
    char * toChar();
    void initFromChar(char * data);
};


#endif //PROYECTOED2_MASTER_IDX_ENTRY_H
