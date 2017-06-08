#ifndef HORARIO
#define HORARIO
#include "Hash.h"
#include "List.h"
#define buffsize 80

typedef struct{
    int dia;
    int mes;
    char clave[10]; ///HORA DE CLASES DEL RAMO
    char diaString[buffsize];
}Fecha; ///DIA/MES DE LA EVALUACION

typedef struct{
    char tipo[20]; ///TIPO DE EVALUACIÓN (CERTAMEN/CONTROL/TAREA/EXAMEN)
    char* contenido; ///"TEMARIO" EVALUACIÓN
}Eval;

typedef struct{
    int cant_ramos;
    char* ramo; ///NOMBRE DEL RAMO
    Fecha fecha;
    Eval evaluacion;
}Asignatura; ///HORARIO ACADÉMICO

int verificaHor(HashMap* Asignaturas_H, List* Asignaturas_D);

long GenerarKey(char A[], long capac);

int is_equal_string(void* a, void* b);

int lower_than_string(char* a, char* b);

int lower_than_int(int a, int b);

Asignatura* createHorary();

long toLong(char Cont[]);

Asignatura* CrearNRamo(Asignatura* A, int i);

void mostrarHashAsig(char Nombre_R[]);

void toGeneric_String(char A[]);

void mostrarTodoList();

void crearEvaluaciones(Asignatura* A);

#endif // HORARIO
