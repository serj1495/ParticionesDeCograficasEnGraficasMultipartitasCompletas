#ifndef COTREENODE_H
#define COTREENODE_H

#include "nontaggedcotreenode.h"
#include<iostream>
#include<vector>
using namespace std;


class CotreeNode{
public:
    CotreeNode* parent = nullptr;
    vector<CotreeNode*> children;
    int leaves = 1;
    int tag = -1; //-1 for vertex
    int color = 0; //1, blue; 2, green; 3, H; 4, I; 5, J; 0, default.
    CotreeNode();
    CotreeNode(NonTaggedCotreeNode *base, int etiqueta);
    void print(int level);
    ~CotreeNode();
};

#endif // COTREENODE_H
