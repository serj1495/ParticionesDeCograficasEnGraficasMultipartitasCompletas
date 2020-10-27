#include "binarycotreenode.h"

int BinaryCotreeNode::vivos = 0;

BinaryCotreeNode::BinaryCotreeNode(){
    vivos++;
    //cout << "Constructor binarycotreenode" << endl;
}

BinaryCotreeNode::BinaryCotreeNode(int etiqueta){
    vivos++;
    //cout << "Constructor binarycotreenode" << endl;
    tag = etiqueta;
}
BinaryCotreeNode::BinaryCotreeNode(int etiqueta, int hojas){
    vivos++;
    //cout << "Constructor binarycotreenode" << endl;
    tag = etiqueta;
    leaves = hojas;
}

void BinaryCotreeNode::setLchild(int etiqueta){
    lchild = new BinaryCotreeNode(etiqueta);
}

void BinaryCotreeNode::setRchild(int etiqueta){
    rchild = new BinaryCotreeNode(etiqueta);
}

void BinaryCotreeNode::setLchild(int etiqueta, int hojas){
    lchild = new BinaryCotreeNode(etiqueta, hojas);
}

void BinaryCotreeNode::setRchild(int etiqueta, int hojas){
    rchild = new BinaryCotreeNode(etiqueta, hojas);
}

void BinaryCotreeNode::print(int level){
    for(int i = 0; i < level; i++)
        cout << ".";
    cout << tag << endl;
    if(tag != -1){
        lchild->print(level+1);
        rchild->print(level+1);
    }
}

BinaryCotreeNode::~ BinaryCotreeNode(){
    vivos--;
    //cout << "DESTRUCTOR binarycotreenode" << endl;
    if(tag != -1){

        lchild->~BinaryCotreeNode();
        rchild->~BinaryCotreeNode();
        free(lchild);
        free(rchild);
    }
}


//***************************************************************************************************************
//IMPLEMENTACIÓN DEL ALGORITMO 1
//  I:r la raíz de un coárbol.
//  O:r' la raíz de un coárbol binario de r.
//  Detalles de implementación:
//      -
//***************************************************************************************************************

BinaryCotreeNode* BinaryCotreeNode::crearCoarbolBinario(CotreeNode *r){
    BinaryCotreeNode* r_p = new BinaryCotreeNode;
    if(r->tag != -1){
        r_p->tag = r->tag;
        BinaryCotreeNode* s = r_p;
        int i;
        for(i = 0; i < r->children.size() - 2; i++){
            s->lchild = crearCoarbolBinario(r->children.at(i));
            s->lchild->parent = s;
            s->rchild = new BinaryCotreeNode;
            s->rchild->parent = s;
            s = s->rchild;
            s->tag = r->tag;
        }
        s->lchild = crearCoarbolBinario(r->children.at(i));
        s->lchild->parent = s;
        s->rchild = crearCoarbolBinario(r->children.at(i+1));
        s->rchild->parent = s;
    }
    return r_p;
}
