#include "controler.h"

void cadastrarAtleta()
{
    char cpf[12];
    char nome[31];
    char ra[11];
    char univ[31];
    char mod[31];

    scanf("%s",cpf);
    scanf("%s", nome);
    scanf("%s", ra);
    scanf("%s",univ);
    scanf("%s",mod);
    //insere no banco de dados e pega a posicao que foi inserida
    int pos = inserirNoBanco(cpf, nome, ra, univ, mod);
    if(pos==-1) //caso ja exista
    {
        printf("Conflito de chave primaria. Registro nao inserido!\n");
        return;
    }
    inserirIndicePrimario(cpf, pos); //insere no arquivo prim.idx a nova posicao

    inserirIndiceSecundario("universidade.idx", univ, cpf); //insere no arquivo universidade.idx a chave secundaria de universidade
    inserirIndiceSecundario("modalidade.idx", mod, cpf); //insere no arquivo modalidade.idx a chave secundar de modalidade


}

void dumpData()
{
    FILE *fp = fopen("data.db", "r"); //abre o data.db
    if(fp==NULL) return;
    char c;
    rewind(fp); //vai para o inicio do arquivo e imprime char a char
    while((c=getc(fp))!=EOF)
    {
        printf("%c", c);
    }
    printf("\n");
    fclose(fp);
}

void buscar(char *cpf, char *universidade, char *modalidade, int flag)
{
    int tam=0, tam2=0;
    int sizeFinal;
    switch(flag)
    {
    case 0: //buscando apenas um dos dados (sem operador logico)
        if(cpf)
        {
            CAux *aux = buscarCpf(cpf, &tam); //busca pelo cpf desejado
            if(aux==NULL) return;
            printaCpf(aux, tam); //imprime cpf encontrado
            free(aux);
        }
        else if(universidade)
        {
            CAux *aux = buscarSk(universidade, NULL, &tam); //busca pela universidade desejada
            if(aux==NULL) return;
            printaCpf(aux, tam); //imprime lista de registros
            free(aux);

        }
        else if(modalidade)
        {
            CAux *aux = buscarSk(NULL, modalidade, &tam); //busca pela modalidade desejada
            if(aux==NULL) return;
            printaCpf(aux, tam); //imprime lista de registros
            free(aux);
        }
        break;
    case 1: //buscando combinacao E

        if(cpf && universidade) //buscando por cpf e universidade
        {
            CAux *aux = buscarCpf(cpf, &tam); //busca o cpf
            CAux *aux2 = buscarSk(universidade, NULL, &tam2); //busca a universidade
            CAux *list=matching(aux, aux2, tam, tam2, &sizeFinal); //faz intersecao dos dois
            if(sizeFinal > 0) //caso nao seja nula
                printaCpf(list, sizeFinal); //imprime registros resultantes
            free(aux2);
            free(aux);
            free(list);
        }
        else if(cpf && modalidade) //buscando por cpf e modalidade
        {
            CAux *aux = buscarCpf(cpf, &tam);//busca o cpf
            CAux *aux2 = buscarSk(NULL, modalidade, &tam2); //busca a modalidade
            CAux *list=matching(aux, aux2, tam, tam2, &sizeFinal); //faz intersecao dos dois
            if(sizeFinal > 0) //caso nao seja nula
                printaCpf(list, sizeFinal); //imprime registros resultantes
            free(aux2);
            free(aux);
            free(list);
        }
        else if(universidade && modalidade)//buscando por universidade e modalidade
        {
            CAux *aux = buscarSk(universidade, NULL, &tam); //busca a universidade
            CAux *aux2 = buscarSk(NULL, modalidade, &tam2); //busca a modalidade
            CAux *list = matching(aux, aux2, tam, tam2, &sizeFinal); //faz intersecao dos dois
            if(sizeFinal > 0) //caso nao seja nula
                printaCpf(list, sizeFinal); //imprime registros resultantes
            free(aux2);
            free(aux);
            free(list);
        }
        break;
    case 2: //buscando combinacao OU
        if(cpf && universidade)
        {
            CAux *aux = buscarCpf(cpf, &tam); //busca o cpf
            CAux *aux2 = buscarSk(universidade, NULL, &tam2); //busca a universidade
            CAux *list=merging(aux, aux2, tam, tam2, &sizeFinal); //faz uniao dos dois
            if(sizeFinal > 0) //caso nao seja nula
                printaCpf(list, sizeFinal); //imprime registros resultantes

            free(aux2);
            free(aux);
            free(list);
        }
        else if(cpf && modalidade) //buscando por cpf ou modalidade
        {
            CAux *aux = buscarCpf(cpf, &tam); //busca o cpf
            CAux *aux2 = buscarSk(NULL, modalidade, &tam2); //busca a modalidade
            CAux *list=merging(aux, aux2, tam, tam2, &sizeFinal); //faz uniao dos dois
            if(sizeFinal > 0) //caso nao seja nula
                printaCpf(list, sizeFinal); //imprime registros resultantes

            free(aux2);
            free(aux);
            free(list);
        }
        else if(universidade && modalidade)
        {
            CAux *aux = buscarSk(universidade, NULL, &tam); //busca a universidade
            CAux *aux2 = buscarSk(NULL, modalidade, &tam2); //busca a modalidade
            CAux *list=merging(aux, aux2, tam, tam2, &sizeFinal); //faz uniao dos dois
            if(sizeFinal > 0) //caso nao seja nula
                printaCpf(list, sizeFinal); //imprime registros resultantes

            free(aux2);
            free(aux);
            free(list);
        }
        break;
    }
}

