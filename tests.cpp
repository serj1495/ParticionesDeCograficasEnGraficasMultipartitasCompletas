#include<iostream>
#include "nontaggedcotreenode.h"
#include "cotreenode.h"
#include "binarycotreenode.h"
#include "subcographfinder.h"
#include "m2_identifier.h"
#include "m2_certifier.h"
#include "skm2_finder.h"


void test_permutations(int n){
    vector<int> *permutacion = new vector<int>;

    for(int i = 0; i < n; i++)
        permutacion->push_back(1);
    int total = 0;

    while (permutacion != nullptr){
        total++;
        for(int i = 0; i < permutacion->size(); i++)
            cout << permutacion->at(i) << ",";
        cout << endl;
        permutacion = NonTaggedCotreeNode::nextPermutation(permutacion);
    }
    cout << "Total de permutaciones: " << total+1 << endl;
}

void test_nextTree(int n){
    vector<int> *permutacion = new vector<int>;

    for(int i = 0; i < n; i++)
        permutacion->push_back(1);

    NonTaggedCotreeNode t;
    t.rebuild(permutacion);
    t.print(0);
    cout << endl;

    int total = 1;

    while(NonTaggedCotreeNode::nextTree(&t) != nullptr){
        total++;
        t.print(0);
        cout << endl;
    }

    cout << "Total de coárboles no etiquetados generados: " << total << endl;

}

void testCotreeConstructor(int n, int tag){
    vector<int> *permutacion = new vector<int>;

    for(int i = 0; i < n; i++)
        permutacion->push_back(1);

    NonTaggedCotreeNode t;
    t.rebuild(permutacion);
    CotreeNode *etiquetado = new CotreeNode(&t,tag);

    int total = 1;

    while(NonTaggedCotreeNode::nextTree(&t) != nullptr){
        total++;
        etiquetado = new CotreeNode(&t,0);
        etiquetado->print(0);
        cout << endl;
        etiquetado->~CotreeNode();
    }

    cout << "Total de coárboles generados: " << total << endl;
}

void testCrearArbolBinario(int n){
    vector<int> *permutacion = new vector<int>;

    for(int i = 0; i < n; i++)
        permutacion->push_back(1);

    NonTaggedCotreeNode t;
    t.rebuild(permutacion);

    CotreeNode *etiquetado = new CotreeNode(&t,0);
    BinaryCotreeNode *b = BinaryCotreeNode::crearCoarbolBinario(etiquetado);
    b->print(0);
    cout << endl;
    etiquetado->~CotreeNode();
    free(etiquetado);
    b->~BinaryCotreeNode();
    free(b);

    while(NonTaggedCotreeNode::nextTree(&t) != nullptr){
        etiquetado = new CotreeNode(&t,0);
        b = BinaryCotreeNode::crearCoarbolBinario(etiquetado);
        b->print(0);
        cout << endl;
        etiquetado->~CotreeNode();
        free(etiquetado);
        b->~BinaryCotreeNode();
        free(b);
    }
}

void testSubcotreeFinder(int n){ //Despliega los coárboles con n hojas y su árbol de verificación para P3 complemento

    //Creamos la obstrucción para las MPC
    BinaryCotreeNode *p3_c_r = new BinaryCotreeNode(0,3);
    p3_c_r->setLchild(-1,1);
    p3_c_r->setRchild(1,2);
    p3_c_r->rchild->setLchild(-1,1);
    p3_c_r->rchild->setRchild(-1,1);

    //Creamos el verificador
    SubcotreeFinder finder;
    finder.addBinaryObstruction(p3_c_r);

    //Creamos los coárboles con n hojas
    vector<int> *permutacion = new vector<int>;
    for(int i = 0; i < n; i++)
        permutacion->push_back(1);
    NonTaggedCotreeNode t;
    t.rebuild(permutacion);

    CotreeNode *etiquetado = new CotreeNode(&t,1);
    BinaryCotreeNode *b = BinaryCotreeNode::crearCoarbolBinario(etiquetado);
    funver *f = finder.funcionDeVerificacion(b, 0);

    //Imprimimos el primer resultado
    etiquetado->print(0);
    cout << endl;
    SubcotreeFinder::printFunVer(f, p3_c_r, 0);

    while(NonTaggedCotreeNode::nextTree(&t) != nullptr){
        cout << endl << endl;

        //Creamos el coárbol y el coárbol binario.
        etiquetado = new CotreeNode(&t,1);
        b = BinaryCotreeNode::crearCoarbolBinario(etiquetado);
        funver *f = finder.funcionDeVerificacion(b, 0);

        //Imprimimos.
        etiquetado->print(0);
        cout << endl;
        SubcotreeFinder::printFunVer(f, p3_c_r, 0);

        //Limpiamos.
        etiquetado->~CotreeNode();
        free(etiquetado);
        b->~BinaryCotreeNode();
        free(b);
    }


}


