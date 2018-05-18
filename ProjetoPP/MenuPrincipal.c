#include "types.h"
#include "arvore.h"
#include "arquivo.h"
#include "medico.h"
#include "cliente.h"
#include "validacao.h"
//#define MEDICOS

void menuCliente(FILE *arq, TNoTree **arv);
void menuMedico(FILE *arq, TNoTree **arv);

int main() {
	FILE *arqCliente, *arqMedico;
	char op, cliente[] = "Cliente.bin", medico[] = "Medico.bin";
	TNoTree *arvCliente = NULL, *arvMedico = NULL;
	
	arqCliente = abrirArquivoCliente();
	if (arqCliente == NULL) {
		printf("Impossivel prosseguir com o programa. Falha ao abrir o arquivo de clientes!\n");
		return;
	}
	arqMedico = abrirArquivoMedico();
	if (arqMedico == NULL) {
		printf("Impossivel prosseguir com o programa. Falha ao abrir o arquivo de medicos!\n");
		return;
	}

	indexarCliente(&arvCliente, arqCliente);
	indexarMedico(&arvMedico, arqMedico);
	//passeio(arvCliente);
	//passeio(arvMedico);
	
	do {
		printf("######### MENU PRINCIPAL #########\n\n");
		printf("Digite 1 para ir ao menu de clientes;\n");
		printf("Digite 2 para ir ao menu de medicos;\n");
		printf("Digite 3 para ir ao menu de consultas;\n");
		printf("Digite 4 para sair;\n");
		printf("Responda: ");
		fflush(stdin);
		op = getchar();
		switch (op) {
		case '1': system("cls");
			menuCliente(arqCliente, &arvCliente);
			break;
		case '2':system("cls");
			//menuMedico(arqMedico, &arvMedico);
			break;
		case '3':system("cls");
			//menuConsultas();
			break;
		case '4': system("cls");
			desindexar(&arvCliente);
			desindexar(&arvMedico);
			manutencaoCliente(arqCliente);
			manutencaoMedico(arqMedico);
			break;
		default: printf("Opcao invalida!\n");
			break;
		}

	} while (op != '4');
	
	return 0;
}

void menuCliente(FILE *arq, TNoTree **arv) {
	char cpf[TAM_CPF];
	int op;


	do {
		system("cls");
		printf("######### MENU CLIENTE #########\n\n");
		printf("1 - Cadastrar contato \n");
		printf("2 - Alterar dados contato \n");
		printf("3 - Consultar contato \n");
		printf("4 - Remover contato \n");
		printf("5 - Listar todos \n");
		printf("6 - Sair \n");
		printf("Resposta: ");
		scanf("%d", &op);
		switch (op) {
		case 1:system("cls");
			printf("Informe o cpf: ");
			scanf("%s", &cpf);
				 while (validarCpf(cpf) != 1) {
				 printf("CPF invalido! Informe novamente: ");
				 scanf("%s", &cpf);
			 }
			cadastrar(cpf, arv, arq);
			break;
		case 2:system("cls");
			printf("Informe o cpf: ");
			scanf("%s", &cpf);
			while (validarCpf(cpf) != 1) {
			printf("CPF invalido! Informe novamente: ");
			scanf("%s", &cpf);
			}
			alterar(arq, *arv, cpf);
			break;
		case 3:system("cls");
			printf("Informe o cpf: ");
			scanf("%s", &cpf);
			while (validarCpf(cpf) != 1) {
			printf("CPF invalido! Informe novamente: ");
			scanf("%s", &cpf);
			}
			exibirCliente(arq, *arv, cpf);
			getch();
			break;

		case 4:system("cls");
			printf("Informe o cpf: ");
			scanf("%s", &cpf);
			while (validarCpf(cpf) != 1) {
			printf("CPF invalido! Informe novamente: ");
			scanf("%s", &cpf);
			}
			removerCliente(arq, arv, cpf);
			break;
		case 5:system("cls");
			listarTodos(arq);
			getch();
			break;
		case 6: 
			break;
		default: printf("\n\nOpcao invalida!\n\n");
		}
	} while (op != 6);
}
#ifdef MEDICO

void menuMedico(FILE *arq, TNoTree **arv) {
	char crm[TAM_CRM];
	int op;

	do {
		system("cls");
		printf("######### MENU MEDICO #########\n\n");
		printf("1 - Cadastrar medico \n");
		printf("2 - Alterar dados do medico \n");
		printf("3 - Consultar medico \n"); 
		printf("4 - Remover medico \n");
		printf("5 - Listar todos os medicos\n");
		printf("6 - Sair\n");
		printf("Resposta: ");
		scanf("%d", &op);
		switch (op) {
		case 1:system("cls");
			printf("Informe o crm: ");
			scanf("%s", &crm);
			/*
			 while (validarcrm(crm) != 1) {
			 printf("crm invalido! Informe novamente: ");
			 scanf("%s", &crm);
			 }*/
			cadastrarMedico(arv, crm, arq);
			passeio(*arv);
			getch();
			break;
		case 2:system("cls");
			printf("Informe o crm: ");
			scanf("%s", &crm);
			/*while (validarcrm(crm) != 1) {
			printf("crm invalido! Informe novamente: ");
			scanf("%s", &crm);
			}*/
			//alterarMedico(arq, *arv, crm);
			break;
		case 3:system("cls");
			printf("Informe o crm: ");
			scanf("%s", &crm);
			/*while (validarcrm(crm) != 1) {
			printf("crm invalido! Informe novamente: ");
			scanf("%s", &crm);
			}*/
			 //exibirMedico(arq, *arv, crm);
			break;

		case 4:system("cls");
			printf("Informe o crm: ");
			scanf("%s", &crm);
			/*while (validarcrm(crm) != 1) {
			printf("crm invalido! Informe novamente: ");
			scanf("%s", &crm);
			}*/
			//removerMedico(arq, arv, crm);
			break;
		case 5:system("cls");
			listarMedicos(arq);
			getch();
			break;
		case 6:
			break;
		default: printf("\n\nOpcao invalida!\n\n");
		}
	} while (op != 6);
}
#endif // MEDICO