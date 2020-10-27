#include "skm2_finder.h"

skm2_finder::skm2_finder()
{

}

int skm2_finder::contar_max_1_k(CotreeNode *g){
    int hijos_de_1 = 0;
    int non_trivial_child = 0;
    CotreeNode *w = nullptr;

    for(int i = 0; i < g->children.size(); i++){
        if(g->children[i]->tag == 1){
            CotreeNode *child = g->children[i];
            non_trivial_child ++;
            for(int j = 0; j < child->children.size(); j++){
                CotreeNode *gchild = child->children[j];
                hijos_de_1++;
                if(gchild->tag != -1){
                    for(int k = 0; k < gchild->children.size(); k++){
                        CotreeNode *ggchild = gchild->children[k];
                        if(ggchild->tag != -1){
                            w = gchild;
                        }
                    }
                }
            }
        }
    }

    if(non_trivial_child > 1){
        //cout <<"Caso 1" << endl;
        return 1;
    }
    else if(w == nullptr){
        //cout <<"Caso 2" << endl;
        return hijos_de_1-1;
    }
    else{
        return hijos_de_1 - 1 + contar_max_1_k(w);
    }
}

vector<pair<int, int>*>* skm2_finder::cpm(CotreeNode *g){
    vector<pair<int, int>*>* ans = new vector<pair<int,int>*>();
    if(g->tag == -1){
        ans->push_back(new pair<int,int>(0,1));
    }
    else if(g->tag == 1){
        ans->push_back(new pair<int,int>(0,0));
        for(int i = 0; i < g->children.size(); i++){
            vector<pair<int, int>*>* local = cpm(g->children[i]);
            //cout << "local: ";
            //for(int j = 0; j < local->size(); j++)
            //    cout << "(" << local->at(j)->first << ", " << local->at(j)->second << "), " << endl;

            vector<pair<int,int>*> *aux1 = new vector<pair<int,int>*>(), *aux2 = new vector<pair<int,int>*>();
            aux1->reserve(ans->size());
            aux2->reserve(ans->size());
            vector<bool> entran_1;
            vector<bool> entran_2;
            entran_1.reserve(ans->size());
            entran_2.reserve(ans->size());
            for(int j = 0; j < ans->size(); j++){
                int s1 = ans->at(j)->first;
                int k1 = ans->at(j)->second;
                int s2 = local->at(0)->first;
                int k2 = local->at(0)->second;
                aux1->push_back(new pair<int,int>(s1+s2,k1+k2));
                aux2->push_back(new pair<int,int>(min(s1+k2,s2+k1),max(s1+k2,s2+k1)));
                free(ans->at(j));
            }
            delete(ans);
            ans = new vector<pair<int,int>*>();

            for(int j = 0; j < aux1->size(); j++){
                entran_1.push_back(true);
                entran_2.push_back(true);
            }

            for(int j = 0; j < aux1->size(); j++){
                for(int k = 0; k < aux2->size(); k++){
                    if(aux1->at(j)->first == aux2->at(k)->first && aux1->at(j)->second == aux2->at(k)->second){
                        entran_2.at(k) = false;
                    }
                    else if(domina(aux1->at(j), aux2->at(k))){
                        entran_1.at(j) = false;
                    }
                    else if(domina(aux2->at(k), aux1->at(j))){
                        entran_2.at(k);
                    }
                }
            }

            for(int j = 0; j < aux1->size(); j++){
                if(entran_1.at(j))
                    ans->push_back(aux1->at(j));
                else
                    free(aux1->at(j));
            }
            for(int j = 0; j < aux2->size(); j++){
                if(entran_2.at(j))
                    ans->push_back(aux2->at(j));
                else
                    free(aux2->at(j));
            }

            free(aux1);
            free(aux2);
            free(local->at(0));
            free(local);
        }
    }
    else{
        int componentes_no_triviales = 0;
        for(int i = 0; i < g->children.size(); i++){
            if(g->children[i]->tag == -1){
                g->children[i]->color = 1;
            }
            else
                componentes_no_triviales++;
        }
        if(componentes_no_triviales == 0){
            ans->push_back(new pair<int,int>(0,1));
        }
        else if(componentes_no_triviales == 1){
            ans->push_back(new pair<int,int>(1,contar_max_1_k(g)));
        }
        else if (g->children.size() == 2){ //Sabemos que hay al menos dos no triviales. Si esas dos son  las únicas, se cumple esta condición
            int s = g->children[0]->children.size();
            int k = g->children[1]->children.size();
            if(s == 2 && k == 2)
                ans->push_back(new pair<int,int>(1,1));
            else
                ans->push_back(new pair<int,int>(min(s,k),max(s,k)));
        }
        else{
            ans->push_back(new pair<int,int>(1,1));
        }
    }
    return ans;
}

bool skm2_finder::domina(pair<int, int>* x, pair<int, int>* y){
    if(x->first >= y->first && x->second >= y->second)
        return true;
    return false;
}

