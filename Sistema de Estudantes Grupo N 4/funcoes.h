#ifndef FUNCOES_H
#define FUNCOES_H

#define MAX_ESTUDANTES 200
#define MAX_NOME 100

typedef struct Estudante {
    int   matricula;
    char  nome[MAX_NOME];
    float nota1;
    float nota2;
    float nota3;
    float media;
} Estudante;

// prototipos para lerem os nossos  Ficheiros
void lerFicheiro(Estudante lista[], int *total);
void gravarFicheiro(Estudante lista[], int total);

// prototipos de visulaização  Visualizacao
void exibirEstudantes(Estudante lista[], int total);

// prototipos para  Insercao / Edicao / Eliminacao
void inserirEstudanteTeclado(Estudante lista[], int *total);
void editarEstudante(Estudante lista[], int total);
void eliminarEstudante(Estudante lista[], int *total);

// prototipos de  Ordenacao
void menuOrdenacao(Estudante lista[], int total);
void bubbleSort(Estudante lista[], int total, int criterio);
void selectionSort(Estudante lista[], int total, int criterio);
void insertionSort(Estudante lista[], int total, int criterio);

//Prototipos de  Pesquisa
void menuPesquisa(Estudante lista[], int total);
int  pesquisaLinearMatricula(Estudante lista[], int total, int matricula);
int  pesquisaBinariaMatricula(Estudante lista[], int total, int matricula);
int  pesquisaLinearNome(Estudante lista[], int total, char nomeProcurado[]);

#endif
