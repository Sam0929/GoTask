#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>
#include "FILA.h"
#include "LISTA.h"

date getdate(boolean ini);
void readTask(Fila *p);
void updateTask(Fila *p);
Fila *finishTask(Fila *p, No **t);
int verifyDate(date d);
void setStatus(task *t);
void printMark();
Fila *updateStatus(Fila *p, No **t);


int main()

{
    Fila *tarefas_criadas = createQueue();
    No *tarefas_concluidas = createList();
    No *tarefas_pendentes = createList();

    int Choose;

    while (Choose != 9)
    {
        system("cls");
        printf("==============================================================");
        printf("\n\n                    Bem vindo ao GoTask!!\n\n");
        printf("==============================================================\n\n");
        printf(" 1 - Incluir Tarefas \n\n 2 - Imprimir fila \n\n 3 - Atualizar tarefa \n\n 4 - Concluir Tarefa\n\n 5 - TESTE - IMPRIMIR LISTA \n\n 6 - Atualizar status \n\n 9 - Sair do sistema \n\n Escolha a opcao:");
        scanf("%d", &Choose);

        switch (Choose)
        {
        case 1:

            system("cls");
            readTask(tarefas_criadas);

            break;

        case 2:
            system("cls");
            printQueue(tarefas_criadas);
            system("pause");

            break;

        case 3:

            system("cls");
            updateTask(tarefas_criadas);

            break;

        case 4:
            system("cls");
            tarefas_criadas = finishTask(tarefas_criadas, &tarefas_concluidas);

            break;

        case 5:
        
            system("cls");
            printList(tarefas_concluidas);
            printList(tarefas_pendentes);
            system("pause");
            break;
        case 6:
            
            tarefas_criadas = updateStatus(tarefas_criadas, &tarefas_pendentes);
            system("pause");
            break;
        }
    }
    system("cls");
    printf("\n\n==============================================================\n\n");
    printf("\t\tObrigado por utilizar nosso sistema!! \n\n\t\t\tAte a proxima!");
    printf("\n\n==============================================================");

    tarefas_criadas = freeQueue(tarefas_criadas);
    tarefas_concluidas = freeList(tarefas_concluidas);

    return 0;
}

void 
printMark ()
{
    printf("==============================================================");
    printf("\n\n                        GoTask 1.0\n\n");
    printf("==============================================================\n\n");
}

date 
getdate(boolean ini)
{
    date d;
    if (ini)
    {
        SYSTEMTIME t;
        GetLocalTime(&t);
        d.day = t.wDay;
        d.month = t.wMonth;
        d.year = t.wYear;
    }

    else
    {
        scanf("%d %d %d", &d.day, &d.month, &d.year);
    }
    return d;
}

void 
readTask(Fila *p)
{

    task *t = (task *)malloc(sizeof(task));
    printMark();
    printf("Digite o codigo da tarefa:");
    scanf("%d", &(t->code));
    fflush(stdin);
    printf("\n\nDigite o nome da tarefa:");
    scanf(" %[^\n]", (t->name));
    printf("\n\nDigite o nome do projeto:");
    scanf(" %[^\n]", (t->project));
    t->start = getdate(1);
    printf("\n\nDigite a data de termino (dd mm aaaa):");
    do
    {
        t->finish = getdate(0);
    } while (t->finish.day < 1 ||
             t->finish.day > 31 || 
             t->finish.month > 12 || 
             t->finish.year > 2100);

    insertQueue(p, t);
    setStatus(t);

    printf("\n\n==============================================================");
    printf("\n\nTarefa lida com sucesso!");
    printf("\n\n==============================================================");
}

No
*searchTask (Fila *p)
{
    No *aux = p->first;
    int code;
    scanf("%d", &code);
    while (aux != NULL && aux->info->code != code)
    {
        aux = aux->next;
    }
    return (aux);
}

