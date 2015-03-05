#ifndef _PARTIDO_H_

void deletarPartido(struct partido *partidoLista){
    struct partido *p = Lista;

    //--------------SE O PARTIDO FOR O PRIMEIRA NA LISTA----------------
    if(Lista==partidoLista){
        Lista = partidoLista->prox;
        free(partidoLista);
        return;
    }
    //--------------SE O PARTIDO FOR O ULTIMO NA LISTA----------------
    if(partidoLista->prox==NULL){
        while(p->prox!=partidoLista)
            p = p->prox;
        p->prox = NULL;
        free(partidoLista);
        return;
    }

    //--------------SE O PARTIDO ESTIVER NO MEIO DA LISTA----------------
    while(p->prox!=partidoLista)
        p = p->prox;

    p->prox = partidoLista->prox;
    free(partidoLista);

}//FIM DELETAR PARTIDO

struct partido *verificarPartidoCodigo(int cod){
    if(Lista==NULL)
        return NULL;

    struct partido *pLista = Lista;

    while(pLista!=NULL){
        if(pLista->codigo==cod)
            return pLista;
        pLista = pLista->prox;
    }
    return NULL;
}//FIM VERIFICA PARTIDO CODIGO

struct partido *buscarPartidoDeputado(struct deputado *deputadoLista){
    struct partido *p = Lista;
    struct deputado *d;
    while(p!=NULL){
            d = p->deputado;
            while(d!=NULL){//LWAS
                if(d==deputadoLista)
                    return p;
                d = d->prox;
            }
        p = p->prox;
    }
}//FIM BUSCA PARTIDO DEPUTADO

void exibirPartido(int posX, int posY, struct partido *p){

    if(p==NULL){
        texto(posX,posY,RED,"Partido n\306o encontrado");
        return;
    }

    texto(posX,posY,GREEN,"C\242digo: ");
    printf("%i",p->codigo);
    texto(posX,posY+2,GREEN,"Sigla: ");
    printf("%s",p->sigla);
    texto(posX,posY+4,GREEN,"Deputados no partido: ");
    printf("%i",quantidadeDeputado(p,0));
    texto(posX,posY+6,GREEN,"Maximo: ");
    printf("%i",p->max);
}//FIM EXIBIR PARTIDO

struct partido *confirmarPartido(struct partido *pLista){
    texto(7,8,CYAN,"CONFIRMAR PARTIDO");
    exibirPartido(7,10,pLista);
    while(1){
        textoDoMenu(7,18,1,"Confirmar",COR_MENU);
        textoDoMenu(7,20,2,"Voltar",COR_MENU);
        andarMenu(2);
        if (TECLA==13){
            if(OPC==1){limpaTela(); return pLista;}                    //CONFIRMAR
            else if(OPC==2){OPC = 1; limpaTela(); return NULL;}        //VOLTAR
        }
    }//FIM WHILE
}//FIM CONFIRMAR PARTIDO

struct partido *buscarPartidoCodigo(){
    texto(7,8,CYAN,"BUSCAR PARTIDO PELO C\340DIGO");
    texto(7,10,COR_LETRA,"Digito o c\242digo: ");
    int cod = 0;
    campoDeInt(24,10,10,COR_LETRA,BLACK,&cod);
    limpaTela();
    return verificarPartidoCodigo(cod);
}//FIM BUSCAR PARTIDO PELO CÓDIGO

struct partido *buscarPartidoSigla(){
    texto(7,8,CYAN,"BUSCAR PARTIDO PELA SIGLA");
    texto(7,10,COR_LETRA,"Digito a sigla: ");
    char sigla[10];
    campoDeString(24,10,10,COR_LETRA,BLACK,&sigla[0]);
    limpaTela();
    return verificarPartidoSigla(sigla);
}//FIM BUSCAR PARTIDO PELA SIGLA

struct partido *selecionarPartidoManualmente(){
    int quantidade = quantidadePartido();
    int pagina = 1;
    int paginas = quantidade/10;
    if(quantidade%10!=0)
        paginas++;

