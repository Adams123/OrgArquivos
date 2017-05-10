#ifndef BTREE_H_
#define BTREE_H_

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
#define SPLIT 3

/*! Numero de descendentes de cada pagina da Arvore-B (Knuth,1988)*/
#define ORDER 4

/*! Valor nulo para Offsets*/
#define NIL -1


/*! Pagina da Arvore-B */
typedef struct
{
    /*! Numero de chaves dentro do no atual */
    int nKeys;
    /*! Array das chaves do no atual */
    long int keys[ORDER-1];
    /*! Offsets dos filhos do no atual */
    int child[ORDER];
    /*! Offset da chave no arquivo de dados*/
    int keyOffset[ORDER-1];
} page_tree;

/*! Pagina Buffer para split */
typedef struct
{
    /*! Numero de chaves dentro do no atual */
    int nKeys;
    /*! Array das chaves do no atual */
    long int keys[ORDER];
    /*! Offsets dos filhos do no atual */
    int child[ORDER+1];
    /*! Offset da chave no arquivo de dados*/
    int keyOffset[ORDER];
} page_tree_buffer;

/* arquivo com a arvore-b */
FILE* bTreeFile;

/* Variavel global que armazena a raiz da arvore-b */
int offset_root;

void printaaaa();
void printPage(page_tree *page);
void printBuffer(page_tree_buffer *page);

/*! Realiza um bubble sort no em um no, utilizando as chaves como parametro de comparacao
 * \param page pagina a ser ordenada
*/
void bubble_sort(page_tree_buffer *page);

/*! Busca por nos na arvore
 *
 * \param offset Offset do no a ser pesquisado
 * \param chave Chave a ser procurada
 * \param offset_encontrado Usado como parametro de retorno.
 *      Retorna o Offset do no onde a chave foi encontrada.
 * \param pos_encontrada Usado como parametro de retorno.
 * 		Retorna a posicao da chave dentro do no onde ela foi encontrada.
 * \return Retorna ENCONTROU ou NAO_ENCONTROU
 */
int search(const int offset, long int pKey, int* offset_found, int* pos_found);

/*! Funcao que dado um Offset, carrega em memoria principal o no
 * 		correspondente.
 * \param offset Offset do no a ser carregado
 * \return no carregado
 */
page_tree* loadPage(const int offset);

/*! Funcao que dado um no, verifica se uma chave pertence a ele
 * 		caso nao pertenca, indica o offset do no filho onde ha
 * 		probabilidade da chave ser encontrada.
 * \param no_atual No onde a chave sera procurada
 * \param chave chave a ser procurada
 * \param pos Usado como parametro de retorno
 * 		retorna a posicao da chave dentro do no ou a posicao
 * 		do no filho onde ha a possibilidade de encontrar a chave
 * \return Retorna ENCONTROU ou NAO_ENCONTROU
 */
int pageSearch(const page_tree* curr_page, long int key, int* pos);

/*! Funcao que insere novas chaves na arvore B, caso seja necessario
 *  cria uma nova raiz
 *
 * \param offset offset do no raiz
 * \param key  chave a ser inserida
 * \param keyOffset  offset da chave a ser inserida
 *
 */
int insert(int offset, long int key, int keyOffset);

/*! Funcao que insere uma chave em uma pagina
 *  ->a pagina devera ter espaco disponivel
 * \param curr_page pagina atual onde sera feita a insercao
 * \param key chave a ser inserida
 * \param keyoffset offset da chave a ser inserida no data.db
 * \param offset_right_child offset do filho da direita da chave promovida
 */
void pageInsert(page_tree *curr_page, long int key, int keyOffset, const int offset_right_child);

/*! Funcao para inserir chave na arvore, quando nao num novo no raiz
 * \param offset offset da raiz da arvore
 * \param key chave a ser inserida
 * \param keyoffset offset da chave a ser inserida no data.db
 * \param child_right_promoted parametro de retorno, indica o offset do filho a direita da chave promovida
 * \param key_promoted parametro de retorno, indica a chave promovida
 * \return PROMOTED, NOT_PROMOTED, ERROR
 */
int insertKey(int offset, long int key, int keyoffset ,int* child_right_promoted, long int* key_promoted);

/*! Funcao que aloca uma nova pagina, na memoria principal
 * \param newpage ponteiro para uma pagina a ser alocada e inicializada
 */
void allocPage(page_tree ** newpage);

/*! Funcao que apaga uma pagina, re-inicializando para novo uso
 * \param page pagina a ser resetada
 */
void resetPage(page_tree* page);

/*! Funcao que salva uma pagina da RAM para o disco
 * \param offset posicao onde sera escrita a pagina
 * \param newpage pagina na memoria principal a ser escrita no disco
 */
void savePage(const int offset, const page_tree * newpage);

/*! Atualiza o offset da raiz, nos primeiros 4 bytes do arquivo
 * \param offset posicao da raiz a ser escrita
 */
void update_root_offset(int offset);

/*! Cria um novo arquivo para armazenar arvore B
 */
void open_initialize_file();

/*! Imprime o arquivo com a arvore, na ordem em que esta armazenado
 * \param rrn offset do no a ser impresso
 * \param altura altura em que o node esta
 */
void printBTree(int rrn, int altura);

/*! Caso uma pagina esteja cheia e seja necessario inserir uma nova chave
 *  a funcao cria uma nova pagina, define uma chave a ser promovida
 *  e divide os elementos restantes entre a pagina antiga e a recem-criada
 * \param key_input chave a ser inserida
 * \param keyoffset offset da chave a ser inserida no data.db
 * \param child_right_input filho a direita da chave a ser inserida
 * \param page pagina onde seria feita a insercao (que deve estar cheia)
 * \param key_promoted chave promovida
 * \param child_promoted offset do filho a direita da chave promovida
 * \param new_page nova pagina criada para distribuicao dos elementos
 *
 */
void split(const long int key_input,const int keyoffset, const int child_right_input,page_tree* page, long int* key_promoted, int* child_promoted, page_tree** new_page);

/*! Aloca uma pagina de buffer
 * \param newpagebuffer ponteiro para a pagina a ser alocada
 *
 */
void allocBuffer(page_tree_buffer **newpagebuffer);

/*! Funcao de comparacao usada no qsort
 * \return diferenca entre os valores de entrada (apenas inteiros)
*/
int compare (const void * a, const void * b);

#endif /*BTREE_H_*/
