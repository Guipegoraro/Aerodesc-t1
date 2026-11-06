#ifndef dados   
#define dados

#define QUANTIDADE_FILEIRAS 4
#define ASSENTOS_FILEIRA 15
#define MAX_AVIOES      4
#define MAX_ASSENTOS    60
#define MAX_PASSAGEIROS 99
#define TAM_STRING      50



void menu_passageiro(int avioes[MAX_AVIOES][MAX_ASSENTOS], char passageiros[MAX_PASSAGEIROS][TAM_STRING], char destinos[MAX_AVIOES][TAM_STRING]);
void menu_aviao(int avioes[MAX_AVIOES][MAX_ASSENTOS], char passageiros[MAX_PASSAGEIROS][TAM_STRING], char destinos[MAX_AVIOES][TAM_STRING]);
void menu_reserva(int avioes[MAX_AVIOES][MAX_ASSENTOS], char passageiros[MAX_PASSAGEIROS][TAM_STRING], char destinos[MAX_AVIOES][TAM_STRING]);

int listar_avioes(char destinos[MAX_AVIOES][TAM_STRING]);
void imprimir_reservas_aviao(char passageiros[MAX_PASSAGEIROS][TAM_STRING], int avioes[MAX_AVIOES][MAX_ASSENTOS], char destinos[MAX_AVIOES][TAM_STRING], int escolhido);

int listar_passageiros(char passageiros[MAX_PASSAGEIROS][TAM_STRING]);

int entrada_int(int tamanho_maximo);

#endif