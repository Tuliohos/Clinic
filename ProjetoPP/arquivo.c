#include "arquivo.h"

int posicaoCliente(char cpf[], FILE *arq) { //Função que procura cliente no arquivo
	int cont = -1, status;
	TCliente aux;

	fseek(arq, 0, 0);
	while (1) {
		status = fread(&aux, sizeof(TCliente), 1, arq);
		if (status != 1) {
			if (!feof(arq)) {
				return -2;
			}
			else {
				return -1;
			}
		}
		else {
			cont++;
			if (aux.status != 0 && strcmp(aux.cpf, cpf) == 0) {
				return cont;
			}
		}
	}
}
int posicaoMedico(char crm[], FILE *arq) { //Função que procura cliente no arquivo
	int cont = -1, status;
	TMedico aux;

	fseek(arq, 0, 0);
	while (1) {
		status = fread(&aux, sizeof(TMedico), 1, arq);
		if (status != 1) {
			if (!feof(arq)) {
				return -2;
			}
			else {
				return -1;
			}
		}
		else {
			cont++;
			if (aux.status != 0 && strcmp(aux.crm, crm) == 0) {
				return cont;
			}
		}
	}
}
void manutencaoCliente(FILE *arq) {
	FILE *aux;
	TCliente leitor;

	aux = fopen("Aux.bin", "w+b");
	if (aux == NULL) {
		printf("Erro ao abrir arquivo auxiliar!\n");
		if (fclose(arq) != 0) {
			printf("Erro ao fechar o arquivo principal!\n");
			return;
		}
		return;
	}
	while (1) {
		if (fread(&leitor, sizeof(TCliente), 1, arq) != 1) {
			if (!feof(arq)) {
				printf("Erro na leitura do arquivo!\n");
				if (fclose(arq) != 0)
					printf("Erro ao fechar o arquivo principal!\n");
				if (fclose(aux) != 0)
					printf("Erro ao fechar o arquivo secundario!\n");
				return;
			}
			break;
		}
		if (leitor.status == 1) {
			if (fwrite(&leitor, sizeof(TCliente), 1, aux) != 1) {
				printf("Erro ao escrever informacao no arquivo!\n");
				if (fclose(arq) != 0)
					printf("Erro ao fechar o arquivo principal!\n");
				if (fclose(aux) != 0)
					printf("Erro ao fechar o arquivo secundario!\n");
				return;
			}
		}
	}
	if (fclose(arq) != 0) {
		printf("Erro ao fechar o arquivo principal!\n");
		if (fclose(aux) != 0) {
			printf("Erro ao fechar o arquivo secundario!\n");
		}
		return;
	}
	remove("Cliente.bin");
	rename("Aux.bin", "Cliente.bin");
}
void manutencaoMedico(FILE *arq) {
	FILE *aux;
	TMedico leitor;

	aux = fopen("Aux.bin", "wb");
	if (aux ==NULL) {
		printf("Erro ao abrir arquivo auxiliar!\n");
		if (fclose(arq) != 0) {
			printf("Erro ao fechar o arquivo principal!\n");
			return;
		}
		return;
	}
	while (1) {
		if (fwrite(&leitor, sizeof(TMedico), 1, arq) != 1) {
			if (!feof(arq)) {
				printf("Erro na leitura do arquivo!\n");
				if (fclose(arq) != 0) {
					printf("Erro ao fechar o arquivo principal!\n");
				}
				if (fclose(aux) != 0) {
					printf("Erro ao fechar o arquivo secundario!\n");
					return;
				}
				break;
			}
		}
		if (leitor.status == 1) {
			if (fwrite(&leitor, sizeof(TMedico), 1, aux) != 1) {
				printf("Erro ao escrever informacao no arquivo!\n");
				if (fclose(arq) != 0) {
					printf("Erro ao fechar o arquivo principal!\n");
				}
				if (fclose(aux) != 0) {
					printf("Erro ao fechar o arquivo secundario!\n"); 
						return;
				}
			}
		}
	}
	if(fclose(arq) != 0) {
		printf("Erro ao fechar o arquivo principal!\n");
		if (fclose(aux) != 0) {
			printf("Erro ao fechar o arquivo secundario!\n");
		}
		return;
	}
	remove("Medico.bin");
	rename("Aux.bin", "Medico.bin");
}

int pesquisarPorNome(FILE *arq, char nome[]) {
	TCliente *buscar;
	int cont = 0;
	while (1) {
		if (fread(&buscar, sizeof(TCliente), 1, arq) != 1) {
			if (!feof(arq)) {
				printf("Erro na leitura do arquivo!\n");
				return -2;
			}
			break;
		}
		cont++;
		if (strcmp(buscar->nome, nome) == 0) {
			return cont;
		}

	}
	return -1;
}
FILE* abrirArquivoCliente() {
	FILE * arq;
	arq = fopen("Cliente.bin", "r+b");
	if (arq == NULL) {
		arq = fopen("Cliente.bin", "w+b");
	}
	return arq;
}

FILE* abrirArquivoMedico() {
	FILE * arq;
	arq = fopen("Medico.bin", "r+b");
	if (arq == NULL) {
		arq = fopen("Medico.bin", "w+b");
	}
	return arq;
}
