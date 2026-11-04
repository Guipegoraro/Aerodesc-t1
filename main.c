#include "dados.h"
#include <stdio.h>


void liberar_assentos(int avioes[MAX_AVIOES][MAX_ASSENTOS]);

int main() {
	char passageiros[MAX_PASSAGEIROS][TAM_STRING] = {0};
	int avioes[MAX_AVIOES][MAX_ASSENTOS] = {0};
	char destinos[MAX_AVIOES][TAM_STRING] = {0};
	liberar_assentos(avioes);

	int menu = 0;
	char entrada[TAM_STRING] = {0};

	do {
		printf("\n=====> MENU PRINCIPAL AERODESC <=====\nEscolha uma das opcoes, 4 para sair:\n1 - Menu avioes\n2 - Menu passageiros\n3 - Menu reservas\n");
		fgets(entrada, TAM_STRING, stdin);

		if (sscanf(entrada, "%d", &menu) != 1) {
			printf("Opcao invalida!\n");
			continue;
		}

		switch (menu) {
		case 1:
			menu_aviao(avioes, passageiros, destinos);
			break;

		case 2:
			menu_passageiro(avioes, passageiros, destinos);
			break;

		case 3:
			menu_reserva(avioes, passageiros, destinos);
			break;

					case 4:
			printf("Finalizando programa, obrigado por usar a Aerodesc!");
			return 0;
			break;

		default:
			printf("Opcao invalida!\n");
			break;
		}
	} while (menu != 4);

	return 0;
}

void liberar_assentos(int avioes[MAX_AVIOES][MAX_ASSENTOS]) {
	for (int i = 0; i < MAX_AVIOES; i++)
		for (int j = 0; j < MAX_ASSENTOS; j++)
			avioes[i][j] = -1;
}

int entrada_int(int tamanho_maximo) {
	char entrada[TAM_STRING];
	int saida = -1;
	fgets(entrada, TAM_STRING, stdin);
	if (sscanf(entrada, "%d", &saida) != 1) {
		printf("\nEntrada invalida, retornando ao menu...");
		return -1;
	}
	if (saida > tamanho_maximo) {
		printf("\nTamanho maximo para selecao: %d", tamanho_maximo);
		return -1;
	}
	if (saida <= 0) {
		printf("\nSelecao cancelada, voltando para o menu...");
		return -1;
	}

	return saida;
}