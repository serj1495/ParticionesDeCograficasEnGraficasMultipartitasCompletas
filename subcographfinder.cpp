#include "subcographfinder.h"

SubcotreeFinder::SubcotreeFinder()
{

}

void SubcotreeFinder::addBinaryObstruction(BCTN* o){
    b_obsts.push_back(o);
}

void SubcotreeFinder::printFunVer(funver* func, BCTN* root, int level){
    for(int i = 0; i < level; i++)
        cout << ".";
    if(func->find(root) == func->end()){
        cout << "NO ENCONRADO" << endl;
    }
    else{
        cout << func->find(root)->second << endl;
        if(root->tag != -1){
            printFunVer(func, root->lchild, level+1);
            printFunVer(func, root->rchild, level+1);
        }
    }
}

void SubcotreeFinder::crearFunverEnBlanco(funver *func, BCTN *nodo){
    func->insert(make_pair(nodo,false));
    if(nodo->tag != -1){
        crearFunverEnBlanco(func, nodo->lchild);
        crearFunverEnBlanco(func, nodo->rchild);
    }
}

//***************************************************************************************************************
//IMPLEMENTACIÓN DEL ALGORITMO 2
//  I:g, la raíz de un coárbol binario en el que se va a buscar un subcoárbol; h, el índice del subcoárbol que se
//    va a buscar dentro de b_obsts.
//  O:un mapa no ordenado que va de los nodos de h a verdadero o falso, que indica si está marcado.
//  Detalles de implementación:
//      -La función de verificación es representada por un mapa no ordenado.
//***************************************************************************************************************

funver* SubcotreeFinder::funcionDeVerificacion(BCTN* g, int h){

    funver *func = new funver();
    crearFunverEnBlanco(func, b_obsts.at(h));


    if(g->tag == -1){
        //Revisamos todas las parejas de la función. Si el primer elemento de una es una hoja en h, entonces cambiamos el
        //  segundo elemento para que sea verdadero. Equivale ala línea 3 del algoritmo.
        for (funver::iterator itr = func->begin(); itr != func->end(); itr++){
             if(itr->first->tag == -1)
                 itr->second = true;
         }
    }
    else{
        funver *vizq = funcionDeVerificacion(g->lchild, h);                         //Línea 5
        funver *vder = funcionDeVerificacion(g->rchild, h);                         //Línea 6
        for (funver::iterator itr = func->begin(); itr != func->end(); itr++){
            if(vizq->find(itr->first)->second || vder->find(itr->first)->second){   //Línea 8
                itr->second = true;                                                 //Línea 9
            }
            else if(                                                                //Todas las condiciones corresponden a la línea 10
                itr->first->tag == g->tag &&
                ((vizq->find(itr->first->lchild)->second && vder->find(itr->first->rchild)->second) ||
                 (vizq->find(itr->first->rchild)->second && vder->find(itr->first->lchild)->second))
            ){
                itr->second = true;                                                 //Línea 11
            }
         }
        vizq->~unordered_map(); //Llamamos al destructor y liberamos memoria para evitar que siga acumulándose.
        free(vizq);
        vder->~unordered_map();
        free(vder);
    }


    return func;                                                                    //Línea 12
}


//***************************************************************************************************************
//IMPLEMENTACIÓN DEL ALGORITMO 3
//  I:g, la raíz de un coárbol en el que se van a buscar todos los coárboles binarios cargados.
//  O:verdadero si g contiene al menos una de las cográficas cargadas, falso en el caso contrario.
//  Detalles de implementación:
//      -
//***************************************************************************************************************

bool SubcotreeFinder::containsSubcograph(CotreeNode* g){

    BinaryCotreeNode *b = BinaryCotreeNode::crearCoarbolBinario(g);                 //Línea 1
    //No es necesario ejecutar la línea 2, debido a que las obstrucciones ya están cargadas
    for(int i = 0; i < b_obsts.size(); i++){                                        //Línea 3
        funver *f = funcionDeVerificacion(b, i);                                    //Línea 4
        if(f->find(b_obsts.at(i))->second){                                         //Línea 5
            f->~unordered_map();
            free(f);
            b->~BinaryCotreeNode();
            return true;                                                            //Línea 6
        }
        f->~unordered_map();
        free(f);
    }
    b->~BinaryCotreeNode();
    free(b);
    return false;                                                                    //Línea 7
}


