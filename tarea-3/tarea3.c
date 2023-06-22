#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo {
    char rut[11];
    char nombre[25];
    int entradas;
    struct nodo *izq;
    struct nodo *der;
};
typedef struct nodo tNodo;
typedef tNodo *ABO;

ABO crearArbol(char rut[11], char nombre[25], int entradas) {
    ABO arbol = (ABO) malloc(sizeof(tNodo));
    strcpy(arbol->rut, rut);
    strcpy(arbol->nombre, nombre);
    arbol->entradas = entradas;
    arbol->izq = NULL;
    arbol->der = NULL;
    return arbol;
}

ABO insertarNodoOCrear(ABO arbol, char rut[11], char nombre[25], int entradas) {
    if (arbol == NULL) {
        arbol = crearArbol(rut, nombre, entradas);
    } else {
        int comparacion = strcmp(rut, arbol->rut);
        if (comparacion == 0) {
            arbol->entradas += entradas;
        } else if (comparacion < 0) {
            arbol->izq = insertarNodoOCrear(arbol->izq, rut, nombre, entradas);
        } else {
            arbol->der = insertarNodoOCrear(arbol->der, rut, nombre, entradas);
        }
    }
    return arbol;
}

ABO leerArchivoYCrearArbol(char *nombreArchivo) {
    ABO arbol;
    char linea[150];
    FILE *archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL) {
        printf("Archivo invalido o no encontrado, cerrando el programa.");
        exit(-1);
    }

    while (fgets(linea, sizeof(linea), archivo)) {
        char *rut;
        char *nombre;
        char *cadena;
        int entradas;
        strtok(linea, "\n");
        rut = strtok(linea, ",");
        nombre = strtok(NULL, ",");
        cadena = strtok(NULL, ",");
        entradas = atoi(cadena);
        if (rut == NULL || nombre == NULL) {
            continue;
        }
        arbol = insertarNodoOCrear(arbol, rut, nombre, entradas);
    }

    fclose(archivo);
    return arbol;
}

FILE *crearArchivoSalida(FILE *archivo, char *nombreArchivoSalida) {
    if (archivo != NULL) {
        return archivo;
    }
    FILE *archivoSalida = fopen(nombreArchivoSalida, "w");
    return archivoSalida;
}

int checkearEntradas(ABO arbol, FILE *archivo) {
    if (arbol == NULL) {
        return 0;
    }
    int count = 0;

    count += checkearEntradas(arbol->izq, archivo);

    if (arbol->entradas > 2) {
        count++;
        if (archivo != NULL) {
            fprintf(archivo, "Rut: %s nombre: %s entradas: %i\n", arbol->rut, arbol->nombre, arbol->entradas);
        }
    }

    count += checkearEntradas(arbol->der, archivo);

    return count;
}

void escribirTotal(ABO arbol, char *nombreArchivo) {
    char nombreArchivoSalida[30];
    strcpy(nombreArchivoSalida, nombreArchivo);
    strtok(nombreArchivoSalida, ".");
    strcat(nombreArchivoSalida, ".sde");
    FILE *archivoSalida = crearArchivoSalida(NULL, nombreArchivoSalida);
    printf("El archivo %s fue generado\n", nombreArchivo);
    int cantidadDeNoAceptados = checkearEntradas(arbol, archivoSalida);
    fprintf(archivoSalida, "\nTotal: %d\n", cantidadDeNoAceptados);
    fclose(archivoSalida);
}

void procesoPrincipal() {
    char nombreArchivo[50];

    printf("Ingresa el nombre del archivo: ");
    fgets(nombreArchivo, 50, stdin);
    strtok(nombreArchivo, "\n");

    ABO arbol = leerArchivoYCrearArbol(nombreArchivo);

    if (checkearEntradas(arbol, NULL) == 0) {
        printf("Todos solicitaron la cantidad correcta de entradas\n");
    } else {
        escribirTotal(arbol, nombreArchivo);
    }
}

int main() {

    procesoPrincipal();
    return 0;
}
