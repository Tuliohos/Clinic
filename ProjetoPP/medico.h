#include "types.h"
#include "arvore.h"
#include "arquivo.h"

void cadastrarMedico(TNoTree **a, char crm[], FILE *arq);
TMedico criaMedico(char crm[]);
TMedico horarioAtendimento();
void listarMedicos(FILE *arq);
void removerMedico(char crm[]);
void procurarEspecialidade(char especialidade[]);
void consultarMedicoPorNome(char nom[]);
void consultarMedicoporCRM(char crm[]);
void alterarDadosMedico(char crm[]);
