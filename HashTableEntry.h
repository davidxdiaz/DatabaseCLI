//
// Created by David on 17/9/2017.
//

#ifndef PROYECTOED2_MASTER_HASHTABLEENTRY_H
#define PROYECTOED2_MASTER_HASHTABLEENTRY_H


class HashTableEntry {
public:
    HashTableEntry(int p,int a);
    int primerBloqueLLave;
    int actualBloqueLLave;

    char * toChar();
    void initFromChar(char * data);

};


#endif //PROYECTOED2_MASTER_HASHTABLEENTRY_H
