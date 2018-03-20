#ifndef _RDP_H
#define _RDP_H

#include <stdio.h>
#include "treelib_char.h"


#define BEGIN_SIN_OR_SH 's'
#define CONTINUE_SIN 'i'
#define CONTINUE_SH 'h'
#define BEGIN_COS_OR_CH_OR_CTG 'c'
#define CONTINUE_COS 'o'
#define CONTINUE_CH 'h'
#define CONTINUE_CTG 't'
#define BEGIN_TAN_OR_TH 't'
#define CONTINUE_TAN 'a'
#define CONTINUE_TH 'h'
#define IS_LOG 'l'
#define IS_FUNC (!isdigit((*buf)[*i])&&((((*buf)[(*i)+1]) == 'i') || (((*buf)[(*i)+1]) == 'h') || (((*buf)[(*i)+1]) == 'o') || (((*buf)[(*i)+1]) == 't') || (((*buf)[(*i)+1]) == 'a')))

class RDP
{
    public:
    Tree* Scan (char** buf, int* i);
    Node* GetN  (char** buf, int* i);
    Node* GetP  (char** buf, int* i);
    Node* GetE  (char** buf, int* i);
    Node* GetD (char** buf, int* i);
    Node* GetT  (char** buf, int* i);
    Node* GetGo (char** buf, int* i);


};






#include "RDP.cpp"
#endif // _RDP_H
