#ifndef BANCODEDADOS_H
#define BANCODEDADOS_H

#include<stdlib.h>
#include<stdio.h>

/*! Insere um cadastro novo no banco de dados, pesquisando se o mesmo existe antes da insercao
*   \param cpf Cpf a ser inserido
*   \param nome Nome a ser inserido
*   \param ra Ra a ser inserido
*   \param univ Universidade a ser inserida
*   \param mod Modalidade a ser inserida
*   \return retorna a posicao em que foi feita o cadastro, quando feito, e -1 caso ja exista o cadastro
*/
int inserirNoBanco(char *cpf, char *nome, char *ra, char *univ, char *mod);

/*! Escreve *********** por cima da chave primaria de um registro do data.db
*   \param pos Posicao inicial do registro no data.db
*/
void removeRegistro(int pos);
#endif
