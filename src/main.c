#include "prot.h"
#include <stdio.h>
#include <stdlib.h>

/* Protótipo da função menu */
void menu(td_aluno **alunos_ptr, int *contar_aluno, int *dim_aluno,
          td_disciplina **disciplinas_ptr, int *contar_disci, int *dim_disci,
          td_matricula **matriculas_ptr, int *contar_matr, int *dim_matr,
          td_compromisso **compromissos_ptr, int *contar_comp, int *dim_comp);

int main(void)
{
    /* Dimensões iniciais */
    int dim_aluno = 10;
    int dim_disci = 10;
    int dim_matr  = 20;
    int dim_comp  = 15;

    /* Contadores*/
    int contar_aluno = 0;
    int contar_disci = 0;
    int contar_matr  = 0;
    int contar_comp  = 0;

    /* Alocações iniciais */
    td_aluno *alunos = (td_aluno*) alocar_vetor(sizeof(td_aluno), dim_aluno);
    if (!alunos)
    {
        fprintf(stderr, "\nErro: falha ao alocar vetor de alunos.\n");
        return 1;
    }

    td_disciplina *disciplinas = (td_disciplina*) alocar_vetor(sizeof(td_disciplina), dim_disci);
    if (!disciplinas)
    {
        free(alunos);
        fprintf(stderr, "\nErro: falha ao alocar vetor de disciplinas.\n");
        return 1;
    }

    td_matricula *matriculas = (td_matricula*) alocar_vetor(sizeof(td_matricula), dim_matr);
    if (!matriculas)
    {
        free(alunos);
        free(disciplinas);
        fprintf(stderr, "\nErro: falha ao alocar vetor de matriculas.\n");
        return 1;
    }

    td_compromisso *compromissos = (td_compromisso*) alocar_vetor(sizeof(td_compromisso), dim_comp);
    if (!compromissos)
    {
        free(alunos);
        free(disciplinas);
        free(matriculas);
        fprintf(stderr, "\nErro: falha ao alocar vetor de compromissos.\n");
        return 1;
    }

    printf("\nProjeto ALG2 - iniciando menu.\n");

    /* Chama o menu principal. Menu pode realocar vetores (por isso passamos ponteiros para ponteiros). */
    menu(&alunos, &contar_aluno, &dim_aluno,
         &disciplinas, &contar_disci, &dim_disci,
         &matriculas, &contar_matr, &dim_matr,
         &compromissos, &contar_comp, &dim_comp);

    /* Ao sair do menu, libera a memória */
    free(alunos);
    alunos = NULL;
    free(disciplinas);
    disciplinas = NULL;
    free(matriculas);
    matriculas = NULL;
    free(compromissos);
    compromissos = NULL;

    printf("\nMemoria liberada. Programa encerrado.\n");
    return 0;
}
