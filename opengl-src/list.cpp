#include "list.h"
void List::insert(Nodo* n){
        if ( t==NULL) {
            t=n;
            t->prec=NULL;
            t->next=NULL;
            c=t;
        }
        else {
            c->next=n;
            n->prec=c;
            n->next=NULL;
            c=n;
        }
        count++;
}
void List::insItem(Figure * f){
        if( f!=NULL) {
        Nodo* n=new Nodo();
        n->f=f;
        if ( t==NULL) {
            t=n;
            t->prec=NULL;
            t->next=NULL;
            c=t;
        }
        else {
            c->next=n;
            n->prec=c;
            n->next=NULL;
            c=n;
        }
        count++;
        }
}
Figure* List::getFirst(){
        if (t!=NULL) return this->t->f;
        return NULL;
}
Figure* List::getLast(){
        if( c!=NULL) return this->c->f;
        return NULL;
}
Figure* List::get(int index){
        Nodo* n=t;
        for (int i =0 ; n!=NULL && i<index; i++  ) n=n->next;
        if( n!=NULL) return n->f;
        return NULL;
}
int List::delItem(Figure* f){
        Nodo*n=t;
        for(;n!=NULL && n->f!=f ;n=n->next) ;
        if ( n==NULL) return 0;
        if ( n->f==NULL) return -1;
        if( n->prec==NULL && n->next==NULL) {
            t=NULL;
            c=NULL;
        }
        else if( n->prec==NULL ){
            n->next->prec=NULL;
            t=n->next;
        }
        else if( n->next==NULL) {
            n->prec->next=NULL;
            c=n->prec;
        }
        else {
            n->prec->next=n->next;
            n->next->prec=n->prec;
        }
        count--;
        delete f;
        delete n;
        return 1;
}
Figure* List::popLast(){
        Figure *f;
        if( c!=NULL && c->f!=NULL) {
            f=c->f;
            if( c->prec==NULL) {
                t=NULL;
                delete c;
                c=NULL;
            }
            else {
                c->prec->next=NULL;
                c=c->prec;
                delete c->next;
            }
            return f;
        }
        return NULL;
}
int List::remAll() {
        for( Nodo* n=t; n!=NULL; ){
            Nodo* temp=n->next;
            if( n->f!=NULL) {
                free(n->f);
            }
            free(n);
            n=temp;
            count--;
        }
        t=NULL;
        c=NULL;
        return 1;
}
int List::getCount(){
		Nodo* n=t;
        int i=0;
		for ( ; n!=NULL; i++  ) n=n->next;
		return i;
}