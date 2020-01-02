#include "LinkedList.h"

namespace CRAZYFISH{
template <class TYPE>
LinkedList<TYPE>::LinkedList(Node &_new)
{
    __head = &_new;
    __head->next = NULL;   // DOUble make sure the end.
    __current = __head;
    __length = 1;
}
template <class TYPE>
LinkedList<TYPE>::LinkedList(TYPE _val)
{
    __head = new Node;
    __head->value = _val;
    __head->next = NULL;
    __current = __head;
    __length = 1;
}
template <class TYPE>
typename LinkedList<TYPE>::Node* LinkeList<TYPE>::find(TYPE _d) const
{
    Node *p = __head;
    if (p == NULL)
        return NULL;
    while (p->value != _d)
    {
        p = p->next;
        if (p == NULL)
            return NULL;
    }
    return p;
}

template <class TYPE>
int LinkedList<TYPE>::insert(Node &_new)
{
    Node *p = __current;
    if (p == NULL)      // Is a empty List?
    {
        __head = &_new;
        __head->next = NULL;   // Whatever make sure the end mark is ser.
        __current = __head;    // The initial value of current will always
                               //  keep same as the head.
    }
    else
    {
        _new.next = p->next;   // Link the part after current.
        p->next = &_new;
    }
    __length += 1;
    return 0;
}

template <class TYPE>
int LinkedList<TYPE>::insert(TYPE _val)
{
    Node *p = __current;
    if (p == NULL)
    {
        __head = new Node;
        __head->value = _val;
        __head->next = NULL;
        __current = __head;
    }
    else
    {
        Node *q = new Node;
        q->value = _val;
        q->next = p->next;
        p->next = q;
    }
    __length += 1;
    return 0;
}

template <class TYPE>
int LinkedList<TYPE>::del()
{
    Node *p = __current;
    if (p == NULL)
    {
        if (__length != 0)
        {
            p = __head;
            __head = head->next;
            delete p;
            __length -= 1;                  //**************wrong
            __current = __head;
        }
    }
    else if (p->next == NULL)
    {
        __head = NULL; // Delete the last node, it becomes an empty List.
        __length = 0;
        delete p;;
    }
    else
    {
        Node *q = 
    }
}
}
