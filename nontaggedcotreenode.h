#ifndef NONTAGGEDCOTREENODE_H
#define NONTAGGEDCOTREENODE_H

#include<iostream>
#include<vector>
using namespace std;


class NonTaggedCotreeNode{

public:
    NonTaggedCotreeNode* parent = nullptr;
    vector<NonTaggedCotreeNode*> children;
    int leaves = 1;
    NonTaggedCotreeNode();
    NonTaggedCotreeNode(int l);
    ~NonTaggedCotreeNode();
    void crearPrimerCoarbol(int n);
    void rebuild(vector<int> *a);
    void print(int level);
    void print(int level, NonTaggedCotreeNode* especial);
    bool is_exhausted();
    NonTaggedCotreeNode *findPivot();

    static vector<int>* nextPermutation(vector<int>* a);
    static void copy_tree(NonTaggedCotreeNode* dest, NonTaggedCotreeNode* orig);
    static NonTaggedCotreeNode* nextTree(NonTaggedCotreeNode* root);

};

#endif // NONTAGGEDCOTREENODE_H
