#include "cotreenode.h"

CotreeNode::CotreeNode()
{
    //cout << "Constructor cotreenode" << endl;
}

CotreeNode::CotreeNode(NonTaggedCotreeNode *base, int etiqueta){
    //cout << "Constructor cotreenode" << endl;
    //CotreeNode* parent = nullptr;
    //vector<CotreeNode*> children;
    leaves = base->leaves;
    color = -1;
    children.reserve(base->children.size());
    tag = base->children.size()>0?etiqueta:-1;
    for(int i = 0; i < base->children.size(); i++){
        CotreeNode* hijo = new CotreeNode(base->children.at(i),etiqueta==0?1:0);
        hijo->parent = this;
        children.push_back(hijo);
    }
}

void CotreeNode::print(int level){
    for(int i = 0; i < level; i++)
        cout << ".";
    cout << tag;
    if(color > 0)
        cout  << ", color:" << color;
    cout  << endl;
    for(int i = 0; i < children.size(); i++)
        children.at(i)->print(level+1);
}

CotreeNode::~CotreeNode(){
    //cout << "DESTRUCTOR cotreenode" << endl;
    for(int i = 0; i < children.size(); i++){
        children.at(i)->~CotreeNode();
        free(children.at(i));
    }
}
