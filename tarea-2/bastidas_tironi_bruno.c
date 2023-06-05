#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Usuario
{
    int id;
    char nombre[25];
    struct Usuario *siguiente;
} Usuario;

int numNodos, numArcos;
int **Grafo;
bool *Visitados;
int *Camino;
Usuario *usuarios;
int Pos = 0;
bool CaminoTerminado = false;

/*
 * Entrada: nombre - El nombre del usuario a agregar.
 *          id - El ID del usuario a agregar.
 * Salida:  No retorna nada.
 * Proceso: Crea un nuevo nodo de Usuario con el nombre y ID dados,
 *          y lo agrega a la cola de usuarios existentes.
 */
void agregarUsuariosALaCola(char *nombre, int id)
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

/*
 * Entrada: No recibe nada.
 * Salida:  No retorna nada.
 * Proceso: Crea los arreglos Visitados y Camino para almacenar los datos
 *          necesarios para el cálculo del camino entre usuarios.
 */
void creaArreglosParaElCamino()
{
    Visitados = calloc(numNodos, sizeof(bool));
    Camino = calloc(numNodos, sizeof(int));
}

/*
 * Entrada: nombre - El nombre del usuario a buscar.
 * Salida:  El ID del usuario correspondiente al nombre especificado.
 *          Si no se encuentra ningún usuario con el nombre dado, se retorna -1.
 * Proceso: Busca en la lista de usuarios el nombre especificado y retorna
 *          el ID del usuario correspondiente.
 */
int obtenerNumeroPorNombre(char *nombre)
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

/*
 * Entrada: numUsuario - El ID del usuario a buscar.
 * Salida:  El nombre del usuario correspondiente al ID especificado.
 *          Si no se encuentra ningún usuario con el ID dado, se retorna NULL.
 * Proceso: Busca en la lista de usuarios el ID especificado y retorna
 *          el nombre del usuario correspondiente.
 */
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

/*
 * Entrada: numUsuario - El ID del usuario a buscar.
 * Salida:  El nombre del usuario correspondiente al ID especificado.
 *          Si no se encuentra ningún usuario con el ID dado, se retorna NULL.
 * Proceso: Busca en la lista de usuarios el ID especificado y retorna
 *          el nombre del usuario correspondiente.
 */
