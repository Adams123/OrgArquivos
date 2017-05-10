#ifndef LISTAINVERTIDA_H
#define LISTAINVERTIDA_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "indiceSecundario.h"

/*! Insere a chave primaria na lista invertida correspondente
*   \param filename Nome do arquivo a ser inserida a chave
*   \param pk Chave primaria a ser inserida
*   \param pos Posicao da antiga head da lista invertida
*   \return posicao da nova head da lista invertida
*/
int inserirListaInvertida(char *filename, char *pk, int pos);

/*! Realiza busca no arquivo de lista invertida
*   \param aux Vetor a ser montado, contendo apenas as chaves primarias. Serao inseridas as posicoes do data.db
*   \param headpos Posicao inicial da lista invertida, baseado na chave secundaria encontrada anteriormente
*   \param flag Qual arquivo esta sendo buscado
*   caso 0 - Buscando por universidades
*   caso 1 - Buscando por modalidades
*   \param tam Quantidade de elementos encontrados
*   \return Vetor contendo as chaves primarias e suas posicoes do data.db
*/
CAux* buscarListaInvertida(CAux *aux, int headpos, int flag, int *tam);
#endif
