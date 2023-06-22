#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo
{
    char rut[11];
    char nombre[25];
    int entradas;
    struct nodo *izq;
    struct nodo *der;
};
typedef struct nodo tNodo;
typedef tNodo *ABO;

/*
 * Entrada: rut del usuario, nombre del usuario, cantidad de entradas solicitadas
 * Salida:  Nodo inicializado con los datos entregados.
 * Proceso: Se eloja la memoria necesaria para el nodo y se inicializan los valores.
 *          luego se retorna el nodo.
 * */
ABO crearArbol(char rut[11], char nombre[25], int entradas)
{
    ABO arbol = (ABO)malloc(sizeof(tNodo));
    strcpy(arbol->rut, rut);
    strcpy(arbol->nombre, nombre);
    arbol->entradas = entradas;
    arbol->izq = NULL;
    arbol->der = NULL;
    return arbol;
}

/*
 * Entrada: Árbol binario de búsqueda (ABO), rut del usuario, nombre del usuario, cantidad de entradas solicitadas.
 * Salida:  Árbol binario de búsqueda con el nodo insertado o creado.
 * Proceso: Verifica si el árbol es nulo. Si es así, crea un nuevo nodo con los datos ingresados.
 *          Si no es nulo, compara el rut del nodo actual con el rut ingresado y decide si el nuevo nodo se inserta a la izquierda o a la derecha.
 *          Luego, realiza la llamada recursiva correspondiente para seguir insertando el nodo en el subárbol izquierdo o derecho.
 *          Finalmente, retorna el árbol modificado con el nuevo nodo insertado o creado.
 * */
ABO insertarNodoOCrear(ABO arbol, char rut[11], char nombre[25], int entradas)
{
    if (arbol == NULL)
    {
        arbol = crearArbol(rut, nombre, entradas);
    }
    else
    {
        int comparacion = strcmp(rut, arbol->rut);
        if (comparacion == 0)
        {
            arbol->entradas += entradas;
        }
        else if (comparacion < 0)
        {
            arbol->izq = insertarNodoOCrear(arbol->izq, rut, nombre, entradas);
        }
        else
        {
            arbol->der = insertarNodoOCrear(arbol->der, rut, nombre, entradas);
        }
    }
    return arbol;
}

/*
 * Entrada: Nombre del archivo a leer.
 * Salida:  Árbol binario de búsqueda construido a partir de los datos del archivo.
 * Proceso: Abre el archivo en modo lectura. Si no se puede abrir, muestra un mensaje de error y cierra el programa.
 *          Lee cada línea del archivo, separa los campos utilizando la coma como delimitador y convierte la cantidad de entradas a un entero.
 *          Luego, llama a la función insertarNodoOCrear() para insertar o crear el nodo correspondiente en el árbol.
 *          Finalmente, cierra el archivo y retorna el árbol construido.
 * */
ABO leerArchivoYCrearArbol(char *nombreArchivo)
{
    ABO arbol;
    char linea[150];
    FILE *archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL)
    {
        printf("Archivo invalido o no encontrado, cerrando el programa.");
        exit(-1);
    }

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
        arbol = insertarNodoOCrear(arbol, rut, nombre, entradas);
    }

    fclose(archivo);
    return arbol;
}

/*
 * Entrada: Archivo a verificar y nombre del archivo de salida.
 * Salida:  Archivo de salida creado o el mismo archivo si ya está abierto.
 * Proceso: Verifica si el archivo ya está abierto. Si es así, lo retorna sin modificar.
 *          Si no está abierto, crea un nuevo archivo de salida con el nombre proporcionado en modo escritura.
 *          Luego, retorna el archivo de salida creado.
 * */
FILE *crearArchivoSalida(FILE *archivo, char *nombreArchivoSalida)
{
    if (archivo != NULL)
    {
        return archivo;
    }
    FILE *archivoSalida = fopen(nombreArchivoSalida, "w");
    return archivoSalida;
}

/*
 * Entrada: Árbol binario de búsqueda y archivo de salida (puede ser NULL).
 * Salida:  Cantidad de nodos en el árbol que cumplen con la condición de tener más de 2 entradas.
 * Proceso: Verifica si el árbol es nulo. Si es así, retorna 0.
 *          Realiza una llamada recursiva para verificar el subárbol izquierdo.
 *          Si el número de entradas del nodo actual es mayor a 2, incrementa el contador y, si el archivo de salida no es nulo, escribe los datos en el archivo.
 *          Finalmente, realiza una llamada recursiva para verificar el subárbol derecho y suma el resultado al contador.
 *          Retorna el contador final.
 * */
int checkearEntradas(ABO arbol, FILE *archivo)
{
    if (arbol == NULL)
    {
        return 0;
    }
    int count = 0;

    count += checkearEntradas(arbol->izq, archivo);

    if (arbol->entradas > 2)
    {
        count++;
        if (archivo != NULL)
        {
            fprintf(archivo, "Rut: %s nombre: %s entradas: %i\n", arbol->rut, arbol->nombre, arbol->entradas);
        }
    }

    count += checkearEntradas(arbol->der, archivo);

    return count;
}

/*
 * Entrada: Árbol binario de búsqueda y nombre del archivo original.
 * Salida:  Ninguna.
 * Proceso: Crea el nombre del archivo de salida reemplazando la extensión con ".sde".
 *          Abre el archivo de salida en modo escritura.
 *          Imprime un mensaje en pantalla indicando el nombre del archivo generado.
 *          Llama a la función checkearEntradas() para obtener la cantidad de nodos que cumplen con la condición.
 *          Escribe el resultado en el archivo de salida junto con un texto adicional.
 *          Cierra el archivo de salida.
 * */
void escribirTotal(ABO arbol, char *nombreArchivo)
{
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

/*
 * Entrada: Ninguna.
 * Salida:  Ninguna.
 * Proceso: Solicita al usuario ingresar el nombre del archivo.
 *          Llama a la función leerArchivoYCrearArbol() para obtener el árbol a partir de los datos del archivo.
 *          Verifica si todos los nodos cumplen con la cantidad correcta de entradas.
 *          Si es así, muestra un mensaje indicando que todos los usuarios solicitaron la cantidad correcta.
 *          Si no, llama a la función escribirTotal() para generar el archivo de salida con los nodos que no cumplieron con la cantidad de entradas.
 * */
void procesoPrincipal()
{
    char nombreArchivo[50];

    printf("Ingresa el nombre del archivo: ");
    fgets(nombreArchivo, 50, stdin);
    strtok(nombreArchivo, "\n");

    ABO arbol = leerArchivoYCrearArbol(nombreArchivo);

    if (checkearEntradas(arbol, NULL) == 0)
    {
        printf("Todos solicitaron la cantidad correcta de entradas\n");
    }
    else
    {
        escribirTotal(arbol, nombreArchivo);
    }
}

/*
 * Entrada: Ninguna.
 * Salida:  0 si el programa finalizó correctamente.
 * Proceso: Llama a la función procesoPrincipal() para iniciar el procesamiento del programa.
 *          Retorna 0 al finalizar.
 * */
int main()
{

    procesoPrincipal();
    return 0;
}
