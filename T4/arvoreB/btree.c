#include "btree.h"

int debug = 1;

int search(const int offset, long int pKey, int* offset_found, int* pos_found)
{
    int pos = 0;
    if (offset == -1)
    {
        return FAIL;
    }

    page_tree * curr_page;
    curr_page = loadPage(offset);

    if (pageSearch(curr_page, pKey, &pos) == SUCCESS)
    {
        *offset_found = offset;
        *pos_found = pos;
        free(curr_page);
        return SUCCESS;
    }
    *offset_found = offset;
    *pos_found = pos;
    free(curr_page);

    return search(curr_page->child[pos], pKey, offset_found, pos_found);
}

page_tree* loadPage(int offset)
{

    page_tree* return_page;
    fseek(bTreeFile, offset, SEEK_SET);
    return_page = (page_tree*)malloc(sizeof(page_tree));
    fread(return_page, sizeof(page_tree), 1, bTreeFile);
    return return_page;
}

int pageSearch(const page_tree* curr_page, long int pKey, int* pos)
{
    int i;

    for (i = 0; i < curr_page->nKeys; i++)
    {
        if (pKey == curr_page->keys[i])
        {
            *pos = i;
            return SUCCESS;
        }
        else if (pKey < curr_page->keys[i])
        {
            *pos = i;
            return FAIL;
        }
    }
    *pos = i;
    return FAIL;
}

int insert(int offset, long int key, int keyOffset)
{
    long int key_promoted = -1;
    int return_value = -1;
    int new_offset = -1;
    int offset_child_right = -1;
    page_tree *page;

    // verifica se eh necessario criar um novo no raiz
    if ((return_value = insertKey(offset, key, keyOffset, &offset_child_right, &key_promoted)) == PROMOTED)
    {
        // aloca nova pagina na ram
        allocPage(&page);
        // insere chave na nova pagina criada (ainda na RAM)
        pageInsert(page, key_promoted, keyOffset, offset_child_right);

        // move o ponteiro para o final do arquivo para pegar a posicao da nova pagina
        fseek(bTreeFile, 0, SEEK_END);
        new_offset = ftell(bTreeFile);

        // salva a pagina no disco
        savePage(new_offset, page);

        update_root_offset(new_offset);

        free(page);
    }
    else if(return_value==SPLIT)
        {
            allocPage(&page);
            int offset_found = -1, pos_found=-1;
            search(offset_root, page->keys[0], &offset_found, &pos_found);
            pageInsert(page, key_promoted, keyOffset, offset_child_right);
            page->child[0]=offset_found;
            fseek(bTreeFile, 0, SEEK_END);
            new_offset = ftell(bTreeFile);
            savePage(new_offset, page);
            update_root_offset(new_offset);
            free(page);
        }
    return return_value;
}

int insertKey(int offset, long int key,int keyoffset, int* child_right_promoted, long int* key_promoted)
{
    page_tree *curr_page; // pagina atual para busca
    page_tree *new_page; // pagina para split
    int pos = -1; // posicao em que a chave deveria ser inserida

    // trata o caso de arvore vazia
    if (offset == NIL)
    {
        *key_promoted = key;
        *child_right_promoted = NIL;
        return PROMOTED;
    }

    curr_page = loadPage(offset); // carrega a pagina para inspecao
    if (pageSearch(curr_page, key, &pos) == SUCCESS)
    {
        return ERROR;
    }

    int return_value = -1;
    int offset_child_promoted = -1;
    long int key_promotion = -1;
    return_value = insertKey(curr_page->child[pos], key,keyoffset, &offset_child_promoted, &key_promotion);

    // verifica se nao eh necessaria mais nenhuma operacao na arvore
    // ou seja, a chave foi inserida mas nao ha promocao
    // ou entao a chave ja existia e foi retornado um erro
    if (return_value == NOT_PROMOTED || return_value == ERROR)
    {
        return return_value;
    }

    // verifica se a chave cabe na pagina atual
    if (curr_page->nKeys < ORDER-1)
    {
        pageInsert(curr_page, key_promotion,keyoffset, offset_child_promoted);
        savePage(offset, curr_page);
        return NOT_PROMOTED;
    }

    // se a chave nao couber na pagina, realiza split
    split(key_promotion,keyoffset, offset_child_promoted, curr_page, key_promoted, child_right_promoted, &new_page);

    savePage(offset, curr_page); // salva a pagina atual
    savePage(*child_right_promoted, new_page); // salva a nova pagina apos split
    free(curr_page);
    free(new_page);
    return SPLIT;
}

