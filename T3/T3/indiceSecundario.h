#ifndef INDICESECUNDARIO_H
#define INDICESECUNDARIO_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "controler.h"

/*! Estrutura auxiliar para ordenacao dos arquivos de chave secundarias*/
typedef struct lAux
{
    char chave[30];
    int pos;
} LAux;

/*! Insere chave no indice secundario correspondente
*   \param filename Nome do arquivo a ser inserido
*   \param sk Chave secundaria a ser inserida
*   \param pk Chave primaria correspondente
*/
void inserirIndiceSecundario(const char *filename, char *sk, char *pk);
/*! Ordena os arquivos de chaves secundarias
*   \param flag Caso 0, ordena universidade.idx - Caso 1, ordena modalidade.idx
*/
void ordenaLista(int flag);
/*! Funcao utilizada como metodo de comparacao para o qsort
*/
int comparaLista(const void *a, const void *b);
/*! Realiza busca binaria no arquivo de chave secundaria correspondente
*   \param flag Caso 0, ordena universidade.idx - Caso 1, ordena modalidade.idx
*   \param sk Chave secundaria sendo buscada
*   \param filePos Posicao da chave secundaria no arquivo correspondente
*   \return posicao da head da listaInvertida correspondente
*/
int buscaBinaria(int flag, char *sk, int *filePos);
/*! Funcao que realiza a pesquisa no arquivo
*   \param array Array contendo o arquivo de indices primarios
*   \param chave Chave a ser buscada
*   \param N Tamanho do array
*   \return retorna -1 se nao encontrou, e a posicao da head da chave no arquivo de ListaInvertida caso encontre
*/
int PesquisaBinaria ( LAux *array, char *chave , int N);
/*! Busca por uma chave secundaria no respectivo arquivo
*   \param universidade Universidade a ser buscada
*   \param modalidade Modalidade a ser buscada
*   \param tam Quantidade de registros encontrados da respectiva chave secundaria no arquivo de lista invertida
*/
CAux* buscarSk(char *universidade, char *modalidade, int *tam);

#endif
