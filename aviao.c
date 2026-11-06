#include "dados.h"
#include <stdio.h>
#include <string.h>

void adicionar_aviao(char destinos[MAX_AVIOES][TAM_STRING]);
void editar_aviao(char destinos[MAX_AVIOES][TAM_STRING]);
int listar_avioes(char destinos[MAX_AVIOES][TAM_STRING]);
void remover_aviao(int avioes[MAX_AVIOES][MAX_ASSENTOS], char destinos[MAX_AVIOES][TAM_STRING]);
void ver_aviao(int avioes[MAX_AVIOES][MAX_ASSENTOS], char passageiros[MAX_PASSAGEIROS][TAM_STRING], char destinos[MAX_AVIOES][TAM_STRING]);
int imprimir_reservas_aviao(char passageiros[MAX_PASSAGEIROS][TAM_STRING], int avioes[MAX_AVIOES][MAX_ASSENTOS], char destinos[MAX_AVIOES][TAM_STRING], int escolhido);
void ranking_destinos(int avioes[MAX_AVIOES][MAX_ASSENTOS], char destinos[MAX_AVIOES][TAM_STRING]);
int contar_ocupados(int avioes[MAX_AVIOES][MAX_ASSENTOS], int aviao, int assento);

void menu_aviao(int avioes[MAX_AVIOES][MAX_ASSENTOS], char passageiros[MAX_PASSAGEIROS][TAM_STRING], char destinos[MAX_AVIOES][TAM_STRING]) {
	int menu = 0;
	char entrada[TAM_STRING] = {0};

	do {

		printf("\n=====> MENU DO AVIAO <=====\nEscolha uma das opcoes, 7 para sair:\n1 - Adicionar aviao\n2 - Listar avioes\n3 - ver aviao\n4 - editar aviao\n5 - remover aviao\n6 - ranking destinos\n");
		fgets(entrada, TAM_STRING, stdin);

		if (sscanf(entrada, "%d", &menu) != 1) {
			printf("Opcao invalida!\n");
			continue;
		}

		switch (menu) {
		case 1:
			adicionar_aviao(destinos);
			break;

		case 2:
			listar_avioes(destinos);
			break;

		case 3:
			ver_aviao(avioes, passageiros, destinos);
			break;

		case 4:
			editar_aviao(destinos);
			break;

		case 5:
			remover_aviao(avioes, destinos);
			break;

		case 6:
			ranking_destinos(avioes, destinos);
			break;

		case 7:
			printf("Voltando ao menu principal...\n");
			return;

		default:
			printf("Opcao invalida!\n");
			break;
		}
	} while (menu != 7);
}

void adicionar_aviao(char destinos[MAX_AVIOES][TAM_STRING]) {
	int indice_cadastrado = -1;
	char destino[TAM_STRING] = {0};

	printf("\nDigite o destino do aviao: ");
	fgets(destino, TAM_STRING, stdin);
	destino[strcspn(destino, "\n")] = '\0';
	if (destino[0] == '\0') {
		printf("\nDestino invalido, voltando ao menu de avioes...");
		return;
	}

	for (int i = 0; MAX_AVIOES > i; i++) {
		if (destinos[i][0] == '\0') {
			indice_cadastrado = i;
			strcpy(destinos[i], destino);
			break;
		}
	}

	if (indice_cadastrado != -1) {
		printf("\nAviao cadastrado:\nId: %d, destino: %s", indice_cadastrado + 1, destinos[indice_cadastrado]);
	} else {
		printf("\nSem mais espacos para avioes, remova um antes de cadastrar outro.");
	}
}

int listar_avioes(char destinos[MAX_AVIOES][TAM_STRING]) {
	int total = 0;
	for (int i = 0; MAX_AVIOES > i; i++) {
		if (destinos[i][0] != '\0') {
			printf("ID: %d, Destino: %s\n", i + 1, destinos[i]);
			total++;
		}
	}

	printf("Total de %d viagem(s).\n", total);

	return total;
}

void ver_aviao(int avioes[MAX_AVIOES][MAX_ASSENTOS], char passageiros[MAX_PASSAGEIROS][TAM_STRING], char destinos[MAX_AVIOES][TAM_STRING]) {
	int escolhido = 0;
	char entrada[TAM_STRING] = {0};
	int quantidade_passageiros = 0;

	if (listar_avioes(destinos) == 0) {
		printf("Sem avioes para ver!");
		return;
	}

	printf("\nEscolha um aviao para ver seus passageiros, 0 para sair: ");
	fgets(entrada, TAM_STRING, stdin);
	if (sscanf(entrada, "%d", &escolhido) != 1) {
		printf("Entrada invalida, retornando ao menu...");
		return;
	}

	if (escolhido <= 0) {
		printf("\nCancelado ver aviao, retornando para menu...");
		return;
	}

	if (escolhido > MAX_AVIOES) {
		printf("\nNao existem avioes apos o ID %d, voltando ao menu...", MAX_AVIOES);
		return;
	}

	escolhido--;

	if (destinos[escolhido][0] == '\0') {
		printf("\nAviao com ID: %d nao existe, voltando ao menu...", escolhido + 1);
		return;
	}
	imprimir_reservas_aviao(passageiros, avioes, destinos, escolhido);
}

int imprimir_reservas_aviao(char passageiros[MAX_PASSAGEIROS][TAM_STRING], int avioes[MAX_AVIOES][MAX_ASSENTOS], char destinos[MAX_AVIOES][TAM_STRING], int escolhido) {
	int quantidade_passageiros = 0;

	printf("\nPassageiros do aviao %d com destino para %s:", escolhido + 1, destinos[escolhido]);

	for (int i = 0; MAX_ASSENTOS > i; i++) {
		if (avioes[escolhido][i] >= 0) {
			printf("\n<--------------------------->\n");
			printf("ID: %d\nAssento: %d\nNome: %s\n", avioes[escolhido][i] + 1, i + 1, passageiros[avioes[escolhido][i]]);
			quantidade_passageiros++;
		}
	}

	if (quantidade_passageiros == 0) {
		printf("\nAviao sem passageiros.\n");
	}

	return quantidade_passageiros;
}

