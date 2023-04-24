#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct usuario
{
    int entradasPedidas;
    int entradasAsignadas;
    char nombre[30];
    char rut[11];
    struct usuario *siguiente;
};

typedef struct usuario tUsuario;

typedef tUsuario *ListaUsuarios;

struct entradas
{
    ListaUsuarios vendidas;
    ListaUsuarios pendientes;
    int disponibles;
};

typedef struct entradas tEntradas;

typedef tEntradas *EntradasUsuarios;

char nombreArchivo[30];

ListaUsuarios crearListaUsuarios(char nombre[30], int numEntradas, char rut[11], struct usuario *siguiente, int entradasAsignadas)
{
    ListaUsuarios aux;
    aux = malloc(sizeof(tUsuario));
    strcpy(aux->rut, rut);
    strcpy(aux->nombre, nombre);
    aux->entradasPedidas = numEntradas;
    aux->entradasAsignadas = entradasAsignadas;
    aux->siguiente = siguiente;
    return aux;
}

ListaUsuarios insertarAlFinalDeLaLista(ListaUsuarios lista, char nombre[30], int entradasPedidas, char rut[11], int entradasAsignadas)
{
    if (lista == NULL)
    {
        return crearListaUsuarios(nombre, entradasPedidas, rut, NULL, entradasAsignadas);
    }
    ListaUsuarios aux;
    aux = lista;
    while (aux->siguiente != NULL)
    {
        aux = aux->siguiente;
    }
    aux->siguiente = crearListaUsuarios(nombre, entradasPedidas, rut, NULL, entradasAsignadas);
    return lista;
}

int existe(ListaUsuarios lista, char rut[11])
{
    ListaUsuarios aux = lista;
    while (aux != NULL)
    {
        if (strcmp(aux->rut, rut) == 0)
        {
            return 0;
        }
        aux = aux->siguiente;
    }
    return 1;
}

ListaUsuarios agregarEntradas(ListaUsuarios lista, char rut[11], int entradas)
{
    ListaUsuarios aux = lista;
    while (aux != NULL)
    {
        if (strcmp(aux->rut, rut) == 0)
        {
            aux->entradasPedidas = aux->entradasPedidas + entradas;
        }
        aux = aux->siguiente;
    }
    return lista;
}

ListaUsuarios leeArchivo()
{
    char linea[150];
    printf("Ingresa el nombre del archivo: ");

    fgets(nombreArchivo, 50, stdin);
    strtok(nombreArchivo, "\n");
    FILE *archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL)
    {
        printf("Archivo invalido o no encontrado, cerrando el programa.");
        exit(-1);
    }

    ListaUsuarios lista = NULL;
    while (fgets(linea, sizeof(linea), archivo))
    {
        char *rut;
        char *nombre;
        char *cadena;
        int entradas;
        strtok(linea, "\n");
        rut = strtok(linea, ",");
        nombre = strtok(NULL, ",");
        cadena = strtok(NULL, ",");
        entradas = atoi(cadena);
        if (rut == NULL || nombre == NULL)
        {
            continue;
        }
        lista = insertarAlFinalDeLaLista(lista, nombre, entradas, rut, 0);
    }

    fclose(archivo);
    return lista;
}

ListaUsuarios retornarEntradasUnicas(ListaUsuarios lista)
{
    ListaUsuarios aux = lista;
    ListaUsuarios listaUnica = NULL;
    while (aux != NULL)
    {
        if (existe(listaUnica, aux->rut))
        {
            listaUnica = insertarAlFinalDeLaLista(listaUnica, aux->nombre, aux->entradasPedidas, aux->rut, aux->entradasAsignadas);
        }
        else
        {
            listaUnica = agregarEntradas(listaUnica, aux->rut, aux->entradasPedidas);
        }
        aux = aux->siguiente;
    }
    return listaUnica;
}

EntradasUsuarios retornarEntradasYAsignarEntradas(ListaUsuarios lista)
{
    ListaUsuarios aux = lista;
    ListaUsuarios vendidas = NULL;
    ListaUsuarios pendientes = NULL;
    int entradasDisponibles = 50;
    while (aux != NULL)
    {
        if (aux->entradasPedidas <= 5 && aux->entradasPedidas > 0) {
            if (aux->entradasPedidas >= 3 && aux->entradasPedidas <= 5) {
                if (entradasDisponibles - aux->entradasPedidas > 0) {
                    vendidas = insertarAlFinalDeLaLista(vendidas, aux->nombre, aux->entradasPedidas, aux->rut, 2);
                    entradasDisponibles = entradasDisponibles - 2;
                }
            }
            else
            {
                if (entradasDisponibles - aux->entradasPedidas < 0)
                {
                    pendientes = insertarAlFinalDeLaLista(pendientes, aux->nombre, aux->entradasPedidas, aux->rut, 0);
                }
                else
                {
                    vendidas = insertarAlFinalDeLaLista(vendidas, aux->nombre, aux->entradasPedidas, aux->rut, aux->entradasPedidas);
                    entradasDisponibles = entradasDisponibles - aux->entradasPedidas;
                }
            }
        }
        aux = aux->siguiente;
    }
    EntradasUsuarios entradas = malloc(sizeof(tEntradas));
    entradas->vendidas = vendidas;
    entradas->pendientes = pendientes;
    entradas->disponibles = entradasDisponibles;

    return entradas;
}

void guardarArchivos(EntradasUsuarios entradas)
{

    char nombreArchivoEntradasAsignadas[30], nombreArchivoEntradasPendientes[30];

    strcpy(nombreArchivoEntradasAsignadas, nombreArchivo);
    strcpy(nombreArchivoEntradasPendientes, nombreArchivo);
    strtok(nombreArchivoEntradasAsignadas, ".");
    strtok(nombreArchivoEntradasPendientes, ".");
    strcat(nombreArchivoEntradasAsignadas, ".asg");
    strcat(nombreArchivoEntradasPendientes, ".esp");
    FILE *archivoEntradasAsignadas = fopen(nombreArchivoEntradasAsignadas, "w");
    FILE *archivoEntradasEnEspera = fopen(nombreArchivoEntradasPendientes, "w");

    ListaUsuarios aux = entradas->vendidas;
    while (aux != NULL)
    {
        fprintf(archivoEntradasAsignadas, "%s,%s,%i\n", aux->rut, aux->nombre, aux->entradasAsignadas);
        aux = aux->siguiente;
    }
    fprintf(archivoEntradasAsignadas, "\nAsignadas: %i: \n", 50 - entradas->disponibles);
    fprintf(archivoEntradasAsignadas, "Pendientes: %i: \n", entradas->disponibles);

    aux = entradas->pendientes;
    while (aux != NULL)
    {
        fprintf(archivoEntradasEnEspera, "%s,%s\n", aux->rut, aux->nombre);
        aux = aux->siguiente;
    }

    fclose(archivoEntradasEnEspera);
    fclose(archivoEntradasAsignadas);
    free(entradas);
    free(aux);
}

void procesoPrincipal()
{
    ListaUsuarios usuarios = leeArchivo();
    ListaUsuarios lista = retornarEntradasUnicas(usuarios);
    EntradasUsuarios entradas = retornarEntradasYAsignarEntradas(lista);
    guardarArchivos(entradas);
}

int main()
{
    procesoPrincipal();
    return 0;
}
