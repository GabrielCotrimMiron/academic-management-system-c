    #include "prot.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Para a validação de email

int leitura_sucesso;
int verifica_data(td_data *data_ptr)
{
    if (data_ptr->ano < 2000 || data_ptr->ano > 2030)
    {
        printf("\nERRO: Ano (%d) fora do intervalo razoavel (2000-2030).\n", data_ptr->ano);
        return 0;
    }
    if (data_ptr->mes < 1 || data_ptr->mes > 12)
    {
        printf("\nERRO: Mes (%d) invalido.\n", data_ptr->mes);
        return 0;
    }
    if (data_ptr->dia < 1 || data_ptr->dia > 31)
    {
        printf("\nERRO: Dia (%d) invalido (Max 31).\n", data_ptr->dia);
        return 0;
    }

    return 1;
}
int verifica_horario(td_hora *hora_ptr)
{
    if (hora_ptr->hora < 0 || hora_ptr->hora > 23)
    {
        printf("\nERRO: Hora (%d) deve ser entre 0 e 23.\n", hora_ptr->hora);
        return 0;
    }
    if (hora_ptr->min < 0 || hora_ptr->min > 59)
    {
        printf("\nERRO: Minuto (%d) deve ser entre 0 e 59.\n", hora_ptr->min);
        return 0;
    }
    return 1;
}

int verifica_email(char email[])
{
    int i;
    int contar_arroba = 0;
    int contar_ponto = 0;
    int pos_arroba = -1; // Variável para rastrear a posição do '@'
    int len = strlen(email);

    // 1. Checagem de caracteres e contagem
    for (i = 0; i < len; i++)
    {
        if (email[i] == '@')
        {
            contar_arroba++;
            pos_arroba = i; // Armazena a posição do '@'
        }
        else if (email[i] == '.')
        {
            contar_ponto++;
        }
        else if (!isalnum(email[i]) && email[i] != '_')
        {
            // Regra: Não pode ter caracteres especiais (exceto @, . e _)
            printf("\nERRO Email: Caractere '%c' nao permitido (exceto @, . e _).\n", email[i]);
            return 0;
        }
    }

    // 2. Checagem de quantidade
    if (contar_arroba != 1)
    {
        printf("\nERRO Email: Deve possuir exatamente um '@'.\n");
        return 0;
    }
    if (contar_ponto == 0)
    {
        printf("\nERRO Email: Deve possuir ao menos um '.'.\n");
        return 0;
    }

    // 3. Checagem de estrutura

    // a) O '@' não pode ser o primeiro ou o último caractere.
    if (pos_arroba == 0 || pos_arroba == len - 1)
    {
        printf("\nERRO Email: O '@' nao pode ser o primeiro ou o ultimo caractere.\n");
        return 0;
    }

    // b) O último caractere não pode ser um ponto
    if (email[len - 1] == '.')
    {
        printf("\nERRO Email: Nao pode terminar com ponto ('.').\n");
        return 0;
    }

    // c) NÃO PODE tera um ponto imediatamente após o arroba

    if (email[pos_arroba + 1] == '.')
    {
        printf("\nERRO Email: Caractere '.' logo apos o '@' e proibido (dominio vazio).\n");
        return 0;
    }

    // d) Deve haver pelo menos um ponto APÓS o arroba
    int ponto_depois_arroba = 0;
    for (i = pos_arroba + 1; i < len; i++)
    {
        if (email[i] == '.')
        {
            ponto_depois_arroba = 1;
            break;
        }
    }

    if (ponto_depois_arroba == 0)
    {
        printf("\nERRO Email: Deve haver um ponto ('.') no dominio (apos o '@').\n");
        return 0;
    }

    return 1; // Email correto
}

int encontra_aluno(td_aluno *vetor_aluno, int dimensao, int ra_procurado)
{
    for (int i = 0; i < dimensao; i++)
    {
        // Se o vetor estiver cheio de zeros (calloc), a busca para.
        if (vetor_aluno[i].ra == 0 && i > 0) break;
        if (vetor_aluno[i].ra == ra_procurado)
        {
            return i;
        }
    }
    return -1;
}
int encontra_disciplina(td_disciplina *vetor_disci, int dimensao, int codigo_procurado)
{
    for (int i = 0; i < dimensao; i++)
    {
        if (vetor_disci[i].codigo_dis == codigo_procurado)
        {
            return i;
        }
    }
    return -1;
}

