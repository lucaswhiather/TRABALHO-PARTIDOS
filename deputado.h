#ifndef _DEPUTADO_H_

int selecionarEstado(){
    system("cd funcionalidades&start selecionarEstado.exe");
    FILE *fpestado;
    int cod = 1;

    while((fpestado = fopen("funcionalidades\\selecionarEstado.dat","rb"))==NULL)
        _sleep(1000);
    fread(&cod,sizeof(cod),1,fpestado);
    fclose(fpestado);

     _sleep(2000);
     system("Del funcionalidades\\selecionarEstado.dat");
    return cod;
}//FIM SELECIONAR ESTADO

void exibirDeputado(int posX, int posY, struct deputado *deputadoLista){

    if(deputadoLista==NULL){
        texto(posX,posY,RED,"Deputado n\306o econtrado");
        return;
    }
    struct deputado *d = deputadoLista;
    struct partido *p = buscarPartidoDeputado(deputadoLista);
    char numero[20];

    sprintf(numero,"%i%i",p->codigo,deputadoLista->numero);

    texto(posX,posY,GREEN,"Numero: ");
    printf("%s",numero);
    texto(posX,posY+2,GREEN,"Nome: ");
    printf("%s",d->nome);
    texto(posX,posY+4,GREEN,"Estado: ");
    printf("%s",estados[d->estado]);
    texto(posX,posY+6,GREEN,"Partido: ");
    printf("%s",p->sigla);
}//FIM EXIBIR PARTIDO

struct deputado *buscarDeputadoNome(){
    texto(7,8,CYAN,"BUSCAR DEPUTADO PELO NOME");
    texto(7,10,COR_LETRA,"Digito o nome: ");
    char nome[30];
    campoDeString(22,10,30,COR_LETRA,BLACK,&nome[0]);
    limpaTela();
    return verificarDeputadoNome(nome);
}//FIM BUSCAR DEPUTADO NOME

struct deputado *buscarDeputadoNumero(){
    texto(7,8,CYAN,"BUSCAR DEPUTADO PELO NUMERO");
    texto(7,10,COR_LETRA,"Digito o numero: ");
    int numero = 0;
    campoDeInt(24,10,10,COR_LETRA,BLACK,&numero);
    limpaTela();
    return verificarDeputadoNumero(numero);
}//FIM BUSCAR DEPUTADO NUMERO

struct deputado *buscarDeputadoTelefone(){
    texto(7,8,CYAN,"BUSCAR DEPUTADO PELO TELEFONE");
    texto(7,10,COR_LETRA,"Digite o telefone: ");
    int telefone = 0;
    campoDeInt(24,10,10,COR_LETRA,BLACK,&telefone);
    limpaTela();
    return verificarTelefone(telefone);
}//FIM BUSCAR DEPUTADO TELEFONE

struct deputado *selecionarDeputadoManualmente(){
    int quantidade = quantidadeDeputado(NULL,0);
    int pagina = 1;
    int paginas = quantidade/10;
    if(quantidade%10!=0)
        paginas++;

