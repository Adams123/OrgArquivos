#include "tad.h"
//-------------------------------------------------------------------------------------------------------------------------------------------

void ordenaDisciplina(FILE *disciplinas, int m)
{
    int i, j;
    disciplina aux[2];

    rewind(disciplinas);
    //inicio bubble sort do arquivo
    for(i=0; i<=m; i++)//primeiro elemento
    {
        for(j=0; j<=m-1; j++)//proximo elemento
        {
            fseek(disciplinas, j*sizeof(disciplina),SEEK_SET);//vai ate a posicao inicial da disciplina 1
            fread(&aux[0],sizeof(disciplina),1,disciplinas);//le a a disciplina 1
            fseek(disciplinas,(i+1)*sizeof(disciplina),SEEK_SET);//vai ate a posicao inicial da disciplina 2
            fread(&aux[1],sizeof(disciplina),1,disciplinas);//le a disciplina 2
            if(strcmp(aux[0].codigo,aux[1].codigo) > 0)//compara os codigos das disciplinas
            {
                //se o codigo da disciplina 1 for maior que o da disciplina 2, troca as disciplinas
                fseek(disciplinas, j*sizeof(disciplina),SEEK_SET);//vai ate a posicao inicial da disciplina 1
                fwrite(&aux[1],sizeof(disciplina),1,disciplinas);//escreve a disciplina 2
                fseek(disciplinas,(i+1)*sizeof(disciplina),SEEK_SET);//vai ate a posicao inicial da disciplina 2
                fwrite(&aux[0],sizeof(disciplina),1,disciplinas);//escreve a disciplina 1
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------

int cadastrarDisciplina(disciplina *disc, FILE *disciplinas, int m)
{
    rewind(disciplinas);

    fseek(disciplinas, m*sizeof(disciplina), SEEK_SET);//coloca o ponteiro na posicao da m-esima disciplina
    fwrite(disc, sizeof(disciplina), 1, disciplinas);//escreve todas as informacoes da disciplina na i-esima posicao
    ordenaDisciplina(disciplinas,m);
    return m+1;//retorna numero de disciplinas cadastradas +1
}

//-------------------------------------------------------------------------------------------------------------------------------------------

void dumpDisciplina(FILE *disciplinas, int m)
{
    if(m==0) return;//se nao ha disciplinas cadastradas, retorna NULL

    disciplina aux;
    int i;

    rewind(disciplinas);

    for(i=m-1; i>=0; i--)//percorre o arquivo de disciplinas de 0 ate m (numero de disciplinas cadastradas)
    {
        fseek(disciplinas, i*sizeof(disciplina), SEEK_SET);
        fread(&aux,(sizeof(disciplina)),1,disciplinas);//le a disciplina
        printf("\%s - \%s - \%s\n",aux.codigo,aux.nomeDisciplina,aux.professor);//imprime dados da disciplina
        //nao eh necessario mover o ponteiro para proximo elemento, pois apos a leitura o ponteiro ja esta no proximo elemento
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------

void ordernaAluno(FILE *alunos, int n)
{
    int i, j;
    aluno aux[2];
    rewind(alunos);
    //inicio bubble sort do arquivo
    for(i=0; i<=n; i++) //primeiro elemento
    {

        for(j=0; j<=n-1; j++) //proximo elemento
        {
            fseek(alunos, j*sizeof(aluno),SEEK_SET);//vai ate a posicao inicial do aluno 1
            fread(&aux[0],sizeof(aluno),1,alunos);//le o aluno 1
            fseek(alunos,(i+1)*sizeof(aluno),SEEK_SET);//vai ate a posicao inicial do aluno 2
            fread(&aux[1],sizeof(aluno),1,alunos);//le o aluno 2
            if(strcmp(aux[0].nUsp,aux[1].nUsp) > 0)//compara o nUsp dos dois alunos
            {
                //se o nUsp do aluno 1 for maior que do aluno 2, troca os alunos
                fseek(alunos, j*sizeof(aluno),SEEK_SET);//vai ate a posicao inicial do aluno 1
                fwrite(&aux[1],sizeof(aluno),1,alunos);//escreve o aluno 2
                fseek(alunos,(i+1)*sizeof(aluno),SEEK_SET);//vai ate a posicao inicial do aluno 2
                fwrite(&aux[0],sizeof(aluno),1,alunos);//escreve o aluno 1
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------

int cadastrarAluno(aluno *al, FILE *alunos, int n)//cadastra aluno al, e retorna quantidade de alunos cadastrados +1
{
    rewind(alunos);

    fseek(alunos, n*sizeof(aluno), SEEK_SET);//coloca o ponteiro na posicao do n-esimo aluno
    fwrite(al, sizeof(aluno), 1, alunos);//escreve todas as informacoes do aluno na i-esima posicao

    ordernaAluno(alunos, n);

    return n+1;//retorna numero de alunos cadastrados +1
}

//-------------------------------------------------------------------------------------------------------------------------------------------

void dumpAluno(FILE *alunos, int n)
{
    if(n==0) return; //se nao ha alunos cadastrados, retorna NULL

    aluno aux;
    int i;

    rewind(alunos);

    for(i=n-1; i>=0; i--)//percorre o arquivo de alunos de 0 ate n (numero de alunos cadastrados)
    {
        fseek(alunos, i*sizeof(aluno), SEEK_SET);
        fread(&aux,(sizeof(aluno)),1,alunos);//le o aluno
        printf("\%s - \%s - \%s\n",aux.nUsp,aux.nome,aux.ano); //imprime dados do aluno
        //nao eh necessario mover o ponteiro para proximo elemento, pois apos a leitura o ponteiro ja esta no proximo elemento
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------

void ordenaMatricula(FILE *matriculas, int o)
{
    int i, j;
    disciplina Daux[2];
    aluno Aaux[2];

    rewind(matriculas);
    //inicio bubble sort do arquivo (ordena por nUsp)
    for(i=0; i<=o; i++) //primeiro elemento
    {
        for(j=0; j<=o-1; j++) //proximo elemento
        {
            fseek(matriculas, j*(sizeof(Aaux[0].nUsp)+sizeof(Daux[0].codigo)),SEEK_SET);//vai ate a posicao inicial da matricula 1
            fread(&Aaux[0].nUsp,sizeof(Aaux[0].nUsp),1,matriculas);//le o nUsp da matricula 1
            fread(&Daux[0].codigo,sizeof(Daux[0].codigo),1,matriculas);//le o codigo da matricula 1
            fseek(matriculas,(i+1)*(sizeof(Aaux[1].nUsp)+sizeof(Daux[1].codigo)),SEEK_SET);//vai ate a posicao inicial da matricula 2
            fread(&Aaux[1].nUsp,sizeof(Aaux[1].nUsp),1,matriculas);//le o nUsp da matricula 2
            fread(&Daux[1].codigo,sizeof(Daux[1].codigo),1,matriculas);//le o codigo da matricula 2
            if(strcmp(Aaux[0].nUsp,Aaux[1].nUsp) > 0)//compara os nUsps das matriculas
            {
                //se o nUsp da matricula 1 for maior que o da matricla 2, troca as matriculas
                fseek(matriculas, j*(sizeof(Aaux[0].nUsp)+sizeof(Daux[0].codigo)),SEEK_SET);//vai ate a posicao inicial da matricula 1
                fwrite(&Aaux[1].nUsp,sizeof(Aaux[1].nUsp),1,matriculas);//escreve o nUsp da matricula 2
                fwrite(&Daux[1].codigo,sizeof(Daux[1].codigo),1,matriculas);//escreve o codigo da matricula 2
                fseek(matriculas,(i+1)*(sizeof(Aaux[1].nUsp)+sizeof(Daux[1].codigo)),SEEK_SET);//vai ate a posicao inicial da matricula 2
                fwrite(&Aaux[0].nUsp,sizeof(Aaux[0].nUsp),1,matriculas);//escreve o nUsp da matricula 1
                fwrite(&Daux[0].codigo,sizeof(Daux[0].codigo),1,matriculas);//escreve o codigo da matricula 2
            }
        }
    }

    //inicio do bubble sort do arquivo (ordena os codigos das disciplinas)
    for(i=0; i<=o; i++) //primeiro elemento
    {
        for(j=0; j<=o-1; j++) //proximo elemento
        {
            fseek(matriculas, j*(sizeof(Aaux[0].nUsp)+sizeof(Daux[0].codigo)),SEEK_SET);//vai ate a posicao inicial da matricula 1
            fread(&Aaux[0].nUsp,sizeof(Aaux[0].nUsp),1,matriculas);//le o nUsp da matricula 1
            fread(&Daux[0].codigo,sizeof(Daux[0].codigo),1,matriculas);//le o codigo da matricula 1
            fseek(matriculas,(i+1)*(sizeof(Aaux[1].nUsp)+sizeof(Daux[1].codigo)),SEEK_SET);//vai ate a posicao inicial da matricula 2
            fread(&Aaux[1].nUsp,sizeof(Aaux[1].nUsp),1,matriculas);//le o nUsp da matricula 2
            fread(&Daux[1].codigo,sizeof(Daux[1].codigo),1,matriculas);//le o codigo da matricula 2
            if(strcmp(Aaux[0].nUsp,Aaux[1].nUsp) == 0)//compara os nUsps das matriculas
            {
                if(strcmp(Daux[0].codigo,Daux[1].codigo) > 0)
                {
                    //se o codigo da matricula 1 for maior que o da matricula 2, troca as matriculas
                    fseek(matriculas, j*(sizeof(Aaux[0].nUsp)+sizeof(Daux[0].codigo)),SEEK_SET);//vai ate a posicao inicial da matricula 1
                    fwrite(&Aaux[1].nUsp,sizeof(Aaux[1].nUsp),1,matriculas);//escreve o nUsp da matricula 2
                    fwrite(&Daux[1].codigo,sizeof(Daux[1].codigo),1,matriculas);//escreve o codigo da matricula 2
                    fseek(matriculas,(i+1)*(sizeof(Aaux[1].nUsp)+sizeof(Daux[1].codigo)),SEEK_SET);//vai ate a posicao inicial da matricula 2
                    fwrite(&Aaux[0].nUsp,sizeof(Aaux[0].nUsp),1,matriculas);//escreve o nUsp da matricula 1
                    fwrite(&Daux[0].codigo,sizeof(Daux[0].codigo),1,matriculas);//escreve o codigo da matricula 2
                }
            }

        }
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------

int buscaAluno(aluno *al, FILE *fp, int n)
{
    int i;
    aluno aux;

    rewind(fp);

    for(i=0; i<n; i++)//percorre o arquivo de 0 ate numero de alunos matriculados (n)
    {
        fseek(fp, i*sizeof(aluno), SEEK_SET);//posiciona ponteiro para leitura do i-esimo aluno
        fread(&aux, sizeof(aluno), 1, fp);//le todos os dados do aluno
        if(strcmp(aux.nUsp,al->nUsp) == 0)//compara numero usp do aluno lido com do aluno buscado. enquanto os numeros nao forem iguais ou chegar a N alunos, continua buscas
        {
            return 1;//o aluno existe
        }
    }
    return -1; //nao existe o aluno buscado
}

//-------------------------------------------------------------------------------------------------------------------------------------------

int buscaDisciplina(disciplina *disc, FILE *fp, int n)
{
    int i;
    disciplina aux;

    rewind(fp);

    for(i=0; i<n; i++)//percorre o arquivo de 0 ate numero de disciplinas matriculadas (n)
    {
        fseek(fp, i*sizeof(disciplina), SEEK_SET);//posiciona ponteiro para leitura da i-esima disciplina
        fread(&aux, sizeof(disciplina), 1, fp);//le todos os dados da disciplina
        if(strcmp(aux.codigo,disc->codigo) == 0)//compara codigo da disciplina lida com codigo da disciplina buscada. enquanto os codigos nao forem iguais ou chegar a N disciplinas, continua buscas
        {
            return 1;//a disciplina existe
        }
    }
    return -1;//nao existe a disciplina buscada
}

//-------------------------------------------------------------------------------------------------------------------------------------------

int matricular(FILE *alunos, FILE *disciplinas, FILE *matricula, aluno *al, disciplina *disc, int n, int m, int o)
{
    if(buscaAluno(al,alunos,n)==-1) return o;//verifica se aluno 'al' existe no arquivo 'alunos' com 'n' alunos cadastrados.

    if(buscaDisciplina(disc,disciplinas,m)==-1) return o;//verifica se aluno 'al' existe no arquivo 'alunos' com 'n' alunos cadastrados

    fseek(matricula,o*(sizeof(al->nUsp)+sizeof(disc->codigo)),SEEK_SET);//posiciona ponteiro para escrita dos dados apos 'o' matriculas
    fwrite(al->nUsp, sizeof(al->nUsp),1,matricula);//escreve nUsp do aluno
    fwrite(disc->codigo,(sizeof(disc->codigo)),1,matricula);//escreve codigo da disciplina
    fseek(matricula,o*(sizeof(al->nUsp)+sizeof(disc->codigo)),SEEK_SET);//posiciona ponteiro para leitura dos dados apos 'o' matriculas
    fread(&al->nUsp, sizeof(al->nUsp),1,matricula);//le nUsp do aluno
    fread(&disc->codigo, sizeof(disc->codigo),1,matricula);//le codigo da disciplina

    ordenaMatricula(matricula, o);

    return o+1;//retorna numero de matriculas + 1
}

//-------------------------------------------------------------------------------------------------------------------------------------------

void dumpMatricula(FILE *matriculas, int o)
{
    if(o==0) return;//se nao ha matriculas feitas, retorna NULL

    char numeroUsp[8], codigoDisc[8];
    int i;

    rewind(matriculas);

    for(i=0; i<o; i++)//percorre o arquivo matriculas de 0 ate o matriculas
    {
        fread(numeroUsp,8*sizeof(char),1,matriculas);//le o numero usp da matricula
        fread(codigoDisc,8*sizeof(char),1,matriculas);//le o codigo da disciplina da matricula
        printf("\%-7s - \%-7s\n",numeroUsp,codigoDisc);//imprime os dados lidos
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------
