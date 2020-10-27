#ifndef M2_IDENTIFIER_H
#define M2_IDENTIFIER_H

#include<iostream>
#include<vector>
#include "subcographfinder.h"
using namespace std;

class M2_Identifier{

public:
    M2_Identifier();
    static BinaryCotreeNode* h1;
    static BinaryCotreeNode* h2;
    static BinaryCotreeNode* h3;
    static BinaryCotreeNode* i1;
    static BinaryCotreeNode* j1;
    bool isInM2(CotreeNode *g);
private:
    SubcotreeFinder finder;
    static BCTN* build_h1();
    static BCTN* build_h2();
    static BCTN* build_h3();
    static BCTN* build_i1();
    static BCTN* build_j1();
};

#endif // M2_IDENTIFIER_H