    while(1){
        texto(7,8,CYAN,"SELECIONAR MANUALMENTE");
        int cont = 1;
        struct partido *p = Lista;
        int auxOPC = 1;
        int auxY = 10;
        while(p!=NULL){
            int posInicial = (pagina-1)*10+1;
            int posFinal = pagina*10;
            if((cont>=posInicial)&&(cont<=posFinal)){
                textoDoMenu(7,auxY,auxOPC,p->sigla,COR_MENU);
                auxY++;
                auxOPC++;
            }
            p = p->prox;
            cont++;
        }//FIM WHILE

        textoDoMenu(7,23,auxOPC,"<<<<",COR_MENU);
        textoDoMenu(24,23,auxOPC+1,">>>>",COR_MENU);
        printf("      pagina: %i",pagina);
        andarMenu(auxOPC+1);//LWAS

        if (TECLA==13){
            if(OPC==auxOPC){OPC = 1; pagina--; if(pagina<1) pagina = paginas; limpaTela();}           //VOLTAR PAGINA
            else if(OPC==auxOPC+1){OPC = 1; pagina++; if(pagina>paginas) pagina = 1; limpaTela();} //AVANÇAR PAGINA
            else{
                struct partido *paux = Lista;
                int cont = 1;

                while(cont!=((pagina-1)*10) + OPC){
                    paux = paux->prox;
                    cont++;
                }
                OPC = 1;
                limpaTela();
                return paux;
            }
        }//FIM TECLA ENTER
    }//FIM WHILE
}//FIM SELECIONAR PARTIDO MANUALMENTE

struct partido *menuSelecionarPartido(){
    while(1){
        texto(7,8,CYAN,"SELECIONAR PARTIDO");
        textoDoMenu(7,10,1,"Buscar pelo c\242digo",COR_MENU);
        textoDoMenu(7,12,2,"Buscar pela sigla",COR_MENU);
        textoDoMenu(7,14,3,"Selecionar manualmente",COR_MENU);
        andarMenu(3);
        if (TECLA==13){
            if(OPC==1){         //BUSCAR PELO CÓDIGO
                limpaTela();
                struct partido *posPartido = confirmarPartido(buscarPartidoCodigo());
                if(posPartido!=NULL){
                    limpaTela();
                    return posPartido;
                }
            }
            else if(OPC==2){    //BUSCAR PELA SIGLA
                OPC = 1;
                limpaTela();
                struct partido *posPartido = confirmarPartido(buscarPartidoSigla());
                if(posPartido!=NULL){
                    OPC = 1;
                    limpaTela();
                    return posPartido;
                }
            }
            else if(OPC==3){
                OPC = 1;
                limpaTela();
                struct partido *posPartido = confirmarPartido(selecionarPartidoManualmente());
                if(posPartido!=NULL){
                    OPC = 1;
                    limpaTela();
                    return posPartido;
                }
            }//FIM TECLA ENTER
        }//FIM TECLA ENTER
    }//FIM WHILE
}//FIM MENU SELECIONAR PARTIDO

void cadastrarPartido(){
    struct partido partido;

    texto(7,8,CYAN,"CADASTRAR PARTIDO");
    texto(7,10,GREEN,"C\242digo:");
    texto(7,12,GREEN,"Sigla:");//LWAS
    texto(7,14,GREEN,"Quantidade maxima de deputados:");

    while(1){//INSERINDO O CÓDIGO DO PARTIDO
        campoDeInt(15,10,20,COR_LETRA,BLACK,&partido.codigo);
        if((partido.codigo>9)&&(partido.codigo<100)&&(verificarPartidoCodigo(partido.codigo)==NULL))
            break;
        texto(15,10,RED,"C\242digo invalido      ");
        _sleep(2000);
    }

    while(1){//INSERINDO A SIGLA DO PARTIDO
        campoDeString(14,12,20,COR_LETRA,BLACK,&partido.sigla[0]);
        if(verificarPartidoSigla(partido.sigla)==NULL)
            break;
        texto(14,12,RED,"Sigla invalida      ");
        _sleep(2000);
    }

    while(1){//INSERINDO A QUANTIDADE MAXIMA DE DEPUTADOS
        campoDeInt(39,14,20,COR_LETRA,BLACK,&partido.max);
        if(partido.max>0)
            break;
        texto(39,14,RED,"Quantidade invalida      ");
        _sleep(2000);
    }

    while(1){
        textoDoMenu(7,16,1,"Cadastrar",COR_MENU);
        textoDoMenu(7,18,2,"Voltar",COR_MENU);
        andarMenu(2);

        if (TECLA==13){ //AO PRESSIONAR A TECLA "ENTER"
            if(OPC==1){                                 //CADASTRAR E VOLTAR
                inserirPartido(partido);
                texto(7,20,GREEN,"Partido cadastrado com sucesso");
                _sleep(3000);
                limpaTela();
                return;
            }
            else if(OPC==2){OPC = 1; limpaTela(); return;}  //VOLTAR
        }//FIM TECLA ENTER
    }//FIM WHILE
}//FIM CADASTRAR PARTIDO

