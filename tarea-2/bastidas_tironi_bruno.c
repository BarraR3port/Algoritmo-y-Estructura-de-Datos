#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NODES 10000
#define infinito 10000000

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

typedef struct Usuario
{
    int id;
    char nombre[20];
    struct Usuario *siguiente;
} Usuario;

int numNodos, numArcos; // Numero de Personas y Numero de Relaciones
int **Grafo;
bool *Visitados;
int *Predecesor;
int *Costo;
int *Camino;
Usuario *usuarios;
int Pos = 0;
bool CaminoTerminado = false;

void agregarUsuariosALaCola(char nombre[25], int id)
{
    Usuario *nuevoUsuario = malloc(sizeof(Usuario));
    nuevoUsuario->id = id;
    strcpy(nuevoUsuario->nombre, nombre);
    nuevoUsuario->siguiente = NULL;

    if (usuarios == NULL)
    {
        usuarios = nuevoUsuario;
    }
    else
    {
        Usuario *current = usuarios;
        while (current->siguiente != NULL)
        {
            current = current->siguiente;
        }
        current->siguiente = nuevoUsuario;
    }
}
void creaArreglosParaElCamino()
{
    Visitados = calloc(numNodos, sizeof(bool));
    Costo = calloc(numNodos, sizeof(int));
    Predecesor = calloc(numNodos, sizeof(int));
    Camino = calloc(numNodos, sizeof(int));
}

int obtenerNumeroPorNombre(char nombre[25])
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

char *obtenerNombrePorNumero(int numUsuario)
{
    Usuario *current = usuarios;
    while (current != NULL)
    {
        if (current->id == numUsuario)
        {
            return current->nombre;
        }
        current = current->siguiente;
    }
    return NULL;
}

