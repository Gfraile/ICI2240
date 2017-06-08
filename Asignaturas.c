#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>
#include "Asignaturas.h"
#include "hash.h"
#include "List.h"
#include <math.h>
#define buffsize 2000

List* Asignaturas_D = NULL;
HashMap* Asignaturas_H = NULL;

int lower_than_int(int a, int b){
    if(a<b) return 1;
    return 0;
}

int is_equal_string(void* a, void* b){
    if(strcmp(a,b)==0) return 1;
    return 0;
}

int lower_than_string(char* a, char* b){
    if(strcmp(a, b)<0) return 1;
    return 0;
}

long GenerarKey(char *A, long capac){
    long h=0;
    int i;
    for( i = strlen(A)-1 ; i>=0 ; i--) {
        h = (((int)A[i]) + 128*h) % capac;
        //printf("veces->%d -> %d\n",i,h);
        //printf("valor posicion %d string -> %d\n",i,(int)A[i]);
    }
    if(h<0) return (-1*h);
    //printf("\ncapac->%d \nstring: %s",capac,A);
    //printf("\nvalor hash: %d",h);
    return (long)h;
}

void toGeneric_String(char A[]){
    for(int i=0 ; i < strlen(A) ; i++) A[i] = tolower(A[i]);
}

int verificaHor(HashMap* Asignaturas_H, List* Asignaturas_D){
    if (!Asignaturas_H && !Asignaturas_D) return 1;
    return 0;

}
//int cantRamos(){}
//int ExisteR(char ramito[]){}

Asignatura* createHorary(){
    ///CREAR HORARIO
    system("cls");
    char n[10];
    Asignatura* A;
    int in;

    do{
        printf("Ingrese cantidad de ramos: ");
        fgets(n,10,stdin);

        n[strlen(n) - 1] = '\0';
        in = atoi(n);

            if(in <= 0){
                printf("Debes ingresar un numero y que sea mayor que 0!\n\n");
                system("pause");
                system("cls");
            }

    }while(in == 0);

    system("cls");

    Asignaturas_D = createList(); ///se crea lista
    Asignaturas_H = createHashMap(is_equal_string, GenerarKey, in);///se crea hashmap
    int i;
    for(i=0;i<in;i++){
        A = CrearNRamo(A,i); ///Crea un ramillo
        push_back(Asignaturas_D,A);
        ///__________________________________
        inserta(Asignaturas_H , A->ramo , A);///INSERCION DATOS HASH-MAP (POR ASIGNATURA)
    }
    A->cant_ramos = in;
    return A;
}

Asignatura* CrearNRamo(Asignatura* A, int i){
A = (Asignatura*)malloc(sizeof(Asignatura));
A->ramo = (char*)malloc(sizeof(char)*buffsize);
Asignatura* B_aux;
        do{
            printf("Ingrese Nombre asignatura %d: ",i+1);
            fflush(stdin);
            fgets(A->ramo,buffsize,stdin); ///Nombre del ramo
            B_aux = search_hash(Asignaturas_H,A->ramo);

            if(B_aux){
                printf("\nEste nombre no esta permitido o ya existe.");
                printf("\nIntente con otro!");
                system("pause");
                system("cls");
            }
        }while(B_aux);

        //printf("Ingrese clave de asignatura (digite de la forma [1-2]): ");
        //fgets(A->asig.fecha.clave,buffsize,stdin);
        printf("Ingrese los dias que corresponden a su asignatura de la siguiente forma: ");
        Sleep(1000);
        printf("\nEjemplo: lunes,miercoles,jueves");
        Sleep(1000);
        printf("\nlunes - Martes - Miercoles - Jueves - Viernes");
        printf("\n\nDia: ");
        fflush(stdin);
        //A->asig.diaString = (char*)malloc(sizeof(char));
        fgets(A->fecha.diaString,buffsize,stdin);
        /*printf("\nIngrese fecha asignatura: ");
        printf("\nMes: ");
        scanf("%d",&A->asig.fecha.mes);
        printf("Dia: ");
        scanf("%d",&A->asig.fecha.dia);
        */
        system("cls");

return A;
}

void mostrarHashAsig(char Nombre_R[]){

    if(verificaHor(Asignaturas_H,Asignaturas_D)){
        printf("Error!\nNo se ha exportado o creado un horario!");
        Sleep(1000);
        return;
    }

    Asignatura* A = (Asignatura*)search_hash(Asignaturas_H,Nombre_R);

    if(!A){
        printf("Error, no se ha encontrado o creado la asignatura :c");
        Sleep(1000);
        return;
    }

        printf("Asignatura: %s\n",A->ramo);
        printf("Clases dia(s): %s\n\n",A->fecha.diaString);
        if(A->evaluacion.tipo){
            printf("Evaluacion: %s\n",A->evaluacion.tipo);
        }
        system("pause");
}

void crearEvaluaciones(Asignatura* A){

    if(verificaHor(Asignaturas_H,Asignaturas_D)){
        printf("Error!\nNo se ha exportado o creado un horario!");
        Sleep(1000);
        return;
    }

    char n[20];
    char* Nombre_R = (char*)malloc(sizeof(char));
    Asignatura* B_aux;

    printf("Ingrese asignatura correspondiente a la evaluacion: ");
    fgets(Nombre_R,buffsize,stdin);
    B_aux = search_hash(Asignaturas_H,Nombre_R);

    if(!B_aux){
        printf("\nNo se ha encontrado la asignatura!");
        system("pause");
        system("cls");
        return;
    }

    printf("\nQue tipo de evaluacion es? Escriba su opcion: ");

        printf("\n\n1-. Certamen");
        printf("\n2-. Control");
        printf("\n3-. Tarea");
        printf("\n4-. Examen");
        printf("\n\n-> ");

        fgets(A->evaluacion.tipo,20,stdin);


    fflush(stdin);
    A->evaluacion.contenido = (char*)malloc(sizeof(char)*(buffsize*4));
    printf("\nIngrese contenido de la evaluacion: ");
    fgets(A->evaluacion.contenido , buffsize*4 , stdin);
    printf("\nIngrese dia y fecha evaluacion (de la forma [dia/mes]); ");
    printf("\nEjemplo: [12/05]");
    printf("\n\nDia: ");
    scanf("%d",&A->fecha.dia);
    printf("\nMes: ");
    scanf("%d",&A->fecha.mes);

    fflush(stdin);

    printf("\nEvaluación guardada exitosamente!");
    Sleep(1000);
    system("cls");
    return;
}

void mostrarTodoList(){;

    if(verificaHor(Asignaturas_H,Asignaturas_D)){
        printf("Error!\nNo se ha exportado o creado un horario!");
        Sleep(1000);
        return;
    }

    if(!Asignaturas_D){
        printf("\n\nNo hay nada D:");
        Sleep(1000);
        return;
    }
    Asignatura* A;

    for(A = firstL(Asignaturas_D); nextL(Asignaturas_D); A = currentL(Asignaturas_D)){
            printf("Asignatura: %s\n",A->ramo);
            printf("clases dia(s): %s\n\n",A->fecha.diaString);
            printf("______________________________________________\n\n");
            Sleep(500);
    }
    system("pause");
}

