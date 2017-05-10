#ifndef CONTROLER_H
#define CONTROLER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "bancoDeDados.h"
#include "indicePrimario.h"
#include "indiceSecundario.h"

/*! Realiza o cadastro do atleta em todos os arquivos */
void cadastrarAtleta();

/*! Imprime o arquivo data.db char-a-char*/
void dumpData();


/*! Imprime os arquivos de lista ou de chaves primarias
*   \param flag Determina qual arquivo será impresso
*   0 - universidade.idx
*   1 - modalidade.idx
*   2 - universidadeListaInvertida.idx
*   3 - modalidadeListaInvertida.idx
*   4 - prim.idx
*/
void dumpLista(int flag);
/*! Busca qualquer registro nos respectivos arquivos
*   \param cpf Cpf a ser buscado
*   \param universidade Universidade a ser buscada
*   \param modalidade Modalidade a ser buscada
*   \param flag Qual operador logico esta sendo usado:
*   caso 0 - Nenhum operador
*   caso 1 - Operador 'e'
*   caso 2 - operador 'ou'
*/
void buscar(char *cpf, char *universidade, char *modalidade, int flag);
/*! Remove um registro dado a chave primaria
*   \param cpf Cpf do registro a ser removido
*/
void remover(char *cpf);
/*! Realiza algoritmo de matching dados duas listas contendo chaves primarias e posicoes do data.db
*   \param a Primeira lista
*   \param b Segunda lista
*   \param size1 Tamanho da primeira lista
*   \param size2 Tamanho da segunda lista
*   \param sizeFinal Tamanho da lista final
*   \return retorna uma terceira lista ordenada contendo a intersecao das duas listas de entrada
*/
CAux* matching(CAux *a, CAux *b, int size1, int size2, int *sizeFinal);
/*! Realiza algoritmo de merging dados duas listas contendo chaves primarias e posicoes do data.db
*   \param a Primeira lista
*   \param b Segunda lista
*   \param size1 Tamanho da primeira lista
*   \param size2 Tamanho da segunda lista
*   \param sizeFinal Tamanho da lista final
*   \return retorna uma terceira lista ordenada contendo a uniao das duas listas de entrada
*/
CAux* merging(CAux *a, CAux *b, int size1, int size2, int *sizeFinal);
#endif
