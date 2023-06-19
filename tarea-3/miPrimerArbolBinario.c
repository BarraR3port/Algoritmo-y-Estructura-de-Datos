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

int veces_peso = 0;

int vecesRepetidas = 0;

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

AB creaNodo(int info)
{
    AB nuevoNodo = malloc(sizeof(tNodo));
    if (nuevoNodo == NULL)
    {
        printf("No hay memoria disponible!\n");
        exit(EXIT_FAILURE);
    }
    nuevoNodo->info = info;
    nuevoNodo->izq = NULL;
    nuevoNodo->der = NULL;
    return nuevoNodo;
}

int algoritmo(AB a)
{
    if (a == NULL)
    {
        return 0;
    }
    vecesRepetidas++;

    return 1 + algoritmo(a->izq) + algoritmo(a->der);
}

AB crearNodos()
{
    AB arbol_main = creaNodo(60);

    AB arbol_1_0 = creaNodo(41);
    AB arbol_1_1 = creaNodo(65);

    AB arbol_2_0 = creaNodo(16);
    AB arbol_2_1 = creaNodo(53);
    AB arbol_2_2 = creaNodo(65);

    AB arbol_3_0 = NULL;

    arbol_main->der = arbol_1_1;
    arbol_main->izq = arbol_1_0;
    arbol_1_0->izq = arbol_2_0;
    arbol_1_0->der = arbol_2_1;
    arbol_1_1->izq = arbol_2_2;
    arbol_1_1->der = NULL;

    return arbol_main;
}

int peso(AB arbol)
{
    veces_peso++;
    if (arbol == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + peso(arbol->izq) + peso(arbol->der);
    }
}

int valores_encontrados = 0;

int encontrar(AB arbol, int x)
{
    veces_peso++;
    if (arbol == NULL)
    {
        return 0;
    }
    if (arbol->info == x)
    {
        valores_encontrados++;
        return 1;
    }
    return encontrar(arbol->izq, x) + encontrar(arbol->der, x);
}

int main()
{
    AB arbol_main = crearNodos();
    ImprimeArbol(arbol_main);
    // printf("Valor del algoritmo: %i y se ejecuta: %i", algoritmo(arbol_main), vecesRepetidas);
    printf("\nEl peso del arbol es: %i", peso(arbol_main));
    printf("\nNumero de dejcuciones: %i", veces_peso);
    int encontrados = encontrar(arbol_main, 65);
    printf("\nNumero de valores encontrados: %i", encontrados);

    return 0;
}