#include <stdio.h>
#include <stdlib.h>
#include "..\lib\conio.c"

#include "..\variaveis.h"
#include "..\funcoes.h"

main(){
    criarTela(400,310,22,18,"SELECIONAR COR",FALSE);

    while(1){
            textoDoMenu(2,2,1,cor_letra[0],WHITE);
            textoDoMenu(2,3,2,cor_letra[1],1);
            textoDoMenu(2,4,3,cor_letra[2],2);
            textoDoMenu(2,5,4,cor_letra[3],3);
            textoDoMenu(2,6,5,cor_letra[4],4);
            textoDoMenu(2,7,6,cor_letra[5],5);
            textoDoMenu(2,8,7,cor_letra[6],6);
            textoDoMenu(2,9,8,cor_letra[7],7);
            textoDoMenu(2,10,9,cor_letra[8],8);
            textoDoMenu(2,11,10,cor_letra[9],9);
            textoDoMenu(2,12,11,cor_letra[10],10);
            textoDoMenu(2,13,12,cor_letra[11],11);
            textoDoMenu(2,14,13,cor_letra[12],12);
            textoDoMenu(2,15,14,cor_letra[13],13);
            textoDoMenu(2,16,15,cor_letra[14],14);
            textoDoMenu(2,17,16,cor_letra[15],15);
            andarMenu(16);

            if (TECLA==13) break;
    }//FIM DO WHILE
    FILE *fpcor;
    int cor = OPC-1;
    fpcor = fopen("selecionarCor.dat","wb");
    fwrite(&cor,sizeof(cor),1,fpcor);
    fclose(fpcor);
    return 0;
}//FIM MAIN
