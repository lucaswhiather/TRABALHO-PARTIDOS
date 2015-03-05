#ifndef _OPCOES_H_

int selecionarCorManualmente(){
    system("cd funcionalidades&start selecionarCor.exe");
    FILE *fpcor;
    int cod = 1;

    while((fpcor = fopen("funcionalidades\\selecionarCor.dat","rb"))==NULL)
        _sleep(1000);
    fread(&cod,sizeof(cod),1,fpcor);
    fclose(fpcor);

    _sleep(2000);
    system("Del funcionalidades\\selecionarCor.dat");
    return cod;
}

void menuOpcoes(){
    while(1){
        texto(7,8,CYAN,"OPÇ\345ES");
        textoDoMenu(7,10,1,"Cor da letra:",WHITE);
        textoDoMenu(7,12,2,"Cor do menu:",WHITE);
        textoDoMenu(7,14,3,"Cor de sele\207\306o:",WHITE);
        textoDoMenu(7,16,4,"Voltar",WHITE);
        texto(21,10,COR_LETRA,cor_letra[COR_LETRA]);
        texto(20,12,COR_MENU,cor_letra[COR_MENU]);
        texto(23,14,COR_SELECAO,cor_letra[COR_SELECAO]);
        andarMenu(4);//LWAS

        if (TECLA==13){ //AO PRESSIONAR A TECLA "ENTER"
            if(OPC==1){COR_LETRA = selecionarCorManualmente(); limpaTela();}                //COR DA LETRA
            else if(OPC==2){COR_MENU = selecionarCorManualmente(); limpaTela();}              //COR DO MENU
            else if(OPC==3){COR_SELECAO = selecionarCorManualmente(); limpaTela();}           //COR DE SELEÇÃO
            else if(OPC==4){OPC = 1; limpaTela(); return;}   //VOLAR        }
        }
    }//FIM DO WHILE
}

#endif
