#include <stdio.h>
#include <malloc.h>
#include <string.h>

/*
 * Estructura de datos para almacenar los datos de los usuarios.
 * */
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

/*
 * Estructura de datos para almacenar las entradas vendidas, pendientes y disponibles.
 * */
struct entradas
{
    ListaUsuarios vendidas;
    ListaUsuarios pendientes;
    int disponibles;
};

typedef struct entradas tEntradas;

typedef tEntradas *EntradasUsuarios;

/*
 * Se crea la variable global nombreArchivo que contendrá el nombre del archivo a leer.
 */
char nombreArchivo[30];

/*
 * Entrada: Nombre del Usuario, Numero de entradas solicitadas, Rut del usuario, Siguiente usuario, Entradas asignadas.
 * Salida:  Se retorna la Lista de usuarios.
 * Proceso: Se aloja memoria para la lista de usuarios y se asignan los valores. Se asignan todos
 *          los valores a la lista. Se retorna la lista.
 *
 */
ListaUsuarios crearListaUsuarios(char nombre[30], int numEntradas, char rut[11], struct usuario *siguiente, int entradasAsignadas)
{
    ListaUsuarios aux = malloc(sizeof(tUsuario));
    strcpy(aux->rut, rut);
    strcpy(aux->nombre, nombre);
    aux->entradasPedidas = numEntradas;
    aux->entradasAsignadas = entradasAsignadas;
    aux->siguiente = siguiente;
    return aux;
}

/*
 * Entrada: Lista original de Usuarios, Nombre del Usuario, Número de entradas solicitadas, Rut del usuario, Entradas
 *          asignadas.
 * Salida:  Se retorna la Lista de usuarios con el nuevo usuario insertado al final de esta.
 * Proceso: Se revisa si la lista es nula, si lo es se crea la lista con el usuario. Si no es nula, se recorre la lista
 *          hasta el final y se inserta el usuario al final de la lista tras crearlo con la función crearListaUsuarios().
 *
 */
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

/*
 * Entrada: Lista de usuarios, Rut del usuario a revisar.
 * Salida:  Se retorna 0 si el usuario no existe y 1 si el usuario existe.
 * Proceso: Se recorre la lista entregada y se revisa si el rut del usuario entregado es igual al rut de algun usuario
 *          en la lista.
 */
int existe(ListaUsuarios lista, char rut[11])
{
    ListaUsuarios aux = lista;
    while (aux != NULL)
    {
        if (strcmp(aux->rut, rut) == 0)
        {
            return 1;
        }
        aux = aux->siguiente;
    }
    return 0;
}

/*
 * Entrada: Lista de usuarios, Rut del usuario a agregar entradas, Número de entradas a agregar.
 * Salida:  Se retorna la lista de usuarios con las entradas actualizadas.
 * Proceso: Se recorre la lista de usuarios y se revisa si el rut del usuario entregado es igual al rut de algún usuario
 *          en la lista, en caso de que se encuentre uno se suman las entradas pedidas más las entradas entregadas.
 *          Una vez finalizado el recorrido se retorna la lista.
 *
 */
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

/*
 * Entrada: No hay entrada.
 * Salida:  Se retorna una Lista de Usuarios.
 * Proceso: Se le pide al usuario el nombre del archivo a leer, luego se abre este archivo y se lee línea por línea. En
 *          caso de no encontrar este archivo se le informa al usuario y se cierra el programa.
 *          Se recorre línea por línea el archivo y se separa por comas, se asigna cada valor a su variable
 *          correspondiente y se inserta al final de la lista de usuarios.
 */
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

/*
 * Entrada: Lista de usuarios.
 * Salida:  Se retorna una Lista de Usuarios Unicos.
 * Proceso: Se asigna a un auxiliar la lista original, luego se crea una lista vaciá que contented los usuarios unicos.
 *          Se recorre la lista original y se revisa si el rut del usuario ya existe en la lista de usuarios unicos,
 *          en caso de que exista se suman las entradas pedidas, en caso de que no exista se inserta al final de la
 *          lista de usuarios unicos. Una vez finalizado el recorrido se retorna la lista de usuarios unicos.
 */
