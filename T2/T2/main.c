#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "run_lenght.h"
#include "huffman.h"


int main(int argc, char *argv[])
{
    int sair=0;
    char magic[3], op[20];
    FILE *fp=NULL;


    char *s; //ponteiro contendo a string do huffman
    int t, i, n_el=0;
    int freq[128]; //todas os valores ascii possiveis sao marcados aqui. sao 127 posicoes para 127 elementos ASCII

    while(!sair)
    {
        fp = NULL;
        scanf("%s", op);
        if(strcmp(op,"sair")==0)
        {
            if(fp!=NULL)
                fclose(fp);
            return 0;
        }
        if(strcmp(op, "dump")==0)
        {
            scanf("%s", op);
            if(strcmp(op, "tree")==0)
            {
                scanf("%s", op);
                fp=fopen(op, "r");
                fseek(fp,0,SEEK_END);
                t=ftell(fp); //pega tamanho maximo do texto
                rewind(fp);
                s=(char*)malloc(sizeof(char)*t); //espaco adicional para o \0
                for(i=0; i<128; i++)
                {
                    freq[i]=-1;//inicializa vetor de frequencias
                }
                fgets(s,t+1,fp); //le o texto a ser usado
                rewind(fp);
                while(*s)
                {
                    freq[(int)*s]++; //incrementa o valor da posicao equivalente ao codigo ASCII da letra lida
                    s=s+1; //avanca a leitura do texto
                }
                for(i=0; i<128; i++)
                if(freq[i]!=-1)
                    n_el++; //verifica quantos elementos teremos na arvore

                node *tree = (struct node*)malloc(sizeof(struct node)*(2*n_el-1)); //aloca espaco para o vetor da arvore
                init_leaves(n_el, freq, tree);//inicializa os nodes
                build_tree(tree,n_el);//constroi a arvore
                fclose(fp);
                //fp=NULL;
                dump(tree, 2*n_el-2); //imprime a arvore


                free(tree);
                tree = NULL;
                n_el=0; //reseta numero de elementos para nao dar conflito com o compactar, caso o dump seja chamado antes
            }
        }
        else if(strcmp(op,"compactar")==0)
        {
            scanf("%s", op);
            if(strcmp(op,"huffman")==0)
            {
                scanf("%s", op);
                fp=fopen(op, "r");
                fseek(fp,0,SEEK_END);
                t=ftell(fp); //pega tamanho maximo do texto
                rewind(fp);
                s=(char*)malloc(sizeof(char)*t); //espaco adicional para o \0
                for(i=0; i<128; i++)
                {
                    freq[i]=-1;//inicializa vetor de frequencias
                }
                fgets(s,t+1,fp);
                char *buffer;
                buffer=s; //salva em um buffer para nao perdermos nunca a string lida
                rewind(fp);
                while(*s)
                {
                    freq[(int)*s]++; //incrementa o valor da posicao equivalente ao codigo ASCII da letra lida
                    s=s+1;//avanca a leitura do texto
                }
                for(i=0; i<128; i++)
                if(freq[i]!=-1)
                    n_el++; //verifica quantos elementos teremos na arvore

                node *tree = (struct node*)malloc(sizeof(struct node)*(2*n_el-1)); //aloca espaco para o vetor da arvore
                init_leaves(n_el, freq, tree); //inicializa os nodes folhas
                build_tree(tree,n_el); //constroi a arvore

                codeTable *codetable; //cria um vetor para salvarmos a tabela de codigo
                codetable=(struct codeTable*)malloc(sizeof(struct codeTable)*n_el);

                code_table(tree,2*n_el-2, 1, codetable); //cria a tabela de codigo baseado na arvore
                ordenaAscii(codetable,n_el); //ordena a tabela de codigo pelo valor ASCII

                for(i=0;i<n_el;i++){
                    printf("%s - %s\n", codetable[i].word,codetable[i].codigo); //imprime a tabela de codigo
                }

                compactar(codetable,buffer); //compacta um texto qualquer

                n_el=0;
                free(tree);
                tree=NULL;
                free(codetable);
                codetable=NULL;



            }
            else if(strcmp(op,"run-lenght")==0)
            {
                scanf("%s", op);
                fp=fopen(op,"rb");
                if(fp!=NULL)
                {
                    fscanf(fp,"%s",magic);
                    if(strcmp(magic,"P2")==0)
                    {
                        cRunLenght(fp);
                    }
                    fclose(fp);
                }

            }
        }
        else if(strcmp(op,"descompactar")==0)
        {
            scanf("%s", op);
            if(strcmp(op,"huffman")==0)
            {
                printf("Nao implementado.\n");
            }
            else if(strcmp(op,"run-lenght")==0)
            {
                scanf("%s", op);
                fp=fopen(op, "rb");

                if(fp!=NULL)
                {
                    fscanf(fp,"%s",magic);
                    if(strcmp(magic,"P8")==0)
                    {

                        dRunLenght(fp);
                    }
                    fclose(fp);

                }
            }
        }
    }
    return EXIT_SUCCESS;
}