void 
updateTask(Fila *p)
{
    printf("==============================================================\n\n");
    printf("Que tarefa deseja modificar?");
    printf("\n\n==============================================================\n\n");
    printf("Digite o codigo da tarefa:");
    No *aux = searchTask(p);

    if (aux == NULL)
    {
        printf("\nImpossivel localizar a tarefa, por favor, tente novamente!\n\n");
        system("pause");
    }

    else
    {
        system("cls");

        task *aux1 = aux->info;

        int Choose;

        printf("==============================================================");
        printf("\n\nO que voce deseja modificar?");
        printf("\n\n==============================================================\n\n");
        printf(" 1 - Codigo \n\n 2 - Nome da tarefa \n\n 3 - Nome do projeto \n\n 4 - Data de inicio \n\n 5 - Data de termino \n\n 6 - Cancelar \n\n Escolha a opcao:");
        scanf("%d", &Choose);

        switch (Choose)
        {
        case 1:

            printf("\n\nDigite o novo codigo da tarefa:");
            scanf("%d", &(aux1->code));

            break;

        case 2:

            printf("\n\nDigite o novo nome da tarefa:");
            scanf(" %[^\n]", (aux1->name));
            break;

        case 3:

            printf("\n\nDigite o novo nome do projeto:");
            scanf(" %[^\n]", (aux1->project));

            break;

        case 4:

            aux1->start = getdate(1);

            break;

        case 5:

            printf("\n\nDigite a nova data de termino da tarefa:");
            aux1->finish = getdate(0);

            break;

        case 6:

            return;

            break;
        }
        printf("\n\n==============================================================");
        printf("\n\nTarefa modificada com sucesso!!");
        sleep(2);
    }
}

Fila 
*finishTask(Fila *p, No **t)
{
    
    printQueue(p);
    task *aux;
    Fila *aux1 = p;
    Fila *aux2 = createQueue();
    int flag = 0;

    int code;
    printf("==============================================================\n\n");
    printf("Que tarefa deseja concluir?");
    printf("\n\n==============================================================\n\n");
    scanf("%d", &code);
    while (!emptyQueue(aux1))
    {
        aux = removeQueue(aux1);
        if (aux->code == code)
        {
            *t = insertListByDate(*t, aux);
            printf("\n==============================================================");
            printf("\n\nTarefa concluida com sucesso!");
            flag++;
        }
        else
        {
            insertQueue(aux2, aux);
        }
    }

    if (!flag)
        printf("\n\nTarefa nao encontrada, por favor, tente novamente!\n\n");

    sleep(2);

    return aux2;
}

int
verifyDate(date d)
{
    SYSTEMTIME t;
    GetLocalTime(&t);
    if (d.year < t.wYear)
        return -1;
    else if (d.year == t.wYear && d.month < t.wMonth)
        return -1;
    else if (d.year == t.wYear && d.month == t.wMonth && d.day < t.wDay)
        return -1;
    else if (d.year == t.wYear && d.month == t.wMonth && d.day == t.wDay)
        return 1;
    else
        return 0;
}

void
setStatus(task *t)
{
      t->status = verifyDate(t->finish);  
}

Fila  
*updateStatus (Fila *p, No **t)
{   
    printQueue(p);
    task *aux;
    Fila *aux1 = p;
    Fila *aux2 = createQueue();
    int flag = 0;
    int code;
    printf("==============================================================\n\n");
    printf("Que tarefa deseja atualizar?");
    printf("\n\n==============================================================\n\n");
    scanf("%d", &code);
    while (!emptyQueue(aux1))
    {
        aux = removeQueue(aux1);
        if (aux->code == code)
        {
            *t = insertListByDate(*t, aux);
            aux -> status = -1;
            printf("\n==============================================================");
            printf("\n\nStatus atualizado com sucesso!\n\n");
            flag++;
        }
        else
        {
            insertQueue(aux2, aux);
        }
    }

    if (!flag)
        printf("\n\nTarefa nao encontrada, por favor, tente novamente!\n\n");

    return aux2;
}
