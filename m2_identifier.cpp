#include "m2_identifier.h"

BCTN* M2_Identifier::build_h1(){
    BCTN* n[11];
    n[0] = new BCTN(-1,1);
    n[1] = new BCTN(-1,1);
    n[2] = new BCTN(-1,1);
    n[3] = new BCTN(1,2);
        n[3]->lchild = n[1];
        n[3]->rchild = n[2];
    n[4] = new BCTN(0,3);
        n[4]->lchild = n[0];
        n[4]->rchild = n[3];
    n[5] = new BCTN(-1,1);
    n[6] = new BCTN(-1,1);
    n[7] = new BCTN(-1,1);
    n[8] = new BCTN(1,2);
        n[8]->lchild = n[6];
        n[8]->rchild = n[7];
    n[9] = new BCTN(1,3);
        n[9]->lchild = n[5];
        n[9]->rchild = n[8];
    n[10] = new BCTN(0,6);
        n[10]->lchild = n[4];
        n[10]->rchild = n[9];
    return n[10];
}

BCTN* M2_Identifier::build_h2(){
    BCTN* n[11];
    n[0] = new BCTN(-1,1);
    n[1] = new BCTN(-1,1);
    n[2] = new BCTN(-1,1);
    n[3] = new BCTN(-1,1);
    n[4] = new BCTN(1,2);
        n[4]->lchild = n[2];
        n[4]->rchild = n[3];
    n[5] = new BCTN(1,3);
        n[5]->lchild = n[1];
        n[5]->rchild = n[4];
    n[6] = new BCTN(0,4);
        n[6]->lchild = n[0];
        n[6]->rchild = n[5];
    n[7] = new BCTN(-1,1);
    n[8] = new BCTN(-1,1);
    n[9] = new BCTN(1,2);
        n[9]->lchild = n[7];
        n[9]->rchild = n[8];
    n[10] = new BCTN(0,6);
        n[10]->lchild = n[6];
        n[10]->rchild = n[9];
    return n[10];
}

BCTN* M2_Identifier::build_h3(){
    BCTN* n[11];
    n[0] = new BCTN(-1,1);
    n[1] = new BCTN(-1,1);
    n[2] = new BCTN(1,2);
        n[2]->lchild = n[0];
        n[2]->rchild = n[1];
    n[3] = new BCTN(-1,1);
    n[4] = new BCTN(-1,1);
    n[5] = new BCTN(-1,1);
    n[6] = new BCTN(1,2);
        n[6]->lchild = n[4];
        n[6]->rchild = n[5];
    n[7] = new BCTN(1,3);
        n[7]->lchild = n[3];
        n[7]->rchild = n[6];
    n[8] = new BCTN(0,5);
        n[8]->lchild = n[2];
        n[8]->rchild = n[7];
    n[9] = new BCTN(-1,1);
    n[10] = new BCTN(0,6);
        n[10]->lchild = n[8];
        n[10]->rchild = n[9];
    return n[10];
}

BCTN* M2_Identifier::build_i1(){
    BCTN* n[11];
    n[0] = new BCTN(-1,1);
    n[1] = new BCTN(-1,1);
    n[2] = new BCTN(1,2);
        n[2]->lchild = n[0];
        n[2]->rchild = n[1];
    n[3] = new BCTN(-1,1);
    n[4] = new BCTN(-1,1);
    n[5] = new BCTN(-1,1);
    n[6] = new BCTN(-1,1);
    n[7] = new BCTN(1,2);
        n[7]->lchild = n[5];
        n[7]->rchild = n[6];
    n[8] = new BCTN(0,3);
        n[8]->lchild = n[4];
        n[8]->rchild = n[7];
    n[9] = new BCTN(1,4);
        n[9]->lchild = n[3];
        n[9]->rchild = n[8];
    n[10] = new BCTN(0,6);
        n[10]->lchild = n[2];
        n[10]->rchild = n[9];
    return n[10];
}

BCTN* M2_Identifier::build_j1(){
    BCTN* n[13];
    n[0] = new BCTN(-1,1);
    n[1] = new BCTN(-1,1);
    n[2] = new BCTN(-1,1);
    n[3] = new BCTN(1,2);
        n[3]->lchild = n[1];
        n[3]->rchild = n[2];
    n[4] = new BCTN(-1,1);
    n[5] = new BCTN(0,3);
        n[5]->lchild = n[3];
        n[5]->rchild = n[4];
    n[6] = new BCTN(-1,1);
    n[7] = new BCTN(-1,1);
    n[8] = new BCTN(-1,1);
    n[9] = new BCTN(1,2);
        n[9]->lchild = n[7];
        n[9]->rchild = n[8];
    n[10] = new BCTN(0,3);
        n[10]->lchild = n[6];
        n[10]->rchild = n[9];
    n[11] = new BCTN(1,6);
        n[11]->lchild = n[5];
        n[11]->rchild = n[10];
    n[12] = new BCTN(0,7);
        n[12]->lchild = n[0];
        n[12]->rchild = n[11];
    return n[12];
}

BCTN* M2_Identifier::h1 = build_h1();
BCTN* M2_Identifier::h2 = build_h2();
BCTN* M2_Identifier::h3 = build_h3();
BCTN* M2_Identifier::i1 = build_i1();
BCTN* M2_Identifier::j1 = build_j1();

//***************************************************************************************************************
//IMPLEMENTACIÓN DEL ALGORITMO 4
//  Detalles de implementación:
//      -La clase M2_Identifier tiene como único objetivo el reconocimiento de las gráficas que pertenecen a M2
//       ejecutando el Algoritmo 4. El constructor ejecuta la línea 1 de este algoritmo al cargar los árboles
//       binarios de las obstrucciones, mientras que el resto del algoritmo es ejecutado por el método containsSubcograph(g)
//       de la clase SubcographFinder.
//***************************************************************************************************************



M2_Identifier::M2_Identifier(){
    finder.addBinaryObstruction(h1);
    finder.addBinaryObstruction(h2);
    finder.addBinaryObstruction(h3);
    finder.addBinaryObstruction(i1);
    finder.addBinaryObstruction(j1);
}
//***************************************************************************************************************
//  I:g, la raíz de un coárbol.
//  O:verdadero si el coárbol con raíz en g representa una gráfica en M2 y falso en el caso contrario.
//***************************************************************************************************************

bool M2_Identifier::isInM2(CotreeNode *g){
    return !finder.containsSubcograph(g);
}