void testContainsSubcograph(int n){
    //Creamos la obstrucción para las MPC
    BinaryCotreeNode *p3_c_r = new BinaryCotreeNode(0,3);
    p3_c_r->setLchild(-1,1);
    p3_c_r->setRchild(1,2);
    p3_c_r->rchild->setLchild(-1,1);
    p3_c_r->rchild->setRchild(-1,1);

    //Creamos el verificador
    SubcotreeFinder finder;
    finder.addBinaryObstruction(p3_c_r);

    //Creamos los coárboles con n hojas
    vector<int> *permutacion = new vector<int>;
    for(int i = 0; i < n; i++)
        permutacion->push_back(1);
    NonTaggedCotreeNode t;
    t.rebuild(permutacion);

    CotreeNode *etiquetado = new CotreeNode(&t,0);
    //Imprimimos el primer resultado
    etiquetado->print(0);
    cout << (finder.containsSubcograph(etiquetado)?"NO ES MPC":"ES MPC") << endl << endl;
    etiquetado->~CotreeNode();
    free(etiquetado);

    etiquetado = new CotreeNode(&t,1);
    //Imprimimos el primer resultado
    etiquetado->print(0);
    cout << (finder.containsSubcograph(etiquetado)?"NO ES MPC":"ES MPC") << endl << endl;
    etiquetado->~CotreeNode();
    free(etiquetado);

    while(NonTaggedCotreeNode::nextTree(&t) != nullptr){

        etiquetado = new CotreeNode(&t,0);
        etiquetado->print(0);
        cout << (finder.containsSubcograph(etiquetado)?"NO ES MPC":"ES MPC") << endl << endl;
        //Limpiamos.
        etiquetado->~CotreeNode();
        free(etiquetado);

        etiquetado = new CotreeNode(&t,1);
        etiquetado->print(0);
        cout << (finder.containsSubcograph(etiquetado)?"NO ES MPC":"ES MPC") << endl << endl;
        //Limpiamos.
        etiquetado->~CotreeNode();
        free(etiquetado);

    }
}

void testM2_identifier(int n){
    M2_Identifier identificador;

    //Creamos los coárboles con n hojas
    vector<int> *permutacion = new vector<int>;
    for(int i = 0; i < n; i++)
        permutacion->push_back(1);
    NonTaggedCotreeNode t;
    t.rebuild(permutacion);

    CotreeNode *etiquetado = new CotreeNode(&t,0);
    etiquetado->print(0);
    cout  << (identificador.isInM2(etiquetado)?"ESTÁ EN M2":"NO ESTÁ EN M2") << endl << endl;
    etiquetado->~CotreeNode();
    free(etiquetado);

    etiquetado = new CotreeNode(&t,1);
    etiquetado->print(0);
    cout  << (identificador.isInM2(etiquetado)?"ESTÁ EN M2":"NO ESTÁ EN M2") << endl << endl;
    etiquetado->~CotreeNode();
    free(etiquetado);

    while(NonTaggedCotreeNode::nextTree(&t) != nullptr){

        etiquetado = new CotreeNode(&t,0);
        etiquetado->print(0);
        cout << (identificador.isInM2(etiquetado)?"ESTÁ EN M2":"NO ESTÁ EN M2") << endl << endl;
        //Limpiamos.
        etiquetado->~CotreeNode();
        free(etiquetado);

        etiquetado = new CotreeNode(&t,1);
        etiquetado->print(0);
        cout << (identificador.isInM2(etiquetado)?"ESTÁ ENTÁ EN M2":"NO ESTÁ EN M2") << endl << endl;
        //Limpiamos.
        etiquetado->~CotreeNode();
        free(etiquetado);

    }

}

void test_certificador(int n){
    //Creamos los coárboles con n hojas
    vector<int> *permutacion = new vector<int>;
    for(int i = 0; i < n; i++)
        permutacion->push_back(1);
    NonTaggedCotreeNode t;
    t.rebuild(permutacion);

    int i = 0;
    CotreeNode *etiquetado;
    do{
        etiquetado = new CotreeNode(&t,0); //CREAMOS EL ÁRBOL CON RAÍZ 0
        bool esM2 = M2_Certifier::find_m2_partition(etiquetado);
        etiquetado->print(0);
        cout << (esM2?"ESTÁ EN M2":"NO ESTÁ EN M2") << endl << endl;
        etiquetado->~CotreeNode();
        free(etiquetado);

        etiquetado = new CotreeNode(&t,1); //CREAMOS EL ÁRBOL CON RAÍZ 1
        esM2 = M2_Certifier::find_m2_partition(etiquetado);
        etiquetado->print(0);
        cout << (esM2?"ESTÁ EN M2":"NO ESTÁ EN M2") << endl << endl;
        etiquetado->~CotreeNode();
        free(etiquetado);

    }while(NonTaggedCotreeNode::nextTree(&t) != nullptr);
}

