#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

/* FUNCOES DE MANIPULACAO DE FILA

Fila* createQueue()  CRIA A FILA

int emptyQueue (Fila* f) VERIFICA SE A FILA ESTA VAIZA

void insertQueue (Fila* f, int v) INSERCAO

int removeQueue (Fila* f) REMOVE - O

Fila* freeQueue (Fila* f) LIBERA A FILA

void printQueue (Fila* f)IMPRIME A FILA
*/
typedef struct date
{
    int day;
    int month;
    int year;
} date;

typedef struct task
{
    int code;
    char name[30];
    char project[30];
    date start;
    date finish;
    int status;
    int priority;
} task;

typedef struct nos
{
    task *info;
    struct nos *next;
} No;

typedef struct fila
{
    No *first;
    No *last;
} Fila;

int
emptyQueue(Fila *f)
{
    if (f->first == NULL)
        return 1;
    return 0;
}

Fila
*createQueue()
{
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->first = f->last = NULL;
    return f;
}

No
*insertLast(No *last, task *A)
{
    No *p = (No *)malloc(sizeof(No));
    p->info = A;
    p->next = NULL;
    if (last != NULL) /* verifica se lista n�o estava vazia */
        last->next = p;
    return p;
}

void
insertQueue(Fila *f, task *v)
{
    f->last = insertLast(f->last, v);
    if (f->first == NULL) /* fila antes vazia? */
        f->first = f->last;
}

No
*removeFirst(No *first)
{
    No *p = first->next;
    free(first);
    return p;
}

task
*removeQueue(Fila *f)
{
    task *v;
    if (emptyQueue(f))
    {
        printf("Fila vazia.\n");
        exit(0); /* aborta programa */
    }
    v = f->first->info;
    f->first = removeFirst(f->first);
    if (f->first == NULL) /* fila ficou vazia? */
        f->last = NULL;
    return v;
}

void
printDate(date d)
{
    if (d.day < 10)
        printf("0%d", d.day);
    else
        printf("%d", d.day);

    if (d.month < 10)
        printf("/0%d", d.month);
    else
        printf("/%d", d.month);

    printf("/%d", d.year);
}

void
printQueue(Fila *f)
{
    No *q;
    if(f->first != NULL)
    {
        q = f->first;
        printf ("\n\n=======================Fila de Tarefas de Prioridade %d=======================\n\n",q->info->priority);
        for (q = f->first; q != NULL; q = q->next)
        {
            printf("===================Tarefa:%d===================\n", q->info->code);

            printf("\nNome da tarefa: %s ", q->info->name);

            printf("\nNome do projeto: %s ", q->info->project);

            printf("\nData de inicio: ");
            printDate(q->info->start);

            printf("\nData de termino: ");
            printDate(q->info->finish);

            printf("\nStatus:");
            if(q->info->status == 0){
                printf(" Em dia");
            }
            else if(q->info->status == 1){
                printf(" Atrasada");
            }
            else if(q->info->status == -1){
                printf(" Pendente");
            }
            printf("\n\n===============================================\n");
        }
        printf ("\n\n=========================Fim da Fila=========================\n\n");
    }

                
    
    else
    {
        printf("\n==============================================================");
        printf("\n\n Fila de Prioridade %d vazia!", q->info->priority);
        printf("\n\n==============================================================\n\n");
    }

}

Fila
*freeQueue(Fila *f)
{
    No *q = f->first;
    while (q != NULL)
    {
        No *t = q->next;
        free(q);
        q = t;
    }
    free(f);
    return NULL;
}

#endif // FILA_H_INCLUDED