void corpoListarPartido(int posInicial, int posFinal){
    campo(7,10,80,20,BLACK," ");

    if (Lista==NULL){
       texto(7,10,RED,"Nenhum partido cadastrado");
       return;
    }

    struct partido *p = Lista;
    int auxY = 10;
    int cont = 1;
    while(p!=NULL){
        if((cont>=posInicial)&&(cont<=posFinal)){
            texto(7,auxY,COR_LETRA,"%i",p->codigo);
            texto(17,auxY,COR_LETRA,p->sigla);
            texto(28,auxY,COR_LETRA,"%i",quantidadeDeputado(p,0));
            texto(40,auxY,COR_LETRA,"%i",p->max);
            auxY++;
        }else if(cont>posFinal)
            break;
        cont++;
        p = p->prox;
    }//FIM WHILE

}//FIM CORPO LISTAR PARTIDO

void listarPartidos(){
    int quantidade = quantidadePartido();

    texto(7,8,GREEN,"C\242digo");
    texto(17,8,GREEN,"Sigla");
    texto(28,8,GREEN,"Deputados");
    texto(40,8,GREEN,"M\240ximo");
    texto(55,8,GREEN,"Partidos cadastrados: %i",quantidade);

    int pagina = 1;
    int paginas = quantidade/10;
    if(quantidade%10!=0)
        paginas++;

    while(1){
        corpoListarPartido((pagina-1)*10+1,pagina*10);
        while(1){
            textoDoMenu(7,23,1,"<<<<",COR_MENU);
            textoDoMenu(15,23,2,"Voltar",COR_MENU);
            textoDoMenu(24,23,3,">>>>",COR_MENU);
            printf("      pagina: %i",pagina);
            andarMenu(3);

            if (TECLA==13){//TECLA ENTER
                if(OPC==1){pagina--; if(pagina<1) pagina = paginas; break;}         //VOLTAR PAGINA
                else if(OPC==2){OPC = 1; limpaTela(); return;}                      //VOLTAR
                else if(OPC==3){pagina++; if(pagina>paginas) pagina = 1; break;}    //AVANÇAR PAGINA
            }
        }// FIM WHILE
    }//FIM WHILE
}//FIM LISTAR PARTIDO

