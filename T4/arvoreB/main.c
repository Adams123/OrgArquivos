#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "btree.h"
#include "prim.h"


int main(void)
{
    open_initialize_file();
    open_data();
    long int cpf;
    int ra;
    char nome[30], univ[30], mod[30];
    char command[31];
    int exit=0, flag;
    while(!exit)
    {
        scanf("%s", command);
        if(strcmp(command, "sair")==0)
        {
            fclose(bTreeFile);
            fclose(dataFile);
            exit=1;
        }
        else if(strcmp(command, "cadastrar")==0)
        {
            scanf("%ld", &cpf);
            scanf("%s", nome);
            scanf("%d", &ra);
            scanf("%s", univ);
            scanf("%s", mod);
            if((flag=cadastrar(cpf,ra,nome,univ,mod))==2) printf("Conflito de chave primaria. Registro nao inserido!\n");
            else
            {
                insert(offset_root, cpf, flag); //offset_root = 4
            }
        }
        else if(strcmp(command, "dump")==0){
            scanf("%s", command);
            if(strcmp(command, "data.db")==0)
                dump_data();
            else printBTree(offset_root, 1);
        }
//        else if(strcmp(command, "testes")==0)
//        {
//            ra=0101;
//            strcpy(nome, "BUNDA");
//            strcpy(univ, "CAASO");
//            strcpy(mod, "DOTA");
//            printf("-----------------------------------------------------\n");
//            cpf=6;
//            if((flag=cadastrar(cpf,ra,nome,univ,mod))==2) printf("JA EXISTE");
//            else {
//                insert(offset_root, cpf,flag);
//            }
//            //getchar();
//            printBTree(offset_root, 1);
//            printf("-----------------------------------------------------\n");
//            //getchar();
//            printaaaa();
//            printf("-----------------------------------------------------\n");
//            //getchar();
//            system("clear");
//            printf("-----------------------------------------------------\n");
//            cpf=5;
//            if((flag=cadastrar(cpf,ra,nome,univ,mod))==2) printf("JA EXISTE");
//            else {
//                printf("\n\nCadastrando %ld no offset %d\n", cpf, flag);
//                getchar();
//                insert(offset_root, cpf,flag);
//            }
//            printf("-----------------------------------------------------\n");
//            printBTree(offset_root, 1);
//            //getchar();
//            printf("-----------------------------------------------------\n");
//            printaaaa();
//            printf("-----------------------------------------------------\n");
//            //getchar();
//            system("clear");
//            printf("-----------------------------------------------------\n");
//            cpf=10;
//            if((flag=cadastrar(cpf,ra,nome,univ,mod))==2) printf("JA EXISTE");
//            else {
//                printf("Cadastrando %ld no offset %d\n", cpf, flag);
//                getchar();
//                insert(offset_root, cpf,flag);
//            }
//            printf("-----------------------------------------------------\n");
//            printBTree(offset_root, 1);
//            //getchar();
//            printf("-----------------------------------------------------\n");
//            printaaaa();
//            printf("-----------------------------------------------------\n");
//            //getchar();
//            system("clear");
//            printf("-----------------------------------------------------\n");
//            cpf=10;
//            if((flag=cadastrar(cpf,ra,nome,univ,mod))==2) printf("JA EXISTE");
//            else {
//                printf("Cadastrando %ld no offset %d\n", cpf, flag);
//                getchar();
//                insert(offset_root, cpf,flag);
//            }
//            printf("-----------------------------------------------------\n");
//            printBTree(offset_root, 1);
//            //getchar();
//            printf("-----------------------------------------------------\n");
//            printaaaa();
//            printf("-----------------------------------------------------\n");
//            //getchar();
//            system("clear");
//            cpf=8;
//            if((flag=cadastrar(cpf,ra,nome,univ,mod))==2) printf("JA EXISTE");
//            else {
//                printf("Cadastrando %ld no offset %d\n", cpf, flag);
//                getchar();
//                insert(offset_root, cpf,flag);
//            }
//
//            printf("-----------------------------------------------------\n");
//            printBTree(offset_root, 1);
//            getchar();
//            system("clear");
//            printf("-----------------------------------------------------\n");
//            printaaaa();
//            printf("-----------------------------------------------------\n");
//            getchar();
//
//            system("clear");
//            printf("IMPRIMINDO AROVRE!\n");
//            printBTree(offset_root, 1);
//            dump_data();
//
//            exit=1;
//         }
}


//    getchar();
//    printf("-----------------------------------------------------\n");
//    printBTree(offset_root, 1);
//    getchar();
//    printf("-----------------------------------------------------\n");

//    getchar();
//    printf("-----------------------------------------------------\n");
//    getchar();
//    printf("-----------------------------------------------------\n");
//    printBTree(offset_root, 1);
//    getchar();
//    printaaaa();
//    getchar();
//    system("clear");
//    dump_prim();
//    getchar();
//    printf("\n");
    return 0;
}
