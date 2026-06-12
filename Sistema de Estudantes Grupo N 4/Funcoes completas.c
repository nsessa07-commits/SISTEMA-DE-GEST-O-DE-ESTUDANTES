#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

//  LEITURA DE DADOS DO REGISTRO

void lerFicheiro(Estudante lista[], int *total) {
    char nomeFicheiro[50];
    printf("Nome do ficheiro a ler (ex: estudantes.txt): ");
    scanf("%s", nomeFicheiro);

    FILE *f = fopen(nomeFicheiro, "r");
    if (f == NULL) {
        printf("[Erro] Nao foi possivel abrir o ficheiro '%s'.\n", nomeFicheiro);
        return;
    }

    *total = 0;
    while (*total < MAX_ESTUDANTES &&
           fscanf(f, "%d;%99[^;];%f;%f;%f\n",
                  &lista[*total].matricula,
                  lista[*total].nome,
                  &lista[*total].nota1,
                  &lista[*total].nota2,
                  &lista[*total].nota3) == 5) {
        lista[*total].media = (lista[*total].nota1 + lista[*total].nota2 + lista[*total].nota3) / 3.0;
        (*total)++;
    }

    fclose(f);
    printf("Dados carregados com sucesso! %d estudantes em memoria.\n", *total);
}
// VER LISTA COMPLETA
void exibirEstudantes(Estudante lista[], int total) {
    if (total == 0) {
        printf("Nenhum estudante na memoria. Carregue o ficheiro primeiro.\n");
        return;
    }
    printf("\n%-10s %-25s %-6s %-6s %-6s %-6s\n",
           "Matricula", "Nome do Estudante", "N1", "N2", "N3", "Media");
    printf("-------------------------------------------------------------------------\n");
    int i;
    for (i = 0; i < total; i++) {
        printf("%-10d %-25s %-6.1f %-6.1f %-6.1f %-6.2f\n",
               lista[i].matricula, lista[i].nome,
               lista[i].nota1, lista[i].nota2, lista[i].nota3, lista[i].media);
    }
}

// LOGICA DE COMPARAÇÃO
int comparar(Estudante a, Estudante b, int criterio) {
    if (criterio == 1) return (a.matricula > b.matricula);
    if (criterio == 2) return (strcasecmp(a.nome, b.nome) > 0);
    if (criterio == 3) return (a.media < b.media);
    return 0;
}

//  ALGORITMOS DE ORDENACAO
void bubbleSort(Estudante lista[], int total, int criterio) {
    Estudante temp;
    int i, j;
    for (i = 0; i < total - 1; i++)
        for (j = 0; j < total - i - 1; j++)
            if (comparar(lista[j], lista[j+1], criterio)) {
                temp = lista[j]; lista[j] = lista[j+1]; lista[j+1] = temp;
            }
}




void selectionSort(Estudante lista[], int total, int criterio) {
    int min_idx, i, j;
    Estudante temp;
    for (i = 0; i < total - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < total; j++)
            if (comparar(lista[min_idx], lista[j], criterio)) min_idx = j;
        temp = lista[min_idx]; lista[min_idx] = lista[i]; lista[i] = temp;
    }
}

void insertionSort(Estudante lista[], int total, int criterio) {
    Estudante chave;
    int i, j;
    for (i = 1; i < total; i++) {
        chave = lista[i];
        j = i - 1;
        while (j >= 0 && comparar(lista[j], chave, criterio)) {
            lista[j+1] = lista[j]; j--;
        }
        lista[j+1] = chave;
    }
}


