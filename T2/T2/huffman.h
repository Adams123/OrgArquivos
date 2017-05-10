#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node
{
    int left, right; //posicoes dos nodes da esquerda e da direita
    char *letra;
    int freq;
    char *bin;//onde serao guardados os bits
    int flag; // se 0 não foi usado para construção da árvore, se 1 foi usado.
} node;

typedef struct codeTable //estrutura para guardar a tabela de codigos
{
    char *codigo;
    char *word;
}codeTable;


void init_leaves(int n_ele, int freq[], node *tree);
void rev(char* str);
char* toBin(int a);
void ordena(node *tree, int n_ele);
void dump(node *tree, int pos);
void build_tree(node *tree, int n_ele);
void code_table(node *tree, int pos, int code, codeTable *codetable);
void compactar(codeTable *codetable, char *s);
void ordenaAscii(codeTable *codetable, int n_ele);
#endif // _HUFFMAN_H
