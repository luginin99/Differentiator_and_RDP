#include <stdio.h>



const int CAPACITY = 50;
const int BRACKET_SHIFT = 2;
const int BEFORESTART = -1;




Node::Node()
{
    root_l = root_r = right = left = NULL;
    flag = 0;
    value = 0;
}



Node::~Node()
{
    flag = 0;
    value = 0;
    if (right) delete right;
    if (left) delete left;
}


int Node::OK ()
{
    if (!this)
        {
            printf ("ERROR pointer is NULL\n");
            return 0;
        }
}

int Node::IsLeaf ()
{
    if (left || right)
        return 0;
    return 1;
}

void Node::LPush(Node* nd)
{
    left = nd;
    nd->root_l = this;
}

void Node::RPush (Node* nd)
{
    right = nd;
    nd->root_r = this;
}

Node* CreateNode (int flag, int value, Node* left, Node* right)
{
    Node* new_nd = new Node();
    new_nd->flag = flag;
    new_nd->value = value;
    if (left)
        new_nd->LPush(left);
    if (right)
        new_nd->RPush(right);
    return new_nd;
}

Node* Node::Copy()
{
    Node* new_nd = new Node();
    new_nd->flag = flag;
    new_nd->value = value;
    if (left)
        new_nd->LPush (left->Copy());
    if (right)
        new_nd->RPush (right->Copy());
    return new_nd;
}

void Node::PrintToFile (FILE* file)
{

    fprintf (file, "(\n");
    fprintf (file, "%d %d\n", flag, value);
    if (left)
        left->PrintToFile (file);
    if (right)
        right->PrintToFile (file);
    fprintf (file,")\n");
}


Tree::Tree ()
{
    head = NULL;
}



Tree::~Tree()
{
    if (head)
        delete head;
}

#define CHOOSE_CUR_SYMB switch (cur->flag)\
    {\
    case NUM:\
        {\
            fprintf (file, "%d [shape = box, style = rounded, color = blue, label = \"%d\"]\n", cur, cur -> value);\
            break;\
        }\
    case FUNC:\
        {\
            switch(cur->value)\
            {\
            case SUM:\
                {\
                    fprintf (file, "%d [shape = box, style = rounded, color = blue, label = \"%c\"]\n", cur, '+');\
                    break;\
                }\
            case SUB:\
                {\
                    fprintf (file, "%d [shape = box, style = rounded, color = blue, label = \"%c\"]\n", cur, '-');\
                    break;\
                }\
            case MUL:\
                {\
                    fprintf (file, "%d [shape = box, style = rounded, color = blue, label = \"%c\"]\n", cur, '*');\
                    break;\
                }\
            case DIV:\
                {\
                    fprintf (file, "%d [shape = box, style = rounded, color = blue, label = \"%c\"]\n", cur, '/');\
                    break;\
                }\
            case POW:\
                {\
                    fprintf (file, "%d [shape = box, style = rounded, color = blue, label = \"%c\"]\n", cur, '^');\
                    break;\
                }\
            case SIN:\
                {\
                    fprintf (file, "%d [shape = box, style = rounded, color = blue, label = \"%s\"]\n", cur, "sin");\
                    break;\
                }\
            case SH:\
                {\
                    fprintf (file, "%d [shape = box, style = rounded, color = blue, label = \"%s\"]\n", cur, "sh");\
                    break;\
                }\
            case COS:\
                {\
                    fprintf (file, "%d [shape = box, style = rounded, color = blue, label = \"%s\"]\n", cur, "cos");\
                    break;\
                }\
            case CH:\
                {\
                    fprintf (file, "%d [shape = box, style = rounded, color = blue, label = \"%s\"]\n", cur, "ch");\
                    break;\
                }\
            case CTG:\
                {\
                    fprintf (file, "%d [shape = box, style = rounded, color = blue, label = \"%s\"]\n", cur, "ctg");\
                    break;\
                }\
            case TAN:\
                {\
                    fprintf (file, "%d [shape = box, style = rounded, color = blue, label = \"%s\"]\n", cur, "tan");\
                    break;\
                }\
            case TH:\
                {\
                    fprintf (file, "%d [shape = box, style = rounded, color = blue, label = \"%s\"]\n", cur, "th");\
                    break;\
                }\
            case LOG:\
                {\
                    fprintf (file, "%d [shape = box, style = rounded, color = blue, label = \"%s\"]\n", cur, "log");\
                    break;\
                }\
            }\
        break;\
        }\
    case VAR:\
        {\
            fprintf (file, "%d [shape = box, style = rounded, color = blue, label = \"%c\"]\n", cur, (cur->value+32));\
            break;\
        }\
    }\

void Tree::DotDump ()
{
    FILE* file = fopen ("graph_dump.txt", "w");
    fprintf (file, "digraph G{\n");
    Node* cur= head;
    CHOOSE_CUR_SYMB;
    cur->Dumper (file);
    fprintf (file, "}");
    fclose (file);
    system ("C:\\Progtam\\bin\\dot.exe -Tpng C:\\Users\\Snax\\Desktop\\c++\\Деференцатор\\graph_dump.txt -o C:\\Users\\Snax\\Desktop\\c++\\Деференцатор\\dump.png");
   // system ("del graph_dump.txt");
    system ("dump.png");
}


int Node::Dumper (FILE* file)
{
    Node* cur = NULL;
    if (left)
    {
        cur = left;
        CHOOSE_CUR_SYMB;
        fprintf (file, "%d -> %d [color = blue]\n", this, left);
        left->Dumper (file);
    }

    if (right)
    {
        cur = right;
        CHOOSE_CUR_SYMB;
        fprintf (file, "%d -> %d [color = blue]\n", this, right);
        right->Dumper (file);
    }

    return 0;
}
