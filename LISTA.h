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

No *InsereLista (No *lista, task *x)
{
    No *novo;
    novo = (No*) malloc(sizeof(No));
    novo->info = x;
    novo->prox = lista;
    return novo;
}

No *RemoveInfo (No *lista, int x)
{
    No *ant = NULL;
    No *p = lista;
    while (p != NULL && p->info->code != x)
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
       printf("\n===================Tarefa:%d===================\n",p->info->code);
        printf("\nNome da tarefa: %s ",p->info->name);
        printf("\nNome do projeto: %s ",p->info->project);
        printf("\nData de inicio: ");
        imprimeData(p->info->start);
        printf("\nData de termino: ");
        imprimeData(p->info->finish);
        //printf("\n%s - ",q->info->status);
        printf("\n\n===============================================\n");
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
    return NULL;
}

#endif // LISTA_H_INCLUDED
