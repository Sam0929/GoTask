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

No
*createList()
{
    return NULL;
}

int
emptyList(No *lista)
{
    if (lista == NULL)
        return 1;
    return 0;
}

No
*insertList(No *lista, task *x)
{
    No *novo;
    novo = (No *)malloc(sizeof(No));
    novo->info = x;
    novo->next = lista;
    return novo;
}

int
compareDates(date d1, date d2)
{
    if (d1.year > d2.year)
    {
        return -1;
    }
    else if (d1.year < d2.year)
    {
        return 1;
    }
    else // Os anos são iguais, verifique os meses e dias.
    {
        if (d1.month > d2.month)
        {
            return -1;
        }
        else if (d1.month < d2.month)
        {
            return 1;
        }
        else // Os meses são iguais, verifique os dias.
        {
            if (d1.day > d2.day)
            {
                return -1;
            }
            else if (d1.day < d2.day)
            {
                return 1;
            }
            else // As datas são iguais.
            {
                return 0;
            }
        }
    }
}
No
*insertListByDate(No *lista, task *x)
{
    No *novo;
    novo = (No *)malloc(sizeof(No));
    novo->info = x;

    if (lista == NULL || compareDates(lista->info->finish, novo->info->finish) < 0)
    {
        novo->next = lista;
        return novo;
    }

    No *prev = NULL;
    No *p = lista;

    while (p != NULL && compareDates(p->info->finish, novo->info->finish) > 0)
    {
        prev = p;
        p = p->next;
    }

    novo->next = p;

    if (prev != NULL)
    {
        prev->next = novo;
        return lista;
    }
    else
    {
        return novo;
    }
}

No
*removeInfo(No *lista, int x)
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

void
printList(No *lista)
{

    No *p = lista;
    printf ("\n\n=======================Lista de Tarefas=======================\n\n");
    while (p != NULL)
    {
        printf("\n===================Tarefa:%d===================\n", p->info->code);
        printf("\nNome da tarefa: %s ", p->info->name);
        printf("\nNome do projeto: %s ", p->info->project);
        printf("\nData de inicio: ");
        printDate(p->info->start);
        printf("\nData de termino: ");
        printDate(p->info->finish);
        printf("\nStatus:");
        if(p->info->status == 0){
            printf(" Em dia");
        }
        else if(p->info->status == 1){
            printf(" Atrasada");
        }
        else if(p->info->status == -1){
            printf(" Pendente");
        }
        printf("\n\n===============================================\n");
        p = p->next;
    }
    printf ("\n\n=========================Fim da Lista=========================\n\n");
}

No
*freeList(No *lista)
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
