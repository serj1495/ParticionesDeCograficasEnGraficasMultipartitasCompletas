#ifndef BINARYCOTREENODE_H
#define BINARYCOTREENODE_H

#include "cotreenode.h"
#include<iostream>
#include<vector>

class BinaryCotreeNode
{
public:
    BinaryCotreeNode* parent = nullptr;
    BinaryCotreeNode* lchild = nullptr;
    BinaryCotreeNode* rchild = nullptr;
    int leaves = 1; //Para no aumentar el tiempo en el que se agrega un hijo, este parámetro debe manejarse de forma manual
    int tag = -1; //-1 for vertex
    BinaryCotreeNode();
    BinaryCotreeNode(int etiqueta);
    BinaryCotreeNode(int etiqueta, int hojas);
    BinaryCotreeNode(CotreeNode *base);
    void setLchild(int tag);
    void setRchild(int tag);
    void setLchild(int tag, int hojas);
    void setRchild(int tag, int hojas);
    void print(int level);
    ~BinaryCotreeNode();
    static BinaryCotreeNode* crearCoarbolBinario(CotreeNode *r); //ALGORITMO 1
    static int vivos;

};

#endif // BINARYCOTREENODE_H