void cadastra_aluno(td_aluno str_aluno[], int posicao)
{
    td_aluno aluno_div;
    char temp_email[100]; // Buffer para validação

    printf("\n--- Cadastro de Aluno ---\n");
    printf("\nEm respeito do aluno, informe:\n");

    do
    {
        printf("\nRA (inteiro):\n");

        leitura_sucesso = scanf("%i", &aluno_div.ra);

        if (leitura_sucesso != 1)
        {
            printf("\nERRO: Entrada invalida. Por favor, digite APENAS numeros inteiros.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        else if (aluno_div.ra <= 0)
        {
            printf("\nERRO: O RA deve ser um numero inteiro positivo.\n");
            leitura_sucesso = 0;
        }
    }
    while (leitura_sucesso != 1);   // Repete enquanto a leitura não for 1 (bem-sucedida)

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nO nome do aluno:\n");
    fgets(aluno_div.nome, 100, stdin);
    aluno_div.nome[strcspn(aluno_div.nome, "\n")] = 0;

    do
    {
        printf("\nO e-mail do aluno:\n");
        scanf("%s", temp_email);
        while ((c = getchar()) != '\n' && c != EOF); // Limpa buffer

        if (verifica_email(temp_email))
        {
            strcpy(aluno_div.email, temp_email);
            break;
        }
    }
    while (1);

    str_aluno[posicao] = aluno_div;
    printf("\nAluno '%s' cadastrado na posicao %d.\n", aluno_div.nome, posicao);
}

void cadastra_disciplina(td_disciplina str_disci[], int posicao)
{
    td_disciplina disciplina_div;

    printf("\n--- Cadastro de Disciplina ---\n");
    printf("\nEm respeito da disciplina, informe:\n");

      do
    {
        printf("\nO codigo (inteiro):\n");
        leitura_sucesso = scanf("%i", &disciplina_div.codigo_dis);
        if (leitura_sucesso != 1)
        {
            printf("\nERRO: Entrada invalida. Por favor, digite APENAS numeros inteiros.\n");

            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        else if (disciplina_div.codigo_dis <= 0)
        {
            printf("\nERRO: O Codigo da Disciplina deve ser um numero inteiro positivo.\n");
            leitura_sucesso = 0;
        }
    }
    while (leitura_sucesso != 1);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nO nome da disciplina:\n");
    fgets(disciplina_div.disciplina, 100, stdin);
    disciplina_div.disciplina[strcspn(disciplina_div.disciplina, "\n")] = 0;

    str_disci[posicao] = disciplina_div;
    printf("\nDisciplina '%s' cadastrada na posicao %d.\n", disciplina_div.disciplina, posicao);
}

void cadastra_matricula(td_matricula str_matr[], int posicao, td_aluno str_aluno[], int limite_aluno, td_disciplina str_disci[], int limite_disci)
{
    td_matricula matricula_div;
    int pos;
    char opcao_menu;

    printf("\n--- Cadastro de Matricula ---\n");
    do
    {
        printf("\nInforme o RA do aluno para a matricula (ou digite 0 para voltar ao menu):\n");
        scanf("%i", &matricula_div.ra);
        while (getchar() != '\n');

        if (matricula_div.ra == 0) return; // Retorna ao menu

        pos = encontra_aluno(str_aluno, limite_aluno, matricula_div.ra);

        if (pos != -1)
        {
            printf("\nAluno encontrado: %s.\n", str_aluno[pos].nome);
            break; // Sai do loop de validação
        }
        else
        {
            printf("\nERRO: RA %d nao encontrado.\n", matricula_div.ra);
        }
    }
    while (1);

    do
    {
        printf("\nInforme o CODIGO da disciplina para a matricula (ou digite 0 para voltar ao menu):\n");
        scanf("%i", &matricula_div.codigo_dis);
        while (getchar() != '\n');

        if (matricula_div.codigo_dis == 0) return; // Retorna ao menu

        pos = encontra_disciplina(str_disci, limite_disci, matricula_div.codigo_dis);

        if (pos != -1)
        {
            printf("\nDisciplina encontrada: %s.\n", str_disci[pos].disciplina);
            break;
        }
        else
        {
            printf("\nERRO: Codigo %d nao encontrado.\n", matricula_div.codigo_dis);
        }
    }
    while (1);

    do
    {
        printf("\nInforme a DATA da matricula (dd mm aaaa):\n");
        scanf("%i %i %i", &matricula_div.data_matricula.dia,
              &matricula_div.data_matricula.mes,
              &matricula_div.data_matricula.ano);
        while (getchar() != '\n');
    }
    while (!verifica_data(&matricula_div.data_matricula));

    printf("\nInforme as 4 notas do aluno:\n");
    for(int i = 0; i < 4; i++)
    {
        printf("\nNota %d:\n", i + 1);
        scanf("%f", &matricula_div.notas[i]);
    }

    // Copia a estrutura local para o vetor dinâmico
    str_matr[posicao] = matricula_div;
    printf("\nMatricula registrada na posicao %d.\n", posicao);
}


// Implementações das funções de checagem complexas (Compromisso)

int procura_data(td_compromisso *vetor_comp, int limite_comp, td_data *data_procurada, int ra_aluno)
{
    int contar = 0;
    for (int i = 0; i < limite_comp; i++)
    {
        if (vetor_comp[i].aluno.ra == ra_aluno &&
                vetor_comp[i].data.dia == data_procurada->dia &&
                vetor_comp[i].data.mes == data_procurada->mes &&
                vetor_comp[i].data.ano == data_procurada->ano)
        {
            contar++;
        }
    }
    // Retorna 1 se houver menos de dois (permite cadastro), 0 se já houver dois (bloqueia)
    return (contar < 2) ? 1 : 0;
}

int procura_horario(td_compromisso *vetor_comp, int limite_comp, td_hora *hora_procurada, td_data *data_procurada, int ra_aluno)
{
    for (int i = 0; i < limite_comp; i++)
    {
        if (vetor_comp[i].aluno.ra == ra_aluno &&
                vetor_comp[i].data.dia == data_procurada->dia &&
                vetor_comp[i].data.mes == data_procurada->mes &&
                vetor_comp[i].data.ano == data_procurada->ano)
        {

            if (vetor_comp[i].horario.hora == hora_procurada->hora &&
                    vetor_comp[i].horario.min == hora_procurada->min)
            {
                return 0;
            }
        }
    }
    return 1; // Retorna 1 se os horários não forem coincidentes (Permite cadastro)
}

void cadastra_compromisso(td_compromisso *vetor_comp, int *indice_comp, td_aluno *vetor_aluno, int limite_aluno)
{
    td_compromisso novo_comp;
    int ra_temp;
    int pos_aluno;

    printf("\n--- Cadastro de Compromisso ---\n");

    do
    {
        printf("\nInforme o RA do aluno para o compromisso (ou -1 para cancelar):\n");
        scanf("%i", &ra_temp);
        while (getchar() != '\n');

        if (ra_temp == -1) return; // Cancelar

        pos_aluno = encontra_aluno(vetor_aluno, limite_aluno, ra_temp);

        if (pos_aluno != -1)
        {
            printf("\nAluno encontrado: %s.\n", vetor_aluno[pos_aluno].nome);
            // Copia os dados do aluno para o compromisso
            novo_comp.aluno = vetor_aluno[pos_aluno];
            break;
        }
        else
        {
            printf("\nERRO: RA %d nao encontrado.\n", ra_temp);
        }
    }
    while (1);

    do
    {
        printf("\nInforme a DATA do compromisso (dd mm aaaa):\n");
        scanf("%i %i %i", &novo_comp.data.dia,
              &novo_comp.data.mes,
              &novo_comp.data.ano);
        while (getchar() != '\n');

        if (!verifica_data(&novo_comp.data)) continue; // Data inválida, repete
        if (!procura_data(vetor_comp, *indice_comp, &novo_comp.data, ra_temp))
        {
            printf("\nERRO: Aluno ja possui dois compromissos nesta data. Escolha outra data.\n");
            continue; // Repete o loop de data
        }
        break; // Data válida e menos de 2 compromissos
    }
    while (1);

    do
    {
        printf("\nInforme o HORARIO do compromisso (hh mm):\n");
        scanf("%i %i", &novo_comp.horario.hora, &novo_comp.horario.min);
        while (getchar() != '\n');

        if (!verifica_horario(&novo_comp.horario)) continue; // Horário inválido, repete
        if (!procura_horario(vetor_comp, *indice_comp, &novo_comp.horario, &novo_comp.data, ra_temp))
        {
            printf("\nERRO: Horario COINCIDENTE encontrado no mesmo dia. Escolha outro horario.\n");
            continue; // Repete o loop de horário
        }
        break; // Horário válido e não coincidente
    }
    while (1);

    // Cadastro da Descrição
    printf("\nInforme a descricao do compromisso:\n");
    fgets(novo_comp.descricao, 300, stdin);
    novo_comp.descricao[strcspn(novo_comp.descricao, "\n")] = 0;

    // Copia para o vetor e atualiza o índice
    vetor_comp[*indice_comp] = novo_comp;
    (*indice_comp)++;
    printf("\nCompromisso cadastrado com sucesso na posicao %d.\n", *indice_comp - 1);
}

void imprime_vetor_de_alunos(td_aluno alunos[], int contar)
{
    if (contar == 0)
    {
        printf("\nNenhum aluno cadastrado.\n");
        return;
    }
    printf("\n--- RELATORIO DE ALUNOS (%d TOTAL) ---\n", contar);
    printf("\n| %-5s | %-40s | %-30s |\n", "RA", "NOME", "EMAIL");
    printf("--------------------------------------------------------------------------------\n");
    for (int i = 0; i < contar; i++)
    {
        printf("\n| %-5d | %-40s | %-30s |\n", alunos[i].ra, alunos[i].nome, alunos[i].email);
    }
    printf("\n--------------------------------------------------------------------------------\n");
}

// Implementações das funções de alocação genéricas (Para o código rodar)

void* alocar_vetor(size_t tamanho_elemento, int num_elementos)
{
    void *novo_vetor = calloc(num_elementos, tamanho_elemento);
    if (novo_vetor == NULL)
    {
        fprintf(stderr, "\nERRO: Falha na ALOCACAO inicial para %d elementos.\n", num_elementos);
    }
    else
    {
        printf("\nAlocacao inicial (CALLOC) de %d elementos bem-sucedida.\n", num_elementos);
    }
    return novo_vetor;
}

void* realocar_vetor(void *vetor_ptr, size_t tamanho_elemento, int novo_num_elementos)
{
    if (novo_num_elementos <= 0)
    {
        if (vetor_ptr != NULL)
        {
            free(vetor_ptr);
            printf("\nMemoria liberada com sucesso (FREE).\n");
        }
        return NULL;
    }
    size_t novo_tamanho_bytes = novo_num_elementos * tamanho_elemento;
    void *novo_vetor = realloc(vetor_ptr, novo_tamanho_bytes);
    if (novo_vetor == NULL)
    {
        fprintf(stderr, "\nERRO: Falha na REALOCACAO para %d elementos. Vetor original preservado.\n", novo_num_elementos);
        return vetor_ptr;
    }
    printf("\nRealocacao para %d elementos bem-sucedida.\n", novo_num_elementos);
    return novo_vetor;
}

td_aluno* realoca_aluno(td_aluno *vetor_ptr, int *dimensao_atual)
{
    int nova_dimensao = *dimensao_atual + 10;
    td_aluno *temp_ptr = (td_aluno*)realocar_vetor(vetor_ptr, sizeof(td_aluno), nova_dimensao);

    // Atualiza a dimensão APENAS se a realocação foi bem-sucedida (o ponteiro mudou)
    if (temp_ptr != NULL && temp_ptr != vetor_ptr)
    {
        *dimensao_atual = nova_dimensao;
    }
    return temp_ptr;
}

td_disciplina* realoca_disciplina(td_disciplina *vetor_ptr, int *dimensao_atual)
{
    int nova_dimensao = *dimensao_atual + 5;
    td_disciplina *temp_ptr = (td_disciplina*)realocar_vetor(vetor_ptr, sizeof(td_disciplina), nova_dimensao);
    if (temp_ptr != NULL && temp_ptr != vetor_ptr)
    {
        *dimensao_atual = nova_dimensao;
    }
    return temp_ptr;
}

td_matricula* realoca_matricula(td_matricula *vetor_ptr, int *dimensao_atual)
{
    int nova_dimensao = *dimensao_atual + 10;
    td_matricula *temp_ptr = (td_matricula*)realocar_vetor(vetor_ptr, sizeof(td_matricula), nova_dimensao);
    if (temp_ptr != NULL && temp_ptr != vetor_ptr)
    {
        *dimensao_atual = nova_dimensao;
    }
    return temp_ptr;
}

td_compromisso* realoca_compromisso(td_compromisso *vetor_ptr, int *dimensao_atual)
{
    int nova_dimensao = *dimensao_atual + 5;
    td_compromisso *temp_ptr = (td_compromisso*)realocar_vetor(vetor_ptr, sizeof(td_compromisso), nova_dimensao);
    if (temp_ptr != NULL && temp_ptr != vetor_ptr)
    {
        *dimensao_atual = nova_dimensao;
    }
    return temp_ptr;
}
