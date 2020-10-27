#include "m2_certifier.h"

CotreeNode* M2_Certifier::findOneLeaf(CotreeNode *g){
    if(g->tag == -1)
        return g;
    else
        return findOneLeaf(g->children.at(0));
}

int M2_Certifier::hermano_que_no_es_hoja(CotreeNode *padre, int indice_hijo){
    for(int i = 0; i < padre->children.size() - 1; i++){
        if(padre->children[i%padre->children.size()]->tag != -1)
            return i%padre->children.size();
    }
    return -1;
}

int M2_Certifier::hijo_no_hoja(CotreeNode *g){
    for(int i = 0; i < g->children.size(); i++)
        if(g->children[i]->tag != -1)
            return i;
    return -1;
}

//***************************************************************************************************************
//IMPLEMENTACIÓN DEL ALGORITMO 5
//  I:g, la raíz de un coárbol.
//  O:verdadero si el coárbol con raíz en g representa una gráfica bipartita completa conexa. Se colorean las hojas
//    del árcol con raíz g.
//      -
//***************************************************************************************************************

bool M2_Certifier::es_bipartita_completa(CotreeNode *g){
    if(g->tag == -1){                                                               //Línea 1
        g->color = 1;                                                               //Línea 2
        return true;                                                                //Línea 3
    }
    else if(g->tag == 0){                                                           //Línea 4
        return false;                                                               //Línea 5
    }
    else if(g->children.size() > 2){                                                //Línea 6
        findOneLeaf(g->children.at(0))->color = 3;                                  //Línea 7x3
        findOneLeaf(g->children.at(1))->color = 3;
        findOneLeaf(g->children.at(2))->color = 3;
        return false;                                                               //Línea 8
    }
    else{                                                                           //Línea 9
        if(g->children[0]->tag == -1){                                              //Línea 10
            g->children[0]->color = 1;                                              //Línea 11
        }
        else{                                                                       //Línea 12
            for(int i = 0; i < g->children[0]->children.size(); i++){               //Línea 13
                CotreeNode *gchild = g->children[0]->children.at(i);
                if(gchild->tag == -1)                                               //Línea 14
                    gchild->color = 1;                                              //Línea 15
                else{                                                               //Línea 16
                    findOneLeaf(gchild->children.at(0))->color = 3;                 //Línea 17x3
                    findOneLeaf(gchild->children.at(1))->color = 3;
                    findOneLeaf(g->children[1])->color = 3;
                    return false;                                                   //Línea 18
                }
            }
        }
        if(g->children[1]->tag == -1){                                              //Línea 19
            g->children[1]->color = 2;                                              //Línea 20
        }
        else{                                                                       //Línea 21
            for(int i = 0; i < g->children[1]->children.size(); i++){               //Línea 22
                CotreeNode *gchild = g->children[1]->children.at(i);
                if(gchild->tag == -1)                                               //Línea 23
                    gchild->color = 2;                                              //Línea 24
                else{                                                               //Línea 25
                    findOneLeaf(gchild->children.at(0))->color = 3;                 //Línea 26x3
                    findOneLeaf(gchild->children.at(1))->color = 3;
                    findOneLeaf(g->children[0])->color = 3;
                    return false;                                                   //Línea 27
                }
            }
        }
    }
    return true;                                                                    //Línea 28
}


//***************************************************************************************************************
//IMPLEMENTACIÓN DEL ALGORITMO 6
//  I:g, la raíz de un coárbol cuya raíz tiene etiqueta 0 y al menos dos hijos que no son hojas.
//  O:verdadero si el coárbol con raíz en g representa una gráfica que pertenece a M2. Se colorean las hojas
//    del árcol con raíz g.
//      -
//***************************************************************************************************************

