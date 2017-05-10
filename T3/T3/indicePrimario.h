#ifndef INDICEPRIMARIO_H
#define INDICEPRIMARIO_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


/*! Estrutura auxiliar de cadastro, usada na organizacao dos arquivos e nas buscas*/
typedef struct cadastro
{
    char cpf[11];
    int pos;

} CAux;


/*! Insere a chave no indice primario
*   \param pk Chave a ser inserida
*   \param pos Posicao da chave no data.db
*/
void inserirIndicePrimario(char *pk, int pos);

/*! Funcao de comparacao para o qsort de ordenacao do prim.idx
*/
int comparaPrim (const void * a, const void * b);

/*! Funcao utilizada para ordenar o arquivo prim.idx por cpf
*/
void ordenaPrim();
/*! Realiza busca binaria pela chave secundaria no arquivo prim.idx
*   \param sk Chave a ser buscada
*   \return retorna se encontrou ou nao a chave
*/
int PbuscaBinaria(char *sk);
/*! Funcao que realiza a pesquisa no arquivo
*   \param array Array contendo o arquivo de indices primarios
*   \param chave Chave a ser buscada
*   \param N Tamanho do array
*   \return retorna se encontrou ou nao a chave
*/
int PPesquisaBinaria ( CAux *array, char *chave , int N);
/*! Busca um cpf no arquivo de chaves primarias
*   \param cpf Cpf a ser buscado
*   \param tam Verifica se encontrou ou nao um cpf
*   \return Uma lista contendo o cpf e a posicao do data.db do mesmo. A posicao sera -1 caso nao seja encontrado
*/
CAux *buscarCpf(char *cpf, int *tam);
/*! Imprime uma lista ordenada de cpfs, contendo os cpfs e as posicoes do data.db
*   \param array Lista ordenada contendo cpfs e as posicoes do data.db
*   \param N Quantidade de elementos a serem impressos
*/
void printaCpf(CAux *array, int N);

#endif
