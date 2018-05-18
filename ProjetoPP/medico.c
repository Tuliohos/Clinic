#include "medico.h"
#include "validacao.h"

void cadastrarMedico(TNoTree **a, char crm[], FILE *arq) {
	TNoTree *novoNo;
	TMedico novoMedico;
	int posicao, status, consulta;

	if (*a == NULL) {
		novoMedico = criaMedico(crm);
		fseek(arq, 0, 0);
		status = fwrite(&novoMedico, sizeof(TMedico), 1, arq);
		if (status != 1) {
			printf("Erro na gravacao do medico no arquivo!\n");
			return;
		}
		posicao = ftell(arq) / sizeof(TMedico) - 1;
		novoNo = novoNoArv(crm, posicao);
		*a = novoNo;
	}
	else {
		consulta = consultarNaArv(crm, *a);
		if (consulta != -1) {
			printf("Ja existe um medico cadastrado com esse CRM!\n");
			return;
		}
		novoMedico = criaMedico(crm);
		fseek(arq, 0, 2);
		status = fwrite(&novoMedico, sizeof(TMedico), 1, arq);
		if (status != 1) {
			printf("Erro na gravacao do medico no arquivo!\n");
			return;
		}
		posicao = ftell(arq) / sizeof(TMedico) - 1;
		novoNo = novoNoArv(crm, posicao);
		inserirNo(novoNo, a);
	}
}
TMedico criaMedico(char crm[]) {
	TMedico medico;
	char op;

	medico = horarioAtendimento();
	system("cls");
	strcpy(medico.crm, crm);
	printf("\nSobre os dados do medico, informe: \n\n");
	printf("Nome: ");
	setbuf(stdin, NULL);
	gets(medico.nome);
	setbuf(stdin, NULL);
	while (validaNome(medico.nome) != 1) {
		printf("Nome invalido!\n Informe-o novamente: ");
		setbuf(stdin, NULL);
		gets(medico.nome);
	}
	strupr(medico.nome);
	printf("Telefone: ");
	scanf("%s", &(medico.telefone));
	while (validaTel(medico.telefone) != 1) {
		printf("Telefone invalido!\n Informe-o novamente: ");
		scanf("%s", &medico.telefone);
	}
	printf("E-mail: ");
	scanf("%s", &(medico.email));
	while (validaEmail(medico.email) != 1) {
		printf("Email invalido!\n Informe-o novamente: ");
		scanf("%s", &medico.email);
	}

	medico.status = 1;

	system("cls");
	printf("~~~~~~~~~~~~~~~ LISTA DE ESPECIALIDADES ~~~~~~~~~~~~~~~\n\n");
	printf("1- \tCancerologia\n");
	printf("2- \tCardiologia\n");
	printf("3- \tCirurgia em geral\n");
	printf("4- \tPediatria\n");
	printf("5- \tDermatologia\n");
	printf("6- \tUrologia\n");
	printf("7- \tGinecologia\n");
	printf("8- \tOftalmologia\n");
	printf("9- \tPsiquiatria\n");
	printf("10-\tObstreticia\n\n");
	fflush(stdin);
	printf("Informe o numero correspondente a especialidade: ");
	scanf("%c", &op);
	switch (op){
	case '1': strcpy(medico.especialidade, "CANCEROLOGIA");
		break;
	case '2': strcpy(medico.especialidade, "CARDIOLOGIA");
		break;
	case '3': strcpy(medico.especialidade, "CIRURGIA EM GERAL");
		break;
	case '4': strcpy(medico.especialidade, "PEDIATRIA");
		break;
	case '5': strcpy(medico.especialidade, "DERMATOLOGIA");
		break;
	case '6': strcpy(medico.especialidade, "UROLOGIA");
		break;
	case '7': strcpy(medico.especialidade, "GINECOLOGIA");
		break;
	case '8': strcpy(medico.especialidade, "OFTALMOLOGIA");
		break;
	case '9': strcpy(medico.especialidade, "PSIQUIATRIA");
		break;
	case '10': strcpy(medico.especialidade, "OBSTETRICIA");
		break;
	default:fflush(stdin);
		printf("Opcao invalida! Informe o numero correspondente a especialidade desejada: ");
		op = getchar();
		break;
	}
	return medico;
}
TMedico horarioAtendimento() {
	TMedico medico;
	char resp;
	int turno, dia, lin, col, flag = 0;

	medico.horarioAtendimento[0][0] = " ";
	medico.horarioAtendimento[0][1] = "SEGUNDA";
	medico.horarioAtendimento[0][2] = "TERCA";
	medico.horarioAtendimento[0][3] = "QUARTA";
	medico.horarioAtendimento[0][4] = "QUINTA";
	medico.horarioAtendimento[0][5] = "SEXTA";
	medico.horarioAtendimento[1][0] = "MANHA";
	medico.horarioAtendimento[2][0] = "TARDE";

	for (lin = 1; lin < 3; lin++) { //Linha 0 contém os dias da semana, portanto, o preenchimento com traços começa na linha 1
		for (col = 1; col < 6; col++) { // Coluna 0 contém os turnos (manhã e tarde), portanto, o preenchimentocom traços começa na coluna 1
			medico.horarioAtendimento[lin][col] = " - ";
		}
	}

	do {
		system("cls");
		printf("########## MENU DE CADASTRO DE HORARIO DE ATENDIMENTO ##########\n");
		fflush(stdin);
		printf("Digite 1 para cadastrar um novo horario. \nDigite 2 para sair do cadastro.\nResposta: ");
		resp = getchar();
		switch (resp) {
		case '1':
			printf("\nDigite 1 para inserir um horario no turno da manha.\n");
			printf("Digite 2 para inserir um horario no turno da tarde.\n");
			printf("Digite 3 para cancelar o processo de insercao de horario.\n");
			printf("Resposta: ");
			scanf("%d", &turno);
			while (turno < 1 || turno > 3) {
				printf("Informe apenas 1, 2 ou 3: ");
				scanf("%d", &turno);
			}
			if (turno == 1 || turno == 2) {
				flag = 1;
				printf("\nDigite: \n");
				printf("1 para segunda-feira.\n2 para terca-feira.\n3 para quarta-feira.\n4 para quinta-feira.\n5 para sexta-feira\nResposta: ");
				scanf("%d", &dia);
				while (dia < 1 || dia > 5) {
					printf("Por favor, insira somente numeros entre 1 e 5: ");
					scanf("%d", &dia);
				}
				medico.horarioAtendimento[turno][dia] = " X ";
			}
			break;

		case '2':if (flag == 0){
				printf("Impossivel sair sem ter cadastrado ao menos um horario!\n");
				resp = '0';
				}
			break;

		default: printf("Resposta invalida!");
			break;
		}
	} while (resp != '2');

	return medico;
}

