#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "TDAFila.h"

//Variables globales:
int **Grafo; //Matriz del grafo
int numNodos, numArcos;

bool *Visitados; //Este arreglo de booleanos se creará cuando se ejecute este programa

bool *creaArreglo(int numCeldas)
{
   bool *Arreglo;

   Arreglo = calloc(numCeldas, sizeof(bool));

   return Arreglo;
}
void reseteaVisitados()
{
    int i;

    for(i=0; i<numNodos;i++)
        Visitados[i] = false;
}
int **creaMatriz(int filas, int columnas)
{
   int **Matriz;
   int i;

   Matriz = calloc(filas, sizeof(int *));

   for(i=0; i<filas; i++)
   {
      Matriz[i] = calloc(columnas, sizeof(int));
   }
   return Matriz;
}
void imprimeMatriz(int **Matriz, int n)
{
    int i, j;

    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            printf("%4i", Matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void leeGrafo()
{
    FILE *arch;
    int i, nodo1, nodo2, costo;
    char nomArchivo[30];

    printf("Ingresa el nombre del archivo: ");
    fgets(nomArchivo, 30, stdin);
    strtok(nomArchivo, "\n");

    arch = fopen(nomArchivo, "r");
    if (arch == NULL)
    {
        printf("El archivo %s no se encuentra. Revisa su ubicacion.", nomArchivo);
        exit(-1);
    }
    fscanf(arch, "%i", &numNodos);
    Grafo = creaMatriz(numNodos, numNodos);
    fscanf(arch, "%i", &numArcos);
    for(i=1; i<=numArcos; i++)
    {
       fscanf(arch, "%i", &nodo1);
       fscanf(arch, "%i", &nodo2);
       fscanf(arch, "%i", &costo);
       Grafo[nodo1][nodo2] = costo;
       Grafo[nodo2][nodo1] = costo;
    }
    fclose(arch);
}
void Profundidad(int nodo)
{
    int i;

    Visitados[nodo] = true;
    printf("%i ", nodo);
    for (i=0; i<numNodos; i++)
    {
        if (Grafo[nodo][i] != 0 && Visitados[i] == false)
        {
            Profundidad(i); //el vértice "i" adyacente a "nodo" y sin visitar, es por donde continúa el recorrido.
        }
    }
}
void Amplitud(int v0)
{
   int i, nodo;

   Encolar(v0);
   while (F != NULL)
   {
      nodo = Desencolar();
      Visitados[nodo] = true;
      printf("%i ", nodo);
      for (i=0; i<numNodos; i++)
      {
         if (Grafo[nodo][i] != 0 && Visitados[i] == false && Esta(i) == false)
         {
            Encolar(i);  //El vértice "i" que es adyacente al "nodo", sin visitar y que no esté en la fila, lo encola.
         }
      }
   }
}
int main()
{
    int v0;

    leeGrafo();
    printf("\nMatriz del grafo: \n");
    imprimeMatriz(Grafo, numNodos);

    Visitados = creaArreglo(numNodos);

    v0 = 1; //Cambia este valor para probar diferentes recorridos.
    printf("Recorrido en profundidad desde el nodo %i: ", v0);
    Profundidad(v0);

    reseteaVisitados();

    printf("\n\nRecorrido en amplitud desde el nodo %i: ", v0);
    Amplitud(v0);

    printf("\n\n");
    return 0;
}







