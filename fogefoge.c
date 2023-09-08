#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fogefoge.h"
#include "mapa.h"
#include "ui.h"


MAPA m;
POSICAO heroi;
int tempilula = 0;

int praOndeFantasmaVai(int xatual, int yatual, int* xdestino, int* ydestino){

    int opcoes[4][2] = {
        {xatual, yatual + 1},
        {xatual + 1, yatual},
        {xatual, yatual - 1},
        {xatual - 1, yatual}
    };

    srand(time(0));
    for(int i = 0; i < 10; i++){
        int posicao = rand() % 4;

        if(podeAndar(&m, FANTASMA, opcoes[posicao][0], opcoes[posicao][1])) {
            *xdestino = opcoes[posicao][0];
            *ydestino = opcoes[posicao][1];

            return 1;
        }
    }
    return 0;

}

void fantasmas(){

    MAPA copia;

    copiaMapa(&copia, &m);

    for(int i = 0; i < m.linhas; i++){
        for(int j = 0; j < m.colunas; j++){

            if(copia.matriz[i][j] == FANTASMA) {

                int xdestino, ydestino;
                int encontrou = praOndeFantasmaVai(i, j, &xdestino, &ydestino);

                if(encontrou) {
                    andaNoMapa(&m, i, j, xdestino, ydestino);
                }
            }

        }
    }
    liberaMapa(&copia);
}


int acabou() {
    POSICAO pos;

    int perdeu = !encontraMapa(&m, &pos, HEROI);
	int ganhou = !encontraMapa(&m, &pos, FANTASMA);

	return ganhou || perdeu;
}

int ehDirecao(char direcao){
    direcao == ESQUERDA ||
       direcao == CIMA ||
       direcao == BAIXO ||
       direcao == DIREITA;
}

void move(char direcao){

    if(!ehDirecao(direcao)) 
        return;
 
    int proximox = heroi.x;
    int proximoy = heroi.y;

    switch (direcao)
    {
        case ESQUERDA:
            proximoy--;
            break;
        case CIMA:
            proximox--;
            break;
        case BAIXO:
            proximox++;
            break;
        case DIREITA:
            proximoy++;
            break;
    };

    if(!podeAndar(&m, HEROI, proximox, proximoy))
        return;
    
    if(ehPersonagem(&m, PILULA, proximox, proximoy)){
        tempilula = 1;
    }
    
    andaNoMapa(&m, heroi.x, heroi.y, proximox, proximoy);
    heroi.x = proximox;
    heroi.y = proximoy;
    

}

void explodePilula(){

    if(!tempilula) return;

    explodePilula2(heroi.x, heroi.y, 0, 1, 3);
    explodePilula2(heroi.x, heroi.y, 0, -1, 3);
    explodePilula2(heroi.x, heroi.y, 1, 0, 3);
    explodePilula2(heroi.x, heroi.y, -1, 0, 3);

    tempilula = 0;
}

void explodePilula2(int x, int y, int somax, int somay, int qtd){

    if(qtd == 0) return;

    int novox = x + somax;
    int novoy = y + somay;


    if(!ehValida(&m, novox, novoy)) return;
    if(ehParede(&m, novox, novoy)) return;

    m.matriz[novox][novoy] = VAZIO;
    explodePilula2(novox, novoy, somax, somay, qtd - 1);
 
}

int main(){

    leMapa(&m);
    encontraMapa(&m, &heroi, HEROI);
    
    do{
        printf("tem pilula: %s\n", (tempilula ? "SIM" : "NAO"));
        imprimeMapa(&m);

        char comando;
        scanf(" %c", &comando);
        move(comando);
        if(comando == BOMBA) explodePilula();

        fantasmas();

    }while(!acabou());

    liberaMapa(&m);
    
}