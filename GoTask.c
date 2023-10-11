#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>
#include "FILA.h"
#include "LISTA.h"

date getdate(boolean ini);
void readTask(Fila *p1, Fila *p2, Fila *p3);
void updateTask(Fila *p1,Fila *p2,Fila *p3);
void finishTask(Fila *p1,Fila *p2,Fila *p3, No **t);
int verifyDate(date d);
void setStatus(task *t);
void printMark();
Fila *updateStatus(Fila *p, No **t);

int main()

{
    Fila *tarefasp1 = createQueue();
    Fila *tarefasp2 = createQueue();
    Fila *tarefasp3 = createQueue();
    No *tarefas_concluidas = createList();
    No *tarefas_pendentes = createList();

    int Choose;

    while (Choose != 9)
    {
        system("cls");
        printf("==============================================================");
        printf("\n\n                    Bem vindo ao GoTask!!\n\n");
        printf("==============================================================\n\n");
        printf(" 1 - Incluir Tarefas \n\n 2 - Imprimir fila \n\n 3 - Atualizar tarefa \n\n 4 - Concluir Tarefa\n\n 5 - Atualizar Status \n\n 6 - Imprimir tarefas concluidas \n\n 7 - Imprimir tarefas pendentes \n\n 8 - Imprimir tarefas concluidas (Com e sem atraso)  \n\n 9 - Sair do sistema \n\n Escolha a opcao:");
        scanf("%d", &Choose);

        switch (Choose)
        {
        case 1:

            system("cls");
            readTask(tarefasp1,tarefasp2,tarefasp3);
            break;

        case 2:

            system("cls");
            printQueue(tarefasp1);
            printQueue(tarefasp2);
            printQueue(tarefasp3);
            system("pause");
            break;

        case 3:

            system("cls");
            updateTask(tarefasp1, tarefasp2, tarefasp3);
            break;

        case 4:

            system("cls");
            finishTask(tarefasp1, tarefasp2, tarefasp3, &tarefas_concluidas);
            break;

        case 5:

            system("cls");
            updateStatus(tarefasp1, tarefasp2, tarefasp3, &tarefas_pendentes);
            system("pause");
            break;
        case 6:

            system("cls");
            printList(tarefas_concluidas);
            system("pause");
            break;
        case 7:

            system("cls");
            printList(tarefas_pendentes);
            system("pause");
            break;
        case 8:
            system("cls");
            printListByStatus(tarefas_concluidas);
            system("pause");
            break;
        }
    }
    
    tarefas_criadas = freeQueue(tarefas_criadas);
    tarefas_concluidas = freeList(tarefas_concluidas);

    system("cls");
    printf("\n\n==============================================================\n\n");
    printf("\t\tObrigado por utilizar nosso sistema!! \n\n\t\t\tAte a proxima!");
    printf("\n\n==============================================================");

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
readTask(Fila *p1, Fila *p2, Fila *p3)
{

    task *t = (task *)malloc(sizeof(task));
    int aux = 0;
    printMark();
    printf("Digite o codigo da tarefa:");
    scanf(" %d", &(t->code));
    fflush(stdin);
    printf("\n\nDigite o nome da tarefa:");
    scanf(" %[^\n]", (t->name));
    printf("\n\nDigite o nome do projeto:");
    scanf(" %[^\n]", (t->project));
    t->start = getdate(1);
    printf("\n\nDigite a data de termino (dd mm aaaa):");
    do
    {   
        if(aux > 0){printf("\nData invalida, por favor insira uma data correta!\nInsira a nova data:");}
        t->finish = getdate(0);
        aux = 1;
    } while (compareDates(t->finish, t->start) > 0||
             t->finish.day < 1||
             t->finish.day > 31 ||
             t->finish.month > 12 ||
             t->finish.year > 2100);
    
    printf("Qual nivel de prioridade (1 - Alta | 2 - Normal | 3 - Baixa):");
    scanf(" %d",&t->priority);
    switch (t->priority)
    {
        case 1:
            insertQueue(p1, t);
            break;
        case 2:
            insertQueue(p2, t);
            break;
        case 3:
            insertQueue(p3, t);
            break;
    
        default:
            printf("Prioridade invalida!");
    }

    setStatus(t);

    printf("\n\n==============================================================");
    printf("\n\nTarefa lida com sucesso!");
    printf("\n\n==============================================================");
}

No
*searchTask (No *p1, No *p2, No *p3, int code)
{
    No *aux = p1;

    while(aux->info->code != code)
    {
        while (aux != NULL)
        {
            aux = aux->next;
        }
        aux = p2;
        while (aux != NULL)
        {
            aux = aux->next;
        }
        aux = p3;
        while (aux != NULL)
        {
            aux = aux->next;
        }
    }
    
    return (aux);
}

Fila
*searchQueue (Fila *f1, Fila *f2, Fila *f3, int code)
{
    Fila *f = f1;
    No *aux = f1->first;

    while(aux->info->code != code)
    {
        while (aux != NULL)
        {
            aux = aux->next;
        }
        f = f2;
        aux = f2->first;
        while (aux != NULL)
        {
            aux = aux->next;
        }
        f = f3;
        aux = f3->first;
        while (aux != NULL)
        {
            aux = aux->next;
        }
    }

    return f;
}



void
updateTask(Fila *p1, Fila *p2, Fila *p3)
{
    printf("==============================================================\n\n");
    printf("Que tarefa deseja modificar?");
    printf("\n\n==============================================================\n\n");
    printf("Digite o codigo da tarefa:");
    int code;
    scanf("%d", &code);
    No *aux = searchTask(p1->first, p2->first, p3->first, code);

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

void
finishTask(Fila *p1,Fila *p2,Fila *p3, No **t)
{

    printQueue(p1);
    printQueue(p2);
    printQueue(p3);
    task *aux;
    Fila *f = createQueue();
    //Fila *aux2 = createQueue();

    int code;
    printf("==============================================================\n\n");
    printf("Que tarefa deseja concluir?");
    printf("\n\n==============================================================\n\n");
    scanf("%d", &code);

    aux = searchTask(p1->first,p2->first,p3->first,code);

    if(aux != NULL)
    {
        f = searchQueue(p1,p2,p3,code);
        removeInfo(f->first,code);
        *t = insertListByDate(*t, aux);
        printf("\n==============================================================");
        printf("\n\nTarefa concluida com sucesso!");
    }
    else
    {
        printf("\n\nTarefa nao encontrada, por favor, tente novamente!\n\n");

        sleep(2);
    }
    //while (!emptyQueue(aux1))
    //{
    //    aux = removeQueue(aux1);
    //    if (aux->code == code)
    //    {
    //        *t = insertListByDate(*t, aux);
    //        printf("\n==============================================================");
    //        printf("\n\nTarefa concluida com sucesso!");
    //        flag++;
    //    }
    //    else
    //    {
    //        insertQueue(aux2, aux);
    //    }
    //}

    //if (!flag)
    //    printf("\n\nTarefa nao encontrada, por favor, tente novamente!\n\n");

    //sleep(2);
}

int
verifyDate(date d)
{
    SYSTEMTIME t;
    GetLocalTime(&t);
    if (d.year < t.wYear)
        return 1;
    else if (d.year == t.wYear && d.month < t.wMonth)
        return 1;
    else if (d.year == t.wYear && d.month == t.wMonth && d.day < t.wDay)
        return 1;
    else
        return 0;
}

void
setStatus(task *t)
{
      t->status = verifyDate(t->finish);
}

void
updateStatus (Fila *p1, Fila *p2, Fila *p3, No **t)
{
    task *aux;
    int flag = 0;
    int choice;
    int code;
    int auxStatus;

    printf("==============================================================\n\n");
    printf("Atualizar uma tarefa da Fila de Tarefas ou da Lista de Tarefas Pendentes?\n\n  1-Fila de Tarefas   2-Lista de Tarefas Pendentes\n\nEscolha a opcao:");
    scanf("%d", &choice);
    printf("\n\n==============================================================\n\n");

    do
    {
        printf ("Que status deseja alocar para a tarefa?\n\n  0 - Em dia // 1 - Atrasada // -1 Pendente\n\nEscolha a opcao:");
        scanf("%d", &auxStatus);
        printf("\n\n==============================================================\n\n");

    }while(auxStatus < -1 || auxStatus > 1);

    system("cls");

    // if(choice == 1)
    // {   
    //     if(emptyQueue(p))
    //     {
    //         printf("\n\nFila vazia, por favor, tente novamente!\n\n");
    //         return p;
    //     }
    //     printQueue(p1);
    //     printQueue(p2);
    //     printQueue(p3);
    // }
    // else
    // {
    //     if(emptyList(*t))
    //     {
    //         printf("\n\nLista vazia, por favor, tente novamente!\n\n");
    //         return p;
    //     }
    //     printList(*t);
    // }

    printf("==============================================================\n\n");
    printf("Que tarefa deseja atualizar?");
    printf("\n\n==============================================================\n\n");
    printf("Digite o codigo da tarefa:");
    scanf("%d", &code);
    Fila *f = searchQueue(p1,p2,p3,code);


    switch (choice)
    {
    case 1:
        Fila *aux1 = f;
            Fila *aux2 = createQueue();
            No *task;
            No *findCode;
            

            if(auxStatus == -1)
            {
                while (!emptyQueue(aux1))
                {
                    aux = removeQueue(aux1);
                    if (aux->code == code)
                    {
                        *t = insertListByDate(*t, aux);
                        aux -> status = auxStatus;
                        printf("\n==============================================================");
                        printf("\n\nStatus atualizado com sucesso!\n\n");
                        flag++;
                    }
                    else
                    {
                        insertQueue(aux2, aux);
                    }
                }
                return aux2;
            }
            else
            {   
                findCode = searchTask(p->first, code);
            }

            if (!flag && findCode == NULL)
            {
                printf("\n\nTarefa nao encontrada, por favor, tente novamente!\n\n");
                return p;
            }
            else
            {
                findCode->info->status = auxStatus;
                printf("\n==============================================================");
                printf("\n\nStatus atualizado com sucesso!\n\n");
                return p;
            }
        break;
    
    default:
        break;
    }
        if (choice == 1)
        {
            
        else
        {
            if(auxStatus != -1)
            {
                if (searchTask(*t, code) != NULL)
                {
                    printf("\n==============================================================");
                    printf("\n\nStatus atualizado com sucesso!\n\n");
                    (*t) -> info -> status = auxStatus;
                    insertQueue(p, (*t) -> info);
                    (*t) = removeInfo((*t), code);
                    return p;
                }
                else
                {
                    printf("\n\nTarefa nao encontrada, por favor, tente novamente!\n\n");
                    return p;
                }

            }
            else
            {
                return p;
            }


        }
}


