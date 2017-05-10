#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad.h"

int main(int argc, char *argv[])
{
    int n=0;
    int m=0;
    int o=0;
    char command[30];
    int exit = 0;
    aluno *al;
    disciplina *disc;
    disc = malloc(sizeof(disciplina));
    al = malloc(sizeof(aluno));

    FILE *alunos;
    FILE *disciplinas;
    FILE *matriculas;
    alunos = fopen("alunos.bin", "w+b");
    disciplinas = fopen("disciplinas.bin", "w+b");
    matriculas = fopen("matriculas.txt", "w+");

    while(!exit)
    {
        scanf("%s",command);
        if(strcmp(command,"sair") == 0)
        {
            exit = 1;
        }
        else if(strcmp(command,"cadastrar") == 0)
        {
            scanf("%s",command);
            if(strcmp(command,"aluno") == 0)
            {
                fflush(stdin);
                scanf("%s", al->nome);
                fflush(stdin);
                scanf("%s", al->nUsp);
                fflush(stdin);
                scanf("%s", al->ano);
                n=cadastrarAluno(al, alunos, n);
            }
            else if(strcmp(command,"disciplina") == 0)
            {
                fflush(stdin);
                scanf("%s", disc->nomeDisciplina);
                fflush(stdin);
                scanf("%s", disc->codigo);
                fflush(stdin);
                scanf("%s", disc->professor);
                fflush(stdin);
                m=cadastrarDisciplina(disc, disciplinas,m);
            }
        }
        else if(strcmp(command,"matricular") == 0)
        {
            fflush(stdin);
            scanf("%s", al->nUsp);
            fflush(stdin);
            scanf("%s", disc->codigo);
            fflush(stdin);
            o=matricular(alunos,disciplinas,matriculas,al,disc,n,m,o);
        }
        else if(strcmp(command,"dump") == 0)
        {
            scanf("%s",command);
            if(strcmp(command,"aluno") == 0)
            {
                dumpAluno(alunos, n);
            }
            else if(strcmp(command,"disciplina") == 0)
            {
                dumpDisciplina(disciplinas, m);
            }
            else if(strcmp(command,"matricula") == 0)
            {
                dumpMatricula(matriculas,o);
            }
        }
    }
    free(al);
    free(disc);
    fclose(alunos);
    fclose(disciplinas);
    fclose(matriculas);
    return EXIT_SUCCESS;
}
