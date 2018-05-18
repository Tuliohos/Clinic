#pragma once
#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define TAM_NOME 50
#define TAM_CPF 15
#define TAM_TEL 15
#define TAM_EMAIL 30
#define TAM_CRM 15
#define TAM_ESPECIALIDADE 15
#define TAM_INFO 15
#define QTD_LIN 3
#define QTD_COL 6


typedef struct NoTree {
	struct NoTree *esq;
	struct NoTree *dir;
	char info[TAM_INFO];
	int pos;
}TNoTree;

typedef struct Cliente {
	char cpf[TAM_CPF];
	char nome[TAM_NOME];
	char telefone[TAM_TEL];
	char email[TAM_EMAIL];
	int status;
}TCliente;

typedef struct Medico{
	char crm[TAM_CRM];
	char nome[TAM_NOME];
	char especialidade[TAM_ESPECIALIDADE];
	char *horarioAtendimento[QTD_LIN][QTD_COL];
	char telefone[TAM_TEL];
	char email[TAM_EMAIL];
	int status;
	int pos;
}TMedico;