bool M2_Certifier::m2_caso_1(CotreeNode *g){
    if(g->children.size() == 2){                                                    //Línea 1
        for(int i = 0; i < g->children[0]->children.size(); i++){                   //Línea 2
            CotreeNode* gchild = g->children[0]->children.at(i);
            if(gchild->tag == -1)                                                   //Línea 3
                gchild->color = 1;                                                  //Línea 4
            else{                                                                   //Línea 5
                for(int j = 0; j < gchild->children.size(); j++){                   //Línea 6
                    CotreeNode* ggchild = gchild->children.at(j);
                    if(ggchild->tag == -1)                                          //Línea 7
                        ggchild->color = 1;                                         //Línea 8
                    else{                                                           //Línea 9
                        findOneLeaf(ggchild->children[0])->color = 4;               //Línea 10x5
                        findOneLeaf(ggchild->children[1])->color = 4;
                        findOneLeaf(gchild->children[j==0?1:0])->color = 4; //Un hermano de ggchild.
                        findOneLeaf(g->children[0]->children[i==0?1:0])->color = 4; //Un hermano de gchild
                        findOneLeaf(g->children[1]->children[0])->color = 4; //Dos hijos diferentes en g->children[1]
                        findOneLeaf(g->children[1]->children[1])->color = 4;
                        return false;                                               //Línea 11
                    }
                }
            }
        }
        for(int i = 0; i < g->children[1]->children.size(); i++){                   //Línea 12
            CotreeNode* gchild = g->children[1]->children.at(i);
            if(gchild->tag == -1)
                gchild->color = 2;
            else{
                for(int j = 0; j < gchild->children.size(); j++){
                    CotreeNode* ggchild = gchild->children.at(j);
                    if(ggchild->tag == -1)
                        ggchild->color = 2;
                    else{
                        findOneLeaf(ggchild->children[0])->color = 4;
                        findOneLeaf(ggchild->children[1])->color = 4;
                        findOneLeaf(gchild->children[j==0?1:0])->color = 4; //Un hermano de ggchild.
                        findOneLeaf(g->children[1]->children[i==0?1:0])->color = 4; //Un hermano de gchild
                        findOneLeaf(g->children[0]->children[0])->color = 4; //Dos hijos diferentes en g->children[0]
                        findOneLeaf(g->children[0]->children[1])->color = 4;
                        return false;
                    }
                }
            }
        }
    }
    else{                                                                           //Línea 13
        for(int i = 0; i < g->children.size(); i++){                                //Línea 14
            CotreeNode *child = g->children[i];
            if(!es_bipartita_completa(child)){                                      //Línea 15
                int hermano_aux = hermano_que_no_es_hoja(g,i);
                findOneLeaf(g->children[hermano_aux]->children[0])->color = 3;      //Línea 16x3. Dos hojas diferentes en un hermano de child
                findOneLeaf(g->children[hermano_aux]->children[1])->color = 3;
                //Elegimos un hijo en un hermano diferente.
                hermano_aux = i!=0&&hermano_aux!=0?0:(i!=1&&hermano_aux!=1?1:2);
                findOneLeaf(g->children[hermano_aux])->color = 3;
                return false;                                                       //Línea 17
            }
        }
    }
    return true;                                                                    //Línea 18
}

//***************************************************************************************************************
//IMPLEMENTACIÓN DEL ALGORITMO 7
//  I:g, la raíz de un coárbol cuya raíz tiene etiqueta 0 y sólo uno de sus hijos no es una hoja.
//  O:verdadero si el coárbol con raíz en g representa una gráfica que pertenece a M2. Se colorean las hojas
//    del árcol con raíz g.
//      -
//***************************************************************************************************************

