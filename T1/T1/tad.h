#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct aluno
{
    char nUsp[8];
    char nome[30];
    char ano[5];
};
typedef struct aluno aluno;

struct disciplina
{
    char nomeDisciplina[30];
    char professor[30];
    char codigo[8];
};
typedef struct disciplina disciplina;

void ordernaAluno(FILE *alunos, int n);
int cadastrarAluno(aluno *al, FILE *alunos, int n);
void dumpAluno(FILE *alunos, int n);
void ordenaDisciplina(FILE *disciplinas, int m);
int cadastrarDisciplina(disciplina *disc, FILE *disciplinas, int m);
void dumpDisciplina(FILE *disciplinas, int m);
void ordenaMatricula(FILE *matriculas, int o);
int buscaAluno(aluno *al, FILE *fp, int n);
int buscaDisciplina(disciplina *disc, FILE *fp, int n);
int matricular(FILE *alunos, FILE *disciplinas, FILE *matricula, aluno *al, disciplina *disc, int n, int m, int o);
void dumpMatricula(FILE *matriculas, int o);
