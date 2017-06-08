#ifndef _List
#define _List

struct Nodo{
    void* data;
    struct Nodo* prev;
    struct Nodo* next;
};

typedef struct Nodo Node;

struct lista{
    Node* first;
    Node* last;
    Node* current;
};

typedef struct lista List;


/* crea una lista vacía y la retorna */
List* createList();

/* crea un nodo, lo llena y devuelve */
Node* createNode(void* data);

/* retorna el dato del nodo actual */
void* currentL(List* L);

/* retorna el nodo actual */
Node* currentN(List* L);

/* avanza el puntero 'current' de la lista hacia el siguiente */
Node* nextL(List* L);

/* retrocede el puntero 'current' de la lista haceia el anterior */
Node* prev(List* L);

/* posiciona 'current' en el primer elemento de la lista y lo retorna */
void* firstL(List* L);

/* posiciona 'current' en el último dato de la lista y lo retorna */
void* last(List* L);


/* inserta un nuevo dato al final de la lista */
List* push_back(List* L, void* data);

/* inserta un nuevo dato al principio de la lista */
List* push_front(List* L, void* data);

/* inserta un nuevo dato a la derecha de la posición 'current' */
List* push_current(List* L, void* data);

/* elimina el último elemento de la lista */
List* pop_back(List* L);

/* elimina el último elemento de la lista */
List* pop_front(List* L);

/* elimina el elemento en la posición 'current' de la lista */
List* pop_current(List* L);

#endif