void dumpLista(int flag)
{
    int TAM;
    FILE *fp;
    switch(flag)
    {
    case 0:
        fp=fopen("universidade.idx", "r");
        TAM = 30;
        break;
    case 1:
        fp=fopen("modalidade.idx", "r");
        TAM = 30;
        break;
    case 2:
        fp=fopen("universidadeListaInvertida.idx", "r");
        TAM = 11;
        break;
    case 3:
        fp=fopen("modalidadeListaInvertida.idx", "r");
        TAM = 11;
        break;
    case 4:
        fp=fopen("prim.idx", "r");
        TAM = 11;
        break;
    }
    int posBancoDeDados;
    char chavePrimaria[TAM];
    rewind(fp);
    while(fscanf(fp, "%s %d\n", chavePrimaria, &posBancoDeDados)!=EOF)
    {
        printf("%s - %d\n", chavePrimaria, posBancoDeDados);
    }
    fclose(fp);

}

void remover(char *cpf)
{
    int tam;
    CAux *aux = buscarCpf(cpf, &tam); //busca pela posicao do cpf a ser removido do data.db
    removeRegistro(aux[0].pos);
    free(aux);
}

CAux* matching(CAux *a, CAux *b, int size1, int size2, int *sizeFinal)
{
    CAux *list; //lista a ser retornada contendo os cpfs e as posicoes do data.db
    //aloca com o menor tamanho
    if(size1<size2)
        list=(CAux*)malloc(sizeof(CAux)*size1);
    else
        list=(CAux*)malloc(sizeof(CAux)*size2);

    int posA = 0, posB = 0, listSize = 0;

    while(posA < size1 && posB < size2) //enquanto nao chegar no final das duas listas
    {
        if(strcmp(a[posA].cpf,b[posB].cpf)<0) //caso o cpf da primeira seja menor que o da segunda, avanca na primeira
            posA++;
        else if(strcmp(a[posA].cpf,b[posB].cpf)>0) //caso o cpf da segunda seja menor que o da primeira, avanca na segunda
            posB++;
        else //cpfs iguais, copia o registro para a nova lista, avanca nas duas listas e incrementa o tamanho da lista final
        {
            list[listSize].pos = b[posB].pos;
            strcpy(list[listSize].cpf, b[posB].cpf);
            listSize++;
            posA++;
            posB++;
        }
    }
    *sizeFinal = listSize;
//    qsort(list, listSize, sizeof(CAux), comparaPrim); //reordena as listas
    return list;
}

CAux* merging(CAux *a, CAux *b, int size1, int size2, int *sizeFinal)
{
    CAux *list;
    list=(CAux*)malloc(sizeof(CAux)*(size1+size2)); //aloca com o tamanho maximo que pode chegar a ser usado

    int posA = 0, posB = 0, listSize = 0;

    while(posA < size1 && posB < size2)
    {
        if(strcmp(a[posA].cpf,b[posB].cpf)<0)  //caso o primeiro cpf seja menor que o segundo, copia o primeiro, incrementa a lista final e avanca na primeira lista
        {
            list[listSize].pos = a[posA].pos;
            strcpy(list[listSize].cpf, a[posA].cpf);
            posA++;
            listSize++;
        }
        else if(strcmp(a[posA].cpf,b[posB].cpf)>0)  //caso o segundo cpf seja menor que o primeiro, copia o segundo, incrementa a lista final e avanca na segunda lista
        {
            list[listSize].pos = b[posB].pos;
            strcpy(list[listSize].cpf, b[posB].cpf);
            posB++;
            listSize++;
        }
        else //sao iguais, copia o segundo, incrementa a lista final e avanca em ambas as listas
        {
            list[listSize].pos = b[posB].pos;
            strcpy(list[listSize].cpf, b[posB].cpf);
            listSize++;
            posA++;
            posB++;
        }
    }
    if(posA < size1) //se nao percorreu a lista 1 inteira
    {
        while(posA < size1) //termina de percorrer a lista copiando os registros remanescentes
        {
            list[listSize].pos = a[posA].pos;
            strcpy(list[listSize].cpf, a[posA].cpf);
            listSize++;
            posA++;
        }
    }
    else if(posB < size2) //se nao percorreu a lista 2 inteira
    {
        while(posB < size2) //termina de percorrer a lista copiando os registros remanescentes
        {
            list[listSize].pos = b[posB].pos;
            strcpy(list[listSize].cpf, b[posB].cpf);
            listSize++;
            posB++;
        }
    }
    *sizeFinal = listSize;
    list=realloc(list, sizeof(CAux)*listSize); //realoca para o tamanho usado
//    qsort(list, listSize, sizeof(CAux), comparaPrim); //reordena as listas
    return list;
}