int leerArchivoYCrearGrafo(char *nombreArchivo)
{

    FILE *archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    fscanf(archivo, "%d %d", &numNodos, &numArcos);

    Grafo = calloc(numNodos, sizeof(int *));

    for (int i = 0; i < numNodos; i++)
    {
        Grafo[i] = calloc(numNodos, sizeof(int));
    }

    for (int i = 0; i < numNodos; i++)
    {
        char nombreUsuario[25];
        fscanf(archivo, "%s", &nombreUsuario);
        agregarUsuariosALaCola(nombreUsuario, i);
    }

    for (int j = 0; j < numArcos; j++)
    {
        char linea[50];
        char nombreUsuario1[25], nombreUsuario2[25];

        fscanf(archivo, "%s", &linea);
        char *lineaActual = strtok(linea, ",");

        if (lineaActual)
        {
            strcpy(nombreUsuario1, lineaActual);
            lineaActual = strtok(NULL, ",");
            if (lineaActual)
            {
                strtok(lineaActual, "\n");
                strcpy(nombreUsuario2, lineaActual);
            }
        }

        if (strcmp(nombreUsuario1, nombreUsuario2) != 0)
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

    fclose(archivo);
    return 0;
}

/*
 * Entrada: numUsuario - El ID del usuario a buscar.
 * Salida:  El nombre del usuario correspondiente al ID especificado.
 *          Si no se encuentra ningún usuario con el ID dado, se retorna NULL.
 * Proceso: Busca en la lista de usuarios el ID especificado y retorna
 *          el nombre del usuario correspondiente.
 */
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

/*
 * Entrada: usuario1 - El ID del usuario de inicio.
 *          usuario2 - El ID del usuario de destino.
 * Salida:  No retorna nada.
 * Proceso: Imprime el camino entre usuario1 y usuario2, si existe,
 *          utilizando la información almacenada en el arreglo Camino.
 */
void ImprimeCaminos(int usuario1, int usuario2)
{
    Pos = 0;
    CaminoTerminado = false;

    for (int i = 0; i < numNodos; i++)
    {
        Visitados[i] = false;
    }

    char *nombreUsuario1 = obtenerNombrePorNumero(usuario1);
    char *nombreUsuario2 = obtenerNombrePorNumero(usuario2);

    if (Grafo[usuario1][usuario2] == 0)
    {
        GeneraCamino(usuario1, usuario2);
    }
    else
    {
        printf("Los usuarios %s y %s son amigos.\n", nombreUsuario1, nombreUsuario2);
        return;
    }
    if (CaminoTerminado)
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
    else
    {
        printf("No se encontró un camino entre los usuarios %s y %s.\n", nombreUsuario1, nombreUsuario2);
    }
}

/*
 * Entrada: nodo1 - El ID del primer nodo a comparar.
 *          nodo2 - El ID del segundo nodo a comparar.
 * Salida:  El número de amigos en común entre los dos nodos.
 * Proceso: Compara las relaciones de amistad entre nodo1 y nodo2
 *          en el grafo y cuenta el número de amigos en común.
 */
int numAmigosEnComun(int nodo1, int nodo2)
{
    int cont = 0;

    for (int i = 0; i < numNodos; i++)
    {
        if (Grafo[nodo1][i] != 0 && Grafo[nodo2][i] != 0)
        {
            cont++;
        }
    }
    return cont;
}

/*
 * Entrada: nombreArchivo - El nombre del archivo de salida a crear.
 * Salida:  0 si se crea el archivo correctamente, 1 si hay algún error.
 * Proceso: Almacena en un archivo de salida la información del camino
 *          generado entre dos usuarios, en el formato especificado.
 */
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

    for (int i = 0; i < numNodos; i++)
    {
        free(GrafoSalida[i]);
    }

    free(GrafoSalida);
    fclose(archivoSalida);
}

/*
 * Entrada: No recibe nada.
 * Salida:  No retorna nada.
 * Proceso: Libera la memoria utilizada por el grafo, los usuarios, el camino
 *          y los visitados.
 */
void liberarMemoria()
{

    for (int i = 0; i < numNodos; i++)
    {
        free(Grafo[i]);
    }

    free(Grafo);
    free(usuarios);
    free(Camino);
    free(Visitados);
}

/*
 * Entrada: No recibe nada.
 * Salida:  0 si el proceso se completa correctamente, 1 si hay algún error.
 * Proceso: Realiza el proceso principal del programa, que incluye leer el archivo
 *          de entrada, crear el grafo, generar caminos, almacenar el archivo de salida
 *          y liberar la memoria utilizada.
 */
int iniciarProceso()
{
    char nombreArchivo[30];

    printf("Ingrese el nombre del archivo de entrada: ");
    scanf("%s", nombreArchivo);

    if (leerArchivoYCrearGrafo(nombreArchivo) == 1)
    {
        return 1;
    }

    creaArreglosParaElCamino();
    printf("\nIngresa tu nombre: ");

    char nombreUsuario[30], nombreUsuario2[30];

    scanf("%s", nombreUsuario);
    int inicio = obtenerNumeroPorNombre(nombreUsuario);

    if (inicio == -1)
    {
        printf("El usuario %s no existe.\n", nombreUsuario);
        return 1;
    }

    printf("A quien deseas conocer?: ");
    scanf("%s", nombreUsuario2);
    printf("\n");

    int destino = obtenerNumeroPorNombre(nombreUsuario2);

    if (destino == -1)
    {
        printf("El usuario %s no existe.\n", nombreUsuario2);
        return 1;
    }

    ImprimeCaminos(inicio, destino);
    almacenarArchivoSalida(nombreArchivo);
    liberarMemoria();
    return 0;
}

/*
 * Entrada: No recibe nada.
 * Salida:  0 si el programa se ejecuta correctamente, 1 si hay algún error.
 * Proceso: Función principal que se ejecuta al iniciar el programa.
 *          Llama a la función iniciarProceso y devuelve su resultado.
 */
int main()
{
    int proceso = iniciarProceso();
    return proceso;
}