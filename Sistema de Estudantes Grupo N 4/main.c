#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "funcoes.h"

int main() {
    setlocale(LC_ALL, "Portuguese");
    Estudante baseDados[MAX_ESTUDANTES];
    int totalEstudantes = 0;
    int opcao;

    do {
        printf("\n--------------------------------------\n");
        printf("   SISTEMA DE GESTAO DE ESTUDANTES\n");
        printf("----------------------------------------\n");
        printf("[1] Ler Ficheiro\n");
        printf("[2] Exibir informações de estudantes \n");
        printf("[3] Ordenar Lista de Estudantes\n");
        printf("[4] Pesquisar por estudante\n");
        printf("[5] Armazenar Dados Atualizados em Ficheiro\n");
        printf("[6] Inserir informações de estudantes (Teclado)\n");
        printf("[7] Editar informaçoes de estudante\n");
        printf("[8] Eliminar informações de estudante\n");
        printf("[0] Sair do Sistema\n");
        printf("---------------------------------------------\n");
        printf("Escolha uma opcao: ");

        
        
        if (scanf("%d", &opcao) != 1) {
            opcao = -1; 
        }
        
        while (getchar() != '\n'); 

        switch(opcao) {
            case 1: lerFicheiro(baseDados, &totalEstudantes);   
			         break;
            case 2: exibirEstudantes(baseDados, totalEstudantes); 
			        break;
            case 3: menuOrdenacao(baseDados, totalEstudantes); 
			           break;
            case 4: menuPesquisa(baseDados, totalEstudantes);
			             break;
            case 5: gravarFicheiro(baseDados, totalEstudantes); 
			          break;
            case 6: inserirEstudanteTeclado(baseDados, &totalEstudantes);
			 break;
            case 7: editarEstudante(baseDados, totalEstudantes);     
			     break;
            case 8: eliminarEstudante(baseDados, &totalEstudantes);  
			     break;
            case 0: printf("Encerrando o sistema. Ate a proxima!\n"); 
			    break;
            default: printf("Opcao invalida! Tente de novo.\n");
        }

    } while (opcao != 0);

    return 0;
}
