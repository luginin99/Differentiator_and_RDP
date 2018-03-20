#include <stdio.h>
#include "treelib_char.h"

Differentiator::Differentiator()
{
};

Node* Differentiator::Diff (Node* nd)
{
    switch (nd->flag)
    {
    case NUM:
        return CreateNode (NUM, 0, NULL, NULL);
    case FUNC:
        switch(nd->value)
        {
        case SUM:
            return CreateNode (FUNC, SUM, Diff(nd->left), Diff(nd->right));
        case SUB:
            return CreateNode (FUNC, SUB, Diff(nd->left), Diff(nd->right));
        case MUL: //u*v=u1*v+v1*u
            {
                Node* u = nd->left->Copy();
                Node* u1 = Diff (u);
                Node* v = nd->right->Copy();
                Node* v1 = Diff (v);
                return CreateNode (FUNC, SUM, CreateNode (FUNC, MUL, u1, v), CreateNode (FUNC, MUL, v1, u));
            }
        case DIV: //u/v = (u1*v-v1*u)/(u*u)
            {
                Node* u = nd->left->Copy();
                Node* u1 = Diff (nd->left);
                Node* v = nd->right->Copy();
                Node* v1 = Diff (nd->right);
                Node* nom = CreateNode (FUNC, SUB, CreateNode (FUNC, MUL, u1, v), CreateNode (FUNC, MUL, v1, u));
                Node* denom = CreateNode (FUNC, MUL, v->Copy(), v->Copy());
                return CreateNode(FUNC, DIV, nom, denom);
            }
        case POW:
            {
                if (nd->left->flag == VAR && nd->left->value == X && nd->right->flag == NUM)
                {
                    Node* u = nd->left->Copy();
                    Node* v = nd->right->Copy ();
                    Node* v_ = CreateNode(NUM, (nd->right->value-1), NULL, NULL);
                    Node* u_ = CreateNode (FUNC, POW, u, v_);
                    return CreateNode (FUNC, MUL, v, u_ );
                }
                Node* u = nd->left->Copy();
                Node* u1 = Diff (u);
                Node* v = nd->right->Copy();
                Node* v1 = Diff (v);
                Node* left_nd = CreateNode(FUNC, POW, u->Copy(), v->Copy() );
                Node* right_left_nd = CreateNode(FUNC, MUL, CreateNode (FUNC, DIV, u1, u->Copy()), v->Copy());
                Node* right_right_nd = CreateNode (FUNC, MUL, v1, CreateNode(FUNC, LOG, NULL, u));
                return CreateNode (FUNC, MUL, left_nd, CreateNode(FUNC, SUM, right_left_nd, right_right_nd));
            }
        case SIN:
            {
                Node* u = nd->right->Copy();
                Node* u1 = Diff (u);
                Node* sin1 = CreateNode(FUNC, COS, NULL, u);
                return CreateNode(FUNC, MUL, sin1, u1);
            }
        case SH:
            {
                Node* u = nd->right->Copy();
                Node* u1 = Diff (u);
                return CreateNode(FUNC, MUL, CreateNode(FUNC, CH, NULL, u), u1);
            }
        case COS:
            {
                Node* u = nd->right->Copy();
                Node* u1 = Diff (u);
                Node* cos1 = CreateNode (FUNC, SUB, CreateNode(NUM, 0, NULL, NULL),CreateNode(FUNC, SIN, NULL, u));
                return CreateNode(FUNC, MUL, cos1, u1);
            }
        case CH:
            {
                Node* u = nd->right->Copy();
                Node* u1 = Diff (u);
                return CreateNode(FUNC, MUL, CreateNode(FUNC, SH, NULL, u), u1);
            }
        case CTG:
            {
                Node* u = nd->right->Copy();
                Node* u1 = Diff (u);
                Node* sin2 = CreateNode(FUNC, POW, CreateNode(FUNC, SIN, NULL, u), CreateNode(NUM, 2, NULL, NULL));
                return CreateNode(FUNC, MUL, CreateNode(FUNC, DIV, CreateNode(NUM, -1, NULL, NULL), sin2), u1);
            }
        case TAN:
            {
                Node* u = nd->right->Copy();
                Node* u1 = Diff (u);
                Node* cos2 = CreateNode(FUNC, POW, CreateNode(FUNC, COS, NULL, u), CreateNode(NUM, 2, NULL, NULL));
                return CreateNode(FUNC, MUL, CreateNode(FUNC, DIV, CreateNode(NUM, 1, NULL, NULL), cos2), u1);
            }
        case TH:
            {
                Node* u = nd->right->Copy();
                Node* u1 = Diff (u);
                Node* ch2 = CreateNode(FUNC, POW, CreateNode(FUNC, CH, NULL, u), CreateNode(NUM, 2, NULL, NULL));
                return CreateNode(FUNC, MUL, CreateNode(FUNC, DIV, CreateNode(NUM, 1, NULL, NULL), ch2), u1);
            }
        case LOG:
            {
                Node* u = nd->right->Copy();
                Node* u1 = Diff (u);
                return CreateNode(FUNC, DIV, u1, u);
            }
        }
    case VAR:
        switch(nd->value)
        {
        case X:
            {
                return CreateNode (NUM, 1, NULL, NULL);
            }
        default:
            {
                return CreateNode (NUM, 0, NULL, NULL);
            }

        }
    }
}


