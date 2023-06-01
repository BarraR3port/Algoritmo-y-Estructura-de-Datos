#include <stdio.h>
#include <stdlib.h>

struct nodo
{
    int info;
    struct nodo *izq;
    struct nodo *der;
};

typedef struct nodo tNodo;
typedef tNodo *AB;

int veces_peso = 0;

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

AB crearNodos()
{
    AB arbol_main = creaNodo(6);
    AB arbol_1_0 = creaNodo(2);
    AB arbol_1_1 = creaNodo(3);
    AB arbol_2_0 = creaNodo(0);
    AB arbol_2_1 = creaNodo(7);
    AB arbol_2_2 = creaNodo(4);
    AB arbol_2_3 = creaNodo(1);
    arbol_main->der = arbol_1_1;
    arbol_main->izq = arbol_1_0;
    arbol_1_0->izq = arbol_2_0;
    arbol_1_0->der = arbol_2_1;
    arbol_1_1->izq = arbol_2_2;
    arbol_1_1->der = arbol_2_3;

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

int main()
{
    AB arbol_main = crearNodos();
    ImprimeArbol(arbol_main);
    printf("El peso del arbol es: %i", peso(arbol_main));
    printf("\nNumero de dejcuciones: %i", veces_peso);

    return 0;
}