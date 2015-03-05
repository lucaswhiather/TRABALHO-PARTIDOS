#include <stdio.h>
#include <stdlib.h>
#include "..\lib\conio.c"

#include "..\variaveis.h"
#include "..\funcoes.h"

main(){
    criarTela(500,300,14,18,"ESTADO",TRUE);
    int estado = 0;
    while(1){
        for(int i = 1; i<15; i++)
            textoDoMenu(2,1+i,i,estados[i],WHITE);
        for(int i = 15; i<=27; i++)
            textoDoMenu(6,i-13,i,estados[i],WHITE);

            andarMenu(27);
            if (TECLA==13) {estado = OPC; break;}
    }//FIM DO WHILE A
    FILE *fpestado;

    fpestado = fopen("selecionarEstado.dat","wb");
    fwrite(&estado,sizeof(estado),1,fpestado);
    fclose(fpestado);
    return 0;
}//FIM MAIN
