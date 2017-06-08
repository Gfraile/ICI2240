#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Asignaturas.h"
#define clean system("cls");

void main(){
char s;
Asignatura* A;
//char *Nombre_A = (char*)malloc(sizeof(char)*100);
    do{
    printf("\n\n\t\t\t\t\t\tMenu Principal\n\n");
    printf("\t\t\t\t\t1-. Crear horario academico\n");
    printf("\t\t\t\t\t2-. Buscar asignatura\n");
    printf("\t\t\t\t\t3-. Ingresar evaluaciones\n");
    printf("\t\t\t\t\t4-. Mostrar todas las asignaturas\n");
    printf("\t\t\t\t\t5-. Salir\n\n");
    printf("\t\t\t\t\tOpcion: ");
    fflush(stdin);
    scanf("%c",&s);
        switch(s){
            case '1':
                fflush(stdin);
                A = createHorary(); ///CREA UN HORARIO (SE CREA LISTA Y HASHMAP)
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tHorario creado exitosamente!");
                Sleep(1000);
                break;
            case '2': ///SE MUESTRA INFORMACION DE UN RAMO EN PARTICULAR (USO DE HASHMAP)
                fflush(stdin);
                printf("\n\t\t\t\t\tIngrese la asignatura a ver: ");
                char Nombre_A[buffsize];
                fgets(Nombre_A,50,stdin);
                mostrarHashAsig(Nombre_A);
                break;
            case '3':///SE CREA UNA EVALUACION DE UN RAMO Y SE INTEGRA COMO INFORMACION
                fflush(stdin);
                crearEvaluaciones(A);
                break;
            case '4':///SE MUESTRA TODAS LAS ASIGNATURAS CON SU RESPECTIVA INFORMACION
                fflush(stdin);
                mostrarTodoList();
                break;
                ///OK!
            case '5':///CIERRA EL PROGRAMA
                printf("\nSaliendo del programa...");
                Sleep(1000);
                return 0;
            default:///OPCION NO VALIDA
                printf("\nIngrese una opcion valida. ");
                system("pause");
                break;
        }
        system("cls");
    }while(1);
}


///YA, ENCONTRE DONDE ESTA EL PROBLEMA PARA INCERSION DE HASH PERO ESO, NO SE POR QUE SUCEDE



