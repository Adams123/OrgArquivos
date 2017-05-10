#include"indicePrimario.h"

void inserirIndicePrimario(char *pk, int pos)
{
    FILE *fp = fopen("prim.idx", "r+");
    if(fp == NULL) fp = fopen("prim.idx", "w+");
    fseek(fp, 0, SEEK_END); //vai a posicao do novo indice primario
    fprintf(fp,"%-11s %10d\n",pk,pos); //escreve
    fclose(fp);
    ordenaPrim(); //reordena o arquivo prim.idx utilizando qsort
}

int PbuscaBinaria(char *sk)
{
    FILE *fp = fopen("prim.idx", "r+");
    if(fp==NULL) fp = fopen("prim.idx", "w+");

    CAux *aux;
    aux=(CAux*)malloc(sizeof(CAux));
    int i=1;
    rewind(fp);
    while(fscanf(fp,"%s %d\n", aux[i-1].cpf, &aux[i-1].pos)!=EOF) //enquanto nao chegar ao fim do arquivo, le o arquivo inteiro
    {
        i++;
        aux=realloc(aux, sizeof(CAux)*(i));
    }
    i--;

    int return_value = PPesquisaBinaria(aux, sk, i); //realiza busca binaria no array criado, pegando sua posicao no data.db

    free(aux);
    fclose(fp);
    return return_value; //retorna posicao encontrada
}


int PPesquisaBinaria ( CAux *array, char *chave , int N)
{
    int inf = 0; //Limite inferior
    int sup = N; //Limite superior
    int meio;
    while (inf <= sup)
    {
        meio = inf + (sup-inf)/2;
        if (strcmp(chave,array[meio].cpf)==0)
        {
            return array[meio].pos; //encontrou
        }
        else if (strcmp(chave,array[meio].cpf)<0)
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

int comparaPrim (const void * a, const void * b)
{

    CAux *A= (CAux *)a;
    CAux *B= (CAux *)b;

    return ( strcmp(A->cpf, B->cpf));
}

void ordenaPrim()
{
    FILE *fp=fopen("prim.idx","r+");
    if(fp==NULL) fp=fopen("prim.idx", "w+");

    CAux *aux;
    aux=(CAux*)malloc(sizeof(CAux));
    int i=1;
    rewind(fp);

    while(fscanf(fp, "%s %d\n", aux[i-1].cpf, &aux[i-1].pos)!=EOF) //le o arquivo inteiro
    {

        i++;
        aux=realloc(aux, sizeof(CAux)*(i));
    }
    i--; //remove um adicional da ultima interacao

    qsort(aux, i, sizeof(CAux), comparaPrim); //reordena o vetor
    rewind(fp);
    int j;

    for(j=0; j<i; j++) //escreve do comeco o vetor ordenado
    {
        fprintf(fp, "%-11s %10d\n", aux[j].cpf, aux[j].pos);
    }

    free(aux);
    fclose(fp);
}

CAux *buscarCpf(char *cpf, int *tam)
{
    FILE *fp = fopen("prim.idx", "r+");
    if(fp==NULL) return NULL;
    CAux *aux=(CAux*)malloc(sizeof(CAux));
    strcpy(aux[0].cpf, cpf);
    aux[0].pos=PbuscaBinaria(cpf); //busca pelo cpf no arquivo prim.idx
    (*tam)++;
    fclose(fp);
    return aux;
}
void printaCpf(CAux *array, int N)
{
    FILE *fp = fopen("data.db", "r+");
    rewind(fp);
    int i;
    char cpf[11];
    char nome[30];
    char ra[10];
    char univ[30];
    char mod[30];
    for(i=0; i<N; i++)
    {
        fseek(fp, array[i].pos, SEEK_SET);
        fscanf(fp,"%[^|]s", cpf);
        if(strcmp(cpf, "***********")!=0)  //caso o registro foi removido
        {
            getc(fp);
            fscanf(fp,"%[^|]s", nome);
            getc(fp);
            fscanf(fp,"%[^|]s", ra);
            getc(fp);
            fscanf(fp,"%[^|]s", univ);
            getc(fp);
            fscanf(fp,"%[^|]s", mod);
            getc(fp);
            printf("%s - %s\n", cpf, nome);
            printf("\tRegistro Academico: %s\n", ra);
            printf("\tUniversidade: %s\n", univ);
            printf("\tModalidade: %s\n", mod);
        }
    }
    fclose(fp);
}
