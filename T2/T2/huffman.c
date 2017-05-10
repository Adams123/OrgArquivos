/*A logica utilizada para este programa foi da wikipedia: http://en.wikipedia.org/wiki/Huffman_tree#Compression
*/

#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void init_leaves(int n_ele, int freq[], node *tree) //constroi todos os nodes folhas
{
    node *leaf;
    int i, j=0;

    leaf=(struct node*)malloc(sizeof(struct node)*n_ele); //cria n folhas

    while(j<n_ele)
        for(i=0; i<128; i++) //procura na tabela de frequencia
        {
            if(freq[i]!=-1) //caso a frequencia foi inicializada
            {
                leaf[j].freq=freq[i]+1; //salva a frequencia final das folhas
                leaf[j].letra=(char*)malloc(sizeof(char)*2);
                leaf[j].letra[0]=i; //coloca a letra na primeira posicao
                leaf[j].letra[1]='\0'; //e um espaco na segunda
                leaf[j].flag=0;  //nao foi utiliziado ainda
                leaf[j].left=-1;
                leaf[j].right=-1;
                tree[j] = leaf[j]; //cria as primeiras n posicoes da arvore
                j++;
            }
        }
    free(leaf);
}

//inverte uma string qualquer utilizando XOR
//retirado do site http://forums.codeguru.com/showthread.php?303185-Reversing-a-string-in-C&p=982893#post982893

void rev(char* str)
{
  int end= strlen(str)-1;
  int start = 0;

  while( start<end )
  {
    str[start] ^= str[end];
    str[end] ^=   str[start];
    str[start]^= str[end];

    ++start;
    --end;
  }
}
/*Converte um numero composto de 1 e 2 para uma string binaria
    Input: int a: numero a ser convertido

    Output: vetor convertido
*/

char* toBin(int a){
        int i, aux=a, aux2=0;
        char *v;
        for(; aux!=0; aux=aux/10)
        {
            aux2++; //conta quantos digitos tem o numero
        }


        v = malloc(sizeof(char)*aux2);
        aux=a;
        for(i=0; i<aux2-1; i++) //percorrendo todos os digitos
        {
            if(aux%10==1) //se o resto da divisao for 1, 1 representa 0
                v[i]='0'; //entao coloca na posicao i um 0
            else if(aux%10==2)//se o resto da divisao for 2, 2 representa 1
                v[i]='1';//entao coloca na posicao i um 1
            aux=aux/10; //vai para a proxima casa
        }
        v[aux2-1]='\0'; //coloca um /0 na ultima posicao
        rev(v); //o vetor resultante esta na ordem invertida, entao usa-se a rev para inverter a string
        return (v); //retorna a string na ordem correta
}



/*Ordena um vetor do tipo tree
    Inputs:
    node *tree: vetor da arvore
    int n_ele: quantidade de elementos a serem ordenados

Utiliza um bubble-sort, pois no pior caso, tera 127 elementos
*/
void ordena(node *tree, int n_ele)
{
    int i,j;
    node aux;

    for(i=0; i<n_ele; i++)
    {
        for(j=i+1; j<n_ele; j++)
            while(tree[i].freq>tree[j].freq)
            {
                aux=tree[i];
                tree[i]=tree[j];
                tree[j]=aux;
            }
    }
}
/* Imprime a arvore in-ordem
    Inputs:
    node *tree: ponteiro para o vetor da arvore
    int n_ele: numero maximo de elementos da arvore
*/
void dump(node *tree, int pos)
{
    if(tree!=NULL)
    {
        if(tree[pos].left != -1)  //condicao de parada: left == -1 indica que nao ha nodes na esquerda
        {
            dump(tree, tree[pos].left); //chama recursivamente para a esquerda
        }

        printf("%6d - %s\n",tree[pos].freq, tree[pos].letra);

        if(tree[pos].right != -1)  //condicao de parada: right == -1 indica que nao ha nodes na direita
        {
            dump(tree, tree[pos].right); //chama recursivamente para a direita
        }
    }
}

/*
Constroi a arvore de huffman em um vetor, onde os n primeiros elementos sao as folhas e os proximos n-1 elementos sao
os nodes resultantes da somas das folhas. Funciona como uma pilha, onde os elementos vao sendo inutlizados ao serem usados.
    Inputs:
    node *tree: ponteiro para o vetor da arvore
    int n_ele: numero maximo de elementos da arvore
*/