    while(1){
        texto(7,8,CYAN,"SELECIONAR MANUALMENTE");
        int cont = 1;
        struct partido *p = Lista;
        struct deputado *d;
        int auxOPC = 1;
        int auxY = 10;
        while(p!=NULL){
            d = p->deputado;
            while(d!=NULL){
                int posInicial = (pagina-1)*10+1;
                int posFinal = pagina*10;
                if((cont>=posInicial)&&(cont<=posFinal)){
                    textoDoMenu(7,auxY,auxOPC,d->nome,COR_MENU);
                    auxY++;
                    auxOPC++;
                }
                d = d->prox;
                cont++;
            }//FIM WHILE
            p = p->prox;
        }//FIM WHILE

        textoDoMenu(7,23,auxOPC,"<<<<",COR_MENU);
        textoDoMenu(24,23,auxOPC+1,">>>>",COR_MENU);
        printf("      pagina: %i",pagina);
        andarMenu(auxOPC+1);//LWAS

        if (TECLA==13){
            if(OPC==auxOPC){OPC = 1; pagina--; if(pagina<1) pagina = paginas; limpaTela();}             //VOLTAR PAGINA
            else if(OPC==auxOPC+1){OPC = 1; pagina++; if(pagina>paginas) pagina = 1; limpaTela();}      //AVANÇAR PAGINA
            else{
                int cont = 1;
                p = Lista;
                while(p!=NULL){
                    d = p->deputado;
                    while(d!=NULL){
                        if(cont>=((pagina-1)*10) + OPC){
                            OPC = 1;
                            limpaTela();
                            return d;
                        }
                        d = d->prox;
                        cont++;
                    }//FIM WHILE d
                    p = p->prox;
                }//FIM WHILE p
            }//FIM ELSE
        }//FIM TECLA ENTER
    }//FIM WHILE
}//FIM SELECIONAR DEPUTADO MANUALMENTE

struct deputado *confirmarDeputado(struct deputado *deputadoLista){
    texto(7,8,CYAN,"CONFIRMAR DEPUTADO");
    exibirDeputado(7,10,deputadoLista);
    while(1){
        textoDoMenu(7,18,1,"Confirmar",COR_MENU);
        textoDoMenu(7,20,2,"Voltar",COR_MENU);
        andarMenu(2);
        if (TECLA==13){
            if(OPC==1){limpaTela(); return deputadoLista;}          //CONFIRMAR
            else if(OPC==2){OPC = 1; limpaTela(); return NULL;}     //VOLTAR
        }
    }//FIM WHILE
}//FIM CONFIRMAR DPEUTADO

struct deputado *menuSelecionarDeputado(){
    while(1){
        texto(7,8,CYAN,"SELECIONAR DEPUTADO");
        textoDoMenu(7,10,1,"Buscar pelo nome",COR_MENU);
        textoDoMenu(7,12,2,"Buscar pelo numero",COR_MENU);
        textoDoMenu(7,14,3,"Buscar pelo telefone",COR_MENU);
        textoDoMenu(7,16,4,"Selecionar manualmente",COR_MENU);
        andarMenu(4);
        if (TECLA==13){
            struct deputado *deputadoLista;
            limpaTela();
            if(OPC==1){deputadoLista = confirmarDeputado(buscarDeputadoNome());}                            //BUSCAR PELO NOME
            else if(OPC==2){OPC = 1; deputadoLista = confirmarDeputado(buscarDeputadoNumero());}            //BUSCAR PELO NUMERO
            else if(OPC==3){OPC = 1; deputadoLista = confirmarDeputado(buscarDeputadoTelefone());}          //BUSCAR PELO TELEFONE
            else if(OPC==4){OPC = 1; deputadoLista = confirmarDeputado(selecionarDeputadoManualmente());}   //SELECIONAR DEPUTADO MANUALMENTE
            if(deputadoLista!=NULL){
                OPC = 1;
                limpaTela();
                return deputadoLista;
            }
        }//FIM TECLA ENTER
    }//FIM WHILE
}//FIM MENU SELECIONAR DEPUTADO