void editar_aviao(char destinos[MAX_AVIOES][TAM_STRING]) {
	char entrada[TAM_STRING] = {0};
	char destino[TAM_STRING] = {0};
	int escolhido = 0;

	if (listar_avioes(destinos) == 0) {
		printf("Sem avioes para editar!\n");
		return;
	}

	printf("\nEscolha um aviao para editar, 0 para sair: ");
	fgets(entrada, TAM_STRING, stdin);
	if (sscanf(entrada, "%d", &escolhido) != 1) {
		printf("Entrada invalida, retornando ao menu...");
		return;
	}

	if (escolhido <= 0) {
		printf("\nVoltando ao menu, cancelada edicao de aviao...");
		return;
	}
	if (escolhido > MAX_AVIOES) {
		printf("\nNao existem avioes apos o ID %d, voltando ao menu...", MAX_AVIOES);
		return;
	}

	escolhido--;

	if (destinos[escolhido][0] == '\0') {
		printf("\nAviao nao encontrado, voltando ao menu...");
		return;
	}

	printf("\nDigite o novo destino do aviao: ");
	fgets(destino, TAM_STRING, stdin);
	destino[strcspn(destino, "\n")] = '\0';
	if (destino[0] == '\0') {
		printf("\nDestino invalido, nada foi alterado, voltando ao menu de avioes...");
		return;
	}

	strcpy(destinos[escolhido], destino);
	printf("\nDestino alterado com sucesso.");
}

void remover_aviao(int avioes[MAX_AVIOES][MAX_ASSENTOS], char destinos[MAX_AVIOES][TAM_STRING]) {
	int escolhido = 0;
	char entrada[TAM_STRING] = {0};
	int quantidade_assentos_cancelados = 0;

	if (listar_avioes(destinos) == 0) {
		printf("Sem avioes para remover!");
		return;
	}

	printf("\nDigite o ID do aviao a ser excluido, 0 para sair: ");
	fgets(entrada, TAM_STRING, stdin);

	if (sscanf(entrada, "%d", &escolhido) != 1) {
		printf("Entrada invalida, retornando ao menu...");
		return;
	}

	if (escolhido <= 0) {
		printf("\nVoltando ao menu, cancelada exclusao de aviao...");
		return;
	}
	if (escolhido > MAX_AVIOES) {
		printf("\nNao existem avioes apos o ID %d, voltando ao menu...", MAX_AVIOES);
		return;
	}

	escolhido--;

	if (destinos[escolhido][0] == '\0') {
		printf("\nAviao nao encontrado, voltando ao menu...");
		return;
	}

	for (int i = 0; MAX_ASSENTOS > i; i++) {
		if (avioes[escolhido][i] >= 0) {
			quantidade_assentos_cancelados++;
			avioes[escolhido][i] = -1;
		}
	}

	destinos[escolhido][0] = '\0';

	printf("\nAviao excluido com sucesso, %d reserva(s) cancelada(s).", quantidade_assentos_cancelados);
}

int contar_ocupados(int avioes[MAX_AVIOES][MAX_ASSENTOS], int aviao, int assento) {
	if (assento == MAX_ASSENTOS) {
		return 0;
	}

	if (avioes[aviao][assento] != -1) {
		return 1 + contar_ocupados(avioes, aviao, assento + 1);
	}

	return contar_ocupados(avioes, aviao, assento + 1);
}

void ranking_destinos(int avioes[MAX_AVIOES][MAX_ASSENTOS], char destinos[MAX_AVIOES][TAM_STRING]) {
	int ocupacao[MAX_AVIOES] = {0};
	int ids[MAX_AVIOES] = {0};
	char nomes[MAX_AVIOES][TAM_STRING] = {0};
	int voos_ocupados = 0;

	for (int i = 0; MAX_AVIOES > i; i++) {
		if (destinos[i][0] == '\0') {
			continue;
		}

		int quantidade_voo = contar_ocupados(avioes, i, 0);

		strcpy(nomes[voos_ocupados], destinos[i]);
		ocupacao[voos_ocupados] = quantidade_voo;
		ids[voos_ocupados] = i;
		voos_ocupados++;
	}

	for (int i = 1; i < voos_ocupados; i++) {
		for (int j = 0; j < voos_ocupados - i; j++) {
			if (ocupacao[j] < ocupacao[j + 1]) {
				int aux = ocupacao[j];
				ocupacao[j] = ocupacao[j + 1];
				ocupacao[j + 1] = aux;

				aux = ids[j];
				ids[j] = ids[j + 1];
				ids[j + 1] = aux;

				char temp[TAM_STRING];
				strcpy(temp, nomes[j]);
				strcpy(nomes[j], nomes[j + 1]);
				strcpy(nomes[j + 1], temp);
			}
		}
	}

	if (voos_ocupados == 0) {
		printf("\nSem avioes cadastrados. Voltando ao menu...");
		return;
	}

	printf("\nRanking de viagens por ocupacao:");

	for (int i = 0; voos_ocupados > i; i++) {
		printf("\n<--------------------------->");
		printf("\nPosicao: %d\nID: %d\nDestino: %s\nOcupacao: %d de %d assentos", i + 1, ids[i] + 1, nomes[i], ocupacao[i], MAX_ASSENTOS);
	}
}