void build_tree(node *tree, int n_ele)
{
    int i=0, cont = 0, a, b, k;
    char *aux;
    ordena(tree,n_ele);
    i=0;
    while(i<2*n_ele-2)
    {

        if(i==n_ele-1)  //inserindo node da arvore direita
        {
            //soma as frequencias dos dois primeiros nodes
            tree[n_ele+cont].freq=tree[i].freq + tree[i+1].freq;
            //faz a inversao da arvore (caso n_ele =2*k+1) colocando o segundo menor no node da esquerda e o menor no node da direita
            tree[n_ele+cont].left=i+1;
            tree[n_ele+cont].right=i;

            a=strlen(tree[i].letra); //pega quantas letras tem o menor
            b=strlen(tree[i+1].letra); //e quantas letras tem o segundo menor

            aux=malloc(sizeof(char)*(a+b)); //cria um vetor auxiliar e o preenche com \0
            for(k=0;k<a+b;k++){
                aux[k]='\0';
            }
            strcpy(aux,tree[i+1].letra); //pega a primeira letra e concatena com a segunda
            strcat(aux,tree[i].letra);

            tree[n_ele+cont].letra = aux; //coloca o resultado no novo node
        }
        else   //inserindo node da arvore esquerda. Processo igual ao da esquerda, exceto que nao eh inserido invertido
        {
            tree[n_ele+cont].freq=tree[i].freq + tree[i+1].freq;//soma as frequencias dos dois primeiros nodes
            tree[n_ele+cont].left=i;
            tree[n_ele+cont].right=i+1;//faz esquerda apontar para o menor e direita apontar para o segundo menor
            a=strlen(tree[i+1].letra);
            b=strlen(tree[i].letra);

            aux=malloc(sizeof(char)*(a+b));
            for(k=0;k<a+b;k++){
                aux[k]='\0';
            }
            strcpy(aux,tree[i].letra);
            strcat(aux,tree[i+1].letra);
            tree[n_ele+cont].letra = aux;
        }
        i=i+2;//avanca para os dois proximos nodes da fila de prioridade
        cont++;//avanca na posicao a ser criado o novo node juncao dos dois menores
    }
    //free(aux);
    //no fim, teremos o ultimo node como a head da arvore
}


/*Constroi a tabela de codigo binario dos nodes folhas da arvore. Note que, durante a construcao, noo codigo o 0 eh representado por 1 e o 1 por 2, para facilitar a aritmetica
    Inputs:
    node *tree: ponteiro para o vetor da arvore
    int pos: posicao da arvore onde iremos colocar o binario
*/


void code_table(node *tree, int pos, int code, codeTable *codetable)
{
    if(tree!=NULL)
    {
        if(tree[pos].left != -1) //se o node da esquerda existe
            code_table(tree,tree[pos].left,code*10+1, codetable); //constroi o codigo pro node da esquerda
            if(tree[pos].left == -1 && tree[pos].right == -1){ //se chegou em um node folha
        char *aux2; //cria um vetor auxiliar
        aux2=toBin(code); //cria codigo binario
        tree[pos].bin=aux2; //coloca no node da arvore
        codetable[pos].codigo=aux2; //coloca na tabela de codigos
        codetable[pos].word=tree[pos].letra; //coloca a letra correspondente para a tabela de codigos
            }
        if(tree[pos].right != -1) //se ha node na direita
            code_table(tree,tree[pos].right,code*10+2, codetable); //constroi codigo para o node da direita
    }
}

/* Converte uma string lida para binario utilizando a tabela de codigos previamente construida
*/

void compactar(codeTable *codetable, char *s){
    int a;
    char *aux = s; //para nao modificarmos a string
    printf("-\n"); //separador
    while(*aux){
            a=0;//reseta contador
    while(codetable[a].word[0] != (int)*aux){ //busca a letra lida na tabela de codigos
        a++;
    }
    printf("%s", codetable[a].codigo); //imprime o codigo encontrado
    aux=aux+1;//avanca na string
    }
    printf("\n");
}

/*Ordena o vetor de codeTable
    Inputs:
    codeTable *codetable: ponteiro para o vetor da tabela de codigos
    int n_ele: quantidade de elementos a serem ordenados

Utiliza um bubble-sort, pois no pior caso, tera 127 elementos
*/
void ordenaAscii(codeTable *codetable, int n_ele)
{
    int i,j;
    codeTable aux;

    for(i=0; i<n_ele; i++)
    {
        for(j=i+1; j<n_ele; j++)
            while(codetable[i].word>codetable[j].word)
            {
                aux=codetable[i];
                codetable[i]=codetable[j];
                codetable[j]=aux;
            }
    }

}
