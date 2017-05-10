#include "bancoDeDados.h"
#include "indicePrimario.h"

//funcao que insere no banco o novo registro
int inserirNoBanco(char *cpf, char *nome, char *ra, char *univ, char *mod)
{
    if(PbuscaBinaria(cpf)!=-1) //verifica se ja existe cadastro no arquivo de indice primario (prim.idx)
        return -1;
    int size = 0;

    //abre o arquivo com append
    FILE *fp = fopen("data.db","a+");

    //garante que o ponteiro esta no fim do arquivo
    //para saber a posicao do prox. registro
    fseek(fp,0,SEEK_END);
    size = ftell(fp);

    //salva o novo registro no banco de dados
    fprintf(fp,"%-11s|",cpf);
    fprintf(fp,"%-30s|",nome);
    fprintf(fp,"%-10s|",ra);
    fprintf(fp,"%-30s|",univ);
    fprintf(fp,"%-30s|",mod);

    //fecha o arquivo
    fclose(fp);

    return size; //retorna a posicao do novo registro no data.db
}

void removeRegistro(int pos)
{
    FILE *fp = fopen("data.db", "r+");
    fseek(fp, sizeof(char)*pos, SEEK_SET); //vai para a posicao inicial do registro, contendo a chave primaria
    fprintf(fp, "***********"); //apaga a chave primaria
    fclose(fp);
}
