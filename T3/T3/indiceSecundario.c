#include "indiceSecundario.h"
#include "listaInvertida.h"

int comparaLista(const void *a, const void *b)
{
    LAux *A= (LAux *)a;
    LAux *B= (LAux *)b;
    return ( strcmp(A->chave, B->chave));
}

void ordenaLista(int flag)
{
    FILE *fp;
    switch(flag) //abre o arquivo pedido
    {
    case 0:
        fp=fopen("universidade.idx", "r+");
        if(fp==NULL) return;
        break;
    case 1:
        fp=fopen("modalidade.idx", "r+");
        if(fp==NULL) return;
        break;
    }
    rewind(fp);
    LAux *aux;
    aux=(LAux*)malloc(sizeof(LAux));
    int i=1;

    while(fscanf(fp,"%s %d\n", aux[i-1].chave, &aux[i-1].pos)!=EOF) //carrega o arquivo na memora
    {

        i++;
        aux=realloc(aux, sizeof(LAux)*(i));
    }
    i--; //remove um adicional da ultima interacao
    int j;

    qsort(aux, i, sizeof(LAux), comparaLista); //ordena o vetor
    rewind(fp);

    for(j=0; j<i; j++)
    {
        fprintf(fp,"%-30s %10d\n", aux[j].chave, aux[j].pos); //reimprime o arquivo
    }
    fclose(fp);

}

int buscaBinaria(int flag, char *sk, int *filePos)
{
    FILE *fp;
    switch(flag) //abre o arquivo indicado
    {
    case 0:
        fp=fopen("universidade.idx", "r+");
        if(fp==NULL) fp=fopen("universidade.idx", "w+");
        break;
    case 1:
        fp=fopen("modalidade.idx", "r+");
        if(fp==NULL) fp=fopen("modalidade.idx", "w+");
        break;
    }
    LAux *aux;
    aux=(LAux*)malloc(sizeof(LAux));
    int i=1;
    rewind(fp);
    int filePosAux;
    while(!feof(fp))
    {
        filePosAux = ftell(fp); //pega a posicao da chave secundaria no arquivo de chaves secundarias
        fscanf(fp,"%s %d\n", aux[i-1].chave, &aux[i-1].pos);
        if(strcmp(aux[i-1].chave, sk)==0) *filePos = filePosAux; //se eh a chave porcurada, guarda a posicao dele
        i++;
        aux=realloc(aux, sizeof(LAux)*(i));
    }
    i--;

    int return_value = PesquisaBinaria(aux, sk, i); //faz busca binaria pela chave secundaria
    free(aux);
    fclose(fp);
    return return_value;
}


int PesquisaBinaria ( LAux *array, char *chave , int N)
{
    int inf = 0; //Limite inferior
    int sup = N; //Limite superior
    int meio;
    while (inf <= sup)
    {
        meio = inf + (sup-inf)/2;
        if (strcmp(chave,array[meio].chave)==0)
        {
            return array[meio].pos; //encontrou. retorna a head da lista invertida
        }
        else if (strcmp(chave,array[meio].chave)<0)
        {
            sup = meio-1;
        }
        else
        {
            inf = meio+1;
        }
    }
    return -1;   // não encontrado
}

void inserirIndiceSecundario(const char *filename, char *sk, char *pk)
{

    char filename2[50];
    int flag;
    if(strcmp(filename, "universidade.idx") == 0)
    {
        sprintf(filename2,"universidadeListaInvertida.idx");
        flag=0;
    }
    else if(strcmp(filename, "modalidade.idx") == 0)
    {
        sprintf(filename2,"modalidadeListaInvertida.idx");
        flag=1;
    }
    int filePos; //posicao da chave secundaria no arquivo de chaves secundarias
    int posAux = buscaBinaria(flag, sk, &filePos); //verifica se a chave secundaria ja existe. Se existe, retorna a head na lista invertida correspondente
    FILE *fp = fopen(filename, "r+");
    if(fp == NULL) fp = fopen(filename, "w+");
    fseek(fp, 0, SEEK_SET);

    if(posAux!=-1)  //achou
    {
        int pos = inserirListaInvertida(filename2, pk, posAux); //insere na lista invertida
        fseek(fp, filePos, SEEK_SET); //vai para a posicao da chave secundaria
        fseek(fp,31*sizeof(char),SEEK_CUR); //pula o tamanho dela + um espaco
        fprintf(fp,"%10d", pos); //sobrescreve a nova posicao da head
        fclose(fp);
    }
    else   //nao achou
    {
        int pos = inserirListaInvertida(filename2, pk, -1); //primeiro elemento da nova lista
        fseek(fp, 0, SEEK_END);
        fprintf(fp,"%-30s %10d\n", sk, pos);
        fclose(fp);
        ordenaLista(flag);
    }
}

CAux* buscarSk(char *universidade, char *modalidade, int *tam)
{
    CAux *aux;
    CAux *aux2;
    aux=(CAux*)malloc(sizeof(CAux));
    int filePos=0, headpos;
    if(universidade)
    {
        headpos=buscaBinaria(0, universidade, &filePos);
        aux=buscarListaInvertida(aux, headpos, 0, tam);
        if(aux==NULL) return NULL;
        aux2 = (CAux*)malloc(sizeof(CAux)*(*tam));
        int i;
        for(i=0; i<(*tam); i++)
        {
            strcpy(aux2[i].cpf,aux[i].cpf);
            aux2[i].pos=PbuscaBinaria(aux[i].cpf);
        }
        qsort(aux2, (*tam), sizeof(CAux), comparaPrim);
    }
    else if(modalidade)
    {
        headpos=buscaBinaria(1, modalidade, &filePos);
        aux=buscarListaInvertida(aux, headpos, 1, tam);
        if(aux==NULL) return NULL;
        aux2 = (CAux*)malloc(sizeof(CAux)*(*tam));
        int i;
        for(i=0; i<(*tam); i++)
        {
            strcpy(aux2[i].cpf,aux[i].cpf);
            aux2[i].pos=PbuscaBinaria(aux[i].cpf);
        }
        qsort(aux2, (*tam), sizeof(CAux), comparaPrim);
    }
    return aux2;
}
