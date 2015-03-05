#ifndef _FUNCOES_H_

//FUNÇÃO PARA MOVER A TELA
HWND WINAPI GetConsoleWindowNT(){
    typedef HWND WINAPI (*GetConsoleWindowT)(void);
    GetConsoleWindowT GetConsoleWindow;
    HMODULE hK32Lib = GetModuleHandle(TEXT("KERNEL32.DLL"));
    GetConsoleWindow = (GetConsoleWindowT)GetProcAddress(hK32Lib,TEXT("GetConsoleWindow"));
    if ( GetConsoleWindow == NULL ) {
         return NULL;
    }
    return GetConsoleWindow();
}

void criarTela(int posX, int posY, int larg, int alt, char titulo[],bool tipo){
    char title[50] = {"title "};
    strcat(title,titulo);
    system(title);
    _setcursortype(_NOCURSOR); // DESABILITA O CURSOR

    if(tipo==TRUE){
        CONSOLE_SCREEN_BUFFER_INFO SBInfo;
        HWND hWnd = GetConsoleWindowNT();
        MoveWindow(hWnd,posX,posY,1,1,TRUE);
    }
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT sr;
    COORD consoleSize;

    consoleSize.X = larg; consoleSize.Y = alt;

    sr.Top=sr.Left=0;
    sr.Right=larg-1;
    sr.Bottom=alt-1;

    SetConsoleWindowInfo(console, TRUE, &sr);
    SetConsoleScreenBufferSize(console, consoleSize);
    SetConsoleWindowInfo(console, TRUE, &sr);
    SetConsoleScreenBufferSize(console, consoleSize);

}

void campo(int inicioX, int inicioY, int fimX, int fimY, int cor, char texto[]){
    int x,y;
    textcolor(cor);
    for(y = inicioY; y<=fimY; y++){
        gotoxy(inicioX,y);//POSICIONA O CURSOR
        for(x = inicioX; x<=fimX; x++)
            printf("%s",texto);
    }
    textcolor(COR_LETRA);
}

void limpaTela(){
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
}

void campoDeString(int posX, int posY, int tamanho, int cor_letra,int cor_campo, char *string){
    gotoxy(posX, posY);
    _setcursortype(_NORMALCURSOR); //HABILITA O CURSOR
    textcolor(cor_letra);
    textbackground(cor_campo);

    campo(posX, posY, posX+tamanho, posY, cor_campo," ");
    gotoxy(posX, posY);
    for(int x = 1; x<=tamanho; x++)
        printf(" ");

    gotoxy(posX, posY);
    fflush(stdin);
    scanf("%30[^\n]",string);

    textcolor(COR_LETRA);
    textbackground(COR_FUNDO);
    _setcursortype(_NOCURSOR); // DESABILITA O CURSOR
}
//------------------------------------------------------------------------
int campoDeInt(int posX, int posY, int tamanho, int cor_letra, int cor_campo, int *inteiro){
    gotoxy(posX, posY);
    _setcursortype(_NORMALCURSOR); //HABILITA O CURSOR
    textcolor(cor_letra);
    textbackground(cor_campo);

    campo(posX, posY, posX+tamanho, posY, cor_campo," ");
    gotoxy(posX, posY);
    for(int x = 1; x<=tamanho; x++)
        printf(" ");

    gotoxy(posX, posY);
    fflush(stdin);
    scanf("%i",inteiro);

    textcolor(COR_LETRA);
    textbackground(COR_FUNDO);
    _setcursortype(_NOCURSOR); // DESABILITA O CURSOR
    return *inteiro;
}

void texto(int x, int y, int cor,const char *format, ...){ //CRIA UM TEXTO NAS COORDENADAS PASSADA POR PARAMETRO
    char buffer[1024] = { 0 };
    gotoxy(x,y); //posiciona o cursor
    textcolor(cor);
    va_list p;
    va_start(p, format);
    vsprintf(buffer, format, p);
    cputs(buffer);
    textcolor(COR_LETRA);
}

