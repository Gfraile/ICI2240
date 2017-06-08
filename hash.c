#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

/*
    Reerva memoria para un hashmap y lo retorna
*/
HashMap* createHashMap(int (*eq)(void* key1, void* key2), long (*hash)(void* key1, long cap), long cap){
    HashMap* mapa = (HashMap*)malloc(sizeof(HashMap)); //reservo memoria para caballo a un puntero a hashmap

    mapa->capac=cap; //se asigna la capacidad de caballo con cap
    mapa->size=0; //elementos no nulos inicializado
    mapa->hash = hash;
    mapa->isequal = eq;
    mapa->hashArray = (hashElem**)malloc(sizeof(hashElem*) * mapa->capac); //reserva memoria para puntero de punteros de hasharray
    for(int i=0;i<mapa->capac;i++){
        mapa->hashArray[i]=NULL; //Null para todos los elementos de la tabla hashmap
    }
    return mapa;
}


/*
    Busca en el mapa 'map' el elemento de clave 'key', luego retorna el dato de éste si existe, sino, retorna NULL
*/
void* search_hash(HashMap* map, void* key){
    int i;
    int new_hvalue;
    //printf("\n\nSe busca %s\t hash retorna %i \t", key, map->hash(key, map->capac));
    int hvalue=map->hash(key,map->capac);
    //printf("\npasa");
    for(i=0;i<map->capac;i++){
        new_hvalue=(hvalue+i)%map->capac;
        if(!map->hashArray[new_hvalue]){
            //printf("No esta");
            return NULL;
        }
        else if( map->isequal(map->hashArray[new_hvalue]->key, key)){
            //printf("\t Encontrado");
           return map->hashArray[new_hvalue]->data;
        }
    }
    //printf("NO esta");
    return NULL;
}

/*
    Busca en el mapa 'map' el elemento de clave 'key' y libera la memoria de hadhelem->data
*/
void erase_hash(HashMap* map, void* key){
    long i;
    long pos=map->hash(key,map->capac);
    i=pos;
//====================================== la misma wea que la funcion search
    if(map->hashArray[pos]==NULL || map->hashArray[pos]->data==NULL) return;

    if( !map->isequal(map->hashArray[pos]->key,key) ){
        for(pos=i+1;pos!=i;pos++){
            if(pos>=map->capac) pos=0;
            if(map->hashArray[pos]==NULL || map->hashArray[pos]->data==NULL) return;
            if( map->isequal(map->hashArray[pos]->key,key)  ) free(map->hashArray[pos]->data); //si se encuentra la wea, se asigna null al dato en la posicion
        }
    }else{
        free(map->hashArray[pos]->data);
    }

}


/*
    Calcula la posición donde meter el dato en el mapa
*/
/*long hash(long key ,long capac){
    float R = 0.5;
    //metodo de dispersion de datos
    int i = R*key;
    float d = R*key - i;

    return ((int)(d*capac));
}*/


/*void insert_hash(HashMap* map, void* key, void* data){
   int hvalue=map->hash(key,map->capac);
   if(hvalue>=map->capac) hvalue = 0;
   if(map->hashArray[hvalue]){ //se busca una casilla disponible a partir de hvalue
       int new_hvalue=-1, i;
       for(i=1;i<map->capac;i++){
          new_hvalue=(hvalue+i)%map->capac;
          if(!map->hashArray[new_hvalue] || !map->hashArray[new_hvalue]->data){
             hvalue=new_hvalue;
             break;
          }
       }
   }

   if(!map->hashArray[hvalue]) map->hashArray[hvalue]=(hashElem*) malloc(sizeof(hashElem));
   map->hashArray[hvalue]->data=data;
   map->hashArray[hvalue]->key=key;
   map->size++;
   if((double)map->size/(double)map->capac > 0.7) enlarge_hash(map); //agranda la tabla
}

*/


/*
    Inserta el un nuevo elemento 'data' con una clave 'key' l mapa 'map'
*/
int inserta(HashMap* map, void* key, void* data){
    long pos;

    if(search_hash(map,key)){
        return NULL;
    }

    float carga=((map->size)/(map->capac));
    if(carga>0.69) enlarge_hash(map);
    pos=map->hash(key,map->capac);
    //printf("\nEsta es pos de %s:%i\n",key, pos);
    if(map->hashArray[pos]!=NULL && map->isequal(map->hashArray[pos]->key,key) ) return 0;
    if(map->hashArray[pos]==NULL){
        map->hashArray[pos]=(hashElem*)malloc(sizeof(hashElem));
        map->hashArray[pos]->data=data;
        map->hashArray[pos]->key=key;
        map->size++;
        return 1;
    }else{
        if(map->hashArray[pos]!=NULL){
            //printf("%i/%i \n", pos, map->capac);
            while(map->hashArray[pos]!=NULL){
                pos++;
                if(pos >= map->capac) pos=0;

                if(map->hashArray[pos]!=NULL && map->isequal(map->hashArray[pos]->key,key)) return 0;
                if(map->hashArray[pos]==NULL || map->hashArray[pos]->data==NULL){
                        map->hashArray[pos]=(hashElem*)malloc(sizeof(hashElem));
                    map->hashArray[pos]->data=data;
                    map->hashArray[pos]->key=key;
                    map->size++;
                    carga = ((map->size)/(map->capac));
                    return 1;
                }
            }

        }
    }

 return 0;

}

/*
    Duplica la capacidad del hashmap y reordena los elementos anteriores
*/

void enlarge_hash(HashMap* map){
    //printf("Se agranda");
    hashElem** aux = map->hashArray;
    map->hashArray = (hashElem**)malloc(sizeof(hashElem*)* map->capac * 2);
    long a=map->capac;

    for(int i=0 ; i<map->capac*2 ; i++){
        map->hashArray[i]=NULL;
    }
    map->size = 0;
    map->capac = (map->capac) * 2;


    for(int i=0 ; i<a ; i++){
        if(aux[i] && aux[i]->key){
            inserta(map, aux[i]->key, aux[i]->data);
            free(aux[i]);
        }
    }
    free(aux);

}
/*
    Retorna primer elemento del Hashmap
*/
void* first_hash(HashMap* map){
    int i=1;

    if(map->hashArray[i]!=NULL && map->hashArray[i]->data!=NULL){ //existe el elemento?
        map->current=i;
        return map->hashArray[i]->data;//retorna dato
    }

    for(i=2 ; i<map->capac ; i++){
        if(map->hashArray[i]!=NULL && map->hashArray[i]->data!=NULL){ //existe el elemento?
            map->current=i;
            return map->hashArray[i]->data;
        }
    }
    map->current=i;
    return NULL;
}

/*
    Retorna el elemento del hashArray que está en la psición map->current
*/
void* current_hash(HashMap* map){
    if(!map) return NULL;

    return map->hashArray[map->current]->data;
}


void* current_hashK(HashMap* map){
    if(!map) return NULL;

    return map->hashArray[map->current]->key;
}
/*
    busca el siguiente elemento no nulo del mapa, cambia la posición de map->current y retorna el dato
*/
void* next_hash(HashMap* map){
    int pos=map->current;

    if(pos == map->capac-1) return NULL;

    for(int i=pos+1 ; i < map->capac ; i++){
        if(map->hashArray[i]!=NULL && map->hashArray[i]->data!=NULL){
            map->current=i;
            return map->hashArray[map->current]->data;
        }
    }

    return NULL;
}
