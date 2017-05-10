#include "listaInvertida.h"

int inserirListaInvertida(char *filename, char *pk, int pos)
{
    int size = 0;
    FILE *fp = fopen(filename, "a+");
    fseek(fp,0,SEEK_END);
    size = ftell(fp);

    fprintf(fp,"%-11s %10d\n",pk,pos);

    fclose(fp);
    return size;
}

CAux* buscarListaInvertida(CAux *aux, int headpos, int flag, int *tam)
{
    FILE *fp;
    switch(flag)
    {
    case 0:
        fp=fopen("universidadeListaInvertida.idx", "r");
        if(fp==NULL) return NULL;
        break;
    case 1:
        fp=fopen("modalidadeListaInvertida.idx", "r");
        if(fp==NULL) return NULL;
        break;
    }
    int i=1;
    fseek(fp, sizeof(char)*headpos, SEEK_SET);
    while(headpos!=-1)
    {
        aux=realloc(aux, sizeof(CAux)*i);
        fscanf(fp,"%s %d", aux[i-1].cpf, &headpos); //copia a nova posicao para o vetor de registros
        aux[i-1].pos=headpos;
        fseek(fp, sizeof(char)*headpos, SEEK_SET);
        i++;
    }
    i--;
    *tam=i;

    fclose(fp);
    return aux;
}
