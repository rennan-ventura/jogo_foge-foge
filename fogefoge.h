void liberaMapa();
void leMapa();
void alocaMapa();

void move(char direcao);
int acabou();
void imprimeMapa();

struct  mapa{
    char** matriz;
    int linhas;
    int colunas; 
};


typedef struct mapa MAPA;