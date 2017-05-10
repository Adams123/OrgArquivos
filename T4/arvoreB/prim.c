#include "prim.h"
#include "btree.h"

void open_data()
{
    dataFile = fopen("data.db", "w+");
}

int cadastrar(long int cpf, int ra, char *nome, char *universidade, char *modalidade)
{
    int pos_found, offset_found;
    int flag = search(offset_root, cpf, &offset_found, &pos_found);
    if(flag==SUCCESS) return ERROR;
    fseek(dataFile, 0, SEEK_END);
    int pos = ftell(dataFile);
    fprintf(dataFile, "0%-10ld|%-30s|%-10d|%-30s|%-30s|", cpf,nome,ra,universidade,modalidade);
    return(pos);
}

void dump_data()
{
    char c;
    rewind(dataFile);
    while((c=getc(dataFile))!=EOF)
        printf("%c", c);
    printf("\n");
}
