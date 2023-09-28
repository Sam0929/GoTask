#include <stdlib.h>
#include <stdio.h>
#include "FILA.h"


date getdate()
{
    date d;
    scanf("%d %d %d", &d.day, &d.month, &d.year);
    return d;
}

void readTask(Fila *p){
    task* t = (task*)malloc(sizeof(task));

    printf("Digite o codigo da tarefa!");
    scanf("%d", &(t->code));
    printf("\n\nDigite o nome da tarefa:");
    scanf("%s", &(t->name));
    printf("\n\n Digite o nome do projeto:");
    scanf("%s", &(t->project));
    printf("\n\nDigite a data de inicio:");
    t->start = getdate();
    printf("\n\nDigite a data de termino:");
    t->finish = getdate();

    InsereFila(p, t);
}

int main ()

{
    Fila *tarefas_criadas = CriaFila();

    readTask(tarefas_criadas);

    imprimeFila(tarefas_criadas);

    return 0;

}
