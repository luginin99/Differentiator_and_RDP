

Tree* RDP::Scan(char** buf, int* i)
{
    Tree* tr = new Tree();
    tr->head = GetGo (buf, i);
    return tr;
}

Node* RDP::GetN (char** buf, int* i)
{
    char b[256] = {0};
    int j = 0;
    Node* nd = new Node();
    if (IS_FUNC)
    {
    switch (((*buf)[*i]))
        {
        case IS_LOG:
            {
                nd->flag = FUNC;
                nd->value = LOG;
                (*i)+=3;
                nd->RPush (GetP(buf, i));
                break;
            }
        case BEGIN_SIN_OR_SH:
            {
                (*i)++;
                switch (((*buf)[*i]))
                {
                case CONTINUE_SIN:
                    {
                        nd->flag = FUNC;
                        nd->value = SIN;
                        (*i)+=2;
                        nd->RPush (GetP(buf, i));
                        break;
                    }
                case CONTINUE_SH:
                    {
                        nd->flag = FUNC;
                        nd->value = SH;
                        (*i)++;
                        nd->RPush (GetP(buf, i));
                        break;
                    }

                }
                break;
            }
        case BEGIN_COS_OR_CH_OR_CTG:
            {
                (*i)++;
                switch (((*buf)[*i]))
                {
                case CONTINUE_COS:
                    {
                        nd->flag = FUNC;
                        nd->value = COS;
                        (*i)+=2;
                        nd->RPush (GetP(buf, i));
                        break;
                    }
                case CONTINUE_CH:
                    {
                        nd->flag = FUNC;
                        nd->value = CH;
                        (*i)++;
                        nd->RPush (GetP(buf, i));
                        break;
                    }
                case CONTINUE_CTG:
                    {
                        nd->flag = FUNC;
                        nd->value = CTG;
                        (*i)+=2;
                        nd->RPush (GetP(buf, i));
                        break;
                    }
                }
                break;
            }
        case BEGIN_TAN_OR_TH:
            {
                (*i)++;
                switch (((*buf)[*i]))
                {
                case CONTINUE_TAN:
                    {
                        nd->flag = FUNC;
                        nd->value = TAN;
                        (*i)+=2;
                        nd->RPush (GetP(buf, i));
                        break;
                    }
                case CONTINUE_TH:
                    {
                        nd->flag = FUNC;
                        nd->value = TH;
                        (*i)++;
                        nd->RPush (GetP(buf, i));
                        break;
                    }

                }
                break;
            }
        }
    }
    else if (!isdigit((*buf)[*i]))
    {
        nd->flag = VAR;
        nd->value = (int) ((*buf)[*i])-32;
        (*i)++;
    }
    else
    {
        while (isdigit((*buf)[*i]))
        {
            b[j] = (*buf)[*i];
            j++;
            (*i)++;
        }
        int k = atoi(b);

        nd->flag = NUM;
        nd->value = k;
    }

    return nd;
}

Node* RDP::GetP (char** buf, int* i)
{
    if ((*buf)[*i] == '(')
    {
        (*i)++;
        Node* nd = GetT (buf, i);
        (*i)++;
        return nd;
    }
    else
    {
        return GetN (buf, i);
    }
}

Node* RDP::GetE (char** buf, int* i)
{
    Node* nd1 = GetP (buf, i);

    while ((*buf)[*i] == '*' || (*buf)[*i] == '/' )
    {
        Node* main_nd = new Node ();
        if ((*buf)[*i] == '*')
        {
           main_nd->flag = FUNC;
           main_nd->value = MUL;
        }
        else
        {
            main_nd->flag = FUNC;
            main_nd->value = DIV;
        }
        (*i)++;
        main_nd->RPush (GetP (buf, i));
        main_nd->LPush (nd1);
        nd1 = main_nd;
    }
    return nd1;
}


Node* RDP::GetD (char** buf, int* i) // работает только если число и степень стоят в скобках
{
    Node* nd1 = GetE (buf, i);

    while ((*buf)[*i] == '^')
    {
        Node* main_nd = new Node ();
        main_nd->flag = FUNC;
        main_nd->value = POW;
        (*i)++;
        main_nd->RPush (GetP (buf, i));
        main_nd->LPush (nd1);
        nd1 = main_nd;
    }
    return nd1;
}



Node* RDP::GetT (char** buf, int* i)
{
    Node* nd1 = GetD (buf, i);
    while ((*buf)[*i] == '+' || (*buf)[*i] == '-' )
    {
        Node* main_nd = new Node ();
        if ((*buf)[*i] == '+')
        {
           main_nd->flag = FUNC;
           main_nd->value = SUM;
        }
        else
        {
            main_nd->flag = FUNC;
            main_nd->value = SUB;
        }
        (*i)++;
        main_nd->RPush (GetD (buf, i));
        main_nd->LPush (nd1);
        nd1 = main_nd;
    }
    return nd1;
}

Node* RDP::GetGo (char** buf, int* i)
{
    if ((*buf)[*i] == '\0')
        return NULL;
    Node* nd = GetT (buf, i);
    return nd;
}
