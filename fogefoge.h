#ifndef _FOGEFOGE_H_
#define _FOGEFOGE_H_

#define CIMA 'w'
#define BAIXO 's'
#define ESQUERDA 'a'
#define DIREITA 'd'
#define BOMBA 'b'

void move(char direcao);
int acabou();
int ehDirecao(char direcao);
void fantasmas();
int praOndeFantasmaVai(int xatual, int yatual, int* xdestino, int* ydestino);
void explodePilula();
void explodePilula2(int x, int y, int somax, int somay, int qtd);

#endif