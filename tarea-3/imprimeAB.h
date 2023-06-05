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
