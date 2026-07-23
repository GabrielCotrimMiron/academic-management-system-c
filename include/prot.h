#ifndef PROT_H
#define PROT_H
#include <stdlib.h>

/* Structs do Projeto */

typedef struct
{
    int dia;
    int mes;
    int ano;
} td_data;

typedef struct
{
    int hora;
    int min;
} td_hora;

typedef struct
{
    int codigo_dis;
    char disciplina[100];
} td_disciplina;

typedef struct
{
    int ra;
    char nome[100];
    char email[100];
} td_aluno;

typedef struct
{
    int ra;
    int codigo_dis;   /* disciplina */
    td_data data_matricula;
    float notas[4];
} td_matricula;

typedef struct
{
    td_aluno aluno;
    td_hora horario;
    td_data data;
    char descricao[300];
} td_compromisso;

/* Protótipos */

/* Cadastro */
void cadastra_aluno(td_aluno [], int);
void cadastra_disciplina(td_disciplina [], int);
void cadastra_matricula(td_matricula [], int, td_aluno [], int, td_disciplina [], int);
void cadastra_compromisso(td_compromisso *, int *, td_aluno *, int);

/* Verificação */
int verifica_data(td_data *);
int verifica_horario(td_hora *);
int verifica_email(char []);

/* Busca e checagem */
int encontra_aluno(td_aluno *, int, int);
int encontra_disciplina(td_disciplina *, int, int);
int procura_data(td_compromisso *, int, td_data *, int);
int procura_horario(td_compromisso *, int, td_hora *, td_data *, int);
void imprime_vetor_de_alunos(td_aluno [], int);

/* Alocação / realocação */
void* alocar_vetor(size_t, int);
void* realocar_vetor(void *, size_t, int);

td_aluno* realoca_aluno(td_aluno *, int *);
td_disciplina* realoca_disciplina(td_disciplina *, int *);
td_matricula* realoca_matricula(td_matricula *, int *);
td_compromisso* realoca_compromisso(td_compromisso *, int *);

#endif
