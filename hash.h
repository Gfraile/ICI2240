#ifndef HASH_H
#define HASH_H

typedef struct nodo{
  void* key;
  void* data;
}hashElem;

typedef struct{
  hashElem** hashArray;
  int size; //cantidad elementos no nulos
  int capac; //Dimension tabla
  int current; //indice al elemento actual
  long (*hash) (void* key, long capac); //funcion del hash
  int (*isequal) (void* key1, void* key2);
}HashMap;

HashMap* createHashMap(int (*eq)(void* key1, void* key2), long (*hash)(void* key1, long cap), long cap);
//Crea un HashMap y lo retorna

void* search_hash(HashMap* map, void* key);
//Busca el dato con la clave key y lo retorna

void erase_hash(HashMap* map, void* key);
//borra un dato con la clave key del HashMap
void* current_hash(HashMap* map);
void* current_hashK(HashMap* map);

int inserta(HashMap* map, void* key, void* data);
//long hash(long key ,long capac);
//traduce el key que contiene el dato en una posicion de memoria

void* first_hash(HashMap* map);
//retorna el primer elemento de la tabla hash

void insert_hash(HashMap* map, void* key, void* data);
//inserta un elemento nuevo en el hashmap, si ya existe o por alguna otra razón no se inserta, retorna 0

void enlarge_hash(HashMap* map);
//duplica la capacidad de hashmap (si la carga del hashmap es mayor al 70%)

void* next_hash(HashMap* map);
//Retorna el dato siguiente respecto a la posicion current


#endif // HASH_H
