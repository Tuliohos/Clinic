#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#define TAM 101

void lerNome(char nome[]);
int validarNome(char nome[]);
void limparNome(char nome[]);
void formatarNome(char nome[]);

int main() {
	char nome[TAM];
	int ehValido;
	do {
		printf("Informe um nome contendo apenas letra e espacos: ");
		lerNome(nome);
		ehValido = validarNome(nome);
	} while (ehValido == 0);
	limparNome(nome);
	formatarNome(nome);
	printf("Nome: %s \n", nome);
	return 0;
}

void lerNome(char nome[]) {
	int i;
	for (i = 0; i < TAM - 1; i++) {
		nome[i] = getche();
		if (nome[i] == '\n') {
			break;
		}
	}
	nome[i] = '\0';
}

int validarNome(char nome[]) {
	int i, tam = strlen(nome);
	for (i = 0; i < tam; i++) {
		if (!isalpha(nome[i]) && !isspace(nome[i])){
			return 0;
		}
	}
	return 1;
}

void limparNome(char nome[]) {
	int i, j, tam = strlen(nome);
	char aux[TAM];

	for (i = 0; i < tam; i++) {
		if (isspace(nome[i]) && isspace(nome[i+1])) {
			for (j = i; j < strlen(nome); j++) {
				nome[j] = nome[j + 1];
			}
		}
	}
}

void formatarNome(char nome []) {
	int i, tam = strlen(nome);
	for (i = 0; i < tam; i++) {
		
	}
}