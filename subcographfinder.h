#ifndef SUBCOTREEFINDER_H
#define SUBCOTREEFINDER_H

#include<iostream>
#include<vector>
#include <bits/stdc++.h>
#include "binarycotreenode.h"
#include "cotreenode.h"

#define funver unordered_map<BinaryCotreeNode*,bool>
#define BCTN BinaryCotreeNode

class SubcotreeFinder
{
public:
    vector<BCTN*> b_obsts;
    SubcotreeFinder();
    void addObstruction(CotreeNode *); //Necesitamos el algoritmo para generar todos los coárboles binarios.
    void addBinaryObstruction(BCTN*);//Puede ser peligroso si no se agregan todas las formas binarias de un coárbol.

//private:
    funver *funcionDeVerificacion(BCTN* g, int i);      //ALGORITMO 2
    void crearFunverEnBlanco(funver *func, BCTN *nodo); //El índice de la obstrucción dentro de la lista de obstrucciones, b_obsts.
    bool containsSubcograph(CotreeNode* g);             //ALGORITMO 3
    static void printFunVer(funver* func, BCTN* root, int level);

};

#endif // SUBCOGRAPHFINDER_H
