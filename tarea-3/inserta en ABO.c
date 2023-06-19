#include <stdio.h>
#include <stdlib.h>

struct nodo{
    int info;
    struct nodo *izq;
    struct nodo *der;
};
typedef struct nodo tNodo;
typedef tNodo *ABO;

//----- FUNCIONES PARA IMPRIMIR EL ÁRBOL BINARIO ORDENADO ----//
void ImprimeElementosNivel(ABO A, int nivel)
{
    if (A == NULL)
        printf(" - ");
    else
    {
        if (nivel == 0)
            printf(" %i ", A->info);
        else
        {
            ImprimeElementosNivel(A->izq, nivel-1);
            printf(" | ");
            ImprimeElementosNivel(A->der, nivel-1);
        }
    }
 }
int Maximo(int a, int b)
{
    if (a>b)
        return a;
    else
        return b;
}
int Altura(ABO A)
{
    if (A == NULL)
        return 0;
    else
        return Maximo(Altura(A->izq), Altura(A->der)) + 1;
}
void ImprimeArbol(ABO A)
{
    int h, i;

    h = Altura(A);

    printf("\n");
    for(i=0;i<h;i++)
    {
        ImprimeElementosNivel(A,i);
        printf("\n");
    }
}
//---------------- FIN IMPRIMIR --------------------//
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
int main()
{
    ABO arbol;
    int dato, i, numNodos;

    numNodos = 4; ///Revisa con diferentes valores, para que valides el árbol que se construye: Debe estar ordenado!

    arbol = NULL;
    for(i=0; i<numNodos; i++)
    {
        printf("Ingresa un entero: ");
        scanf("%i", &dato);
        arbol = Insertar(arbol, dato);
    }
    ImprimeArbol(arbol);

    printf("\n\n");
    return 0;
}
