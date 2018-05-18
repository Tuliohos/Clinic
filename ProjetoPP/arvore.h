#include "types.h"

void inserirNo(TNoTree *novoNo, TNoTree **a);
TNoTree *novoNoArv(char cpf[], int pos);
int consultarNaArv(char cpf[], TNoTree *a);
void indexarCliente(TNoTree **a, FILE *arq);
void indexarMedico(TNoTree **a, FILE *arq);
void passeio(TNoTree *a);
void removerNoRecur(TNoTree **raiz, char cpf[]);
void removerNo(TNoTree **raiz);
TNoTree* maior(TNoTree **raiz);
void desindexar(TNoTree **raiz);