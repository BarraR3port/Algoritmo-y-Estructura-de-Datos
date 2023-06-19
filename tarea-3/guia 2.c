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
typedef tNodo *AB;

/*Variable global para contar el n�mero de ejecuciones*/
int cont;

//----- FUNCIONES PARA IMPRIMIR EL �RBOL BINARIO ----//
void ImprimeElementosNivel(AB A, int nivel)
{
    if (A == NULL)
        printf(" - ");
    else
    {
        if (nivel == 0)
            printf(" %i ", A->info);
        else
        {
            ImprimeElementosNivel(A->izq, nivel - 1);
            printf(" | ");
            ImprimeElementosNivel(A->der, nivel - 1);
        }
    }
}
int Maximo(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}
int Altura(AB A)
{
    if (A == NULL)
        return 0;
    else
        return Maximo(Altura(A->izq), Altura(A->der)) + 1;
}
void ImprimeArbol(AB A)
{
    int h, i;

    h = Altura(A);

    printf("\n");
    for (i = 0; i < h; i++)
    {
        ImprimeElementosNivel(A, i);
        printf("\n");
    }
}
//---------------- FIN IMPRIMIR --------------------//
AB creaNodo(int valor)
{
    AB aux;

    aux = (AB)malloc(sizeof(tNodo));
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
/// Ejercicio 3 de la Gu�a desarrollada en Clases:
bool buscaElemento(AB T, int X)
{
    cont++;
    if (T == NULL)
        return false;
    if (T->info == X)
        return true;
    return buscaElemento(T->izq, X) || buscaElemento(T->der, X);
}
/// Ejercicio 4 de la Gu�a desarrollada en Clases (se llama "algoritmo" en la gu�a):
int Peso(AB T)
{
    cont++;
    if (T == NULL)
        return 0;
    else
        return 1 + Peso(T->izq) + Peso(T->der);
}

/// CREA AQU� LA FUNCI�N "numeroHojas": QUE RETORNE CU�NTAS "hojas" (nodos con hijos nulos) TIENE DE UN �RBOL BINARIO (Ejercicio 5) ///

/// CREA AQU� LA FUNCI�N "numeroRepeticiones" QUE RETORNE CU�NTAS VECES "se repite un dato" DENTRO DE UN �RBOL (Ejercicio 6) ///

int numeroRepeticiones(AB T, int X)
{
    cont++;
    if (T == NULL)
        return 0;
    else if (T->info == X)
        return 1 + numeroRepeticiones(T->izq, X) + numeroRepeticiones(T->der, X);
    else
        return numeroRepeticiones(T->izq, X) + numeroRepeticiones(T->der, X);
}

int main()
{
    AB arbol1, arbol2;
    int numNodos, X;

    // �rbol Binario del ejercicio 3
    arbol1 = creaNodo(20);
    arbol1->izq = creaNodo(12);
    arbol1->der = creaNodo(30);
    arbol1->izq->izq = creaNodo(8);
    arbol1->izq->der = creaNodo(15);
    printf("Arbol Binario del ejercicio 3: \n");
    ImprimeArbol(arbol1);
    cont = 0;
    X = 15;
    buscaElemento(arbol1, X);
    printf("\nLa funcion buscaElemento se ejecuto %i veces al buscar %i en el arbol.", cont, X);
    cont = 0;
    X = 60;
    buscaElemento(arbol1, X);
    printf("\nLa funcion buscaElemento se ejecuto %i veces al buscar %i en el arbol.", cont, X);

    // �rbol Binario del ejercicio 4
    arbol2 = creaNodo(60);
    arbol2->izq = creaNodo(41);
    arbol2->der = creaNodo(74);
    arbol2->izq->izq = creaNodo(16);
    arbol2->izq->der = creaNodo(53);
    arbol2->der->izq = creaNodo(63);
    arbol2->izq->izq->der = creaNodo(25);
    arbol2->izq->der->izq = creaNodo(46);
    arbol2->izq->der->der = creaNodo(55);
    arbol2->der->izq->izq = creaNodo(63);
    arbol2->der->izq->der = creaNodo(70);
    arbol2->izq->der->izq->izq = creaNodo(42);
    arbol2->der->izq->izq->izq = creaNodo(63);
    arbol2->der->izq->izq->izq = creaNodo(62);
    arbol2->der->izq->izq->der = creaNodo(64);
    printf("\n\nArbol Binario del ejercicio 4: \n");
    ImprimeArbol(arbol2);

    cont = 0;
    numNodos = Peso(arbol2);
    printf("\nEl peso del arbol es: %i, y se ejecuto %i veces.", numNodos, cont);

    //------------------TRABAJO DE HOY: descomenta las lineas de abajo, para probar tus funciones "numeroHojas" y "numeroRepeticiones"

    // printf("\n\nEl primer arbol tiene %i hojas", numeroHojas(arbol1));

    // printf("\n\nEl segundo arbol tiene %i hojas", numeroHojas(arbol2));

    X = 63; // Tendr�s que repetir este valor en el arbol 2 para probar tu funci�n!!!

    printf("\n\nEl %i se repite %i veces en el segundo arbol", X, numeroRepeticiones(arbol2, X));

    printf("\n\n");
    return 0;
}
