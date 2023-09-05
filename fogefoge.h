#define CIMA 'w'
#define BAIXO 's'
#define ESQUERDA 'a'
#define DIREITA 'd'

void move(char direcao);
int acabou();
int ehDirecao(char direcao);
void fantasmas();
int praOndeFantasmaVai(int xatual, int yatual, int* xdestino, int* ydestino);