int leerArchivoYCrearGrafo(char nombreArchivo[9])
{

    FILE *inputFile = fopen(nombreArchivo, "r");

    if (inputFile == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    fscanf(inputFile, "%d %d", &numNodos, &numArcos);

    // Crear grafo
    Grafo = calloc(numNodos, sizeof(int *));
    for (int i = 0; i < numNodos; i++)
    {
        Grafo[i] = calloc(numNodos, sizeof(int));
    }

    // Leer aristas y agregarlas al grafo
    for (int i = 0; i < numNodos; i++)
    {
        char nombreUsuario[25];
        fscanf(inputFile, "%s", &nombreUsuario);
        // printf("Numero: %i %s\n", i, nombreUsuario);
        agregarUsuariosALaCola(nombreUsuario, i);
    }

    for (int j = 0; j < numArcos; j++)
    {
        char linea[50];
        char nombreUsuario1[25], nombreUsuario2[25];
        fscanf(inputFile, "%s", &linea);
        char *token = strtok(linea, ",");
        if (token)
        {
            strcpy(nombreUsuario1, token);
            token = strtok(NULL, ",");
            if (token)
            {
                strtok(token, "\n");
                strcpy(nombreUsuario2, token);
            }
        }

        if (strcmp(nombreUsuario1, nombreUsuario2) != 0 && nombreUsuario1 != NULL && nombreUsuario2 != NULL)
        {
            int idUsuario1 = obtenerNumeroPorNombre(nombreUsuario1);
            int idUsuario2 = obtenerNumeroPorNombre(nombreUsuario2);
            Grafo[idUsuario1][idUsuario2] = 1;
            Grafo[idUsuario2][idUsuario1] = 1;
        }
        else
        {
            j--;
        }
    }

    // Cerrar archivo de entrada y liberar memoria
    fclose(inputFile);
    return 0;
}

void GeneraCamino(int usuario1, int usuario2)
{
    Visitados[usuario1] = true;
    Camino[Pos] = usuario1;
    Pos++;
    if (usuario1 == usuario2)
    {
        CaminoTerminado = true;
        return;
    }
    else
    {
        for (int i = 0; i < numNodos; i++)
        {
            if (Grafo[usuario1][i] != 0 && Visitados[i] == false)
            {
                GeneraCamino(i, usuario2);
                if (CaminoTerminado == false)
                {
                    Pos--;
                    Visitados[i] = false;
                }
                else
                {
                    return;
                }
            }
            else
            {
                if (CaminoTerminado == true)
                {
                    return;
                }
            }
        }
    }
}

void ImprimeCaminos(int usuario1, int usuario2)
{
    // Restablecer los valores iniciales
    Pos = 0;
    CaminoTerminado = false;
    memset(Visitados, false, numNodos * sizeof(bool));

    // Revisar si son amigos o no:
    if (Grafo[usuario1][usuario2] == 1)
    {
        printf("Los usuarios %s y %s son amigos.\n", obtenerNombrePorNumero(usuario1), obtenerNombrePorNumero(usuario2));
        return;
    }
    else
    {
        // Generar el camino
        GeneraCamino(usuario1, usuario2);
    }
    if (!CaminoTerminado)
    {
        printf("No se encontró un camino entre los usuarios %s y %s.\n", obtenerNombrePorNumero(usuario1), obtenerNombrePorNumero(usuario2));
    }
    else
    {
        printf("La secuencia de Nombres es: \n");
        for (int i = 0; i < Pos; i++)
        {
            int numero = Camino[i];
            char *nombre = obtenerNombrePorNumero(numero);
            if (nombre == NULL)
            {
                continue;
            }
            printf("%s \n", nombre);
        }
        printf("\n");
    }
}

int numAmigosEnComun(int nodo1, int nodo2)
{
    int cont;
    int i;
    cont = 0;
    for (i = 0; i < numNodos; i++)
    {
        if (Grafo[nodo1][i] != 0 && Grafo[nodo2][i] != 0)
        {
            cont++;
        }
    }
    return cont;
}

void almacenarArchivoSalida(char *nombreArchivo)
{
    char nombreArchivoSalida[30];
    strcpy(nombreArchivoSalida, nombreArchivo);
    strtok(nombreArchivoSalida, ".");
    strcat(nombreArchivoSalida, ".aee");

    FILE *archivoSalida = fopen(nombreArchivoSalida, "w");
    if (archivoSalida == NULL)
    {
        printf("Error al abrir el archivo de salida.\n");
        return;
    }

    int **GrafoSalida = calloc(numNodos, sizeof(int *));
    for (int i = 0; i < numNodos; i++)
    {
        GrafoSalida[i] = calloc(numNodos, sizeof(int));
    }
    for (int i = 0; i < numNodos; i++)
    {
        int amistades = 0;
        for (int j = 0; j < numNodos; j++)
        {
            if (Grafo[i][j] == 1 && GrafoSalida[i][j] == 0 && GrafoSalida[j][i] == 0)
            {
                amistades++;
                char *nombreUsuario1 = obtenerNombrePorNumero(i);
                char *nombreUsuario2 = obtenerNombrePorNumero(j);
                fprintf(archivoSalida, "%s,%s: %i\n", nombreUsuario1, nombreUsuario2, numAmigosEnComun(i, j));
                GrafoSalida[i][j] = 1;
                GrafoSalida[j][i] = 1;
            }
        }
    }

    fclose(archivoSalida);
}

int iniciarProceso()
{
    if (leerArchivoYCrearGrafo("red2.txt") == 1)
    {
        return 1;
    }
    creaArreglosParaElCamino();

    // Encontrar secuencia de nombres de personas utilizando Dijkstra
    int inicio = obtenerNumeroPorNombre("Rocio"); // Índice del nodo de inicio
    int destino = obtenerNumeroPorNombre("Luis"); // Índice del nodo de destino

    ImprimeCaminos(inicio, destino);
    almacenarArchivoSalida("red1.txt");
    // Liberar memoria
    for (int i = 0; i < numNodos; i++)
    {
        free(Grafo[i]);
    }
    free(Grafo);
    free(usuarios);
    return 0;
}
int main()
{
    int proceso = iniciarProceso();
    return proceso;
}