#ifndef _LIB_FOR_DIF_
#define _LIB_FOR_DIF_

#include "treelib_char.h"

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
#endif

#include "treelib_char.h"

class Differentiator
{
public:

    Differentiator();
    Node* Diff(Node* nd);
};








#include "dif_func.cpp"
#endif // _LIB_FOR_DIF_
