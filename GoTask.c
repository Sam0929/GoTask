#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "FILA.h"


date getdate();
void readTask(Fila *p);
void updateTask(Fila *p);

int main ()

{
    Fila *tarefas_criadas = CriaFila();

    int Choose;

    while (Choose != 6)
    {       system("cls");
            printf ("==============================================================");
            printf ("\n\n Bem vindo ao GoTask!!\n\n");
            printf ("==============================================================\n\n");
            printf (" 1 - Incluir Tarefas \n\n 2 - Imprimir fila \n\n 3 - Atualizar tarefa \n\n 4 - NA \n\n 5 - NA \n\n 6 - Sair do sistema \n\n Escolha a opcao:");
            scanf ("%d", &Choose);

        switch (Choose)
        {
            case 1:

                system ("cls");
                readTask(tarefas_criadas);

            break;

            case 2:

                system ("cls");
                imprimeFila(tarefas_criadas);
                system ("pause");

            break;

            case 3:

                system ("cls");
                updateTask(tarefas_criadas);

            break;

            case 4:

            break;

            case 5:

            break;
        }
    }
    system("cls");
    printf ("\n\n==============================================================\n\n");
    printf("\t\tObrigado por utilizar nosso sistema!! \n\n\t\t\tAte a proxima!");
    printf ("\n\n==============================================================");

    liberaFila(tarefas_criadas);

    return 0;
}

date getdate()
{
    date d;
    scanf("%d %d %d", &d.day, &d.month, &d.year);
    return d;
}

void readTask(Fila *p){

    task* t = (task*)malloc(sizeof(task));


    printf("Digite o codigo da tarefa:");
    scanf("%d", &(t->code));
    printf("\n\nDigite o nome da tarefa:");
    scanf("%s", &(t->name));
    printf("\n\nDigite o nome do projeto:");
    scanf("%s", &(t->project));
    printf("\n\nDigite a data de inicio:");
    t->start = getdate();
    printf("\n\nDigite a data de termino:");
    t->finish = getdate();

    InsereFila(p, t);

    printf("\n\nTarefa lida com sucesso!");
    sleep(2);
}


void updateTask (Fila *p)

{
    No *aux = p->ini;
    int code;
    printf("==============================================================\n\n");
    printf("Que tarefa deseja modificar?");
    printf ("\n\n==============================================================\n\n");
    scanf("%d", &code);
    while (aux != NULL && aux->info->code != code)
    {
        aux = aux -> prox;
    }

    if(aux == NULL)
    {
        printf("\nImpossivel localizar a tarefa, por favor, tente novamente!\n\n");
        system("pause");
    }
    else
    {
        system ("cls");

        task *aux1 = aux->info;

        int Choose;

        printf ("==============================================================");
        printf("\n\nO que voce deseja modificar?");
        printf ("\n\n==============================================================\n\n");
        printf (" 1 - Codigo \n\n 2 - Nome da tarefa \n\n 3 - Nome do projeto \n\n 4 - Data de inicio \n\n 5 - Data de termino \n\n 6 - Cancelar \n\n Escolha a opcao:");
        scanf("%d", &Choose);

        switch (Choose)
        {
            case 1:

                printf("\n\nDigite o novo codigo da tarefa:");
                scanf("%d", &(aux1->code));

            break;

            case 2:

                printf("\n\nDigite o novo nome da tarefa:");
                scanf("%s", &(aux1->name));
            break;

            case 3:

                printf("\n\nDigite o novo nome do projeto:");
                scanf("%s", &(aux1->project));

            break;

            case 4:

                printf("\n\nDigite a nova data de inicio da tarefa:");
                aux1 -> start = getdate();

            break;

            case 5:

                printf("\n\nDigite a nova data de termino da tarefa:");
                aux1 -> finish = getdate();

            break;

            case 6:

                return;

            break;
        }
        printf ("\n\n==============================================================");
        printf("\n\nTarefa modificada com sucesso!!");
        sleep(2);
    }
}