void fusaoPartidaria(){

    if(quantidadePartido()<2){
        texto(7,8,RED,"Tem que ter no minimo 2 partidos para essa op\207\306o");
        textoDoMenu(7,10,1,"Voltar",COR_MENU);
        getch();
        limpaTela();
        return;
    }

    struct partido *partidoLista1 = menuSelecionarPartido();

    texto(7,8,CYAN,"FUS\266O PARTIDARIA");
    texto(7,10,COR_LETRA,"Agora selecione o outro partido");
    textoDoMenu(7,12,1,"OK",COR_MENU);
    getch();
    limpaTela();

    struct partido *partidoLista2 = menuSelecionarPartido();

    if(partidoLista1==partidoLista2){
        texto(7,8,RED,"Nem a pau Juvenal, n\306o pode escolher duas vezes o mesmo partido");
        textoDoMenu(7,10,1,"Voltar",COR_MENU);
        getch();
        limpaTela();
        return;
    }

    texto(7,8,CYAN,"FUS\266O PARTIDARIA");

    texto(7,10,GREEN,"Juntar o partido: "); printf("%s",partidoLista1->sigla);
    texto(7,12,GREEN,"Com o partido: ");    printf("%s",partidoLista2->sigla);

    while(1){
        textoDoMenu(7,14,1,"SIM",COR_MENU);
        textoDoMenu(7,16,2,"N\266O",COR_MENU);
        andarMenu(2);

        if (TECLA==13){ //AO PRESSIONAR A TECLA "ENTER"
            if(OPC==1){                                         //SIM
                limpaTela();
                int novoCodigo = 0;
                char novaSigla[10] = "\0";
                texto(7,8,CYAN,"Informa\207\344es do novo partido");
                texto(7,10,GREEN,"C\242digo:");
                texto(7,12,GREEN,"Sigla:");//LWAS
                while(1){//INSERINDO O CÓDIGO DO PARTIDO
                    campoDeInt(15,10,20,COR_LETRA,BLACK,&novoCodigo);
                    if((novoCodigo>9)&&(novoCodigo<100)&&((verificarPartidoCodigo(novoCodigo)==NULL)||(novoCodigo==partidoLista1->codigo)||(novoCodigo==partidoLista2->codigo)))
                        break;
                    texto(15,10,RED,"C\242digo invalido      ");
                    _sleep(2000);
                }

                while(1){//INSERINDO A SIGLA DO PARTIDO
                    campoDeString(14,12,20,COR_LETRA,BLACK,&novaSigla[0]);
                    if((verificarPartidoSigla(novaSigla)==NULL)||(strcmp(novaSigla,partidoLista1->sigla)==0)||(strcmp(novaSigla,partidoLista2->sigla)==0))
                        break;
                    texto(14,12,RED,"Sigla invalida      ");
                    _sleep(2000);
                }

                struct partido partido;
                partido.codigo = partidoLista1->codigo;
                strcpy(partido.sigla,partidoLista1->sigla);
                partido.deputado = partidoLista1->deputado;
                partido.max = partidoLista1->max;

                deletarPartido(partidoLista1);

                partidoLista2->codigo = novoCodigo;
                strcpy(partidoLista2->sigla,novaSigla);
                partidoLista2->max += partido.max;

                struct deputado *d = partidoLista2->deputado;

                if(d==NULL)
                    partidoLista2->deputado = partido.deputado;
                else{
                    while(d->prox!=NULL)
                        d = d->prox;

                    d->prox = partido.deputado;
                }
                texto(7,14,GREEN,"Fus\306o efetuada com sucesso");
                _sleep(3000);
                limpaTela();
                return;
            }
            else if(OPC==2){OPC = 1; limpaTela(); return;}      //NÃO
        }//FIM TECLA ENTER
    }//FIM WHILE
}//FIM FUSÃO PARTIDARIA

void menuPrincipalPartido(){
    while(1){
        texto(7,8,CYAN,"MENU PARTIDO");
        textoDoMenu(7,10,1,"Cadastrar partido",COR_MENU);
        textoDoMenu(7,12,2,"Listar partidos",COR_MENU);
        textoDoMenu(7,14,3,"Fus\306o partidaria",COR_MENU);
        textoDoMenu(7,16,4,"Voltar",COR_MENU);
        andarMenu(4);

        if (TECLA==13){ //AO PRESSIONAR A TECLA "ENTER"
            if(OPC==1){limpaTela(); cadastrarPartido();}                                //CADASTRAR PARTIDO
            else if(OPC==2){OPC = 1; limpaTela(); listarPartidos();}                    //LISTAR PARTIDOS
            else if(OPC==3){OPC = 1; limpaTela(); fusaoPartidaria();}             //FUSÃO PARTIDARIA
            else if(OPC==4){OPC = 1; limpaTela(); return;}                               //VOLTAR
        }
    }//FIM DO WHILE
}

#endif