void texto(int cor,char texto[]){ //CRIA UM TEXTO
    textcolor(cor);;
    printf("%s",texto);
    textcolor(COR_LETRA);
}
//------------------------------------------------------------------------
void textoDoMenu(int x, int y, int opc, char textoA[],int cor){
    if(opc == OPC) textbackground(COR_SELECAO);
    texto(x,y,cor,textoA);
    textbackground(COR_FUNDO);
}
//FUNÇÃO QUE DETECTA SE A TECLA APERTADA É UMA SETA
//E MUDA A VARIAVEL "OPC"
void andarMenu(int tamanho_menu){
    fflush(stdin); //limpa o buffer do teclado
    TECLA = getch();

    if(TECLA==80) OPC++;        //BAIXO
    else if(TECLA==72) OPC--;   //CIMA
    else if(TECLA==75) OPC--;   //ESQUERDA
    else if(TECLA==77) OPC++;   //DIREITA

    if(OPC<1) OPC = tamanho_menu;
    if(OPC>tamanho_menu) OPC = 1;
}
//-------------================FUNÇÕES DA LISTA================-------------
int quantidadePartido(){
    struct partido *p = Lista;
    int cont = 0;
    while(p!=NULL){
          cont++;
          p = p->prox;
      }
    return cont;
}//FIM QUANTIDADE PARTIDO

int quantidadeDeputado(struct partido *partidoLista, int estado){
    struct deputado *d;
    struct partido *p = partidoLista;

    int cont = 0;
    if(p==NULL){
        p = Lista;
        while(p!=NULL){
            d = p->deputado;
            while(d!=NULL){
                if(estado==0)
                    cont++;
                else if(d->estado==estado)
                    cont++;
                d = d->prox;
            }
            p = p->prox;
        }
        return cont;
    }

    d = p->deputado;

    while(d!=NULL){
        cont++;
        d = d->prox;
    }
    return cont;
}//FIM QUANTIDADE DEPUTADO

int quantidadeTelefone(struct telefone *telefoneLista){
    struct telefone *t = telefoneLista;
    int cont = 0;
    while(t!=NULL){
        cont++;
        t = t->prox;
    }
    return cont;
}//FIM QUANTIDADE TELEFONE

struct deputado *verificarTelefone(int numero){
    struct partido *p = Lista;
    struct deputado *d;
    struct telefone *t;

    while(p!=NULL){
        d = p->deputado;
        while(d!=NULL){
            t = d->telefone;
            while(t!=NULL){
                if(t->numero==numero)
                    return d;
                t = t->prox;
            }//FIM WHILE t
            d = d->prox;
        }//FIM WHILE d
        p = p->prox;
    }//FIM WHILE p
    return NULL;
}//FIM VERIFICAR TELEFONE

void inserirPartido(struct partido partido){
    struct partido *n,*p;

    n = (struct partido *)malloc(sizeof(struct partido));
    n->codigo = partido.codigo;
    strcpy(n->sigla,partido.sigla);
    n->max = partido.max;
    n->prox = NULL;
    n->deputado = NULL;

    if (Lista==NULL) //Lista Vazia
        Lista = n;
    else{
        p = Lista;
        while(p->prox!=NULL)//posiciona p no ultimo no
            p = p->prox;
        p->prox = n;  //Faz o encadeamento
    }
}//FIM INSERIR PARTIDO

void inserirDeputado(struct deputado deputado,struct partido *partido){

    struct deputado *d = partido->deputado;
    struct deputado *n = (struct deputado *)malloc(sizeof(struct deputado));

    n->numero = deputado.numero;
    strcpy(n->nome,deputado.nome);
    n->estado = deputado.estado;
    n->telefone = NULL;
    n->prox = NULL;

    if(d==NULL){
        partido->deputado = n;
        return;
    }

    while(d->prox!=NULL)
        d = d->prox;

    d->prox = n;

}//FIM INSERIR DEPUTADO