bool M2_Certifier::m2_caso_2(CotreeNode *g){
    CotreeNode* aux_gchild = nullptr;                                               //Línea 1
    int aux_gchild_index = -1;
    int ggchildren_no_hojas = 0;                                                    //Línea 2
    for(int i = 0; i < g->children.size(); i++){                                    //Línea 3
        CotreeNode* child = g->children[i];
        if(child->tag == -1)                                                        //Línea 4
            child->color = 1;                                                       //Línea 5
        else{                                                                       //Línea 6
            for(int j = 0; j < child->children.size(); j++){                        //Línea 7
                CotreeNode* gchild = child->children[j];
                if(gchild->tag == -1)                                               //Línea 8
                    gchild->color = 2;                                              //Línea 9
                else{                                                               //Línea 10
                    for(int k = 0; k < gchild->children.size(); k++){               //Línea 11
                        CotreeNode* ggchild = gchild->children[k];
                        if(ggchild->tag == -1)                                      //Línea 12
                            ggchild->color = 2;                                     //Línea 13
                        else if(aux_gchild == nullptr || aux_gchild == gchild){     //Línea 14
                            aux_gchild = gchild;                                    //Línea 15
                            aux_gchild_index = k;
                            ggchildren_no_hojas++;                                  //Línea 16
                        }
                        else{                                                       //Línea 17
                            g->children[i==0?1:0]->color = 5;                       //Línea 18x8 Un hijo de g que es una hoja.
                            findOneLeaf(ggchild->children[0])->color = 5;           //Dos hojas cuyo acmp es ggchild.
                            findOneLeaf(ggchild->children[1])->color = 5;
                            findOneLeaf(gchild->children[(k+1)%gchild->children.size()])->color = 5; //Una hoja en un hermano de ggchild.
                            int aux = hijo_no_hoja(aux_gchild);
                            findOneLeaf(aux_gchild->children[aux]->children[0])->color = 5;//Dos hojas cuyo acmp es un hijo de aux_gchild que no es una hoja.
                            findOneLeaf(aux_gchild->children[aux]->children[1])->color = 5;
                            findOneLeaf(aux_gchild->children[(aux+1)%aux_gchild->children.size()])->color = 5; //Una hoja en un hijo de aux_child diferente del anterior.
                            return false;                                           //Línea 19
                        }
                    }
                }
            }
            if(ggchildren_no_hojas == 0)                                            //Línea 20
                return true;                                                        //Línea 21
            else if(ggchildren_no_hojas == 1)                                       //Línea 22
                return m2_caso_2(aux_gchild);                                       //Línea 23
            else{                                                                   //Línea 24
                for(int i = 0; i < aux_gchild->children.size(); i++){               //Línea 25
                    CotreeNode *ggchild = aux_gchild->children[i];
                    if(!es_bipartita_completa(ggchild)){                            //Línea 26
                        CotreeNode *hermano_aux = aux_gchild->children[hermano_que_no_es_hoja(aux_gchild, i)];
                        findOneLeaf(hermano_aux->children[0])->color = 3;                      //Línea 27x3 Dos hojas cuyo acmp es un hermano de ggchild
                        findOneLeaf(hermano_aux->children[1])->color = 3;
                        findOneLeaf(g->children[i==0?1:0])->color = 3;  //Un hijo de g que es una hoja.
                        return false;                                               //Línea 28
                    }
                }
            }
        }
    }
    return true;
}


//***************************************************************************************************************
//IMPLEMENTACIÓN DEL ALGORITMO 7
//  I:g, la raíz de un coárbol cuya raíz tiene etiqueta 0 y sólo uno de sus hijos no es una hoja.
//  O:verdadero si el coárbol con raíz en g representa una gráfica que pertenece a M2. Se colorean las hojas
//    del árcol con raíz g.
//      -
//***************************************************************************************************************

bool M2_Certifier::find_m2_partition(CotreeNode *g){
    if(g->tag == -1){                                                           //Línea 1
        g->color = 1;                                                           //Línea 2
        return true;                                                            //Línea 3
    }
    else if(g->tag == 1){                                                       //Línea 4
        for(int i = 0; i < g->children.size(); i++)                             //Línea 5
            if(!find_m2_partition(g->children[i]))                              //Línea 6
                return false;                                                   //Línea 7
        return true;                                                            //Línea 8
    }
    else{                                                                       //Línea 9
        int componentes_no_triviales = 0;                                       //Línea 10
        for(int i = 0; i < g->children.size(); i++){                            //Línea 11
            if(g->children[i]->tag == -1){                                      //Línea 12
                g->children[i]->color = 1;                                      //Línea 13
            }
            else                                                                //Línea 14
                componentes_no_triviales++;                                     //Línea 15
        }
        if(componentes_no_triviales == 0)                                       //Línea 16
            return true;                                                        //Línea 17
        else if(componentes_no_triviales == 1)                                  //Línea 18
            return m2_caso_2(g);                                                //Línea 19
        else                                                                    //Línea 20
            return m2_caso_1(g);                                                //Línea 21
    }
}

