/*
TRABALHO DE ESTRUTURA DE DADOS

Nome: EDUADOR LIMA BELMONTE PEREIRA
Nome: LUCAS WHIATHER ABRÃO DE SOUZA
Periodo: VESPERTINO9

DANÇA DOS DEPUTADOS
Versão: 1.61
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/conio.c"

#include "variaveis.h"
#include "funcoes.h"

#include "partido.h"
#include "deputado.h"
#include "opcoes.h"

int main(){
    carregar();
    criarTela(200,200,tamanhoProgramaX,tamanhoProgramaY,"DANÇA DOS PARTIDOS",TRUE);

    campo(1,5,tamanhoProgramaX,6,WHITE,"\333");
    campo(4,1,4,tamanhoProgramaY,7,"\333");

    texto(7,2,RED,"DAN\200A DOS PARTIDOS 1.61");
    texto(50,2,GREEN,"Eduardo Lima Belmonte Pereira");
    texto(50,3,GREEN,"Lucas Whiather Abr\306o de Souza");

    while(1){
        texto(7,8,CYAN,"MENU PRINCIPAL");
        textoDoMenu(7,10,1,"Menu partido",COR_MENU);
        textoDoMenu(7,12,2,"Menu deputado",COR_MENU);
        textoDoMenu(7,14,3,"Salvar",COR_MENU);
        textoDoMenu(7,16,4,"Op\207\344es",COR_MENU);
        textoDoMenu(7,18,5,"Sair",COR_MENU);
        andarMenu(5);

        if(TECLA==13){ //AO PRESSIONAR A TECLA "ENTER"
            if(OPC==1){limpaTela(); menuPrincipalPartido();}                    //MENU PARTIDO
            else if(OPC==2){OPC = 1; limpaTela(); menuPrincipalDeputado();}     //MENU DEPUTADO
            else if(OPC==3){OPC = 1; limpaTela(); salvar();}                    //SALVAR
            else if(OPC==4){OPC = 1; limpaTela(); menuOpcoes();}                //MENU OPÇÕES
            else if(OPC==5) return 0;                                           //SAIR
        }
    }//FIM WHILE
}
