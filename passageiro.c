#include "dados.h"
#include <stdio.h>
#include <string.h>

void adicionar_passageiro(char passageiros[MAX_PASSAGEIROS][TAM_STRING]);
void editar_passageiro(char passageiros[MAX_PASSAGEIROS][TAM_STRING]);
int listar_passageiros(char passageiros[MAX_PASSAGEIROS][TAM_STRING]);
void remover_passageiro(char passageiros[MAX_PASSAGEIROS][TAM_STRING], int avioes[MAX_AVIOES][MAX_ASSENTOS]);
void ver_passageiro(char passageiros[MAX_PASSAGEIROS][TAM_STRING], int avioes[MAX_AVIOES][MAX_ASSENTOS], char destinos[MAX_AVIOES][TAM_STRING]);

void menu_passageiro(char passageiros[MAX_PASSAGEIROS][TAM_STRING], int avioes[MAX_AVIOES][MAX_ASSENTOS], char destinos[MAX_AVIOES][TAM_STRING]) {
	int menu = 0;
	char entrada[TAM_STRING] = {0};

	do {

		printf("\n=====> MENU DO PASSAGEIRO <=====\n\nEscolha uma das opções, 6 para sair:\n1 - Adicionar passageiro\n2 - Listar passageiros\n3 - ver passageiro\n4 - editar passageiro\n5 - remover passageiro\n");
		fgets(entrada, TAM_STRING, stdin);

		if (sscanf(entrada, "%d", &menu) != 1) {
			printf("Opcao invalida!\n");
			continue;
		}

		switch (menu) {
		case 1:
			adicionar_passageiro(passageiros);
			break;

		case 2:
			listar_passageiros(passageiros);
			break;

		case 3:
			ver_passageiro(passageiros, avioes, destinos);
			break;

		case 4:
			editar_passageiro(passageiros);
			break;

		case 5:
			remover_passageiro(passageiros, avioes);
			break;

		case 6:
			printf("Voltando ao menu principal...\n");
			return;

		default:
			printf("Opcao invalida!\n");
			break;
		}
	} while (menu != 6);
}

void adicionar_passageiro(char passageiros[MAX_PASSAGEIROS][TAM_STRING]) {
	int indice_cadastrado = -1;
	char nome[TAM_STRING] = {0};

	printf("\nDigite o nome do passageiro: ");
	fgets(nome, TAM_STRING, stdin);
	nome[strcspn(nome, "\n")] = '\0';
	if (nome[0] == '\0') {
		printf("\nNome invalido, voltando ao menu de passageiros...");
		return;
	}

	for (int i = 0; MAX_PASSAGEIROS > i; i++) {
		if (passageiros[i][0] == '\0') {
			indice_cadastrado = i;
			strcpy(passageiros[i], nome);
			break;
		}
	}

	if (indice_cadastrado != -1) {
		printf("\nPassageiro cadastrado:\nId: %d, Nome: %s", indice_cadastrado + 1, passageiros[indice_cadastrado]);
	} else {
		printf("\nSem mais espaços para passageiros, remova um antes de cadastrar outro.");
	}
}

int listar_passageiros(char passageiros[MAX_PASSAGEIROS][TAM_STRING]) {
	int total = 0;
	for (int i = 0; MAX_PASSAGEIROS > i; i++) {
		if (passageiros[i][0] != '\0') {
			printf("ID: %d, Nome: %s\n", i + 1, passageiros[i]);
			total++;
		}
	}

	printf("Total de %d passageiro(s).\n", total);

	return total;
}