void cadastrarDeputado(){

    struct deputado deputado;
    texto(7,8,CYAN,"CADASTRAR DEPUTADO");
    texto(7,10,GREEN,"Numero:");
    texto(7,12,GREEN,"Nome:");
    texto(7,14,GREEN,"Sigla do Estado onde elegeu:");

    while(1){
        campoDeInt(15,10,20,COR_LETRA,BLACK,&deputado.numero);
        if((verificarDeputadoNumero(deputado.numero)==0)&&(deputado.numero>0))
            break;
        texto(15,10,RED,"Numero invalido      ");
        _sleep(2000);
    }//FIM WHILE

    campoDeString(13,12,30,COR_LETRA,BLACK,&deputado.nome[0]);
    deputado.estado = selecionarEstado();
    texto(36,14,COR_LETRA,"%s",estados[deputado.estado]);

    while(1){
        textoDoMenu(7,16,1,"Confirmar",COR_MENU);
        textoDoMenu(7,18,2,"Cancelar",COR_MENU);
        andarMenu(2);

        if (TECLA==13){ //AO PRESSIONAR A TECLA "ENTER"
            if(OPC==1){limpaTela(); break;}                     //CONFIRMAR
            else if(OPC==2){OPC = 1; limpaTela(); return;}      //VOLTAR
        }
    }//FIM WHILE

    struct partido *partidoLista = menuSelecionarPartido();

    if(partidoLista==NULL){limpaTela(); OPC = 1; return;}

     while(1){
        texto(7,8,CYAN,"CADASTRAR DEPUTADO");
        texto(7,10,GREEN,"Numero:"); printf(" %i",deputado.numero);
        texto(7,12,GREEN,"Nome:"); printf(" %s",deputado.nome);
        texto(7,14,GREEN,"Sigla do Estado onde elegeu:"); printf(" %s",estados[deputado.estado]);
        texto(7,16,GREEN,"Partido:"); printf(" %s",partidoLista->sigla);

        textoDoMenu(7,18,1,"Confirmar",COR_MENU);
        textoDoMenu(7,20,2,"Cancelar",COR_MENU);
        andarMenu(2);

        if (TECLA==13){ //AO PRESSIONAR A TECLA "ENTER"
            if(OPC==1) {
                if(quantidadeDeputado(partidoLista,0)<partidoLista->max){
                    inserirDeputado(deputado, partidoLista);
                    texto(7,22,GREEN,"Deputado cadastrado com sucesso");
                }
                else{
                    texto(7,22,RED,"Deu pau, deputado n\306o foi cadastrado");
                    texto(7,24,RED,"o partido est\240 com o maximo de deputados");
                    _sleep(2000);
                }
                _sleep(3000);
                limpaTela();
                return;
            }                                   //CONFIRMAR
            else if(OPC==2) {limpaTela(); OPC = 1; return;} //VOLTAR
        }//FIM TECLA ENTER
    }//FIM WHILE
}//FIM CADASTRAR DEPUTADO

void corpoListarDeputado(int posInicial, int posFinal, struct partido *ListaPartido, int estado){
    campo(7,10,80,20,BLACK," ");
    int auxY = 10;
    int cont = 1;
    struct partido *p = ListaPartido;
    if(p==NULL)
        p = Lista;
    struct deputado *d = p->deputado;

    while(p!=NULL){
        if(ListaPartido==NULL)
            d = p->deputado;

        while(d!=NULL){
            if((estado==0)||(d->estado==estado)){
                if((cont>=posInicial)&&(cont<=posFinal)){
                    char numero[20];
                    sprintf(numero,"%i%i",p->codigo,d->numero);
                    texto(7,auxY,COR_LETRA,"%s",numero);
                    texto(17,auxY,COR_LETRA,d->nome);
                    texto(47,auxY,COR_LETRA,"%s",estados[d->estado]);
                    texto(55,auxY,COR_LETRA,"%s",p->sigla);
                    auxY++;
                }else if(cont>posFinal)
                    return;
                cont++;
            }
            d = d->prox;
        }//FIM WHILE
        p = p->prox;
    }//FIM WHILE
}//FIM CORPO LISTAR DEPUTADOS