void menuOrdenacao(Estudante lista[], int total) {
    if (total == 0) { printf("Carregue os dados primeiro.\n"); return; }
    int alg, crit;
    printf("\n--- MENU DE ORDENACAO ---\n");
    printf("Algoritmo:\n1. Bubble Sort\n2. Selection Sort\n3. Insertion Sort\nOpcao: ");
    scanf("%d", &alg);
    printf("Criterio:\n1. Matricula (Crescente)\n2. Nome (Alfabetico)\n3. Media (Decrescente)\nOpcao: ");
    scanf("%d", &crit);
    switch(alg) {
        case 1: bubbleSort(lista, total, crit);    printf("Ordenado via Bubble Sort.\n");    break;
        case 2: selectionSort(lista, total, crit); printf("Ordenado via Selection Sort.\n"); break;
        case 3: insertionSort(lista, total, crit); printf("Ordenado via Insertion Sort.\n"); break;
        default: printf("Algoritmo invalido.\n");
    }
}

// ALGORITMOS DE BUSCA 

int pesquisaLinearMatricula(Estudante lista[], int total, int matricula) {
    int i;
    for (i = 0; i < total; i++)
        if (lista[i].matricula == matricula) return i;
    return -1;
}

int pesquisaBinariaMatricula(Estudante lista[], int total, int matricula) {
    int inicio = 0, fim = total - 1;
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        if (lista[meio].matricula == matricula) return meio;
        if (lista[meio].matricula < matricula) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

int pesquisaLinearNome(Estudante lista[], int total, char nomeProcurado[]) {
    int i;
    for (i = 0; i < total; i++)
        if (strcasecmp(lista[i].nome, nomeProcurado) == 0) return i;
    return -1;
}

void menuPesquisa(Estudante lista[], int total) {
    if (total == 0) { printf("Nao ha dados em memoria.\n"); return; }
    int tipo, resultado = -1;
    printf("\n--- MENU DE PESQUISA ---\n");
    printf("1. Por Matricula\n2. Por Nome\nOpcao: ");
    scanf("%d", &tipo);

    if (tipo == 1) {
        int mat, opBusca;
        printf("Matricula: "); scanf("%d", &mat);
        printf("1. Linear\n2. Binaria (lista deve estar ordenada por matricula)\nOpcao: ");
        scanf("%d", &opBusca);
        resultado = (opBusca == 1)
            ? pesquisaLinearMatricula(lista, total, mat)
            : pesquisaBinariaMatricula(lista, total, mat);
    } else if (tipo == 2) {
        char nomeProcurado[MAX_NOME];
        printf("Nome: "); getchar();
        fgets(nomeProcurado, MAX_NOME, stdin);
        strtok(nomeProcurado, "\n");
        resultado = pesquisaLinearNome(lista, total, nomeProcurado);
    }

    if (resultado != -1)
        printf("\nEncontrado -> Matricula: %d | Nome: %s | N1: %.1f | N2: %.1f | N3: %.1f | Media: %.2f\n",
               lista[resultado].matricula, lista[resultado].nome,
               lista[resultado].nota1, lista[resultado].nota2,
               lista[resultado].nota3, lista[resultado].media);
    else
        printf("Estudante nao encontrado.\n");
}

//  armazenamento EM FICHEIRO das informacoes
void gravarFicheiro(Estudante lista[], int total) {
    if (total == 0) { printf("Nao ha dados para gravar.\n"); return; }
    int modo;
    char nomeFicheiro[50];
    printf("\n1. Texto (.txt)\n2. Binario (.bin)\nOpcao: ");
    scanf("%d", &modo);
    printf("Nome do ficheiro (sem extensao): ");
    scanf("%s", nomeFicheiro);

    if (modo == 1) {
        strcat(nomeFicheiro, ".txt");
        FILE *f = fopen(nomeFicheiro, "w");
        if (f == NULL) { printf("[Erro] Nao foi possivel criar o ficheiro.\n"); return; }
        int i;
        for (i = 0; i < total; i++)
            // SEM a media — formato identico ao ficheiro original para releitura correcta
            fprintf(f, "%d;%s;%.2f;%.2f;%.2f\n",
                    lista[i].matricula, lista[i].nome,
                    lista[i].nota1, lista[i].nota2, lista[i].nota3);
        fclose(f);
    } else {
        strcat(nomeFicheiro, ".bin");
        FILE *f = fopen(nomeFicheiro, "wb");
        if (f == NULL) { printf("[Erro] Nao foi possivel criar o ficheiro.\n"); return; }
        fwrite(lista, sizeof(Estudante), total, f);
        fclose(f);
    }
    printf("Ficheiro '%s' gravado com sucesso! (%d estudantes)\n", nomeFicheiro, total);
}

//  INSERIR informacoes  PELO TECLADO 
void inserirEstudanteTeclado(Estudante lista[], int *total) {
    if (*total >= MAX_ESTUDANTES) {
        printf("[Erro] Limite de %d estudantes atingido!\n", MAX_ESTUDANTES);
        return;
    }
    Estudante novo;
    printf("\n--- INSERIR NOVO ESTUDANTE ---\n");
    printf("Matricula: "); scanf("%d", &novo.matricula);
    getchar();
    printf("Nome: "); fgets(novo.nome, MAX_NOME, stdin); strtok(novo.nome, "\n");
    printf("Nota 1: "); scanf("%f", &novo.nota1);
    printf("Nota 2: "); scanf("%f", &novo.nota2);
    printf("Nota 3: "); scanf("%f", &novo.nota3);
    novo.media = (novo.nota1 + novo.nota2 + novo.nota3) / 3.0;
    lista[*total] = novo;
    (*total)++;
    printf("Estudante inserido com sucesso! Media calculada: %.2f\n", novo.media);
}

// EDITAR informações ESTUDANTE
void editarEstudante(Estudante lista[], int total) {
    if (total == 0) { printf("Nao ha dados em memoria.\n"); return; }
    int mat, idx;
    printf("\n--- EDITAR ESTUDANTE ---\n");
    printf("Matricula do estudante a editar: ");
    scanf("%d", &mat);
    idx = pesquisaLinearMatricula(lista, total, mat);
    if (idx == -1) { printf("Estudante com matricula %d nao encontrado.\n", mat); return; }

    printf("Estudante encontrado: %s\n", lista[idx].nome);
    printf("O que deseja editar?\n");
    printf("1. Nome\n2. Nota 1\n3. Nota 2\n4. Nota 3\n5. Tudo\nOpcao: ");
    int op; scanf("%d", &op);

    if (op == 1 || op == 5) {
        printf("Novo nome: "); getchar();
        fgets(lista[idx].nome, MAX_NOME, stdin);
        strtok(lista[idx].nome, "\n");
    }
    if (op == 2 || op == 5) { printf("Nova Nota 1: "); scanf("%f", &lista[idx].nota1); }
    if (op == 3 || op == 5) { printf("Nova Nota 2: "); scanf("%f", &lista[idx].nota2); }
    if (op == 4 || op == 5) { printf("Nova Nota 3: "); scanf("%f", &lista[idx].nota3); }

    // calcula de novo 
    lista[idx].media = (lista[idx].nota1 + lista[idx].nota2 + lista[idx].nota3) / 3.0;
    printf("Estudante actualizado com sucesso! Nova media: %.2f\n", lista[idx].media);
}

// ELIMINAR DASOS DE  ESTUDANTE
void eliminarEstudante(Estudante lista[], int *total) {
    if (*total == 0) { printf("Nao ha dados em memoria.\n"); return; }
    int mat, idx, i;
    printf("\n--- ELIMINAR ESTUDANTE ---\n");
    printf("Matricula do estudante a eliminar: ");
    scanf("%d", &mat);
    idx = pesquisaLinearMatricula(lista, *total, mat);
    if (idx == -1) { printf("Estudante com matricula %d nao encontrado.\n", mat); return; }

    printf("Confirma a eliminacao de '%s'? (1=Sim / 0=Nao): ", lista[idx].nome);
    int conf; scanf("%d", &conf);
    if (conf != 1) { printf("Operacao cancelada.\n"); return; }



    // Desloca 
    for (i = idx; i < *total - 1; i++)
        lista[i] = lista[i + 1];
    (*total)--;
    printf("Estudante eliminado com sucesso! Total actual: %d estudantes.\n", *total);
}