void ver_passageiro(char passageiros[MAX_PASSAGEIROS][TAM_STRING], int avioes[MAX_AVIOES][MAX_ASSENTOS], char destinos[MAX_AVIOES][TAM_STRING]) {
	int escolhido = 0;
	char entrada[TAM_STRING] = {0};
	int quantidade_viagens = 0;
	int avioes_passageiro[MAX_AVIOES];
	int assentos_passageiro[MAX_AVIOES];

	if (listar_passageiros(passageiros) == 0) {
		printf("Sem passageiros para ver!");
		return;
	}

	printf("\nEscolha um passageiro para ver suas viagens, 0 para sair: ");
	fgets(entrada, TAM_STRING, stdin);
	if (sscanf(entrada, "%d", &escolhido) != 1) {
		printf("Entrada invalida, retornando ao menu...");
		return;
	}

	if (escolhido <= 0) {
		printf("\nCancelado ver passageiro, retornando para menu...");
		return;
	}

	if (escolhido > MAX_PASSAGEIROS) {
		printf("\nNão existem passageiros após o ID %d, voltando ao menu...", MAX_PASSAGEIROS);
		return;
	}

	escolhido--;

	if (passageiros[escolhido][0] == '\0') {
		printf("\nPassageiro com ID: %d não existe, voltando ao menu...", escolhido + 1);
		return;
	}

	for (int i = 0; MAX_AVIOES > i; i++) {
		for (int j = 0; MAX_ASSENTOS > j; j++) {
			if (avioes[i][j] == escolhido) {
				avioes_passageiro[quantidade_viagens] = i;
				assentos_passageiro[quantidade_viagens] = j;
				quantidade_viagens++;
			}
		}
	}

	if (quantidade_viagens == 0) {
		printf("\nPassageiro sem viagens.");
		return;
	}

	printf("\nDestinos do passageiro %s", passageiros[escolhido]);

	for (int i = 0; quantidade_viagens > i; i++) {
		printf("\n<--------------------------->");
		printf("\nAvião: %d\nAssento: %d\nDestino: %s", avioes_passageiro[i] + 1, assentos_passageiro[i] + 1, destinos[avioes_passageiro[i]]);
	}
}

void editar_passageiro(char passageiros[MAX_PASSAGEIROS][TAM_STRING]) {
	char entrada[TAM_STRING] = {0};
	char nome[TAM_STRING] = {0};
	int escolhido = 0;

	if (listar_passageiros(passageiros) == 0) {
		printf("Sem passageiros para editar!");
		return;
	}

	printf("\nEscolha um passageiro para editar, 0 para sair: ");
	fgets(entrada, TAM_STRING, stdin);
	if (sscanf(entrada, "%d", &escolhido) != 1) {
		printf("Entrada invalida, retornando ao menu...");
		return;
	}

	if (escolhido <= 0) {
		printf("\nVoltando ao menu, cancelada edição de passageiro...");
		return;
	}
	if (escolhido > MAX_PASSAGEIROS) {
		printf("\nNão existem passageiros após o ID %d, voltando ao menu...", MAX_PASSAGEIROS);
		return;
	}

	escolhido--;

	if (passageiros[escolhido][0] == '\0') {
		printf("\nPassageiro não encontrado, voltando ao menu...");
		return;
	}

	printf("\nDigite o novo nome do passageiro: ");
	fgets(nome, TAM_STRING, stdin);
	nome[strcspn(nome, "\n")] = '\0';
	if (nome[0] == '\0') {
		printf("\nNome invalido, nada foi alterado, voltando ao menu de passageiros...");
		return;
	}

	strcpy(passageiros[escolhido], nome);
	printf("\nNome alterado com sucesso.");
}

void remover_passageiro(char passageiros[MAX_PASSAGEIROS][TAM_STRING], int avioes[MAX_AVIOES][MAX_ASSENTOS]) {
	int escolhido = 0;
	char entrada[TAM_STRING] = {0};

	if (listar_passageiros(passageiros) == 0) {
		printf("Sem passageiros para remover!");
		return;
	}

	printf("\nDigite o ID do passageiro a ser excluido, 0 para sair: ");
	fgets(entrada, TAM_STRING, stdin);

	if (sscanf(entrada, "%d", &escolhido) != 1) {
		printf("Entrada invalida, retornando ao menu...");
		return;
	}

	if (escolhido <= 0) {
		printf("\nVoltando ao menu, cancelada exclusão de passageiro...");
		return;
	}
	if (escolhido > MAX_PASSAGEIROS) {
		printf("\nNão existem passageiros após o ID %d, voltando ao menu...", MAX_PASSAGEIROS);
		return;
	}

	escolhido--;

	if (passageiros[escolhido][0] == '\0') {
		printf("\nPassageiro não encontrado, voltando ao menu...");
		return;
	}

	for (int i = 0; MAX_AVIOES > i; i++) {
		for (int j = 0; MAX_ASSENTOS > j; j++) {
			if (avioes[i][j] == escolhido) {
				avioes[i][j] = -1;
			}
		}
	}

	passageiros[escolhido][0] = '\0';

	printf("\nPassageiro excluído com sucesso.");
}