void listarDeputados(){

    int quantidade = quantidadeDeputado(NULL,0);
    texto(7,8,GREEN,"Numero");
    texto(17,8,GREEN,"Nome");
    texto(47,8,GREEN,"Estado");
    texto(55,8,GREEN,"Partido");
    texto(65,8,GREEN,"Deputados: ");
    printf("%i",quantidade);
    int pagina = 1;
    int paginas = quantidade/10;
    if(quantidade%10!=0)
        paginas++;

    while(1){
        if(quantidade==0)
            texto(7,12,RED,"Nenhum deputado cadastrado");
        else
            corpoListarDeputado((pagina-1)*10+1,pagina*10,NULL,0);
        while(1){
            textoDoMenu(7,23,1,"<<<<",COR_MENU);
            textoDoMenu(15,23,2,"Voltar",COR_MENU);
            textoDoMenu(24,23,3,">>>>",COR_MENU);
            printf("      pagina: %i",pagina);
            andarMenu(3);

            if (TECLA==13){
                if(OPC==1){pagina--; if(pagina<1) pagina = paginas; break;}   //VOLTAR PAGINA
                if(OPC==2){limpaTela();  OPC = 1; return;}                            //VOLTAR
                if(OPC==3){pagina++; if(pagina>paginas) pagina = 1; break;}   //AVANÇAR PAGINA
            }
        }// FIM WHILE
    }//FIM WHILE
}//FIM LISTAR DEPUTADOS

void listarDeputadosPartido(){
    struct partido *partidoLista = menuSelecionarPartido();

    if(partidoLista==NULL){
        limpaTela();
        return;
    }

    int quantidade = quantidadeDeputado(partidoLista,0);

    if(quantidade==0){
        texto(7,8,RED,"Nenhum deputado encontrado desse partido");
        textoDoMenu(7,10,1,"Voltar",COR_MENU);
        getch();
        limpaTela();
        return;
    }

    int pagina = 1;
    int paginas = quantidade/10;
    if(quantidade%10!=0)
        paginas++;

    texto(7,8,GREEN,"Numero");
    texto(17,8,GREEN,"Nome");
    texto(47,8,GREEN,"Estado");
    texto(55,8,GREEN,"Partido");
    texto(67,8,GREEN,"Deputados: ");
    printf("%i",quantidade);

    while(1){
        corpoListarDeputado((pagina-1)*10,pagina*10,partidoLista,0);

        while(1){
            textoDoMenu(7,23,1,"<<<<",COR_MENU);
            textoDoMenu(15,23,2,"Voltar",COR_MENU);
            textoDoMenu(24,23,3,">>>>",COR_MENU);
            printf("      pagina: %i",pagina);
            andarMenu(3);

            if (TECLA==13){
                if(OPC==1){ pagina--; if(pagina<1) pagina = paginas; break;}   //VOLTAR PAGINA
                if(OPC==2){limpaTela(); OPC = 1; return;}                            //VOLTAR
                if(OPC==3){ pagina++; if(pagina>paginas) pagina = 1; break;}   //AVANÇAR PAGINA
            }
        }// FIM WHILE
    }//FIM WHILE
}//FIM LISTAR DEPUTADOS PARTIDO

void listarDeputadosEstado(){
    int estado = selecionarEstado();
    int quantidade = quantidadeDeputado(NULL,estado);

    if(quantidade==0){
        texto(7,8,RED,"Nenhum deputado encontrado do estado %s",estados[estado]);
        textoDoMenu(7,10,1,"Voltar",COR_MENU);
        getch();
        limpaTela();
        return;
    }

    int pagina = 1;
    int paginas = quantidade/10;
    if(quantidade%10!=0)
        paginas++;

    texto(7,8,GREEN,"Numero");
    texto(17,8,GREEN,"Nome");
    texto(47,8,GREEN,"Estado");
    texto(55,8,GREEN,"Partido");
    texto(67,8,GREEN,"Deputados: ");
    printf("%i",quantidade);

    while(1){
        corpoListarDeputado((pagina-1)*10,pagina*10,NULL,estado);

        while(1){
            textoDoMenu(7,23,1,"<<<<",COR_MENU);
            textoDoMenu(15,23,2,"Voltar",COR_MENU);
            textoDoMenu(24,23,3,">>>>",COR_MENU);
            printf("      pagina: %i",pagina);
            andarMenu(3);

            if (TECLA==13){
                if(OPC==1){ pagina--; if(pagina<1) pagina = paginas; break;}   //VOLTAR PAGINA
                if(OPC==2){limpaTela(); OPC = 1; return;}                            //VOLTAR
                if(OPC==3){ pagina++; if(pagina>paginas) pagina = 1; break;}   //AVANÇAR PAGINA
            }
        }// FIM WHILE
    }//FIM WHILE
}//FIM LISTAR DEPUTADOS ESTADO

