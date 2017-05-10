#ifndef _PRIM_H
#define _PRIM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*! Define sucesso na execucao de procedimentos */
#define SUCCESS 0
/*! Define falha na execucao de procedimentos */
#define FAIL 1

/*! Define macro para chave promovida */
#define PROMOTED 1
/*! Define macro para chave nao promovida */
#define NOT_PROMOTED 0
/*! Define macro para erro */
#define ERROR 2

/*! Numero de descendentes de cada pagina da Arvore-B (Knuth,1988)*/
#define ORDER 4

/*! Valor nulo para Offsets*/
#define NIL -1

/*! Estrutura auxiliar de cadastro de atleta*/
typedef struct atleta
{
    int cpf;
    char nome[30];
    int ra;
    char universidade[30];
    char modalidade[30];
} atleta;

FILE *dataFile;
/*! Inicializa arquivo contendo os cadastros (no caso, data.db)*/
void open_data();

/*! Cadastra um novo atleta no arquivo data.db
 * \param cpf CPF a ser cadastrado.
 * \param ra Registro Academico a ser cadastrado.
 * \param nome Nome a ser cadastrado.
 * \param universidade Universidade a ser cadastrada.
 * \param modalidade Modalidade a ser cadastrada.
 * \return Retorna posicao de offset salva no data.db
*/
int cadastrar(long int cpf, int ra, char *nome, char *universidade, char *modalidade);

/*! Imprime o arquivo de cadastros char-a-char com um \n no fim*/
void dump_data();
#endif // _PRIM_H