void inserirTelefone(struct deputado *deputadoLista,int telefone){
    struct telefone *t =deputadoLista->telefone;
    struct telefone *n = (struct telefone *)malloc(sizeof(struct telefone));

    n->numero = telefone;
    n->prox = NULL;

    if(t==NULL){
        deputadoLista->telefone = n;
        return;
    }

    while(t->prox!=NULL)
        t = t->prox;

    t->prox = n;
}//FIM INSERIR TELEFONE

void removerTelefoneFim(struct deputado *deputadoLista){
    struct telefone *t = deputadoLista->telefone;

    if(t==NULL)
        return;

    if (t->prox==NULL){
      free(t);
      deputadoLista->telefone = NULL;
      return;
    }

    while(t->prox->prox!=NULL)
        t = t->prox;
    free(t->prox);

    t->prox = NULL;
}//FIM REMOVER TELEFONE FIM

struct partido *verificarPartidoSigla(char sigla[]){
    if(Lista==NULL)
        return NULL;

    struct partido *pLista = Lista;
    int cont = 1;

    while(pLista!=NULL){
        if(strcmp(pLista->sigla,sigla)==0)
            return pLista;
        pLista = pLista->prox;
        cont++;
    }
    return NULL;
}//FIM VERIFICA PARTIDO SIGLA

struct deputado *verificarDeputadoNome(char nome[]){
    struct partido *p = Lista;
    struct deputado *d;

    while(p!=NULL){
        d = p->deputado;
        while(d!=NULL){//LWAS
            if(strcmp(nome,d->nome)==0)
                return d;
            d = d->prox;
        }
        p = p->prox;
    }
    return NULL;
}//FIM VERIFICAR DEPUTADO NOME

struct deputado *verificarDeputadoNumero(int numero){

    struct partido *p = Lista;
    struct deputado *d;

    while(p!=NULL){
        d = p->deputado;
        while(d!=NULL){
            if(d->numero==numero)
                return d;
            d = d->prox;
        }
        p = p->prox;
    }
    return NULL;
}//FIM VERIFICAR DEPUTADO NUMERO

