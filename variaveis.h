#ifndef _VARIAVEIA_H_
//--------------------VARIAVEIS GLOBAIS-----------------------
int OPC = 1;
int TECLA;
int COR_LETRA = 7;
int COR_SELECAO = RED;
int COR_FUNDO = BLACK;
int COR_MENU = WHITE;

struct telefone{
    int numero;
    struct telefone *prox;
};

struct deputado{
    int numero;
    char nome[30];
    int estado;
    struct deputado *prox;
    struct telefone *telefone;
};

struct partido{
    int codigo;
    char sigla[10];
    int max;
    struct deputado *deputado;
    struct partido *prox;
};

struct partido *Lista = NULL;

int tamanhoProgramaX = 80;
int tamanhoProgramaY = 25;

char estados[28][30] = {
        "AA", //0
        "AC", //1
        "AL", //2
        "AP", //3
        "AM", //4
        "BA", //5
        "CE", //6
        "DF", //7
        "ES", //8
        "GO", //9
        "MA", //10
        "MT", //11
        "MS", //12
        "MG", //13
        "PA", //14
        "PB", //15
        "PR", //16
        "PE", //17
        "PI", //18
        "RJ", //19
        "RN", //20
        "RS", //21
        "RO", //22
        "RR", //23
        "SC", //24
        "SP", //25
        "SE", //26
        "TO", //27
};

char cor_letra[16][20] = {
        "PRETO",                //0
        "AZUL",                 //1
        "VERDE",                //2
        "VERDE-\265GUA",        //3
        "VERMELHO",             //4
        "ROXO",                 //5
        "AMARELO",              //6
        "BRANCO",               //7
        "CINZA",                //8
        "AZUL CLARO",           //9
        "VERDE CLARO",          //10
        "VERDE-\265GUA CLARO",  //11
        "VERMELHO CLARO",       //12
        "LIL\265S",             //13
        "AMARELO CLARO",        //14
        "BRANCO BRILHANTE"      //15
};

#endif
