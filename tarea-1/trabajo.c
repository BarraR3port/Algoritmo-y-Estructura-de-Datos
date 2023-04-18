//
// Created by barra on 10-04-2023.
//
#include<stdio.h>
#include <malloc.h>
#include<string.h>

struct usuario {
    int entradasPedidas;
    int entradasOtorgadas;
    char nombre[30];
    char rut[11];
    struct usuario *siguiente;
};


typedef struct usuario tUsuario;

typedef tUsuario *LISTA;

struct entradas {
    LISTA vendidas;
    LISTA declinadas;
};

typedef struct entradas tEntradas;

typedef tEntradas *ENTRADAS;

int ENTRADAS_DISPONIBLES = 0;

LISTA crearNodo(char nombre[30], int numEntradas, char rut[11], struct usuario *siguiente, int entradasOtorgadas) {
    LISTA aux;
    aux = malloc(sizeof(tUsuario));
    strcpy(aux->rut, rut);
    strcpy(aux->nombre, nombre);
    aux->entradasPedidas = numEntradas;
    aux->entradasOtorgadas = entradasOtorgadas;
    aux->siguiente = siguiente;
}

LISTA insertarAlFinalDeLaLista(LISTA L, char nombre[30], int numEntradas, char rut[11], int numEntradasOtorgadas) {
    if (L == NULL) {
        return crearNodo(nombre, numEntradas, rut, NULL,numEntradasOtorgadas);
    }
    LISTA aux;
    aux = L;
    while (aux->siguiente != NULL) {
        aux = aux->siguiente;
    }
    aux->siguiente = crearNodo(nombre, numEntradas, rut, NULL,numEntradasOtorgadas);
    return L;
}

void imprimirLista(LISTA lista) {
    LISTA aux = lista;
    int i = 0;
    printf("\n");
    while (aux != NULL) {
        printf("AUX = %i | Nombre: %s Entradas: %i rut: %s\n", i, aux->nombre, aux->entradasPedidas, aux->rut);
        i++;
        aux = aux->siguiente;
    }
    free(aux);
}

int existe(LISTA lista, char rut[11]) {
    LISTA aux = lista;
    int counts = 0;
    while (aux != NULL && rut != NULL) {
        if (strcmp(aux->rut, rut) == 0){
            counts++;
        }
        if (counts >= 2) return 0;
        aux = aux->siguiente;
    }
    free(aux);
    return 1;
}

LISTA agregarEntradas(LISTA lista, char rut[11], int entradas) {
    LISTA aux = lista;
    while (aux != NULL) {
        if (strcmp(aux->rut, rut) == 0) {
            aux-> entradasPedidas = aux->entradasPedidas + entradas;
        }
        aux = aux->siguiente;
    }
    return lista;
}

LISTA limpiarYReducirLista(LISTA listaOriginal){
    LISTA aux = listaOriginal;
    LISTA nuevaLista = NULL;
    imprimirLista(listaOriginal);
    while (aux != NULL) {
        int existeEnLaLista = existe(nuevaLista , aux->rut);
        if ( existeEnLaLista == 0 ){
            nuevaLista = agregarEntradas(nuevaLista, aux->rut, aux->entradasPedidas);
        } else {
            nuevaLista = insertarAlFinalDeLaLista(nuevaLista, aux->nombre, aux->entradasPedidas, aux->rut, aux->entradasOtorgadas);
        }
        printf("\nExiste: %s rut: %s : %s", aux->nombre,aux->rut, existeEnLaLista == 0 ? "Si" : "No");

        aux = aux->siguiente;
    }
    printf("\nNueva lista: ");
    imprimirLista(nuevaLista);
    return nuevaLista;
}

ENTRADAS asignarEntradas(ENTRADAS entradas, LISTA lista) {
    LISTA nuevaLista = limpiarYReducirLista(lista);
    while (nuevaLista != NULL) {
        if (nuevaLista->entradasPedidas <= 2) {
            entradas->vendidas = insertarAlFinalDeLaLista(entradas->vendidas, nuevaLista->nombre, nuevaLista->entradasPedidas, nuevaLista->rut, nuevaLista->entradasPedidas);
        } else {
            entradas->declinadas = insertarAlFinalDeLaLista(entradas->declinadas, nuevaLista->nombre, nuevaLista->entradasPedidas, nuevaLista->rut, nuevaLista->entradasPedidas);
        }
        nuevaLista = nuevaLista->siguiente;
    }
    /*printf("\nVendidas: ");
    imprimirLista(entradas->vendidas);
    printf("Declinadas: ");
    imprimirLista(entradas->declinadas);*/
    return entradas;
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
        char *rut;
        char *nombre;
        char *cadena;
        int entradas;
        strtok(linea, "\n");
        rut = strtok(linea, ",");
        nombre = strtok(NULL, ",");
        cadena = strtok(NULL, ",");
        entradas = atoi(cadena);
        if (rut == NULL || nombre == NULL) continue;
        lista = insertarAlFinalDeLaLista(lista, nombre, entradas, rut,0);
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
