#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct perro
{
    int edad;
    char nombre[30];
    char rut[11];
    struct perro *siguiente;
};

struct rutsRepetidos{
    char rut[11];
    int cantidad;
};

typedef struct perro tPerro;
typedef tPerro *LISTA;

typedef struct rutsRepetidos tRutRepetidos;
typedef struct rutsRepetidos *ListaDeRutsRepetidos;


void imprimeLista(LISTA lista)
{
    LISTA aux;
    LISTA auxInicial = lista;
    aux = lista;

    ListaDeRutsRepetidos listaDeRuts;
    int rutsRepetidos = 0;

    while(aux != NULL){
        printf("Nombre: %s Edad: %i   siguiente-> %s\n", aux->nombre, aux->edad, aux->siguiente->nombre);

        while( auxInicial != NULL){

            if (auxInicial->rut == aux->rut ){
                listaDeRuts = malloc(sizeof (ListaDeRutsRepetidos));

                rutsRepetidos++;
            }
            auxInicial = auxInicial->siguiente;

        }
        auxInicial = lista;
        aux = aux->siguiente;
    }
}

int main()
{
    LISTA perro1;
    perro1 = malloc(sizeof(tPerro));
    if(perro1 == NULL) {
        printf("No hay suficiente memoria disponible.");
        exit(-1);
    }
    strcpy(perro1->nombre, "Bruno");
    strcpy(perro1->rut, "214244012-2");
    perro1->edad = 17;
    perro1->siguiente = NULL;



    perro1->siguiente = malloc(sizeof(tPerro));
    if(perro1->siguiente == NULL) {
        printf("No hay suficiente memoria disponible.");
        exit(-1);
    }
    strcpy(perro1->siguiente->nombre, "El casti");
    strcpy(perro1->siguiente->rut, "214244012-2");
    perro1->siguiente->edad = 20;
    perro1->siguiente->siguiente = NULL;

    perro1->siguiente->siguiente = malloc(sizeof(tPerro));

    if (perro1->siguiente->siguiente == NULL) {
        printf("No hay suficiente memoria disponible.");
        exit(-1);
    }

    strcpy(perro1->siguiente->siguiente->nombre, "El mas que suena");
    strcpy(perro1->siguiente->siguiente->rut, "214244012-3");
    perro1->siguiente->siguiente->edad = 20;

    imprimeLista(perro1);


/*
    printf("Nombre del perro de %s es %s", perro1->nombre, perro1->siguiente->nombre);
*/

    return 0;

}