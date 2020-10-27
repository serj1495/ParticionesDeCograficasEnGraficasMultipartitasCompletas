#ifndef SKM2_FINDER_H
#define SKM2_FINDER_H

#include "cotreenode.h"
#include "m2_certifier.h"


class skm2_finder
{
public:
    skm2_finder();
    static vector<pair<int, int>*>* cpm(CotreeNode *g);
    static bool isSKM2(CotreeNode *g, pair<int,int> sk);
    static void print_obstructions(pair<int,int> sk);
//pritate:
    static int contar_max_1_k(CotreeNode *g);
    static bool domina(pair<int, int>* x, pair<int, int>* y);
    static vector<CotreeNode *>* listar_hojas(CotreeNode *g);
    static void listar_hojas_aux(CotreeNode *g, vector<CotreeNode *>*);
    static CotreeNode* copiar_sin(CotreeNode* g, CotreeNode* no);
};

#endif // SKM2_FINDER_H
