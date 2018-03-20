
#define REDUCE_LEAF  nd->LPush (ReduceConst (nd->left));\
                     nd->RPush (ReduceConst (nd->right));

#define DELETE_LEAF  delete (nd->left);\
                     nd->left = NULL;\
                     delete (nd->right);\
                     nd->right = NULL;

#define DESTROY_ZERO_LEAF    if (nd->left) nd->LPush (DestroyZero (nd->left));\
                             if (nd->right) nd->RPush (DestroyZero (nd->right));

#define DESTROY_ONE_LEAF     if (nd->left) nd->LPush (DestroyOne (nd->left));\
                             if (nd->right) nd->RPush (DestroyOne (nd->right));


Tree* Optimization::Optimize(Tree* tr)
{
    tr->head = ReduceConst(tr->head);
    tr->head = DestroyZero(tr->head);
    tr->head = DestroyOne (tr->head);

}

Node* Optimization::ReduceConst(Node* nd)
{
    switch (nd->flag)
    {
    case FUNC:
        {
            switch (nd->value)
            {
            case MUL:
                {
                    if (!nd->IsLeaf())
                    {
                    REDUCE_LEAF;
                    if (nd->left->flag == NUM && nd->right->flag == NUM)
                        {
                        nd->flag = NUM;
                        nd->value = nd->left->value * nd->right->value;
                        DELETE_LEAF;
                        }
                    }
                    return nd;
                }
            case SUM:
                {
                    if (!nd->IsLeaf())
                    {
                    REDUCE_LEAF;
                    if (nd->left->flag == NUM && nd->right->flag == NUM)
                        {
                        nd->flag = NUM;
                        nd->value = nd->left->value + nd->right->value;
                        DELETE_LEAF;
                        }
                    }
                    return nd;
                }
            case SUB:
                {
                    if (!nd->IsLeaf())
                    {
                    REDUCE_LEAF;
                    if (nd->left->flag == NUM && nd->right->flag == NUM)
                        {
                        nd->flag = NUM;
                        nd->value = nd->left->value - nd->right->value;
                        DELETE_LEAF;
                        }
                    }
                    return nd;
                }
            case DIV:
                {
                    if (!nd->IsLeaf())
                    {
                    REDUCE_LEAF;
                    if (nd->left->flag == NUM && nd->right->flag == NUM)
                        {
                        nd->flag = NUM;
                        nd->value = nd->left->value + nd->right->value;
                        DELETE_LEAF;
                        }
                    }
                    return nd;
                }
            }
        }
    }
    return nd;

}


Node* Optimization::DestroyOne (Node* nd)
{
     if (nd->flag == FUNC)
    {
        switch (nd->value)
            {
        case MUL:
            {
                DESTROY_ONE_LEAF;
                if ((nd->left->flag == NUM) && nd->left->value == 1)
                {
                    delete (nd->left);
                    nd->left = NULL;
                    return DestroyOne (nd->right);
                }
                if ((nd->right->flag == NUM) && nd->right->value == 1)
                {
                    delete nd->right;
                    nd->right = NULL;
                    return DestroyOne (nd->left);
                }
                return nd;
            }
        case DIV:
            {
                DESTROY_ONE_LEAF;
                return nd;
            }
        case SUM:
            {
                DESTROY_ONE_LEAF;
                return nd;
            }
        case SUB:
            {
                DESTROY_ONE_LEAF;
                return nd;
            }
        case POW:
            {
                if (nd->right->flag == NUM && nd->right->value == 1)
                {
                    delete (nd->right);
                    nd->right = NULL;
                    return nd->left;
                }
                return nd;
            }
            }
    }
    return nd;

}

Node* Optimization::DestroyZero(Node* nd)
{
    if (nd->flag == FUNC)
    {
        switch (nd->value)
            {
        case MUL:
            {
                DESTROY_ZERO_LEAF;
                if ((nd->left->flag == NUM && nd->left->value == 0) || (nd->right->flag == NUM && nd->right->value == 0))
                {
                    nd->flag = NUM;
                    nd->value = 0;
                    DELETE_LEAF;
                    return nd;
                }
                return nd;
            }
        case DIV:
            {
                DESTROY_ZERO_LEAF;
                if ((nd->left->flag == NUM) && nd->left->value == 0)
                {
                    nd->flag = NUM;
                    nd->value = 0;
                    DELETE_LEAF;
                    return nd;
                }
                return nd;
            }
        case SUM:
            {
                DESTROY_ZERO_LEAF;
                if ((nd->left->flag == NUM) && nd->left->value == 0)
                {
                    delete (nd->left);
                    nd->left = NULL;
                    return DestroyZero (nd->right);
                }
                if ((nd->right->flag == NUM) && nd->right->value == 0)
                {
                    delete nd->right;
                    nd->right = NULL;
                    return DestroyZero (nd->left);
                }
                return nd;
            }
        case SUB:
            {
                DESTROY_ZERO_LEAF;
                if ((nd->right->flag == NUM) && nd->right->value == 0)
                {
                    delete nd->right;
                    nd->right = NULL;
                    return DestroyZero (nd->left);
                }
                return nd;
            }
            }
    }
    return nd;

}

