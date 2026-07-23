#include "prot.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* compara data+hora */
static int cmp_data_hora(const void *pa, const void *pb)
{
    const td_compromisso *a = (const td_compromisso *)pa;
    const td_compromisso *b = (const td_compromisso *)pb;

    if (a->data.ano != b->data.ano) return a->data.ano - b->data.ano;
    if (a->data.mes != b->data.mes) return a->data.mes - b->data.mes;
    if (a->data.dia != b->data.dia) return a->data.dia - b->data.dia;
    if (a->horario.hora != b->horario.hora) return a->horario.hora - b->horario.hora;
    return a->horario.min - b->horario.min;
}

/* compara RA, depois data+hora */
static int cmp_ra_data_hora(const void *pa, const void *pb)
{
    const td_compromisso *a = (const td_compromisso *)pa;
    const td_compromisso *b = (const td_compromisso *)pb;

    if (a->aluno.ra != b->aluno.ra) return a->aluno.ra - b->aluno.ra;
    return cmp_data_hora(pa, pb);
}

/* compara hora+minuto, depois RA */
static int cmp_hora_ra(const void *pa, const void *pb)
{
    const td_compromisso *a = (const td_compromisso *)pa;
    const td_compromisso *b = (const td_compromisso *)pb;

    if (a->horario.hora != b->horario.hora) return a->horario.hora - b->horario.hora;
    if (a->horario.min != b->horario.min) return a->horario.min - b->horario.min;
    return a->aluno.ra - b->aluno.ra;
}

/* compara data+hora e depois RA */
static int cmp_data_hora_ra(const void *pa, const void *pb)
{
    int r = cmp_data_hora(pa, pb);
    if (r != 0) return r;
    const td_compromisso *a = (const td_compromisso *)pa;
    const td_compromisso *b = (const td_compromisso *)pb;
    return a->aluno.ra - b->aluno.ra;
}

/* imprime um compromisso em formato legível */
static void print_compromisso(const td_compromisso *c)
{
    printf("\nRA:%d | %02d/%02d/%04d %02d:%02d | %s\n",
           c->aluno.ra,
           c->data.dia, c->data.mes, c->data.ano,
           c->horario.hora, c->horario.min,
           c->descricao);
}

/* Função auxiliar para qsort de alunos por RA */
static int cmp_alunos_ra(const void *pa, const void *pb)
{
    const td_aluno *a = (const td_aluno *)pa;
    const td_aluno *b = (const td_aluno *)pb;
    return a->ra - b->ra;
}

