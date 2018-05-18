#include "types.h"
int posicaoCliente(char cpf[], FILE *arq);
int posicaoMedico(char crm[], FILE *arq);
void manutencaoCliente(FILE *arq);
void manutencaoMedico(FILE *arq);
int pesquisarPorNome(FILE *arq, char nome[]);
FILE* abrirArquivoCliente();
FILE* abrirArquivoMedico();