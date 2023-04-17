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

struct entradas {
    LISTA vendidas;
    LISTA declinadas;
};
typedef struct entradas tEntradas;

typedef tEntradas *ENTRADAS;

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

LISTA insertarSiguienteAlFinalDeLaLista(LISTA L, LISTA siguiente) {
    if (L == NULL){
        L = siguiente;
        L->siguiente = NULL;
        return L;
    }
    LISTA aux = L;
    while (aux->siguiente != NULL) {
        aux = aux->siguiente;
    }
    aux->siguiente = siguiente;
    return L;
}

void imprimirLista(LISTA lista) {
    LISTA aux = lista;
    int i = 0;
    printf("\n");
    while (aux != NULL) {
        printf("AUX = %i | Nombre: %s Entradas: %i %s rut: %s siguiente-> "
               "\n", i, aux->nombre, aux->entradas, aux->rut,
               !aux->siguiente ? "NULL" : aux->siguiente->nombre);
        i++;
        aux = aux->siguiente;
    }
}

int vecesRepetidas(LISTA lista, tNodo *nodo) {
    int veces = 0;
    LISTA aux = lista;
    while (aux != NULL) {
        if (strcmp(aux->rut, nodo->rut) == 0) {
            veces = veces + aux->entradas;
        }
        aux = aux->siguiente;
    }
    return veces;
}

LISTA existe(LISTA lista, tNodo *nodo) {
    LISTA aux = lista;
    while (aux != NULL) {
        if (strcmp(aux->rut, nodo->rut) == 0) {
            return aux;
        }
        aux = aux->siguiente;
    }
    return NULL;
}

ENTRADAS asignarEntradas(ENTRADAS entradas, LISTA lista) {
    LISTA aux = lista;
    LISTA nuevaLista = NULL;
    while (aux != NULL) {
        LISTA subAux = aux->siguiente;
        while (subAux != NULL) {
            if (strcmp(aux->rut, subAux->rut) == 0) {
                aux->entradas = aux->entradas + subAux->entradas;
            }
            subAux = subAux->siguiente;
        }
        nuevaLista = insertarSiguienteAlFinalDeLaLista(nuevaLista, &aux);
        //imprimirLista(aux);
        aux = aux->siguiente;
    }
    LISTA entradasFiltradas = NULL;
    //imprimirLista(nuevaLista);

    aux = nuevaLista;
    while (aux != NULL){
        LISTA esta = existe(entradasFiltradas, aux);
        if (esta == NULL){
            entradasFiltradas = insertarSiguienteAlFinalDeLaLista(entradasFiltradas, &aux);
        }
        aux = aux->siguiente;
    }
    imprimirLista(entradasFiltradas);

    LISTA aceptadas = NULL;
    LISTA declinadas = NULL;
    entradas->vendidas = aceptadas;
    entradas->declinadas = declinadas;
    return entradas;
}

LISTA retornarEntradasUnicas(LISTA listaInicial) {
    LISTA aux = listaInicial;
    LISTA listaUnica = NULL;
    while (aux != NULL) {
        int repetidas = vecesRepetidas(listaInicial, aux);
        if (repetidas <= 2) {
            if (listaUnica == NULL) {
                listaUnica = aux;
            } else {
                listaUnica->siguiente = aux;
            }
        }
        //printf("Veces repetidas de RUT: %s es: %i\n", aux->rut, repetidas);
        aux = aux->siguiente;
    }
    return listaUnica;
}


void leeArchivo() {
    char nombreArchivo[30], nombreArchivoSalida[30], linea[150];
    printf("Ingresa el nombre del archivo: ");

    //fgets(nombreArchivo, 50, stdin);
    //strtok(nombreArchivo, "\n");
    strcpy(nombreArchivo, "datos1.txt");
    FILE *archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL) {
        printf("Archivo invalido o no encontrado, cerrando el programa.");
        exit(-1);
    }

    strcpy(nombreArchivoSalida, nombreArchivo);
    strtok(nombreArchivoSalida, ".");
    strcat(nombreArchivoSalida, ".sal");
    FILE *archivoSalida = fopen(nombreArchivoSalida, "w");

    LISTA lista = NULL;
    while (fgets(linea, sizeof(linea), archivo)) {
        if (linea[0] == "\n") continue;
        char *rut;
        char *nombre;
        char *cadena;
        int entradas;
        strtok(linea, "\n");
        rut = strtok(linea, ",");
        nombre = strtok(NULL, ",");
        cadena = strtok(NULL, ",");
        entradas = atoi(cadena);
        //printf("Rut: %11s nombre: %20s             entradas: %i\n", rut, nombre, entradas);
        if (rut == NULL || nombre == NULL) continue;
        lista = insertarAlFinalDeLaLista(lista, nombre, entradas, rut);
        /*write data inside the sal file*/
        fprintf(archivoSalida, "Rut: %11s nombre: %20s             entradas: %i \n", rut, nombre, entradas);
    }

    ENTRADAS entradas = malloc(sizeof(ENTRADAS));
    entradas = asignarEntradas(entradas, lista);
    // imprimirLista(lista);
    // LISTA entradasUnicas = retornarEntradasUnicas(lista);

    //imprimirLista(entradasUnicas);


    fclose(archivo);
    fclose(archivoSalida);
}

void procesoPrincipal() {
    leeArchivo();
}

int main() {
    procesoPrincipal();
    return 0;
}
