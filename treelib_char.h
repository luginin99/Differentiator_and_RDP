#ifndef _TREELIB_FOR_AK_
#define _TREELIB_FOR_AK_
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <locale.h>

#ifndef _CONST_
#define _CONST_

const int  NUM     = 1;

const int  FUNC    = 2,
            SUM     = 1,
            SUB     = 2,
            MUL     = 3,
            DIV     = 4,
            LOG      = 5,
            POW     = 6,
            SIN     = 7,
            COS     = 8,
            TAN     = 9,
            CTG     = 10,
            SH      = 11,
            CH      = 12,
            TH      = 13;


const int  VAR     = 3,
            X       = 88,
            Y       = 89;

#endif // _CONST_

typedef char*  T;

class Node
{
public:
    Node* right = NULL;
    Node* left = NULL;
    Node* root_l = NULL;
    Node* root_r = NULL;

    char flag;
    int  value;


    void  LPush (Node* nd);
    void  RPush (Node* nd);
    OK();

    Node* Copy();
    Node ();
    ~Node();
    int IsLeaf ();
    void PrintToFile (FILE* file);
    void ScanFromBuf (char** buffer, int* i);
    int  Dumper (FILE* file);

};

class Tree
{
public:

    Node* head;


    void DotDump ();
    Tree();
    ~Tree();

};



#include "tree_char.cpp"
#endif // _TREELIB_FOR_AK_
