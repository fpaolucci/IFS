#ifndef LIST_H
#define LIST_H
#include "struct.h"

class List
{
public:
    Nodo* t;
    Nodo* c;
    int count;
    
    inline List(){t=NULL; c=NULL;  count=0;}
    void insert(Nodo* n);
    void insItem(Figure * f);
    Figure* getFirst();
    Figure* getLast();
    Figure* get(int index);
    int delItem(Figure* f);
    Figure* popLast();
    int remAll() ;
    int getCount();
};

#endif // LIST_H