void test_coherencia(int n){
    M2_Identifier identificador;
    //Creamos los coárboles con n hojas
    vector<int> *permutacion = new vector<int>;
    for(int i = 0; i < n; i++)
        permutacion->push_back(1);
    NonTaggedCotreeNode t;
    t.rebuild(permutacion);

    int i = 0;
    CotreeNode *etiquetado;
    do{
        etiquetado = new CotreeNode(&t,0); //CREAMOS EL ÁRBOL CON RAÍZ 0
        if(identificador.isInM2(etiquetado) != M2_Certifier::find_m2_partition(etiquetado)){
            cout << "EL RESULATDO NO ES COHERENTE" << endl;
            etiquetado->print(0);
        }
        etiquetado->~CotreeNode();
        free(etiquetado);

        etiquetado = new CotreeNode(&t,1); //CREAMOS EL ÁRBOL CON RAÍZ 1
        if(identificador.isInM2(etiquetado) != M2_Certifier::find_m2_partition(etiquetado)){
            cout << "EL RESULATDO NO ES COHERENTE" << endl;
            etiquetado->print(0);
        }
        etiquetado->~CotreeNode();
        free(etiquetado);

        if((++i)%1000 == 0)
            cout << i << " procesados." << endl;

    }while(NonTaggedCotreeNode::nextTree(&t) != nullptr);
}

void test_cpm(int n){
    //Creamos los coárboles con n hojas

    NonTaggedCotreeNode t;
    t.crearPrimerCoarbol(n);
    CotreeNode *etiquetado;

    do{
        for(int j = 0; j < 2; j++){
            etiquetado = new CotreeNode(&t,j);
            if(M2_Certifier::find_m2_partition(etiquetado)){ //Primero revisamos si está en M2
                etiquetado->print(0);
                vector<pair<int,int>*> *ans = skm2_finder::cpm(etiquetado);
                cout << "{";
                for(int i = 0; i < ans->size(); i++)
                        cout << "(" << ans->at(i)->first << "," << ans->at(i)->second << ")" << (i==ans->size()-1?"":", ");
                cout << "}" << endl << endl;
                for(int i = 0; i < ans->size(); i++){
                    ans->at(i)->~pair();
                    free(ans->at(i));
                }
                ans->~vector();
                free(ans);
            }
            etiquetado->~CotreeNode();
            free(etiquetado);
        }


    }while(NonTaggedCotreeNode::nextTree(&t) != nullptr);
}

void test_skM2_Identifier(int n, int s, int k){
    //Creamos los coárboles con n hojas
    vector<int> *permutacion = new vector<int>;
    for(int i = 0; i < n; i++)
        permutacion->push_back(1);
    NonTaggedCotreeNode t;
    t.rebuild(permutacion);

    int i = 0;
    CotreeNode *etiquetado;
    do{
        etiquetado = new CotreeNode(&t,0); //CREAMOS EL ÁRBOL CON RAÍZ 0
        bool esM2 = M2_Certifier::find_m2_partition(etiquetado);
        etiquetado->print(0);
        if(esM2){
            cout << "ESTÁ EN M2" << endl << (skm2_finder:: isSKM2(etiquetado, make_pair(s,k))?"ESTÁ EN (":"NO ESTÄ EN (") << s << "," << k << ")-M2" << endl << endl;
        }
        else
            cout << "NO ESTÁ EN M2" << endl << endl;
        etiquetado->~CotreeNode();
        free(etiquetado);

        etiquetado = new CotreeNode(&t,1); //CREAMOS EL ÁRBOL CON RAÍZ 1
        esM2 = M2_Certifier::find_m2_partition(etiquetado);
        etiquetado->print(0);
        if(esM2){
            cout << "ESTÁ EN M2" << endl << (skm2_finder:: isSKM2(etiquetado, make_pair(s,k))?"ESTÁ EN (":"NO ESTÄ EN (") << s << "," << k << ")-M2" << endl << endl;
        }
        else
            cout << "NO ESTÁ EN M2" << endl << endl;
        etiquetado->~CotreeNode();
        free(etiquetado);

    }while(NonTaggedCotreeNode::nextTree(&t) != nullptr);
}