ListaUsuarios retornarEntradasUnicas(ListaUsuarios lista)
{
    ListaUsuarios aux = lista;
    ListaUsuarios listaUnica = NULL;
    while (aux != NULL)
    {
        if (existe(listaUnica, aux->rut))
        {
            listaUnica = agregarEntradas(listaUnica, aux->rut, aux->entradasPedidas);
        }
        else
        {
            listaUnica = insertarAlFinalDeLaLista(listaUnica, aux->nombre, aux->entradasPedidas, aux->rut, aux->entradasAsignadas);
        }
        aux = aux->siguiente;
    }
    return listaUnica;
}

/*
 * Entrada: Lista de usuarios.
 * Salida:  Se retorna un objeto que contiene una lista con los usuarios con entradas asignadas y una lista con los
 *          usuarios que quedaron en la lista de espera.
 * Proceso: Se asigna a un auxiliar la lista original, luego se crean dos listas vaciás que contented las entradas
 *          vendidas y las entradas pendientes por vender. Se recorre la lista original y se revisa si las entradas
 *          pedidas son entre 1 y 5, en caso de que no se sigue con la siguiente, ya que no cumple con los requisitos
 *          para obtener entradas o quedar en la lista de espera. En caso de que las entradas solicitadas por este
 *          usuario estén dentro del rango se revisa si son entre 3 y 5, en caso de que no significa que este usuario
 *          está solicitando 1 o 2 entradas, por lo que primero se revisa de que existan entradas disponibles, si no
 *          quedan disponibles se inserta este usuario al final de la lista pendientes. Si quedan entradas disponibles
 *          se inserta este usuario al final de la lista vendidas y se restan las entradas disponibles. En caso de que
 *          las entradas solicitadas por este usuario estén entre 3 y 5, se revisa si quedan entradas disponibles, si no
 *          quedan disponibles se sigue con el siguiente usuario. Si quedan entradas disponibles se inserta este usuario
 *          al final de la lista vendidas y se restan las entradas disponibles.
 *          Tras finalizar el recorrido se crea un objeto EntradasUsuarios que contendrá las listas de usuarios vendidos
 *          y pendientes y se retorna este objeto luego de asignar las respectivas listas a este objeto.
 */
EntradasUsuarios retornarEntradasYAsignarEntradas(ListaUsuarios lista)
{
    ListaUsuarios aux = lista, vendidas = NULL, pendientes = NULL;
    int entradasDisponibles = 50;
    while (aux != NULL)
    {
        if (aux->entradasPedidas <= 5 && aux->entradasPedidas > 0)
        {
            if (aux->entradasPedidas >= 3 && aux->entradasPedidas <= 5)
            {
                if (entradasDisponibles - aux->entradasPedidas > 0)
                {
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

/*
 * Entrada: Objeto que contiene las listas de usuarios vendidos y pendientes.
 * Salida:  No retorna nada.
 * Proceso: Se crean 2 variables que contendrán los nombres de los archivos donde se mostrarán los usuarios con sus
 *          entradas asignadas y los que quedaron en lista de espera. Se copia el nombre del archivo original en ambas
 *          variables y luego se reemplazan ambas extensiones por .asg y .esp respectivamente. Se abren ambos archivos
 *          en modo escritura y se recorren ambas listas, escribiendo en el archivo correspondiente los datos de cada
 *          usuario. Luego se cierran los archivos y se libera la memoria de los objetos creados.
 */
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

/*
 * Entrada: No recibe nada.
 * Salida:  No retorna nada.
 * Proceso: Se crea crea una lista de usuarios obteniendo los datos desde el archivo de texto por medio de la función
 *          leeArchivo(). Luego se crea una lista de usuarios que contendrá los usuarios únicos. A continuación por
 *          medio de la función retornarEntradasUnicas() se crea un objeto EntradasUsuarios que contendrá las listas de
 *          usuarios vendidos y pendientes y se usara para guardar los usuarios con la función guardarArchivos().
 */
void procesoPrincipal()
{
    ListaUsuarios usuarios = leeArchivo();
    ListaUsuarios lista = retornarEntradasUnicas(usuarios);
    EntradasUsuarios entradas = retornarEntradasYAsignarEntradas(lista);
    guardarArchivos(entradas);
}

/*
 * Entrada: No recibe nada.
 * Salida:  Retorna 0.
 * Proceso: Se llama a la función procesoPrincipal() y luego retorna 0.
 */
int main()
{
    procesoPrincipal();
    return 0;
}