void incluirTelefone(struct deputado *deputadoLista){
    texto(7,8,CYAN,"INCLUIR TELEFONE");
    texto(7,10,COR_LETRA,"Digito o telefone: ");
    int telefone = 0;
    while(1){
        campoDeInt(26,10,20,COR_LETRA,BLACK,&telefone);
        if((telefone>0)&&(verificarTelefone(telefone)==NULL))
            break;
            texto(26,10,RED,"Telefone invalido");
        _sleep(2000);
    }//FIM WHILE
    inserirTelefone(deputadoLista,telefone);
    texto(7,12,GREEN,"Telefone cadastrado com sucesso");
    _sleep(3000);
    limpaTela();
}//FIM INCLUIR TELEFONE

void alterarTelefone(struct deputado *deputadoLista){
    if(deputadoLista->telefone==NULL){
        texto(7,8,CYAN,"ALTERAR TELEFONE");
        texto(7,10,RED,"Nenhum telefone para esse deputado");
        textoDoMenu(7,12,1,"Voltar",COR_MENU);
        getch();//LWAS
        limpaTela();
        return;
    }

    int quantidade = quantidadeTelefone(deputadoLista->telefone);
    int pagina = 1;
    int paginas = quantidade/10;
    if(quantidade%10!=0)
        paginas++;
    struct telefone *t = deputadoLista->telefone;
    texto(7,8,CYAN,"SELECIONE O TELEFONE A SER ALTERADO");
    while(1){
        int cont = 1;
        int auxOPC = 1;
        int auxY = 10;
        int posInicial = (pagina-1)*10+1;
        int posFinal = pagina*10;
        t = deputadoLista->telefone;
        while(t!=NULL){
            if((cont>=posInicial)&&(cont<=posFinal)){
                char telefone[20] = "\0";
                sprintf(telefone,"%i",t->numero);
                textoDoMenu(7,auxY,auxOPC,telefone,COR_MENU);
                auxY++;
                auxOPC++;
            }
            t = t->prox;
            cont++;
        }//FIM WHILE

        textoDoMenu(7,23,auxOPC,"<<<<",COR_MENU);
        textoDoMenu(15,23,auxOPC+1,">>>>",COR_MENU);
        printf("      pagina: %i",pagina);
        andarMenu(auxOPC+1);

        if (TECLA==13){
            if(OPC==auxOPC){OPC = 1; pagina--; if(pagina<1) pagina = paginas; limpaTela();}             //VOLTAR PAGINA
            else if(OPC==auxOPC+1){OPC = 1; pagina++; if(pagina>paginas) pagina = 1; limpaTela();}      //AVANÇAR PAGINA
            else{
                struct telefone *taux = deputadoLista->telefone;
                int cont = 1;

                while(cont!=((pagina-1)*10) + OPC){
                    taux = taux->prox;
                    cont++;
                }
                OPC = 1;
                limpaTela();

                texto(7,10,COR_LETRA,"Digito o novo telefone: ");
                int telefone = 0;
                while(1){
                    campoDeInt(31,10,20,COR_LETRA,BLACK,&telefone);
                    if((telefone>0)&&(verificarTelefone(telefone)==NULL))
                        break;
                    texto(26,10,RED,"Telefone invalido");
                    _sleep(2000);
                }//FIM WHILE
                taux->numero = telefone;
                texto(7,12,GREEN,"Telefone alterado com sucesso");
                _sleep(3000);
                limpaTela();
                return;
            }
        }//FIM TECLA ENTER
    }//FIM WHILE
}//FIM ALTERAR TELEFONE