void listarMedicos(FILE *arq) {
	TMedico aux;
	int flag = 0, lin, col;

	system("cls");
	fseek(arq, 0, 0);
	while (1) {
		if (fread(&aux, sizeof(TMedico), 1, arq) != 1) {
			if (!feof(arq)) {
				printf("Erro na leitura do arquivo!\n");
			}
			break;
		}
		if (aux.status == 1) {
			flag = 1;
			printf("\nNome: %s", aux.nome);
			printf("\nCRM: %s", aux.crm);
			printf("\nTelefone: %s", aux.telefone);
			printf("\nE-mail: %s\n", aux.email);
			printf("Especialidade: %s\n", aux.especialidade);
			printf("Tabela de horario de funcionamento: \n\n");
			for (lin = 0; lin < 3; lin++) {
				for (col = 0; col < 6; col++) {
					printf("%s\t", aux.horarioAtendimento[lin][col]);
				}
				printf("\n");
			}
		}
	}
	if (flag == 0) {
		printf("\n\nO arquivo esta vazio!\n\n");
	}
}
void removerMedico(char crm);
void procurarEspecialidade(char especialidade[]);
void consultarMedicoPorNome(char nom[]);
void consultarMedicoporCRM(char crm[]);
void alterarDadosMedico(char crm[]);
