#ifndef modelo_dados
#define modelo_dados

//15 assentos por fileira, 4 fileiras, numeradas:
// []
// 01
//assento livre contém -1
//array bid, {aviao, assentos}


#define MAX_AVIOES      4
#define MAX_ASSENTOS    60
#define MAX_PASSAGEIROS 99
#define TAM_STRING      50



void menu_passageiro(char passageiros[MAX_PASSAGEIROS][TAM_STRING], int avioes[MAX_AVIOES][MAX_ASSENTOS], char destinos[MAX_AVIOES][TAM_STRING]);
void menu_aviao(int avioes[MAX_AVIOES][MAX_ASSENTOS], char passageiros[MAX_PASSAGEIROS][TAM_STRING], char destinos[MAX_AVIOES][TAM_STRING]);
int listar_avioes(char destinos[MAX_AVIOES][TAM_STRING]);
int listar_passageiros(char passageiros[MAX_PASSAGEIROS][TAM_STRING]);


#endif