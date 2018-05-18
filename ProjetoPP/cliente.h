#include "types.h"
#include "arquivo.h"
#include "arvore.h"
#include "validacao.h"

void cadastrar(char cpf[], TNoTree **a, FILE *arq);
TCliente criaCliente(char cpf[]);
void listarTodos(FILE *arq);
void alterar(FILE* arq, TNoTree *a, char cpf[]);
void menuAlterar();
void exibirCliente(FILE* arq, TNoTree *a, char cpf[]);
void removerCliente(FILE *arq, TNoTree **a, char cpf[]);
