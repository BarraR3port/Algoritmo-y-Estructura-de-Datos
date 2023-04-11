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

void leeArchivo() {
    char nombreArchivo[30], nombreArchivoSalida[30], linea[150];
    printf("Ingresa el nombre del archivo: ");

    fgets(nombreArchivo, 50, stdin);
    strtok(nombreArchivo, "\n");

    FILE *archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL) {
        printf("Archivo invalido o no encontrado, cerrando el programa.");
        exit(-1);
    }

    strcpy(nombreArchivoSalida, nombreArchivo);
    strtok(nombreArchivoSalida, ".");
    strcat(nombreArchivoSalida, ".sal");
    FILE *archivoSalida = fopen(nombreArchivoSalida, "w");

    while (fgets(linea, sizeof(linea), archivo)) {
        if (linea[0] == "\n") continue;
        char *rut;
        char *nombre;
        char *cadena;
        int edad;
        strtok(linea, "\n");
        rut = strtok(linea, ",");
        nombre = strtok(NULL, ",");
        cadena = strtok(NULL, ",");
        edad = atoi(cadena);
        if (rut == NULL || nombre == NULL || edad == NULL) continue;
        printf("Rut: %11s nombre: %20s             edad: %i\n", rut, nombre, edad);
        fprintf(archivoSalida, "Rut: %11s nombre: %20s             edad: %i\n", rut, nombre, edad);

    }

    fclose(archivo);
    fclose(archivoSalida);
}

void procesoPrincipal() {
    LISTA L = insertarAlFinalDeLaLista(NULL, "Bruno Bastidas", 5, "21424401-2");

    imprimirLista(L);
}

int main() {
    procesoPrincipal();
    return 0;
}
