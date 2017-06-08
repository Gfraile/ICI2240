#include "List.h"
#include <stdio.h>
#include <stdlib.h>

List* createList(){
    List* L = (List*) malloc(sizeof(List));
    L->first = NULL;
    L->last = NULL;
    L->current = NULL;

    return L;
}

Node* createNode(void* data){

    Node* nodo = (Node*)malloc(sizeof(Node));
    nodo->data = data;
    nodo->prev = NULL;
    nodo->next = NULL;

    return nodo;
}



Node* nextL(List* L){
    if(!L->current) return NULL;

    if(L->current->next){
        L->current = L->current->next;
        return L->current;
    }
    return NULL;
}



void* currentL(List* L){
    if(!L || !L->first) return NULL;
    return L->current->data;

}


Node* currentN(List* L){
    if(!L || !L->first) return NULL;
    return L->current;
}


Node* prev(List* L){
    if(!L->current) return NULL;

    if(L->current->prev){
        L->current = L->current->prev;
        return L->current;
    }

    return NULL;



}


void* firstL(List* L){

    if(!L || !L->first) return NULL;

    L->current = L->first;
    return L->current->data;

}


void* last(List* L){

    if(!L || !L->first) return NULL;

    L->current = L->last;
    return L->current->data;

}


List* push_back(List* L, void* data){
    Node* nuevo = createNode(data);

    if(!L->last){
        L->current = nuevo;
        L->first = nuevo;
        L->last = nuevo;
        return L;
    }
    L->last->next = nuevo;
    nuevo->prev = L->last;
     L->last = nuevo;
    return L;

}



List* push_front(List* L, void* data){
    Node* nuevo = createNode(data);
    if(!L->first){
        L->first = nuevo;
        L->current = nuevo;
        L->last = nuevo;
        return L;
    }

    L->first->prev = nuevo;
    nuevo->next = L->first;
    L->first = nuevo;

    return L;
}


List* push_current(List* L, void* data){
    Node* nuevo = createNode(data);

    if(!L->current){
        L->first = nuevo;
        L->current = nuevo;
        L->last = nuevo;

        return L;
    }
    if(L->current == L->first){
        L->first->prev = nuevo;
        nuevo->next = L->first;
        L->first = nuevo;

        return L;
    }

    if(L->current == L->last){
        L->last->next = nuevo;
        nuevo->prev = L->last;
        L->last = nuevo;

        return L;
    }

    nuevo->next = L->current->next;
    nuevo->prev = L->current->prev;
    L->current->next = nuevo;
    nuevo->next->prev = nuevo;

    return L;
}



List* pop_back(List* L){

    if(!L->last) return L;

    if(L->first == L->last){
        free(L->last);
        L->last = NULL;
        L->first = NULL;
        L->current = NULL;
        return L;
    }

    Node* aux = L->last;

    L->last = L->last->prev;
    L->last->next = NULL;
    free(aux);

    return L;


}
List* pop_front(List* L){

    if(!L->first) return L;

    if(L->first == L->last){
        free(L->first);
        L->last = NULL;
        L->first = NULL;
        L->current = NULL;
        return L;
    }

    Node* aux = L->first;

    L->first = L->first->next;
    L->first->prev = NULL;
    free(aux);
    return L;




}


List* pop_current(List* L){
    Node* nodo;
    if(L->current){
        nodo=L->current;
        if(L->current==L->first){
            if(L->last!=L->current){ //es el primero pero no el único de la lista
                L->first=nodo->next;
                L->current=nodo->next;
                L->current->prev=NULL;
                free(nodo);
                return L;
            }
            else{ // es el primero y el único de la lista
                L->current=NULL;
                L->first=NULL;
                L->last=NULL;
                free(nodo);
                return L;
            }
        }
        else{
            if(L->current!=L->last){
                L->current=nodo->next;
                L->current->prev=nodo->prev;
                L->current->prev->next=nodo->next;
                free(nodo);
                return L;
            }
            else{
                L->current=nodo->prev;
                L->last=nodo->prev;
                L->last->next=NULL;
                free(nodo);
                return L;
            }
        }
    }
    return L;
}
