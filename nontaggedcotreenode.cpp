#include "nontaggedcotreenode.h"

#include<iostream>
using namespace std;


NonTaggedCotreeNode::NonTaggedCotreeNode()
{

}

NonTaggedCotreeNode::NonTaggedCotreeNode(int l)
{
    children.reserve(l);
}

void NonTaggedCotreeNode::crearPrimerCoarbol(int n){
    for(int i = 0; i < children.size(); i++){
        children.at(i)->~NonTaggedCotreeNode();
        free(children.at(i));
    }
    children = vector<NonTaggedCotreeNode*>();
    children.reserve(n);
    leaves = n;
    for(int i = 0; i < n; i++){
        children.push_back(new NonTaggedCotreeNode(1));
        children.at(i)->parent = this;
        children.at(i)->leaves = 1;
    }
}

void NonTaggedCotreeNode::rebuild(vector<int> *a){


    for(int i = 0; i < children.size(); i++){
        children.at(i)->~NonTaggedCotreeNode();
        free(children.at(i));
    }


    children = vector<NonTaggedCotreeNode*>();
    children.reserve(a->size());
    leaves = 0;

    for(int i = 0; i < a->size(); i++){
        leaves += a->at(i);
        children.push_back(new NonTaggedCotreeNode(a->at(i)));
        children.at(i)->parent = this;
        children.at(i)->leaves = a->at(i);
        if(a->at(i)>1)
            for(int j = 0; j < a->at(i); j++){
                children.at(i)->children.push_back(new NonTaggedCotreeNode());
                children.at(i)->children.at(j)->parent = children.at(i);
            }
    }

}

void NonTaggedCotreeNode::print(int level){
    for(int i = 0; i < level; i++)
        cout << "-";
    cout << leaves << endl;

    for(int i = 0; i < children.size(); i++)
        children.at(i)->print(level+1);
}

void NonTaggedCotreeNode::print(int level, NonTaggedCotreeNode* especial){
    for(int i = 0; i < level; i++)
        cout << "-";
    cout << leaves;

    if(this == especial)
        cout << " <- MARCADO";
    cout << endl;

    for(int i = 0; i < children.size(); i++)
        children.at(i)->print(level+1, especial);
}

bool NonTaggedCotreeNode::is_exhausted(){
    if(children.size() == 0)
        return true;
    if(children.size() == 2 && children.at(0)->leaves == leaves/2 && children.at(1)->leaves == (leaves+1)/2)
        return true;
    return false;
}

NonTaggedCotreeNode* NonTaggedCotreeNode::findPivot(){
    for(int i = children.size()-1; i >= 0; i--){
        NonTaggedCotreeNode* found = children.at(i)->findPivot();
        if(found != nullptr)
            return found;
    }
    return is_exhausted()?nullptr:this;
}

NonTaggedCotreeNode::~NonTaggedCotreeNode(){
    //cout << "DESTRUCTOR nontaggedcotreenode" << endl;
    for(int i = 0; i < children.size(); i++){
        children.at(i)->~NonTaggedCotreeNode();
        free(children.at(i));
    }
}

vector<int>* NonTaggedCotreeNode::nextPermutation(vector<int>* a){
    vector<int> *b = new vector<int>;

    int n = 0;
    for(int i = 0; i < a->size(); i++)
        n += a->at(i);

    if(a->at(0) != n/2){
        if(a->at(a->size()-1) - a->at(a->size()-2) <= 1){
            for(int i = 0; i < a->size()-2; i++)
                b->push_back(a->at(i));
            b->push_back(a->at(a->size()-1)+a->at(a->size()-2));
            return b;
        }else{
            int a_k_1 = a->at(a->size()-2) + 1;
            int a_k = a->at(a->size()-1) - 1;
            int q = a_k/a_k_1;
            int r = a_k%a_k_1;
            if(q>1){
                for(int i = 0; i < a->size()-2; i++)
                    b->push_back(a->at(i));
                for(int i = 0; i < q; i++)
                    b->push_back(a_k_1);
                b->push_back(a_k_1+r);
                return b;
            }
            else{
                for(int i = 0; i < a->size()-2; i++)
                    b->push_back(a->at(i));
                b->push_back(a_k_1);
                b->push_back(a_k);
                return b;
            }
        }
    }
    else{
        if(n!=3)
            return nullptr;
        else{
            if(a->at(1)==((n+1)/2))
                return nullptr;
            else{
                b->push_back(1);
                b->push_back(2);
                return b;
            }
        }
    }

    return b;
}

void NonTaggedCotreeNode::copy_tree(NonTaggedCotreeNode* dest, NonTaggedCotreeNode* orig){
    //We do not copy the parent
    dest->leaves = orig->leaves;
    for(int i = 0; i < dest->children.size(); i++){
        dest->children.at(i)->~NonTaggedCotreeNode();
        free(dest->children.at(i));
    }
    dest->children = vector<NonTaggedCotreeNode*>();
    dest->children.reserve(orig->children.size());
    for(int i = 0; i < orig->children.size(); i++){
        dest->children.push_back(new NonTaggedCotreeNode());
        dest->children.at(i)->parent = dest;
        copy_tree(dest->children.at(i), orig->children.at(i));
    }
}

NonTaggedCotreeNode* NonTaggedCotreeNode::nextTree(NonTaggedCotreeNode* root){
    NonTaggedCotreeNode* v = root->findPivot();
    if(v != nullptr){
        vector<int> a, *b;
        a.reserve(v->children.size());
        for(int i = 0; i < v->children.size(); i++)
            a.push_back(v->children.at(i)->leaves);
        b = nextPermutation(&a);
        v->rebuild(b);
        free(b);
        NonTaggedCotreeNode* x = v;
        while(x->parent != nullptr){
            int number_of_child = 0;
            while(x != x->parent->children.at(number_of_child))
                number_of_child++;
            for(int i = number_of_child+1; i < x->parent->children.size(); i++){
                NonTaggedCotreeNode* y = x->parent->children.at(i);

                if(y->leaves == x->leaves){
                    //cout << "Usa copy" << endl;
                    copy_tree(y,x);
                }
                else{
                    vector<int> c;
                    c.reserve(y->leaves);
                    for(int j = 0; j < y->leaves; j++)
                        c.push_back(1);
                    y->rebuild(&c);
                }
            }
            x = x->parent;
        }
        return root;
    }
    return nullptr;
}