void alterarIncluirTelefone(){

    if(quantidadeDeputado(NULL,0)==0){
        texto(7,10,RED,"Nenhum deputado cadastrado");
        textoDoMenu(7,12,1,"Voltar",COR_MENU);
        getch();
        limpaTela();
        return;
    }

    struct deputado *deputadoLista = menuSelecionarDeputado();

    while(1){
        texto(7,8,CYAN,"ALTERAR INCLUIR TELEFONE");
        exibirDeputado(7,10,deputadoLista);
        textoDoMenu(7,18,1,"Incluir",COR_MENU);
        textoDoMenu(7,20,2,"Alterar",COR_MENU);
        textoDoMenu(7,22,3,"Voltar",COR_MENU);
        andarMenu(3);
        if (TECLA==13){ //AO PRESSIONAR A TECLA "ENTER"
            if(OPC==1){limpaTela(); incluirTelefone(deputadoLista);}                       //INCLUIR
            else if(OPC==2){OPC = 1; limpaTela(); alterarTelefone(deputadoLista);}           //ALTERAR
            else if(OPC==3){OPC = 1; limpaTela(); return;}   	    		   	//VOLTAR
        }//FIM TECLA ENTER
    }//FIM WHILE
}//FIM ALTERAR TELEFONE

void exibirTelefone(int posInicial, int posFinal, struct deputado *deputadoLista){
    struct telefone *t = deputadoLista->telefone;

    texto(7,17,CYAN,"TELEFONES");

    if(t==NULL){
        texto(7,18,RED,"Nenhum telefone cadastrado");
        return;
    }
    campo(7,18,80,23,BLACK," ");
    int auxY = 18;
    int cont = 1;
    while(t!=NULL){
        if((cont>=posInicial)&&(cont<=posFinal)){
            texto(7,auxY,COR_LETRA,"%i",t->numero);
            auxY++;
        }else if(cont>posFinal)
            break;
        cont++;
        t = t->prox;
    }//FIM WHILE

}//FIM EXIBIR TELEFONE

void consultarDeputado(){
    texto(7,8,CYAN,"CONSULTAR DEPUTADO");
    if(quantidadeDeputado(NULL,0)==0){
        texto(7,10,RED,"Nenhum deputado cadastrado");
        textoDoMenu(7,12,1,"Voltar",COR_MENU);
        getch();
        limpaTela();
        return;
    }

    struct deputado *deputadoLista = menuSelecionarDeputado();

    exibirDeputado(7,10,deputadoLista);

    int quantidade = quantidadeTelefone(deputadoLista->telefone);
    int pagina = 1;
    int paginas = quantidade/5;
    if(quantidade%5!=0)
        paginas++;
    texto(7,8,CYAN,"CONSULTAR DEPUTADO");
    while(1){
        exibirTelefone((pagina-1)*5+1, pagina*5,deputadoLista);
        while(1){
            textoDoMenu(7,24,1,"<<<<",COR_MENU);
            textoDoMenu(14,24,2,"Voltar",COR_MENU);
            textoDoMenu(24,24,3,">>>>",COR_MENU);
            andarMenu(3);
            if (TECLA==13){ //AO PRESSIONAR A TECLA "ENTER"
                if(OPC==1){pagina--; if(pagina<1) pagina = paginas; break;}         //VOLTAR PAGINA
                else if(OPC==2){OPC = 1; limpaTela(); return;}   	    		   	//VOLTAR
                else if(OPC==3){pagina++; if(pagina>paginas) pagina = 1; break;}    //AVANÇAR PAGINA
            }//FIM TECLA ENTER
        }//FIM WHILE
    }//FIM WHILW
}//FIM CONSULTAR DEPUTADO