void menu(td_aluno **alunos_ptr, int *contar_aluno, int *dim_aluno,
          td_disciplina **disciplinas_ptr, int *contar_disci, int *dim_disci,
          td_matricula **matriculas_ptr, int *contar_matr, int *dim_matr,
          td_compromisso **compromissos_ptr, int *contar_comp, int *dim_comp)
{
    int opc = 0;

    for (;;)
    {
        printf("\n===== MENU =====\n");
        printf("1 - cadastrar aluno\n");
        printf("2 - cadastrar disciplina\n");
        printf("3 - cadastrar matricula\n");
        printf("4 - cadastrar compromisso\n");
        printf("5 - imprimir compromissos\n");
        printf("6 - imprimir dados de um aluno\n");
        printf("7 - imprimir dados de todos os alunos\n");
        printf("8 - sair\n");
        printf("Escolha: ");

        if (scanf("%d", &opc) != 1)
        {
            /* entrada inválida: limpa linha e repete */
            while (getchar() != '\n' && !feof(stdin));
            printf("\nEntrada invalida. Tente novamente.\n");
            continue;
        }
        while (getchar() != '\n' && !feof(stdin)); /* consome resto da linha */

        switch (opc)
        {
        case 1:   /* cadastrar aluno */
        {
            if (*contar_aluno >= *dim_aluno)
            {
                td_aluno *tmp = realoca_aluno(*alunos_ptr, dim_aluno);
                if (!tmp)
                {
                    printf("\nErro: falha ao realocar vetor de alunos.\n");
                    break;
                }
                *alunos_ptr = tmp;
            }
            cadastra_aluno(*alunos_ptr, *contar_aluno);
            (*contar_aluno)++;
            break;
        }

        case 2:   /* cadastrar disciplina */
        {
            if (*contar_disci >= *dim_disci)
            {
                td_disciplina *tmp = realoca_disciplina(*disciplinas_ptr, dim_disci);
                if (!tmp)
                {
                    printf("\nErro: falha ao realocar vetor de disciplinas.\n");
                    break;
                }
                *disciplinas_ptr = tmp;
            }
            cadastra_disciplina(*disciplinas_ptr, *contar_disci);
            (*contar_disci)++;
            break;
        }

        case 3:   /* cadastrar matrícula */
        {
            if (*contar_matr >= *dim_matr)
            {
                td_matricula *tmp = realoca_matricula(*matriculas_ptr, dim_matr);
                if (!tmp)
                {
                    printf("\nErro: falha ao realocar vetor de matriculas.\n");
                    break;
                }
                *matriculas_ptr = tmp;
            }
            cadastra_matricula(*matriculas_ptr, *contar_matr, *alunos_ptr, *contar_aluno, *disciplinas_ptr, *contar_disci);
            (*contar_matr)++;
            break;
        }

        case 4:   /* cadastrar compromisso */
        {
            if (*contar_comp >= *dim_comp)
            {
                td_compromisso *tmp = realoca_compromisso(*compromissos_ptr, dim_comp);
                if (!tmp)
                {
                    printf("\nErro: falha ao realocar vetor de compromissos.\n");
                    break;
                }
                *compromissos_ptr = tmp;
            }
            cadastra_compromisso(*compromissos_ptr, contar_comp, *alunos_ptr, *contar_aluno);
            break;
        }

        case 5:   /* imprimir compromissos (submenu) */
        {
            if (*contar_comp == 0)
            {
                printf("\nNenhum compromisso cadastrado.\n");
                break;
            }

            printf("\n--- Imprimir compromissos ---\n");
            printf("a - de um aluno (ordenado por data e hora)\n");
            printf("b - de todos os alunos (ordenado por ra,data,hora)\n");
            printf("c - de uma data (ordenado por hora e ra)\n");
            printf("d - de todas as datas (ordenado por data,hora,ra)\n");
            printf("Escolha (a/b/c/d): ");

            char line[64];
            if (!fgets(line, sizeof(line), stdin)) line[0] = '\0';
            char optc = (line[0] != '\0') ? (char)tolower((unsigned char)line[0]) : '\0';

            /* copia dos compromissos para ordenar sem destruir o original */
            td_compromisso *tmp = malloc((size_t)(*contar_comp) * sizeof(td_compromisso));
            if (!tmp)
            {
                printf("\nErro: memoria insuficiente.\n");
                break;
            }
            memcpy(tmp, *compromissos_ptr, (size_t)(*contar_comp) * sizeof(td_compromisso));

            switch (optc)
            {
            case 'a':
            {
                int ra;
                printf("\nInforme RA do aluno: ");
                if (scanf("%d", &ra) != 1)
                {
                    while (getchar()!='\n');
                    printf("\nEntrada invalida.\n");
                    free(tmp);
                    break;
                }
                while (getchar()!='\n');

                td_compromisso *f = malloc((size_t)(*contar_comp) * sizeof(td_compromisso));
                if (!f)
                {
                    printf("\nErro: memoria.\n");
                    free(tmp);
                    break;
                }
                int fn = 0;
                for (int i = 0; i < *contar_comp; i++) if (tmp[i].aluno.ra == ra) f[fn++] = tmp[i];
                if (fn == 0)
                {
                    printf("\nNenhum compromisso para o RA %d.\n", ra);
                    free(f);
                    free(tmp);
                    break;
                }
                qsort(f, fn, sizeof(td_compromisso), cmp_data_hora);
                printf("\n-- Compromissos do RA %d --\n", ra);
                for (int i = 0; i < fn; i++) print_compromisso(&f[i]);
                free(f);
                break;
            }

            case 'b':
            {
                qsort(tmp, *contar_comp, sizeof(td_compromisso), cmp_ra_data_hora);
                printf("\n-- Compromissos de todos (ordenado por RA,data,hora) --\n");
                for (int i = 0; i < *contar_comp; i++) print_compromisso(&tmp[i]);
                break;
            }

            case 'c':
            {
                int d,m,a;
                printf("\nInforme data (dd mm aaaa): ");
                if (scanf("%d %d %d", &d, &m, &a) != 3)
                {
                    while (getchar()!='\n');
                    printf("\nEntrada invalida.\n");
                    free(tmp);
                    break;
                }
                while (getchar()!='\n');

                td_compromisso *f = malloc((size_t)(*contar_comp) * sizeof(td_compromisso));
                if (!f)
                {
                    printf("\nErro: memoria.\n");
                    free(tmp);
                    break;
                }
                int fn = 0;
                for (int i = 0; i < *contar_comp; i++)
                {
                    if (tmp[i].data.dia == d && tmp[i].data.mes == m && tmp[i].data.ano == a) f[fn++] = tmp[i];
                }
                if (fn == 0)
                {
                    printf("\nNenhum compromisso nessa data %02d/%02d/%04d.\n", d,m,a);
                    free(f);
                    free(tmp);
                    break;
                }
                qsort(f, fn, sizeof(td_compromisso), cmp_hora_ra);
                printf("\n-- Compromissos em %02d/%02d/%04d --\n", d,m,a);
                for (int i = 0; i < fn; i++) print_compromisso(&f[i]);
                free(f);
                break;
            }

            case 'd':
            {
                qsort(tmp, *contar_comp, sizeof(td_compromisso), cmp_data_hora_ra);
                printf("\n-- Compromissos todas as datas (ordenado por data,hora,ra) --\n");
                for (int i = 0; i < *contar_comp; i++) print_compromisso(&tmp[i]);
                break;
            }

            default:
                printf("\nOpcao invalida no submenu.\n");
                break;
            }

            free(tmp);
            break;
        }

        case 6:   /* imprimir dados de um aluno */
        {
            int ra;
            printf("\nInforme RA do aluno: ");
            if (scanf("%d", &ra) != 1)
            {
                while (getchar()!='\n');
                printf("\nEntrada invalida.\n");
                break;
            }
            while (getchar()!='\n');
            int pos = encontra_aluno(*alunos_ptr, *contar_aluno, ra);
            if (pos == -1) printf("\nAluno RA %d nao encontrado.\n", ra);
            else
            {
                td_aluno *a = &(*alunos_ptr)[pos];
                printf("\n--- Dados do Aluno ---\nRA: %d\nNome: %s\nEmail: %s\n", a->ra, a->nome, a->email);
            }
            break;
        }

    case 7:   /* imprimir todos os alunos ordenado por RA */
        {
            if (*contar_aluno == 0)
            {
                printf("\nNenhum aluno cadastrado.\n");
                break;
            }
            td_aluno *copy = malloc((size_t)(*contar_aluno) * sizeof(td_aluno));
            if (!copy)
            {
                printf("\nErro: memoria.\n");
                break;
            }
            memcpy(copy, *alunos_ptr, (size_t)(*contar_aluno) * sizeof(td_aluno));

            /* CORREÇÃO: Usando qsort ao invés do for loop manual */
            qsort(copy, *contar_aluno, sizeof(td_aluno), cmp_alunos_ra);

            printf("\n-- Lista de Alunos (ordenado por RA) --\n");
            for (int i = 0; i < *contar_aluno; i++)
                printf("\nRA:%d | Nome: %s | Email: %s\n", copy[i].ra, copy[i].nome, copy[i].email);
            free(copy);
            break;
        }

        case 8:
            printf("\nSaindo do menu.\n");
            return;

        default:
            printf("\nOpcao invalida. Tente novamente.\n");
            break;
        } /* fim switch */
    } /* fim loop */
}
