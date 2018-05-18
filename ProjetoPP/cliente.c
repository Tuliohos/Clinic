#include "cliente.h" 

void cadastrar(char cpf[], TNoTree **a, FILE *arq) { //Procedimendo de cadastrar novo cliente
	TNoTree *novoNo;
	TCliente novoCliente;
	int posicao, status, consulta;

	if (*a == NULL) {
		novoCliente = criaCliente(cpf);
		fseek(arq, 0, 0);
		status = fwrite(&novoCliente, sizeof(TCliente), 1, arq);
		if (status != 1) {
			printf("Erro na gravacao do contato no arquivo!\n");
			getch();
			return;
		}
		posicao = ftell(arq) / sizeof(TCliente) - 1;
		novoNo = novoNoArv(cpf, posicao);
		*a = novoNo;
	}
	else {
		consulta = consultarNaArv(cpf, *a);
		if (consulta != -1) {
			printf("Ja existe um cliente cadastrado com esse CPF!\n");
			getch();
			return;
		}
		novoCliente = criaCliente(cpf);
		fseek(arq, 0, 2);
		status = fwrite(&novoCliente, sizeof(TCliente), 1, arq);
		if (status != 1) {
			printf("Erro na gravacao do contato no arquivo!\n");
			getch();
			return;
		}
		posicao = ftell(arq) / sizeof(TCliente) - 1;
		novoNo = novoNoArv(cpf, posicao);
		inserirNo(novoNo, &(*a));
	}
}

TCliente criaCliente(char cpf[]) { //Função para preencher a struct cliente
	TCliente novo;

	strcpy(novo.cpf, cpf);
	printf("Sobre os dados do cliente, informe: \n\n");
	printf("Nome: ");
	fflush(stdin);
	gets(novo.nome);
	while (validaNome(novo.nome) != 1) {
		printf("Nome invalido!\n Informe-o novamente: ");
		gets(novo.nome);
	}
	strupr(novo.nome);
	printf("Telefone: ");
	scanf("%s", &novo.telefone);
	while (validaTel(novo.telefone) != 1) {
		printf("Telefone invalido!\n Informe-o novamente: ");
		scanf("%s", &novo.telefone);
	}
	printf("E-mail: ");
	scanf("%s", &novo.email);
	while (validaEmail(novo.email) != 1) {
		printf("Email invalido!\n Informe-o novamente: ");
		scanf("%s", &novo.email);
	}
	novo.status = 1;
	return novo;
}

void listarTodos(FILE *arq) {
	TCliente aux;
	int flag = 0;
	fseek(arq, 0, 0);
	while (1) {
		if (fread(&aux, sizeof(TCliente), 1, arq) != 1) {
			if (!feof(arq)) {
				printf("Erro na leitura do arquivo!\n");
				getch();
			}
			break;
		}
		if (aux.status == 1) {
			flag = 1;
			printf("\nNome: %s", aux.nome);
			printf("\nCPF: %s", aux.cpf);
			printf("\nTelefone: %s", aux.telefone);
			printf("\nE-mail: %s\n\n", aux.email);
		}
	}
	if (flag == 0) {
		printf("\n\nO arquivo esta vazio!\n\n");
		getch();
	}
}

void alterar(FILE *arq, TNoTree *a, char cpf[]){
	TCliente aux;
	int pos, resp;

	pos = consultarNaArv(cpf, a);
	if (pos == -1) {
		printf("Cliente nao encontrado!\n");
		getch();
		return;
	}
	else {
		fseek(arq, pos * sizeof(TCliente), 0);
		if (fread(&aux, sizeof(TCliente), 1, arq) != 1) {
			printf("Erro de leitura!\n");
			getch();
			return;
		}
		do {
			system("cls");
			menuAlterar();
			scanf("%d", &resp);
			switch (resp) {
			case 1: printf("Informe o novo nome: ");
				gets(aux.nome);
				while (validaNome(aux.nome) != 1) {
					printf("Nome invalido!\n Informe-o novamente: ");
					gets(aux.nome);
				}
				strupr(aux.nome);
				break;
			case 2: printf("Informe o novo telefone: ");
				scanf("%s", &aux.telefone);
				while (validaTel(aux.telefone) != 1) {
					printf("Telefone invalido!\n Informe-o novamente: ");
					scanf("%s", &aux.telefone);
				}
				break;
			case 3: printf("Informe o novo e-mail: ");
				scanf("%s", &aux.email);
				while (validaEmail(aux.email) != 1) {
					printf("E-mail invalido!\n Informe-o novamente: ");
					scanf("%s", &aux.email);
				}
				break;
			case 4: break;
			default: printf("Opcao invalida.");
				getch();
			}
		} while (resp != 4);
		fseek(arq, pos * sizeof(TCliente), 0);
		if (fwrite(&aux, sizeof(TCliente), 1, arq) != 1) {
			printf("Erro na gravacao dos novo dados no arquivo!\n");
			getch();
			return;
		}
	}
}

void exibirCliente(FILE* arq, TNoTree *a,char cpf[]) {
	TCliente aux;
	int pos;

	pos = consultarNaArv(cpf, a);
	if (pos == -1) {
		printf("Cliente nao encontrado!\n");
		getch();
		return;
	}
	else {
		fseek(arq, pos * sizeof(TCliente), 0);
		if (fread(&aux, sizeof(TCliente), 1, arq) != 1) {
			printf("Erro de leitura!\n");
			getch();
			return;
		}
		if (aux.status != 0) {
			printf("\nNome: %s", aux.nome);
			printf("\nCPF: %s", aux.cpf);
			printf("\nTelefone: %s", aux.telefone);
			printf("\nE-mail: %s\n\n", aux.email);
		}
		else {
			printf("Cliente nao encontrado!\n");
			getch();
		}

	}
}

void menuAlterar() {
	printf("\n\nDigite: \n");
	printf("1- Alterar nome;\n");
	printf("2- Alterar telefone;\n");
	printf("3- Alterar email;\n");
	printf("4- Finalizar alteracao;\n");
	printf("Resposta: ");
}

void removerCliente(FILE *arq, TNoTree **a, char cpf []) {
	TCliente remover;
	int pos;

	pos = consultarNaArv(cpf, *a);
	if (pos == -1) {
		printf("Contato nao encontrado!\n");
		getch();
		return;
	}
	fseek(arq, pos * sizeof(TCliente), 0);
	if (fread(&remover, sizeof(TCliente), 1, arq) != 1) {
		printf("Erro ao ler o arquivo!\n");
		getch();
		return;
	}
	else {
		remover.status = 0;
		fseek(arq,pos * sizeof(TCliente), 0);
		if (fwrite(&remover,sizeof(TCliente), 1, arq) != 1) {
			printf("Erro ao escrever dados no arquivo!\n");
			getch();
			return;
		}
		printf("\n\nCliente removido com sucesso!\n\n");
		getch();
	}
	//passeio(*a);
	removerNoRecur(a, cpf);
}

