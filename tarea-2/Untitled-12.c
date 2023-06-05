#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define MAX_NODES 100

typedef struct Usuario
{
    int id;
    char nombre[20];
    struct Usuario *siguiente;
} Usuario;

typedef struct Grafo
{
    int numNodos;
    int **matriz;
} Grafo;

// Función auxiliar para agregar usuarios a la cola
void agregarUsuariosALaCola(char nombre[20], int id, Usuario **usuarios)
{
    Usuario *nuevoUsuario = malloc(sizeof(Usuario));
    nuevoUsuario->id = id;
    strcpy(nuevoUsuario->nombre, nombre);
    nuevoUsuario->siguiente = NULL;

    if (*usuarios == NULL)
    {
        *usuarios = nuevoUsuario;
    }
    else
    {
        Usuario *current = *usuarios;
        while (current->siguiente != NULL)
        {
            current = current->siguiente;
        }
        current->siguiente = nuevoUsuario;
    }
}

// Función auxiliar para imprimir la lista de usuarios
void imprimirUsuarios(Usuario *usuarios)
{
    Usuario *current = usuarios;
    while (current != NULL)
    {
        printf("%s - ID: %i\n", current->nombre, current->id);
        current = current->siguiente;
    }
}

// Función auxiliar para obtener el ID de un usuario por su nombre
int obtenerNumeroPorNombre(char nombre[20], Usuario *usuarios)
{
    Usuario *current = usuarios;
    while (current != NULL)
    {
        if (strcmp(current->nombre, nombre) == 0)
        {
            return current->id;
        }
        current = current->siguiente;
    }
    return -1;
}

// Función para leer el archivo y crear el grafo
Grafo *leerArchivoYCrearGrafo(char nombreArchivo[9], Usuario **usuarios)
{
    FILE *inputFile = fopen(nombreArchivo, "r");

    if (inputFile == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return NULL;
    }

    int numNodos, numArcos;
    fscanf(inputFile, "%d %d", &numNodos, &numArcos);

    // Crear grafo
    Grafo *grafo = malloc(sizeof(Grafo));
    grafo->numNodos = numNodos;
    grafo->matriz = calloc(numNodos, sizeof(int *));
    for (int i = 0; i < numNodos; i++)
    {
        grafo->matriz[i] = calloc(numNodos, sizeof(int));
    }

    // Leer nodos y agregarlos a la lista de usuarios
    for (int i = 0; i < numNodos; i++)
    {
        char nombreUsuario[20];
        fscanf(inputFile, "%s", nombreUsuario);
        agregarUsuariosALaCola(nombreUsuario, i, usuarios);
    }

    // Leer arcos y agregarlos al grafo
    for (int i = 0; i < numArcos; i++)
    {
        char nombreUsuario1[20], nombreUsuario2[20];
        fscanf(inputFile, "%s %s", nombreUsuario1, nombreUsuario2);
        int idUsuario1 = obtenerNumeroPorNombre(nombreUsuario1, *usuarios);
        int idUsuario2 = obtenerNumeroPorNombre(nombreUsuario2, *usuarios);
        grafo->matriz[idUsuario1][idUsuario2] = 1;
    }

    fclose(inputFile);
    return grafo;
}

// Función para encontrar la secuencia de personas utilizando Dijkstra
void encontrarSecuenciaDePersonas(Grafo *grafo, Usuario *usuarios, int inicio, int destino)
{
    int distancia[MAX_NODES];
    bool visitado[MAX_NODES];
    int predecesor[MAX_NODES];

    for (int i = 0; i < grafo->numNodos; i++)
    {
        distancia[i] = INT_MAX;
        visitado[i] = false;
        predecesor[i] = -1;
    }

    distancia[inicio] = 0;

    for (int count = 0; count < grafo->numNodos - 1; count++)
    {
        int u = -1;
        int minDistancia = INT_MAX;

        for (int i = 0; i < grafo->numNodos; i++)
        {
            if (!visitado[i] && distancia[i] < minDistancia)
            {
                minDistancia = distancia[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visitado[u] = true;

        for (int v = 0; v < grafo->numNodos; v++)
        {
            if (!visitado[v] && grafo->matriz[u][v] != 0 && distancia[u] != INT_MAX && distancia[u] + grafo->matriz[u][v] < distancia[v])
            {
                distancia[v] = distancia[u] + grafo->matriz[u][v];
                predecesor[v] = u;
            }
        }
    }

    if (distancia[destino] == INT_MAX)
    {
        printf("No se encontró una secuencia de personas para llegar al destino.\n");
        return;
    }

    Usuario *secuencia = NULL;
    int nodo = destino;
    while (nodo != -1)
    {
        agregarUsuariosALaCola(usuarios[nodo].nombre, usuarios[nodo].id, &secuencia);
        nodo = predecesor[nodo];
    }

    printf("Secuencia de personas para llegar al destino:\n");
    imprimirUsuarios(secuencia);

    // Liberar memoria
    Usuario *current = secuencia;
    while (current != NULL)
    {
        Usuario *temp = current;
        current = current->siguiente;
        free(temp);
    }
}

int main()
{
    Usuario *usuarios = NULL;
    Grafo *grafo = leerArchivoYCrearGrafo("red1.txt", &usuarios);
    if (grafo != NULL)
    {
        int inicio = 0; // ID del nodo inicial
        int destino = 3; // ID del nodo destino
        encontrarSecuenciaDePersonas(grafo, usuarios, inicio, destino);

        // Liberar memoria
        for (int i = 0; i < grafo->numNodos; i++)
        {
            free(grafo->matriz[i]);
        }
        free(grafo->matriz);
        free(grafo);

        Usuario *current = usuarios;
        while (current != NULL)
        {
            Usuario *temp = current;
            current = current->siguiente;
            free(temp);
        }
    }

    return 0;
}
