#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED


/* FUNCOES DE MANIPULACAO DE LISTA

no* CriaLista()  CRIA A LISTA

int VaziaLista (no* lista) VERIFICA SE A LISTA ESTA VAIZA

no *InsereLista (no* lista, int x) INSERCAO

no *RemoveInfo (no* lista, int x) REMOVE - O ELEMENTO

void imprimeLista (no* lista)IMPRIME A LISTA

no *liberaLista (no* lista) LIBERA A LISTA

*/

No *CriaLista()
{
    return NULL;
}

int VaziaLista (No *lista)
{
    if (lista == NULL) return 1;
    return 0;
}

No *InsereLista (No *lista, No *x)
{
    No *novo;
    novo = x;
    novo->prox = lista;
    return novo;
}

No *RemoveInfo (No *lista, No* x)
{
    No *ant = NULL;
    No *p = lista;
    while (p != NULL && p->info != x)
    {
        ant = p;
        p = p->prox;
    }
    if (p == NULL)
    {
        return lista;
    }
        if (ant == NULL)
        {
            lista = p->prox;
        }
        else
        {
            ant->prox = p->prox;
        }

    free(p);
    return lista;
}

void imprimeLista (No* lista)
{

    No *p = lista;
    while (p != NULL)
    {
        printf("%d\n", p->info->code);
        p = p->prox;
    }
}

No *liberaLista (No* lista)
{
    No *p = lista;
    while (p != NULL)
    {
        No *t = p->prox;
        free(p);
        p = t;
    }
    free (lista);
}

#endif // LISTA_H_INCLUDED
