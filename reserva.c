#include "dados.h"
#include <stdio.h>

void adicionar_reserva(char passageiros[MAX_PASSAGEIROS][TAM_STRING], int avioes[MAX_AVIOES][MAX_ASSENTOS], char destinos[MAX_AVIOES][TAM_STRING]);
void remover_reserva(char passageiros[MAX_PASSAGEIROS][TAM_STRING], int avioes[MAX_AVIOES][MAX_ASSENTOS], char destinos[MAX_AVIOES][TAM_STRING]);
void imprimir_assentos(int avioes[MAX_AVIOES][MAX_ASSENTOS], int escolhido);

void menu_reserva(int avioes[MAX_AVIOES][MAX_ASSENTOS], char passageiros[MAX_PASSAGEIROS][TAM_STRING], char destinos[MAX_AVIOES][TAM_STRING]) {
	int menu = 0;
	char entrada[TAM_STRING] = {0};

	do {

		printf("\n=====> MENU RESERVAS <=====\nEscolha uma das opcoes, 3 para sair:\n1 - Adicionar reserva\n2 - Remover reservas\n");
		fgets(entrada, TAM_STRING, stdin);

		if (sscanf(entrada, "%d", &menu) != 1) {
			printf("Opcao invalida!\n");
			continue;
		}

		switch (menu) {
		case 1:
			adicionar_reserva(passageiros, avioes, destinos);
			break;

		case 2:
			remover_reserva(passageiros, avioes, destinos);
			break;

		case 3:
			printf("Voltando ao menu principal...\n");
			return;

		default:
			printf("Opcao invalida!\n");
			break;
		}
	} while (menu != 3);
}

void adicionar_reserva(char passageiros[MAX_PASSAGEIROS][TAM_STRING], int avioes[MAX_AVIOES][MAX_ASSENTOS], char destinos[MAX_AVIOES][TAM_STRING]) {
	int entrada = 0;
	int aviao_escolhido = -1;
	int passageiro_escolhido = -1;
	int assento_escolhido = -1;

	if (listar_avioes(destinos) == 0) {
		printf("\nSem avioes cadastrados, primeiro cadastre um aviao. Voltando ao menu...");
		return;
	}
	printf("\nEscolha um aviao para reservar uma viagem, 0 para sair: ");
	entrada = entrada_int(MAX_AVIOES);
	if (entrada <= 0) {
		return;
	}
	aviao_escolhido = entrada - 1;
	if (destinos[aviao_escolhido][0] == '\0') {
		printf("\nDestino invalido, retornando ao menu...");
		return;
	}

	if (listar_passageiros(passageiros) == 0) {
		printf("\nSem passageiros cadastrados, primeiro cadastre um passageiro. Voltando ao menu...");
		return;
	}
	printf("\nEscolha um passageiro, 0 para sair: ");
	entrada = entrada_int(MAX_PASSAGEIROS);
	if (entrada <= 0) {
		return;
	}
	passageiro_escolhido = entrada - 1;
	if (passageiros[passageiro_escolhido][0] == '\0') {
		printf("\nPassageiro invalido, retornando ao menu...");
		return;
	}

	for (int i = 0; MAX_ASSENTOS > i; i++) {
		if (avioes[aviao_escolhido][i] == passageiro_escolhido) {
			printf("\nPassageiro ja esta nesse aviao! voltando para o menu...");
			return;
		}
	}

	imprimir_assentos(avioes, aviao_escolhido);

	printf("\nEscolha um assento, 0 para sair: ");
	entrada = entrada_int(MAX_ASSENTOS);
	if (entrada <= 0) {
		return;
	}
	assento_escolhido = entrada - 1;
	if (avioes[aviao_escolhido][assento_escolhido] >= 0) {
		printf("\nLocal ja ocupado! voltando para o menu...");
		return;
	}

	avioes[aviao_escolhido][assento_escolhido] = passageiro_escolhido;
	printf("\nReserva criada com sucesso.");
}

void remover_reserva(char passageiros[MAX_PASSAGEIROS][TAM_STRING], int avioes[MAX_AVIOES][MAX_ASSENTOS], char destinos[MAX_AVIOES][TAM_STRING]) {
	int entrada = 0;
	int aviao_escolhido = -1;
	int passageiro_escolhido = -1;
	int assento_escolhido = -1;

	if (listar_avioes(destinos) == 0) {
		printf("\nSem avioes cadastrados. Voltando ao menu...");
		return;
	}
	printf("\nEscolha um aviao para remover uma reserva, 0 para sair: ");
	entrada = entrada_int(MAX_AVIOES);
	if (entrada <= 0) {
		return;
	}
	aviao_escolhido = entrada - 1;
	if (destinos[aviao_escolhido][0] == '\0') {
		printf("\nAviao invalido, retornando ao menu...");
		return;
	}

	if (imprimir_reservas_aviao(passageiros, avioes, destinos, aviao_escolhido) == 0) {
		printf("Aviao sem reservas! voltando ao menu...");
		return;
	}
	printf("Escolha o ID do passageiro a ter sua reserva cancelada: ");
	entrada = entrada_int(MAX_PASSAGEIROS);
	if(entrada == -1){
		return;
	}
	passageiro_escolhido = entrada - 1;

	for (int i = 0; MAX_ASSENTOS > i; i++) {
		if(avioes[aviao_escolhido][i] == passageiro_escolhido){
			avioes[aviao_escolhido][i] = -1;
			printf("\nReserva cancelada com sucesso.");
			return;
		}
	}
	printf("Passageiro escolhido nao esta na viagem, retornando ao menu...");
}

void imprimir_assentos(int avioes[MAX_AVIOES][MAX_ASSENTOS], int escolhido) {
	printf("\nAssento livre: [o]   |    Assento ocupado [x]\n\n");

	for (int fileira = 0; QUANTIDADE_FILEIRAS > fileira; fileira++) {
		int inicio_fileira = fileira * ASSENTOS_FILEIRA;

		for (int i = inicio_fileira; inicio_fileira + ASSENTOS_FILEIRA > i; i++) {
			if (avioes[escolhido][i] >= 0) {
				printf("[x] ");
			} else {
				printf("[o] ");
			}
		}
		printf("\n");

		for (int i = inicio_fileira; inicio_fileira + ASSENTOS_FILEIRA > i; i++) {
			printf(" %02d ", i + 1);
		}
		printf("\n");

		if (fileira == QUANTIDADE_FILEIRAS / 2 - 1) {
			printf("\n===========================================================\n\n");
		}
	}
}