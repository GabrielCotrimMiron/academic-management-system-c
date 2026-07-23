# 🎓 Sistema de Gerenciamento Acadêmico

<p align="center">

![C](https://img.shields.io/badge/C-Language-A8B9CC?style=for-the-badge&logo=c&logoColor=white)
![GCC](https://img.shields.io/badge/GCC-Compiler-00599C?style=for-the-badge&logo=gnu&logoColor=white)
![Code::Blocks](https://img.shields.io/badge/Code::Blocks-IDE-red?style=for-the-badge)
![UTFPR](https://img.shields.io/badge/UTFPR-Projeto%20Acadêmico-blue?style=for-the-badge)
![License](https://img.shields.io/github/license/GabrielCotrimMiron/projeto-algoritmos-2?style=for-the-badge)

</p>

Sistema desenvolvido em **linguagem C** para gerenciamento de alunos, disciplinas, matrículas e compromissos acadêmicos.

Este projeto foi desenvolvido para a disciplina de **Algoritmos II** do curso de **Bacharelado em Engenharia de Software** da **Universidade Tecnológica Federal do Paraná (UTFPR)**, sob orientação do **Prof. Gabriel Canhadas Genvigir**.

O principal objetivo do trabalho é aplicar conceitos fundamentais de programação estruturada utilizando linguagem C, com ênfase em estruturas (`struct`), vetores dinâmicos, modularização, alocação dinâmica de memória, validação de dados, ordenação utilizando `qsort` e organização de projetos em múltiplos arquivos.

---

# 📑 Sumário

- [Visão Geral](#-visão-geral)
- [Funcionalidades](#-funcionalidades)
- [Estruturas Utilizadas](#-estruturas-utilizadas)
- [Estrutura do Projeto](#-estrutura-do-projeto)
- [Como Executar](#-como-executar)
- [Conceitos Aplicados](#-conceitos-aplicados)
- [Possíveis Melhorias](#-possíveis-melhorias)
- [Autores](#-autores)
- [Contexto Acadêmico](#-contexto-acadêmico)
- [Licença](#-licença)

---

# 📖 Visão Geral

O projeto simula um sistema de gerenciamento acadêmico capaz de cadastrar alunos, disciplinas, matrículas e compromissos.

Durante seu desenvolvimento foram aplicados conceitos clássicos da linguagem C, como modularização do código, manipulação de ponteiros, alocação dinâmica de memória, validação de dados e ordenação de registros utilizando a função `qsort()` da biblioteca padrão.

A aplicação é executada em modo console por meio de um menu interativo, permitindo o gerenciamento das informações armazenadas em memória.

---

# ✨ Funcionalidades

- Cadastro de alunos
- Cadastro de disciplinas
- Cadastro de matrículas
- Cadastro de compromissos
- Busca de alunos por RA
- Busca de disciplinas por código
- Validação de e-mail
- Validação de datas
- Validação de horários
- Relatórios de alunos
- Relatórios de compromissos
- Ordenação de registros utilizando `qsort`
- Alocação dinâmica de memória
- Realocação automática dos vetores

---

# 🗂 Estruturas Utilizadas

O sistema utiliza as seguintes estruturas:

| Estrutura | Descrição |
|-----------|-----------|
| **td_data** | Armazena uma data (dia, mês e ano). |
| **td_hora** | Armazena um horário (hora e minuto). |
| **td_aluno** | Dados cadastrais dos alunos. |
| **td_disciplina** | Informações das disciplinas. |
| **td_matricula** | Relaciona alunos e disciplinas, armazenando notas e data da matrícula. |
| **td_compromisso** | Gerencia compromissos vinculados aos alunos. |

---

# 📂 Estrutura do Projeto

```text
projeto-algoritmos-2
│
├── include
│   └── Prot.h
│
├── src
│   ├── main.c
│   ├── menu.c
│   └── func.c
│
├── .gitignore
├── Projeto Alg2.cbp
├── Projeto Alg2.layout
├── LICENSE
└── README.md
```

---

# 🚀 Como Executar

## 1. Clone o repositório

```bash
git clone https://github.com/GabrielCotrimMiron/projeto-algoritmos-2.git
```

---

## 2. Abra o projeto

Abra o arquivo

```
Projeto Alg2.cbp
```

utilizando o **Code::Blocks**.

---

## 3. Compile

Utilize a opção **Build and Run** (`F9`) para compilar e executar o projeto.

---

# 🧠 Conceitos Aplicados

Durante o desenvolvimento foram utilizados conceitos importantes da disciplina de Algoritmos II:

- Programação Estruturada
- Modularização
- Arquivos `.h`
- Structs
- Ponteiros
- Vetores Dinâmicos
- Alocação Dinâmica (`calloc`)
- Realocação Dinâmica (`realloc`)
- Liberação de Memória (`free`)
- Validação de Dados
- Busca Sequencial
- Ordenação utilizando `qsort`
- Passagem de parâmetros por referência
- Organização de projetos em múltiplos arquivos

---

# 🚀 Possíveis Melhorias

Como evolução do projeto, podem ser implementadas funcionalidades como:

- Persistência dos dados em arquivos
- Interface gráfica
- Utilização de listas encadeadas
- Sistema de autenticação
- Exportação de relatórios
- Interface baseada em menus mais intuitivos

---

# 👨‍💻 Autores

**Gabriel Cotrim Miron**

Estudante de Engenharia de Software — UTFPR

GitHub: https://github.com/GabrielCotrimMiron

---

**Hugo Pessoni Batista**

Estudante de Engenharia de Software — UTFPR

---

# 🎓 Contexto Acadêmico

Projeto desenvolvido como atividade prática da disciplina de **Algoritmos II** do curso de **Bacharelado em Engenharia de Software** da **Universidade Tecnológica Federal do Paraná (UTFPR)**.

**Professor:** Gabriel Canhadas Genvigir

---

# 📄 Licença

Este projeto está licenciado sob a **MIT License**.

Consulte o arquivo `LICENSE` para mais informações.