void open_initialize_file()
{
    bTreeFile = fopen("data_btree.dat", "wb+");
    int offset_root_new = -1;
    fwrite(&offset_root_new, sizeof(int), 1, bTreeFile);
    offset_root = -1;
}

void update_root_offset(int offset)
{
    fseek(bTreeFile, 0, SEEK_SET);
    fwrite(&offset, sizeof(int), 1, bTreeFile);
    offset_root = offset;
}

void savePage(const int offset, const page_tree * newpage)
{
    fseek(bTreeFile, offset, SEEK_SET);
    fwrite(newpage, sizeof(page_tree), 1, bTreeFile);
}


void allocPage(page_tree **newpage)
{
    int i;
    *newpage = (page_tree*) malloc(sizeof(page_tree));
    for (i = 0; i < ORDER-1; i++)
    {
        (*newpage)->keys[i] = NIL;
        (*newpage)->keyOffset[i] = NIL;
        (*newpage)->child[i] = NIL;
    }
    (*newpage)->child[i] = NIL;
    (*newpage)->nKeys = 0; // total de chaves
}

void resetPage(page_tree *page)
{
    int i;
    for (i = 0; i < ORDER-1; i++)
    {
        page->keys[i] = NIL;
        page->keyOffset[i] = NIL;
        page->child[i] = NIL;
    }
    page->child[i] = NIL;
    page->nKeys = 0; // total de chaves
}

void pageInsert(page_tree *curr_page, long int key, int keyoffset, const int offset_right_child)
{
    int i;
    // se a pagina for nova, e estiver vazia
    if (curr_page->nKeys == 0)
    {
        curr_page->nKeys++;
        curr_page->child[1] = offset_right_child;
        curr_page->keys[0] = key;
        curr_page->keyOffset[0] = keyoffset;
        return;
    }

    // percorre a pagina do ultimo elemento para o primeiro
    // copia os elementos maiores do que a chave para a direita
    for (i = curr_page->nKeys-1; i >= 0; i--)
    {

        if (curr_page->keys[i] > key)
        {
            // desloca chaves maiores e seus filhos para a direita
            curr_page->keys[i+1] = curr_page->keys[i];
            curr_page->keyOffset[i+1] = curr_page->keyOffset[i];
            curr_page->child[i+2] = curr_page->child[i+1];

            if (i == 0)
            {
                curr_page->keys[i] = key;
                curr_page->keyOffset[i] = keyoffset;
                curr_page->child[1] = offset_right_child;
                curr_page->nKeys++;
            }
        }
        else
        {
            curr_page->keys[i+1] = key;
            curr_page->keyOffset[i+1] = keyoffset;
            curr_page->child[i+2] = offset_right_child;
            curr_page->nKeys++;
            break;
        }
    }
}

void printBTree(int rrn, int altura)
{
    if(rrn == NIL)
    {
        return;
    }
    int i;
    page_tree* nextPage = loadPage(rrn);

    printf("Altura: %d | num. Chaves: %d | chaves = [ ", altura, nextPage->nKeys);
    for (i = 0; i < nextPage->nKeys; i++)
    {
        printf("0%ld ", nextPage->keys[i]);
    }
    printf("]\n");
    for (i = 0; i < ORDER; i++)
        printBTree(nextPage->child[i], altura+1);
}

void allocBuffer(page_tree_buffer **newpagebuffer)
{
    int i;
    *newpagebuffer = (page_tree_buffer*) malloc(sizeof(page_tree_buffer));
    for (i = 0; i < ORDER; i++)
    {
        (*newpagebuffer)->keys[i] = NIL;
        (*newpagebuffer)->keyOffset[i] = NIL;
        (*newpagebuffer)->child[i] = NIL;
    }
    (*newpagebuffer)->child[i] = NIL;
    (*newpagebuffer)->nKeys = 0; // total de chaves
}

