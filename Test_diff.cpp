#include <cctype>
#include <cstdlib>
#include "dif_lib.h"
#include <stdio.h>
#include <string.h>
#include "treelib_char.h"
#include "RDP.h"
#include "opt_lib.h"


int main()
{
    Differentiator* dif;
    RDP* rdp;
    Optimization* opt;
    int i = 0;
    char* buf;
    buf = (char*) calloc (sizeof(char),256 );
    scanf ("%s", buf);
    Tree* tr= rdp->Scan(&buf, &i);
    tr->head = dif->Diff (tr->head);
    tr = opt->Optimize(tr);
    tr->DotDump();
}
