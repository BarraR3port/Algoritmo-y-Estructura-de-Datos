#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct nodo
{
    int info;
    struct nodo *izq;
    struct nodo *der;
};
typedef struct nodo tNodo;
typedef tNodo *ABO;

ABO creaNodo(int valor)
{
    ABO aux;

    aux = malloc(sizeof(tNodo));
    if (aux != NULL)
    {
        aux->info = valor;
        aux->izq = NULL;
        aux->der = NULL;
    }
    else
    {
        printf("\nNo hay memoria suficiente.");
        exit(1);
    }
    return aux;
}
ABO Insertar(ABO A, int dato)
{
    if (A == NULL)
    {
        A = creaNodo(dato);
    }
    else
    {
        if (dato < A->info)
        {
            A->izq = Insertar(A->izq, dato);
        }
        else
        {
            A->der = Insertar(A->der, dato);
        }
    }
    return A;
}

int cuentaMayoresQueValor(ABO arbol, int valor)
{
    int cont = 0;
    if (arbol == NULL)
        return 0;
    if (arbol->info > valor)
        cont++;
    cont += cuentaMayoresQueValor(arbol->izq, valor);
    cont += cuentaMayoresQueValor(arbol->der, valor);
    return cont;
}
void inOrden(ABO arbol)
{
    if (arbol != NULL)
    {
        inOrden(arbol->izq);
        printf("%i ", arbol->info);
        inOrden(arbol->der);
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
        inOrdenArchivo(arbol, archivo);
        fclose(archivo);
    }
}

int main()
{
    ABO arbol;
    int cont;

    arbol = NULL;
    arbol = Insertar(arbol, 60);
    arbol = Insertar(arbol, 41);
    arbol = Insertar(arbol, 74);
    arbol = Insertar(arbol, 16);
    arbol = Insertar(arbol, 53);
    arbol = Insertar(arbol, 65);
    arbol = Insertar(arbol, 25);
    arbol = Insertar(arbol, 46);
    arbol = Insertar(arbol, 55);
    arbol = Insertar(arbol, 63);
    arbol = Insertar(arbol, 70);
    arbol = Insertar(arbol, 42);
    arbol = Insertar(arbol, 62);
    arbol = Insertar(arbol, 64);

    cont = cuentaMayoresQueValor(arbol, 50);

    printf("\nNumero de nodos menores que 50: %i\n\n", cont);

    inOrden(arbol);

    escribeEnArchivo(arbol);

    printf("\n\n");
    return 0;
}