bool skm2_finder:: isSKM2(CotreeNode *g, pair<int,int> sk){
    bool ans = false;
    //g->print(0);
    vector<pair<int, int>*> * cpm_g = cpm(g);

    for(int i = 0; i < cpm_g->size(); i++){
        //cout << "(" << cpm_g->at(i)->first << "," << cpm_g->at(i)->second << "), ";
        ans |= domina(&sk,cpm_g->at(i));
        cpm_g->at(i)->~pair();
        free(cpm_g->at(i));
    }

    //cout << endl;

    cpm_g->~vector();
    free(cpm_g);
    return ans;
}

void skm2_finder::print_obstructions(pair<int,int> sk){
    int total = 0;
    //int cota_superior = (sk.first + sk.second + 1)*(sk.first + sk.second + 1);
    int cota_superior = 14; //Por comodidad.
    //int contador = 0; //Nos sirve para identificar una gráfica en específico.
    for(int i = 2; i <= cota_superior; i++){
        NonTaggedCotreeNode t;
        t.crearPrimerCoarbol(i);
        CotreeNode *etiquetado;

        do{
            //contador++;
            //if(contador != 3447)
            //    continue;

            etiquetado = new CotreeNode(&t,0); //CREAMOS EL ÁRBOL CON RAÍZ 0
            if(M2_Certifier::find_m2_partition(etiquetado)){
                if(!isSKM2(etiquetado, sk)){
                    //Ahora revisamos que sea mínimo.
                    vector<CotreeNode*>* hojas = listar_hojas(etiquetado);
                    bool es_minimo = true;
                    for(int j = 0; j < hojas->size(); j++){
                        CotreeNode *copia = copiar_sin(etiquetado, hojas->at(j));
                        if(!isSKM2(copia, sk)){
                            es_minimo = false;
                            break;
                        }
                        copia->~CotreeNode();
                        free(copia);

                    }
                    if(es_minimo){
                        total++;
                        etiquetado->print(0);
                        cout << endl;
                    }
                    delete(hojas);
                }
            }
            etiquetado->~CotreeNode();
            free(etiquetado);


            etiquetado = new CotreeNode(&t,1); //CREAMOS EL ÁRBOL CON RAÍZ 1
            if(M2_Certifier::find_m2_partition(etiquetado)){
                if(!isSKM2(etiquetado, sk)){
                    //Ahora revisamos que sea mínimo.
                    //etiquetado->print(0);
                    vector<CotreeNode*>* hojas = listar_hojas(etiquetado);
                    bool es_minimo = true;
                    for(int j = 0; j < hojas->size(); j++){
                        CotreeNode *copia = copiar_sin(etiquetado, hojas->at(j));
                        //cout << endl << "Copia____________________________________________________"<< endl;
                        //copia->print(0);
                        if(!isSKM2(copia, sk)){
                            es_minimo = false;
                            copia->~CotreeNode();
                            free(copia);
                            break;
                        }
                        copia->~CotreeNode();
                        free(copia);
                    }
                    if(es_minimo){
                        total++;
                        etiquetado->print(0);
                        cout << endl;
                    }
                    delete(hojas);
                }
            }
            etiquetado->~CotreeNode();
            free(etiquetado);
        }while(NonTaggedCotreeNode::nextTree(&t) != nullptr);
    }
    cout << "TOTAL: " << total << " Obstrucciones." << endl;
}

vector<CotreeNode *>* skm2_finder::listar_hojas(CotreeNode *g){
    vector<CotreeNode *> *ans = new vector<CotreeNode *>;
    listar_hojas_aux(g, ans);

    return ans;
}

void skm2_finder::listar_hojas_aux(CotreeNode *g, vector<CotreeNode *>* lista){
    if(g->tag == -1){
        if(lista->size() == 0)
            lista->push_back(g);
        else if(lista->back()->parent != g->parent)
            lista->push_back(g);
    }
    else{
        for(int i = 0; i < g->children.size(); i++)
            listar_hojas_aux(g->children[i], lista);
    }
}

CotreeNode* skm2_finder::copiar_sin(CotreeNode* g, CotreeNode* h){
    if(g == h)
        return nullptr;
    else if(g->tag == -1){
        return new CotreeNode();
    }
    else{
        CotreeNode *nuevo = new CotreeNode();
        nuevo->tag = g->tag;
        nuevo->color = g->color;
        nuevo->leaves = 0;
        for(int i = 0; i < g->children.size(); i++){
            CotreeNode *hijo = copiar_sin(g->children.at(i), h);
            if(hijo != nullptr){
                if(nuevo->tag != hijo->tag){
                    hijo->parent = nuevo;
                    nuevo->leaves += hijo->leaves;
                    nuevo->children.push_back(hijo);
                }
                else{
                    for(int j = 0; j < hijo->children.size(); j++){
                        hijo->children[j]->parent = nuevo;
                        nuevo->leaves += hijo->children[j]->leaves;
                        nuevo->children.push_back(hijo->children[j]);
                    }
                }
            }
        }
        if(nuevo->children.size() > 1)
            return nuevo;
        else{
            CotreeNode *aux = nuevo->children.at(0);
            free(nuevo);
            return aux;
        }

    }
}
