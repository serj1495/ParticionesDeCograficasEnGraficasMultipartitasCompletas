#ifndef M2_CERTIFIER_H
#define M2_CERTIFIER_H

#include "cotreenode.h"

class M2_Certifier
{
public:
    static bool find_m2_partition(CotreeNode *g);
//private:
    static CotreeNode* findOneLeaf(CotreeNode *g);
    static bool es_bipartita_completa(CotreeNode *g);
    static bool m2_caso_1(CotreeNode *g);
    static bool m2_caso_2(CotreeNode *g);
    static int hermano_que_no_es_hoja(CotreeNode *padre, int indice_hijo);
    static int hijo_no_hoja(CotreeNode *g);

};

#endif // M2_CERTIFIER_H
