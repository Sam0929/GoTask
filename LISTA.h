#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

/* FUNCOES DE MANIPULACAO DE LISTA

no* createList()  CRIA A LISTA

int emptyList (no* lista) VERIFICA SE A LISTA ESTA VAIZA

no *insertList (no* lista, int x) INSERCAO

no *removeInfo (no* lista, int x) REMOVE - O ELEMENTO

void printList (no* lista)IMPRIME A LISTA

no *freeList (no* lista) LIBERA A LISTA

*/

No *createList()
{
    return NULL;
}

int emptyList(No *lista)
{
    if (lista == NULL)
        return 1;
    return 0;
}

No *insertList(No *lista, task *x)
{
    No *novo;
    novo = (No *)malloc(sizeof(No));
    novo->info = x;
    novo->next = lista;
    return novo;
}

No *removeInfo(No *lista, int x)
{
    No *ant = NULL;
    No *p = lista;
    while (p != NULL && p->info->code != x)
    {
        ant = p;
        p = p->next;
    }
    if (p == NULL)
    {
        return lista;
    }
    if (ant == NULL)
    {
        lista = p->next;
    }
    else
    {
        ant->next = p->next;
    }

    free(p);
    return lista;
}

void printList(No *lista)
{

    No *p = lista;
    while (p != NULL)
    {
        printf("\n===================Tarefa:%d===================\n", p->info->code);
        printf("\nNome da tarefa: %s ", p->info->name);
        printf("\nNome do projeto: %s ", p->info->project);
        printf("\nData de inicio: ");
        printDate(p->info->start);
        printf("\nData de termino: ");
        printDate(p->info->finish);
        // printf("\n%s - ",q->info->status);
        printf("\n\n===============================================\n");
        p = p->next;
    }
}

No *freeList(No *lista)
{
    No *p = lista;
    while (p != NULL)
    {
        No *t = p->next;
        free(p);
        p = t;
    }
    free(lista);
    return NULL;
}

#endif // LISTA_H_INCLUDED
