#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

ABO leeArchivo(char nombreArchivo[50])
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

    ABO arbol = NULL;
    while (fgets(linea, sizeof(linea), archivo))
    {
        char *rut;
        char *nombre;
        int entradas;
        strtok(linea, "\n");
        rut = strtok(linea, ",");
        nombre = strtok(NULL, ",");
        entradas = atoi(cadena);
        if (rut == NULL || nombre == NULL)
        {
            continue;
        }
        arbol = Insertar(arbol, rut, nombre, entradas);
    }

    fclose(archivo);
    return arbol;
}

ABO Insertar(ABO A, char rut[11], char nombre[25], int entradas)
{
    if (A == NULL)
    {
        A = creaNodo(dato);
    }
    else
    {
        if (strcmp(rut, A->rut) < 0)
        {
            A->izq = Insertar(A->izq, rut, nombre, entradas);
        }
        else
        {
            A->der = Insertar(A->der, rut, nombre, entradas);
        }
    }
    return A;
}

int cuentaMayoresQueValor(ABO arbol)
{
    int cont = 0;
    if (arbol == NULL)
        return 0;
    if (arbol->entradas > 2)
        cont++;
    cont += cuentaMayoresQueValor(arbol->izq);
    cont += cuentaMayoresQueValor(arbol->der);
    return cont;
}
void escribeArbol(ABO arbol, FILE *archivo)
{
    if (arbol != NULL)
    {
        escribeArbol(arbol->izq, archivo);
        fprintf(archivo, "%s\n", arbol->rut);
        printf("%s\n", arbol->rut);
        escribeArbol(arbol->der, archivo);
    }
}

void escribeEnArchivo(ABO arbol)
{
    FILE *archivo;
    archivo = fopen("arbol.txt", "w");
    if (archivo == NULL)
    {
        printf("\nError al abrir el archivo.");
        exit(1);
    }
    else
    {
        escribeArbol(arbol, archivo);
        fclose(archivo);
    }
}

ABO leerArchivoYCrearArbol(FILE *archivo)
{
    ABO arbol;
    while (!feof(archivo))
    {
        fscanf(archivo, "%s %s %i", &rut, &nombre, &entradas);
        arbol = Insertar(arbol, rut, nombre, entradas);
    }
    return arbol;
}

int main()
{

    ABO arbol = leeArchivo();

    cont = cuentaMayoresQueValor(arbol, 50);

    printf("\nNumero de nodos menores que 50: %i\n\n", cont);

    escribeEnArchivo(arbol);

    printf("\n\n");
    return 0;
}