void carregar(){
    FILE *fptr;
    if((fptr = fopen("Partido.csv","r"))==NULL){
        texto(2,2,RED,"O ARQUVIO Partido.csv nao foi encontrado");
        _sleep(3000);
        system("cls");
        return;
    }

    while(getc(fptr)!='\n'){}// le uma linha inteira
    while(getc(fptr)!='\n'){}

    while(1){// CARREGANDO OS PARTIDOS
        struct partido partido;

        //-------------Lendo código-------------
        char codigo[2] = "\0";
        fscanf(fptr,"%[^;]",&codigo);
        getc(fptr);

        if(strcmp(codigo,":")==0)
            break;
        partido.codigo = atoi(codigo);
        printf("Codigo = %i",partido.codigo);

        //-------------Lendo sigla-------------
        char sigla[10] = "\0";
        fscanf(fptr,"%[^;]",&sigla);
        getc(fptr);
        strcpy(partido.sigla,sigla);
        printf("      Sigla = %s",partido.sigla);

        //-------------Lendo maximo-------------
        char max[10] = "\0";
        fscanf(fptr,"%[^\n]",&max);
        getc(fptr);
        partido.max = atoi(max);
        printf("   max = %i\n",partido.max);
        inserirPartido(partido);

    }//FIM WHILE QUE CARREGA OS PARTIDOS

    while(getc(fptr)!='\n'){}//le linha deputatos
    while(getc(fptr)!='\n'){}//le a linha Numero;Nome;Partido;Estado
    while(getc(fptr)!='\n'){}//le a linha Numero;Nome;Partido;Estado

    printf("\n\nDeputados\n");

    while(1){// CARREGANDO OS DEPUTADOS
        struct deputado deputado;

        //-------------Lendo numero-------------
        char numero[10] = "\0";
        fscanf(fptr,"%[^;]",&numero);
        getc(fptr);
        if(strcmp(numero,":")==0)
            break;

        deputado.numero = atoi(numero);
        printf("\nNumero = %i",deputado.numero);

        //---------------Lendo nome------------
        char nome[30] = "\0";
        fscanf(fptr,"%[^;]",&nome);
        getc(fptr);
        strcpy(deputado.nome,nome);
        printf("  Nome = %s",deputado.nome);

        //---------------Lendo Estado------------
        char estado[3] = "\0";
        fscanf(fptr,"%[^;]",&estado);
        getc(fptr);
        estado[2] = '\0';

        for(int i = 0; i<28; i++)
            if(strcmp(estado,estados[i])==0){
                deputado.estado = i;
                break;
        }
        printf(" Estado = %s",estados[deputado.estado]);

        //---------------Lendo Partido------------
        char sigla[10] = "\0";
        fscanf(fptr,"%[^;]",&sigla);
        getc(fptr);
        printf(" Partido = %s",sigla);

        struct partido *auxPartido = verificarPartidoSigla(sigla);

        if(auxPartido!=NULL){
            inserirDeputado(deputado,auxPartido);
        }
        else{
            while(getc(fptr)!='\n'){}
            break;
        }
        struct deputado *auxDeputado = verificarDeputadoNome(deputado.nome);

        //---------------Lendo Telefone------------
        while(1){
            char telefone[20] = "\0";
            fscanf(fptr,"%[^;]",&telefone);
            getc(fptr);
            if(strcmp(telefone,"+")==0){
                while(getc(fptr)!='\n'){}
                break;
            }
            else{
                printf("\nTelefone = %i",atoi(telefone));
                inserirTelefone(auxDeputado,atoi(telefone));
            }
        }//FIM WHILE CARREGA TELEFONES
    }//FIM WHILE QUE CARREGA OS DEPUTADOS

    fclose(fptr);
    texto(GREEN,"\n\nOS DADOS FORAM CARREGADOS COM SUCESSO");
    _sleep(3000);
    system("cls");
}//FIM CARREGAR

void salvar(){

    FILE *fptr;
    fptr = fopen("Partido.csv","w");
    fputs("Partidos\n",fptr);
    fputs("Codigo;Sigla;Maximo\n",fptr);

    if(Lista==NULL){
        fclose(fptr);
        return;
    }

    struct partido *p = Lista;

    while(p!=NULL){
        char linha[100] = "\0";
        sprintf(linha,"%i;%s;%i;\n",p->codigo,p->sigla,p->max);
        fputs(linha,fptr);
        p = p->prox;
    }
    fputs(":;\n",fptr);
    fputs("Deputados\n",fptr);
    fputs("Numero;Nome;Estado;Partido\n",fptr);

    p = Lista;
    struct deputado *d;
    struct telefone *t;

    while(p!=NULL){
        d = p->deputado;
        while(d!=NULL){
            char linha[200] = "\0";
            sprintf(linha,"%i;%s;%s;%s;",d->numero,d->nome,estados[d->estado],p->sigla);
            fputs(linha,fptr);
            t = d->telefone;
            while(t!=NULL){
                char numero[20] = "\0";
                sprintf(numero,"%i;",t->numero);
                fputs(numero,fptr);
                t = t->prox;
            }//FIM WHILE t
            fputs("+;\n",fptr);
            d = d->prox;
        }//FIM WHILE d
        p = p->prox;
    }//FIM WHILE p
    fputs(":;\n",fptr);
    fclose(fptr);
    texto(7,8,GREEN,"OS DADOS FORAM SALVO COM SUCESSO");
    _sleep(3000);
    limpaTela();

}//FIM SALVAR

#endif
