#include "run_lenght.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*Verifica se ha quebra de linha ou nao
    inputs:
    -int c: caracter lido no arquivo
    -FILE *fp: arquivo a ser verificado
    outputs:
    1: chegou na quebra de linha
    0: nao ha quebra de linha
*/
int eol(int c, FILE *fp)
{
    if (c == '\n') return 1;//caso sistema Linux, em que a quebra de linha eh representada por \n
    if (c == '\r')
    {
        if ((c = getc(fp)) != '\n') ungetc(c, fp);//caso sistema Windows, em que a quebra de linha eh representada por \r\n
        return 1;
    }
    return 0;
}

/*Posiciona o cabecote de leitura do arquivo na proxima linha
    Inputs:
        File *fp: arquivo a ser usado
    Outputs
        0 se chegou no fim da linha
        1 caso contrario
*/
int skipline(FILE *fp)
{
    int c;
    //verifica se chegou no final do arquivo ((c = getc(fp)) != EOF)
    //e se houve quebra de linha utilizando a funcao eol
    while ((c = getc(fp)) != EOF && !eol(c, fp));
    return c == EOF;
}

/*Le um arquivo *.pgm e compacta o arquivo. Em seguida, imprime na tela o arquivo compactado
    Inputs:
    File *fp: arquivo a ser lido

    Outputs:
    output.r1 compactado impresso em stdout
*/

void cRunLenght(FILE *fp)
{
    rewind(fp);
    int i=0, j, l, c, var, cont,maxv;
    i=skipline(fp);//pula o magic number

    fscanf(fp,"%d",&c); //le a quantidade de colunas
    fscanf(fp,"%d",&l); //le a quantidade de linhas
    i=skipline(fp);
    fscanf(fp,"%d",&maxv); //le o maior valor de tom de cinza
    i=skipline(fp);

    int data[l][c];
    for(i=0; i<l; i++) //percorrer todas as linhas
    {
        for(j=0; j<c; j++)//percorrer todas as colunas (caracteres das linhas) ate encontrar \n ou \r
        {
            fscanf(fp,"%d",&data[i][j]); //le toda uma linha e guarda em data
        }
        var=skipline(fp);//pula linha
    }

    //escrita do arquivo compactado
    fprintf(stdout, "P8\n"); //imprime em stdout o magic number
    fprintf(stdout, "%d %d\n", c, l);//imprime em stdout quantidade de colunas e linhas
    fprintf(stdout, "%d\n", maxv); //imprime em stdout o max valor de tom de cinza

    int x;
    for(i=0; i<l; i++)
    {
        var=1; //variavel para contagem de caracteres iguais
        for(j=0; j<c; j++) //percorre linha ate o fim
        {
            while(data[i][j]==data[i][j+1]&&j<c-1)//enquanto caracter lido for igual ao proximo e nao chegar ao fim da linha
            {
                var++;//aumenta numero de caracteres iguais
                j++;//avanca na linha
            }
            x=data[i][j];//ultimo caracter lido
            if(var>3)//caso haja 4 ou mais repeticoes escreve no arquivo out
            {
                if(j!=c-1) //caso nao seja o ultimo caracter
                    fprintf(stdout,"ff %d %d ",x,var);
                else fprintf(stdout,"ff %d %d\n",x,var); //caso seja o ultimo caracter
                var=1;
            }
            else //caso contrario
            {
                for(cont=0; cont<var; cont++)//imprime o ultimo caracter lido var vezes
                {
                    if(j!=c-1)//caso nao seja o ultimo caracter
                        fprintf(stdout, "%d ",x);
                    else fprintf(stdout, "%d\n",x);//caso seja o ultimo caracter
                }
                var=1;
            }
        }
    }
}

/*Le um arquivo *.r1 e descompacta o arquivo. Em seguida imprime na tela o arquivo descompactado
    Inputs:
    File *fp: arquivo a ser lido

    Outputs:
    arquivo descompactado em stdout
*/
//void dRunLenght(FILE *fp, FILE *sd)
void dRunLenght(FILE *fp)
{
    rewind(fp);
    //rewind(sd);
    int i=0, j, l, c, maxv;
    i=skipline(fp);//pula o magic number

    //inicializa imagem

    fscanf(fp,"%d",&c);//le quantidade de colunas
    fscanf(fp,"%d",&l);//le quantidade de linhas
    i=skipline(fp);
    fscanf(fp,"%d",&maxv);//le maximo valor de tom de cinza
    i=skipline(fp);

    //imprime o magic number, numero de linhas, colunas e max valor de tom de cinza
    fprintf(stdout, "P2\n");
    fprintf(stdout, "%d %d\n", c, l);
    fprintf(stdout, "%d\n", maxv);

//    fprintf(sd, "P2\n"); //imprime em stdout o magic number
//    fprintf(sd, "%d %d\n", c, l);//imprime em stdout quantidade de colunas e linhas
//    fprintf(sd, "%d\n", maxv); //imprime em stdout o max valor de tom de cinza

    int n,x, aux=1;
    char p[3];
    for(i=0; i<l; i++) //percorre todas as linhas do arquivo
    {
        for(j=0; j<c; j++) //percorre a linha ate o fim
        {
            fscanf(fp,"%s", p); //le a primeira string
            if(strcmp(p,"ff")==0)//caso ela seja "ff", le qual eh o caracter repetido e quantas vezes ocorre a repeticao
            {
                fscanf(fp,"%d",&x); //le qual eh o elemento a ser escrito
                fscanf(fp,"%d",&n); //le quantas vezes o elemento deve ser escriito
                if(((j+n)==c)||(n==c)) //caso seja o ultimo caracter a ser escrito ou vai escrever uma linha inteira
                {
                    for(aux=0; aux<n-1; aux++)  //escreve o elemento n-1 vezes
                    {
                        fprintf(stdout,"%d ",x);
                        //fprintf(sd,"%d ",x);
                    }
                    fprintf(stdout,"%d\n",x);//escreve o ultimo elemento seguido de \n
                    //fprintf(sd,"%d\n",x);//escreve o ultimo elemento seguido de \n
                }
                else //caso seja uma repeticao no meio da linha
                {
                    for(aux=0; aux<n; aux++)  //escreve o elemento n vezes
                    {
                        fprintf(stdout,"%d ",x);
                        //fprintf(sd,"%d ",x);
                    }
                }
                j=j+n-1; //anda ate o fim das repeticoes
            }
            else  //caso nao encontre o marcador, passa a string para inteiro e a imprime
            {
                x=atoi(p);
                if(j!=c-1) //caso nao seja o ultimo caracter da linha
                {
                    fprintf(stdout, "%d ", x);
                    //fprintf(sd, "%d ", x);
                }
                else
                {
                    fprintf(stdout, "%d\n", x);//ultimo caracter da linha
                    //fprintf(sd, "%d\n", x);
                }
            }
        }
    }
}

