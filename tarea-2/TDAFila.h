typedef struct nodo{
    int info;
    struct nodo *sig;
} tNodo;

typedef tNodo *Fila;

//La fila se maneja en forma global:
Fila F, U = NULL;    //F es el puntero al primer elemento de la fila, U es el puntero al último elemento.

Fila CreaNodo(int valor)
{
    Fila aux;
    aux = malloc(sizeof(tNodo));
    aux->info = valor;
    aux->sig = NULL;
    return aux;
}
void Encolar(int x)
{
    Fila aux, pNodo;

    aux = F;
    pNodo = CreaNodo(x);
    if (F == NULL)
        F = pNodo;
    else
        U->sig = pNodo;
    U = pNodo;
    pNodo = NULL;
}
int Desencolar()
{
    Fila aux;
    int valor;

    aux = F;
    if (aux != NULL)
    {
        valor = aux->info;
        if (F == U)
            U = NULL;
        F = F->sig;
        aux->sig = NULL;
        free(aux);
    }
    return valor;
}
bool Esta(int dato)
{
    Fila aux = F;

    while (aux != NULL)
    {
        if (dato == aux->info)
            return true;
        aux = aux->sig;
    }
    return false;
}
