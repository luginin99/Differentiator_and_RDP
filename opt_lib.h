#ifndef _OPT_LIB_H
#define _OPT_LIG_H
#include "treelib_char.h"

class Optimization
{
    public:
    Tree* Optimize    (Tree* tr);
    Node* DestroyZero (Node* nd);
    Node* DestroyOne  (Node* nd);
    Node* ReduceConst (Node* nd);
};







#include "opt.cpp"
#endif // _OPT_LIB_H