void bubble_sort(page_tree_buffer *page) {
	long int j, t = 1, n=ORDER, c=1;
	while (n-- && t)
		for (j = t = 0; j < n; j++) {
			if (page->keys[j] <= page->keys[j + 1]) continue;
			t = page->keys[j];
			c=page->keyOffset[j];
			page->keys[j] = page->keys[j + 1];
			page->keyOffset[j] = page->keyOffset[j + 1];
			page->keys[j + 1] = t;
			page->keyOffset[j + 1] = c;
			c=1;
			t=1;
		}
}

void split(const long int key_input, const int keyoffset, const int child_right_input, page_tree* page, long int* key_promoted, int* child_promoted, page_tree** new_page)
{

    page_tree_buffer *page_buffer; //pagina para fazer o split
    allocBuffer(&page_buffer);
    allocPage(new_page);

    page_buffer->nKeys=ORDER; //pagina vai estar cheia
    int i;
    for(i=0;i<ORDER-1;i++) {//copia a pagina da esquerda para a nova pagina
        page_buffer->keys[i]=page->keys[i];
        page_buffer->keyOffset[i]=page->keyOffset[i];
    }
    page_buffer->keys[i]=key_input; //insere a chave e o seu offset no buffer
    page_buffer->keyOffset[i]=keyoffset;

    bubble_sort(page_buffer); //ordena o buffer

    resetPage(page); //zera a pagina da esquerda
    for(i=0;i<ORDER/2;i++)
        pageInsert(page,page_buffer->keys[i], page_buffer->keyOffset[i], -1); //insere os elementos da esquerda do buffer na pagina da esquerda

    for(i=ORDER/2;i<ORDER;i++)
        pageInsert((*new_page),page_buffer->keys[i],page_buffer->keyOffset[i], -1); //insere os elementos da direita do buffer na pagina da direita

    fseek(bTreeFile,0,SEEK_END); //vai para a posicao de insercao da nova pagina
    *child_promoted=ftell(bTreeFile); //offset do filho a ser promovido
    *key_promoted=(*new_page)->keys[0]; //chave que foi promovida


    int offset_found=-1, pos_found=-1;
    search(offset_root, page->keys[0], &offset_found, &pos_found);

    (*new_page)->keys[0]=(*new_page)->keys[1];
    (*new_page)->keyOffset[0]=(*new_page)->keyOffset[1];
    (*new_page)->keys[1]=NIL;
    (*new_page)->keyOffset[1]=NIL;
    (*new_page)->nKeys=1;

    free(page_buffer);
}

void printaaaa()
{
    rewind(bTreeFile);
    page_tree *paux;
    allocPage(&paux);

    int aux;
    fread(&aux,sizeof(int),1,bTreeFile);
    printf("root_offset %d\n", aux);
    int i=1;
    int pos;
    while(!feof(bTreeFile))
    {
        printf("Interacao %d - offset: %d\n",i, pos=ftell(bTreeFile));
        fread(paux,sizeof(page_tree),1,bTreeFile);
        printf("Numero de chaves na pagina: %d\n",paux->nKeys);
        printf("%ld %ld %ld| %d %d %d | %d %d %d %d\n", paux->keys[0],paux->keys[1],paux->keys[2], paux->keyOffset[0],paux->keyOffset[1],paux->keyOffset[2],
               paux->child[0],paux->child[1],paux->child[2],paux->child[3]);
        i++;
    }
}

void printPage(page_tree *page)
{
    printf("Numero de chaves: %d\n", page->nKeys);
    printf("chaves: [");
    int i;
    for(i=0;i<ORDER-1;i++)
        printf("%ld ", page->keys[i]);
    printf("]\n Posicoes no data.db: [");
    for(i=0;i<ORDER-1;i++)
        printf("%d ", page->keyOffset[i]);
    printf("]Posicoes dos filhos: [");
    for(i=0;i<ORDER;i++)
        printf("%d ", page->child[i]);
    printf("]");

}
void printBuffer(page_tree_buffer *page)
{
    printf("Numero de chaves: %d\n", page->nKeys);
    printf("chaves: [");
    int i;
    for(i=0;i<ORDER;i++)
        printf("%ld ", page->keys[i]);
    printf("]\n Posicoes no data.db: [");
    for(i=0;i<ORDER;i++)
        printf("%d ", page->keyOffset[i]);
    printf("]Posicoes dos filhos: [");
    for(i=0;i<ORDER+1;i++)
        printf("%d ", page->child[i]);
    printf("]");

}
