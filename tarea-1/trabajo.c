//
// Created by barra on 10-04-2023.
//
#include<stdio.h>
#include <malloc.h>
#include<string.h>

struct nodo {
    int entradas;
    char nombre[30];
    char rut[11];
    struct nodo *siguiente;
};

typedef struct nodo tNodo;

typedef tNodo *LISTA;

LISTA crearNodo(char nombre[30], int numEntradas, char rut[11], struct nodo *siguiente) {
    LISTA aux;
    aux = malloc(sizeof(tNodo));
    strcpy(aux->rut, rut);
    strcpy(aux->nombre, nombre);
    aux->entradas = numEntradas;
    aux->siguiente = siguiente;
}

LISTA insertarAlFinalDeLaLista(LISTA L, char nombre[30], int numEntradas, char rut[11]) {
    if (L == NULL) {
        return crearNodo(nombre, numEntradas, rut, NULL);
    }
    LISTA aux;
    aux = L;
    while (aux->siguiente != NULL) {
        aux = aux->siguiente;
    }
    aux->siguiente = crearNodo(nombre, numEntradas, rut, NULL);
    return L;
}

void imprimirLista(LISTA lista) {
    LISTA aux = lista;
    int i = 0;
    while (aux != NULL) {
        printf("AUX = %i | Nombre: %s Edad: %i siguiente-> %s\n", i, aux->nombre, aux->entradas,
               !aux->siguiente ? "NULL" : aux->siguiente->nombre);
        i++;
        aux = aux->siguiente;
    }
}

void procesoPrincipal() {
    LISTA L = insertarAlFinalDeLaLista(NULL, "Bruno Bastidas", 5, "21424401-2");
    insertarAlFinalDeLaLista(L, "Juan Perez", 3, "21424401-2");
    insertarAlFinalDeLaLista(L, "Pedro Martinez", 2, "21424401-2");
    insertarAlFinalDeLaLista(L, "Maria Gonzalez", 1, "21424401-2");
    insertarAlFinalDeLaLista(L, "Juliam Sanchez", 4, "21424401-2");
    insertarAlFinalDeLaLista(L, "Pericia aria Gonzalez", 1, "21424401-2");
    insertarAlFinalDeLaLista(L, "Noacho Sanchez", 4, "21424401-2");

    imprimirLista(L);
}

int main() {
    procesoPrincipal();
    return 0;
}
