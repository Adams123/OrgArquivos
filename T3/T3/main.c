#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"controler.h"

int main(int argc, char *argv[])
{

    int sair = 0;
    char comando[30];
    char c;
    while(!sair)
    {
        scanf("%s",comando);
        if(strcmp(comando,"sair") == 0)
        {
            sair = 1;
        }
        else if(strcmp(comando, "remover")==0)
        {
            char cpf[11];
            scanf("%s", cpf);
            remover(cpf);
        }
        else if(strcmp(comando,"cadastrar") == 0)
            cadastrarAtleta();
        else if(strcmp(comando,"buscar") == 0)
        {
            scanf("%s", comando);
            if(strcmp(comando, "cpf")==0)
            {
                scanf("%s", comando);
                char cpf[12];
                scanf("%s", cpf);
                c=getchar();
                if(c=='\r' || c=='\n') //APENAS CPF
                    buscar(cpf, NULL, NULL, 0);
                else scanf("%s", comando);
                if(strcmp(comando, "e")==0)
                {
                    scanf("%s", comando);
                    if(strcmp(comando, "modalidade")==0) //CPF E MODALIDADE
                    {

                        scanf("%s", comando);
                        char modalidade[30];
                        scanf("%s", modalidade);
                        buscar(cpf, NULL, modalidade, 1);
                    }
                    else if(strcmp(comando, "universidade")==0) //CPF E UNIVERSIDADE
                    {

                        scanf("%s", comando);
                        char universidade[30];
                        scanf("%s", universidade);
                        buscar(cpf, universidade, NULL, 1);
                    }
                }
                else if(strcmp(comando, "ou")==0)
                {
                    scanf("%s", comando);
                    if(strcmp(comando, "modalidade")==0) //CPF OU MODALIDADE
                    {

                        scanf("%s", comando);
                        char modalidade[30];
                        scanf("%s", modalidade);
                        buscar(cpf, NULL, modalidade, 2);
                    }
                    else if(strcmp(comando, "universidade")==0) //CPF OU UNIVERSIDADE
                    {

                        scanf("%s", comando);
                        char universidade[30];
                        scanf("%s", universidade);
                        buscar(cpf, universidade,NULL, 2);
                    }
                }
            }
            else if(strcmp(comando, "universidade")==0)
            {
                scanf("%s", comando);
                char universidade[30];
                scanf("%s", universidade);
                c=getchar();
                if(c=='\r' || c=='\n')
                {
                    //APENAS UNIVERSIDADE
                    buscar(NULL, universidade, NULL, 0);
                }
                else scanf("%s", comando);
                if(strcmp(comando, "e")==0)
                {
                    scanf("%s", comando);
                    if(strcmp(comando, "modalidade")==0) //UNIVERSIDADE E MODALIDADE
                    {
                        scanf("%s", comando);
                        char modalidade[30];
                        scanf("%s", modalidade);
                        buscar(NULL, universidade, modalidade, 1);
                    }
                    else if(strcmp(comando, "cpf")==0) //UNIVERSIDADE E CPF
                    {

                        scanf("%s", comando);
                        char cpf[11];
                        scanf("%s", cpf);
                        buscar(cpf, universidade, NULL, 1);
                    }
                }
                else if(strcmp(comando, "ou")==0)
                {
                    scanf("%s", comando);
                    if(strcmp(comando, "modalidade")==0) //UNIVERSIDADE OU MODALIDADE
                    {

                        scanf("%s", comando);
                        char modalidade[30];
                        scanf("%s", modalidade);
                        buscar(NULL, universidade, modalidade, 2);
                    }
                    else if(strcmp(comando, "cpf")==0) //UNIVERSIDADE OU CPF
                    {

                        scanf("%s", comando);
                        char cpf[11];
                        scanf("%s", cpf);
                        buscar(cpf, universidade,NULL, 2);
                    }
                }
            }
            else if(strcmp(comando, "modalidade")==0) //COMBINACOES MODALIDADE PRIMEIRO
            {
                scanf("%s", comando);
                char modalidade[30];
                scanf("%s", modalidade);
                c=getchar();
                if(c=='\r' || c=='\n') //APENAS MODALIDADE
                    buscar(NULL, NULL, modalidade, 0);
                else scanf("%s", comando);
                if(strcmp(comando, "e")==0)
                {
                    scanf("%s", comando);
                    if(strcmp(comando, "universidade")==0) //MODALIDADE E UNIVERSIDADE
                    {
                        scanf("%s", comando);
                        char universidade[30];
                        scanf("%s", universidade);
//                        printf("Buscando por %s e %s\n", universidade, modalidade);
                        buscar(NULL, universidade, modalidade, 1);
                    }
                    else if(strcmp(comando, "cpf")==0) //MODALIDADE E CPF
                    {
                        scanf("%s", comando);
                        char cpf[11];
                        scanf("%s", cpf);
                        buscar(cpf, NULL, modalidade, 1);
                    }
                }
                else if(strcmp(comando, "ou")==0)
                {
                    scanf("%s", comando);
                    if(strcmp(comando, "universidade")==0) //MODALIDADE OU UNIVERSIDADE
                    {

                        scanf("%s", comando);
                        char universidade[30];
                        scanf("%s", universidade);
                        buscar(NULL, universidade, modalidade, 2);
                    }
                    else if(strcmp(comando, "cpf")==0) //MODALIDADE OU CPF
                    {

                        scanf("%s", comando);
                        char cpf[11];
                        scanf("%s", cpf);
                        buscar(cpf, NULL, modalidade, 2);
                    }
                }
            }
        }
        else if(strcmp(comando, "dump")==0)
            scanf("%s", comando);
        {
            if(strcmp(comando, "prim.idx")==0)
                dumpLista(4);
            else if(strcmp(comando, "universidade.idx")==0)
                dumpLista(0);
            else if(strcmp(comando, "modalidade.idx")==0)
                dumpLista(1);
            else if(strcmp(comando, "universidadeListaInvertida.idx")==0)
                dumpLista(2);
            else if(strcmp(comando, "modalidadeListaInvertida.idx")==0)
                dumpLista(3);
            else if(strcmp(comando, "data.db")==0)
                dumpData();
        }
    }

    return 0;
}
