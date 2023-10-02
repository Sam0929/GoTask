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

typedef struct no {

    int info;
    struct no *prox;
}no;

no *CriaLista()
{
        no *lista;
        lista = (no*) malloc(sizeof(no));
        if (lista != NULL)
            lista->prox = NULL;
        return lista;
}

int VaziaLista (no *lista)
{
    if (lista == NULL) return 1;
    return 0;
}

no *InsereLista (no *lista, int x)
{
    no *novo;
    novo = (no*) malloc(sizeof(no));
    novo->info = x;
    novo->prox = lista;
    return novo;
}

no *RemoveInfo (no *lista, int x)
{
    no *ant = NULL;
    no *p = lista;
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

void imprimeLista (no* lista)
{

    no *p = lista;
    while (p != NULL)
    {
        printf("%d\n", p->info);
        p = p->prox;
    }
}

no *liberaLista (no* lista)
{
    no *p = lista;
    while (p != NULL)
    {
        no *t = p->prox;
        free(p);
        p = t;
    }
    free (lista);
}























#endif // LISTA_H_INCLUDED