void deletarDeputado(struct deputado *deputadoLista, int telefone){


    //--------------DELETANDO OS TELEFONES----------------
    if(telefone==1){
        if(deputadoLista->telefone!=NULL)
            while(quantidadeTelefone(deputadoLista->telefone)!=0)
                removerTelefoneFim(deputadoLista);
    }
    //-----------------------------------------------------

     struct partido *p = buscarPartidoDeputado(deputadoLista);

    //--------------SE O DEPUTADO FOR O PRIMEIRA NA LISTA----------------
    if(p->deputado==deputadoLista){
        p->deputado = deputadoLista->prox;
        free(deputadoLista);
        return;
    }
    //--------------SE O DEPUTADO FOR O ULTIMO NA LISTA----------------
    if(deputadoLista->prox==NULL){
        struct deputado *d = p->deputado;
        while(d->prox!=deputadoLista)
            d = d->prox;
        d->prox = NULL;
        free(deputadoLista);
        return;
    }

    //--------------SE O DEPUTADO ESTIVER NO MEIO DA LISTA----------------
    struct deputado *d =  p->deputado;
    while(d->prox!=deputadoLista)
        d = d->prox;

    d->prox = deputadoLista->prox;
    free(deputadoLista);

}//FIM DELETAR DEPUTADO

void cassarDeputado(){

    if(quantidadeDeputado(NULL,0)==0){
        texto(7,10,RED,"Nenhum deputado cadastrado");
        textoDoMenu(7,12,1,"Voltar",COR_MENU);
        getch();
        limpaTela();
        return;
    }

    struct deputado *deputadoLista = menuSelecionarDeputado();
    exibirDeputado(7,10,deputadoLista);

    while(1){
        texto(7,18,CYAN,"Cassar deputado ?");
        textoDoMenu(7,20,1,"SIM",COR_MENU);
        textoDoMenu(13,20,2,"NAO",COR_MENU);
        andarMenu(2);//LWAS
        if (TECLA==13){ //AO PRESSIONAR A TECLA "ENTER"
            if(OPC==1){
                deletarDeputado(deputadoLista,1);
                texto(7,22,GREEN,"Deputado cassado com sucesso");
                _sleep(2000);
                limpaTela();
                return;
            }            //SIM
            else if(OPC==2){OPC = 1; limpaTela(); return;}   	    		   	//NÃO
        }//FIM TECLA ENTER
    }//FIM WHILE
}//FIM CASSAR DEPUTADO

void menuListarDeputados(){
   while(1){
        texto(7,8,CYAN,"MENU LISTAR DEPUTADOS");
        textoDoMenu(7,10,1,"Listar todos deputados",COR_MENU);
        textoDoMenu(7,12,2,"Listas deputados por partido",COR_MENU);
        textoDoMenu(7,14,3,"Listas deputados por Estado",COR_MENU);
        textoDoMenu(7,16,4,"Voltar",COR_MENU);
        andarMenu(4);

        if (TECLA==13){ //AO PRESSIONAR A TECLA "ENTER"
            if(OPC==1){limpaTela(); listarDeputados();}                          //LISTAR TODOS DEPUTADOS
            else if(OPC==2){OPC = 1; limpaTela(); listarDeputadosPartido();}     //LISTAR DEPUTADOS POR PARTIDO
			else if(OPC==3){OPC = 1; limpaTela(); listarDeputadosEstado();}   	 //LISTAR DEPUTADOS POR ESTADO
            else if(OPC==4){OPC = 1; limpaTela(); return;}   	    		   	 //VOLTAR
        }//FIM TECLA ENTER
    }//FIM DO WHILE
}//FIM MENU LISTAR DEPUTADOS

