#include <stdio.h>
#include <stdlib.h>

struct grafo {
    int **matriz;
    int filas;
};

typedef struct grafo tGrafo;
typedef tGrafo *Grafo;

int **creaMatriz(int M, int N) {
    int **Matriz;
    int i;

    Matriz = malloc(M * sizeof(int *));

    for (i = 0; i < M; i++) {
        Matriz[i] = calloc(N,sizeof(int));
    }
    return Matriz;
}

void imprimeMatriz(int **M, int n) {
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%4i",M[i][j]);
        }
        printf("\n");
    }
}
/*CUARTO: Crea la fución "imprimeAdyacentes".
Esta función debe recibir como parámetro 1 nodo y debe imprimir los adyacentes que posea en el grafo.
Esta función NO tiene retorno.
*/

/*PRIMERO:
Genera la función "leeGrafo" revisada en clases.
Esta funcion debe "retornar" el grafo, el número de nodos ("n") y el número de arcos ("m")
*/

Grafo leeGrafo(char nomArchivo[50]) {
    FILE *arch;
    int n, m, i, nodo1, nodo2, costo;
    int **M; //Matriz del grafo

    arch = fopen(nomArchivo, "r");
    fscanf(arch, "%i", &n);
    M = creaMatriz(n, n);
    fscanf(arch, "%i", &m);
    for (i = 1; i <= m; i++) {
        fscanf(arch, "%i", &nodo1);
        fscanf(arch, "%i", &nodo2);
        fscanf(arch, "%i", &costo);
        M[nodo1][nodo2] = costo;
        M[nodo2][nodo1] = costo;
    }
    fclose(arch);
    Grafo grafo = malloc(sizeof(tGrafo));
    grafo->matriz = M;
    grafo->filas = n;
    return grafo;
}



int main() {
    /*
    SEGUNDO: Llama a la función "leeGrafo"
    */
    Grafo grafo = leeGrafo("grafo1.txt");

    imprimeMatriz(grafo->matriz, grafo->filas);

    /*
    TERCERO: imprime la matriz del grafo usando la función "imprimeMatriz"
    */
    /*
    QUINTO:
    Pídele aquí al usuario (en main) un nodo.
    Verifica que el nodo que solicita el usuario sea un valor entre 0 y n-1
    Si el nodo es válido, llama a la función "imprimeAdyacentes"
    */
    printf("\n\n");
    return 0;
}
