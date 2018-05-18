#include "arvore.h"
#include <string.h>

void inserirNo(TNoTree *novoNo, TNoTree **a) {
	TNoTree *aux = *a;

	if (aux == NULL) {
		*a = novoNo;
		return;
	}
	else if (strcmp(novoNo->info, aux->info) > 0) {
		inserirNo(novoNo, &aux->dir);
	}
	else {
		inserirNo(novoNo, &aux->esq);
	}
}

TNoTree *novoNoArv(char info[], int pos) {
	TNoTree *novo;
	novo = (TNoTree*)malloc(sizeof(TNoTree));
	novo->esq = NULL;
	novo->dir = NULL;
	strcpy(novo->info, info);
	novo->pos = pos;
	return novo;
}

 int consultarNaArv(char info[], TNoTree *a) { //Função consultar cliente na árvore
	if (a == NULL){
		return -1;
	}
	if (strcmp(info,a->info) == 0) {
		return a->pos;
	}
	else if (strcmp(info, a->info) > 0) {
		return consultarNaArv(info, a->dir);
	}
	else {
		return consultarNaArv(info, a->esq);
	}
}

 void indexarCliente(TNoTree **a, FILE *arq) {
	 TCliente aux;
	 TNoTree *no;
	 int pos;
	 fseek(arq, 0, 0);

	 while (1) {
		 if (fread(&aux, sizeof(TCliente), 1, arq) != 1) {
			 if (!feof(arq)) {
				 printf("Erro na leitura do arquivo!\n");
				 getch();
				 return;
			 }
			 break;
		 }
		 pos = ftell(arq) / sizeof(TCliente) - 1;
		 if (aux.status == 1) {
			 no = novoNoArv(aux.cpf, pos);
			 inserirNo(no, a);
		 }
	 }
 }

 void indexarMedico(TNoTree **a, FILE *arq) {
	 TMedico aux;
	 TNoTree *no;
	 int pos;
	 fseek(arq, 0, 0);

	 while (1) {
		 if (fread(&aux, sizeof(TMedico), 1, arq) != 1) {
			 if (!feof(arq)) {
				 printf("Erro na leitura do arquivo!\n");
				 getch();
				 return;
			 }
			 break;
		 }
		 pos = ftell(arq) / sizeof(TMedico) - 1;
		 if (aux.status == 1) {
			 no = novoNoArv(aux.crm, pos);
			 inserirNo(no, a);
		 }
	 }
 }

void passeio(TNoTree *a) {
	 if (a == NULL) {
		 return;
	 }
	 else {
		 passeio(a->esq);
		 printf("\n\n%s\n\n", a->info);
		 passeio(a->dir);
	 }
 }

 void removerNoRecur(TNoTree **raiz, char info[]) {
	 if (*raiz == NULL) {
		 printf("Contato nao encontrado na arvore!\n");
		 return;
	 }
	 else if (strcmp((*raiz)->info, info) == 0) {
		 removerNo(raiz);
	 }
	 else {
		 if (strcmp(info, (*raiz)->info) > 0) {
			 removerNoRecur(&((*raiz)->dir), info);
		 }
		 else
			 removerNoRecur(&((*raiz)->esq), info);
	 }
 }

 void removerNo(TNoTree **raiz) {
	 TNoTree* aux;
	 aux = *raiz;
	 if ((*raiz)->esq == NULL && (*raiz)->dir == NULL) { // Não tem filhos
		 *raiz = NULL;
	 }
	 else if ((*raiz)->esq == NULL) { // Não tem filho a esquerda
		 *raiz = (*raiz)->dir;
	 }
	 else if ((*raiz)->dir == NULL) { // Não tem filho a direita
		 *raiz = (*raiz)->esq;
	 }
	 else { // Tem ambos os filhos
		 aux = maior(&((*raiz)->esq));
		 strcpy((*raiz)->info, aux->info);
		 (*raiz)->pos = aux->pos;
	 }
	 free (aux);
 }

 TNoTree* maior(TNoTree **raiz){
	 TNoTree * aux;
	 aux = *raiz;
	 if (aux->dir == NULL){
		 *raiz = (*raiz)->esq;
		 return (aux);
	 }
	 else {
		 return maior(&((*raiz)->dir));
	 }
 }

 void desindexar(TNoTree **raiz){
	 if (*raiz == NULL) {
		 return;
	 }
	 desindexar(&((*raiz)->esq));
	 desindexar(&((*raiz)->dir));
	 free(*raiz);
 }