void trocarPartido(){
    texto(7,8,CYAN,"TROCAR PARTIDO");

    struct deputado *deputadoLista = menuSelecionarDeputado();

    texto(7,10,COR_LETRA,"Agora selecione um novo partido para o deputado");
    textoDoMenu(7,12,1,"OK",COR_MENU);
    getch();
    limpaTela();

    struct partido *partidoLista = menuSelecionarPartido();

    if(partidoLista==buscarPartidoDeputado(deputadoLista)){
        texto(7,10,RED,"Voce n\306o pode mudar o partido do deputado para o mesmo que ele esta");
        textoDoMenu(7,12,1,"Voltar",COR_MENU);
        getch();
        limpaTela();
        return;
    }

    texto(7,10,GREEN,"Trocar o partido do deputado: "); printf("%s",deputadoLista->nome);
    texto(7,12,GREEN,"Do partido: "); printf("%s",buscarPartidoDeputado(deputadoLista)->sigla);
    texto(7,14,GREEN,"Para o partido: ");printf("%s",partidoLista->sigla);

    while(1){
        textoDoMenu(7,16,1,"SIM",COR_MENU);
        textoDoMenu(7,18,2,"N\266O",COR_MENU);
        andarMenu(2);
        if(TECLA==13){
            if(OPC==1){
                struct deputado deputado;
                struct telefone *taux = deputadoLista->telefone;
                deputado.numero = deputadoLista->numero;
                strcpy(deputado.nome,deputadoLista->nome);
                deputado.estado = deputadoLista->estado;

                if(quantidadeDeputado(partidoLista,0)<partidoLista->max){
                    deletarDeputado(deputadoLista,0);
                    inserirDeputado(deputado,partidoLista);
                    verificarDeputadoNumero(deputado.numero)->telefone = taux;
                    texto(7,20,GREEN,"Troca de partido foi feita com sucesso");
                }
                else{
                    texto(7,20,RED,"Deu pau, nada foi alterado");
                    texto(7,22,RED,"o partido est\240 com o maximo de deputados");
                    _sleep(2000);
                }
                _sleep(3000);
                limpaTela();
                return;
            }
            else if(OPC==2){OPC = 1; limpaTela(); return;}  //VOLTA
        }//FIM TECLA ENTER
    }//FIM WHILE
}//FIM TROCAR PARTIDO

void menuPrincipalDeputado(){
    if(Lista==NULL){
        texto(7,8,CYAN,"MENU PARTIDO");
        texto(7,10,RED,"Esse menu estara desativado enquanto nenhum partido estiver cadastrado");
        textoDoMenu(7,12,1,"Voltar",COR_MENU);
        getch();
        limpaTela();
        return;
    }

    while(1){
        texto(7,8,CYAN,"MENU PARTIDO");
        textoDoMenu(7,10,1,"Cadastrar deputado",COR_MENU);
        textoDoMenu(7,12,2,"Listar deputados",COR_MENU);
        textoDoMenu(7,14,3,"Alterar/incluir telefone",COR_MENU);
        textoDoMenu(7,16,4,"Consultar deputado",COR_MENU);
        textoDoMenu(7,18,5,"Cassar deputado",COR_MENU);
        textoDoMenu(7,20,6,"Trocar partido",COR_MENU);
        textoDoMenu(7,22,7,"Voltar",COR_MENU);
        andarMenu(7);

        if (TECLA==13){ //AO PRESSIONAR A TECLA "ENTER"
            if(OPC==1){limpaTela(); cadastrarDeputado();}                       //CADASTRAR DEPUTADO
            else if(OPC==2){OPC = 1; limpaTela(); menuListarDeputados();}           //LISTAR DEPUTADOS
			else if(OPC==3){OPC = 1; limpaTela(); alterarIncluirTelefone();}   	//ALTERAR TELEFONE
			else if(OPC==4){OPC = 1; limpaTela(); consultarDeputado();}			//CONSULTAR DEPUTADO
			else if(OPC==5){OPC = 1; limpaTela(); cassarDeputado();}			//CASSAR DEPUTADO
            else if(OPC==6){OPC = 1; limpaTela(); trocarPartido();}             //TROCAR PARTIDO
            else if(OPC==7){OPC = 1; limpaTela(); return;}   	    		   	//VOLTAR
        }//FIM TECLA ENTER
    }//FIM DO WHILE
}//FIM MENU PRINCIPAL DEPUTADO
#endif
