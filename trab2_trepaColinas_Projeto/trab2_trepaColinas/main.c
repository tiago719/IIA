#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "utils.h"

#define DEFAULT_RUNS 30
#define DEFAULT_ITER 50

int main(int argc, char *argv[])
{
    char    nome_fich[100];
	int     ele, num_iter = DEFAULT_ITER, k, runs = DEFAULT_RUNS, rand_1, best_rand1=0;
	int     *sol, *best, *aux;
	float  *grafo;
	float   mbf = 0.0, custo=0, best_custo=0;
	int cont = 0, flag = 0;

	if(argc == 2)
	{
		strcpy(nome_fich, argv[1]);
	}
        else
        {
            printf("Nome do Ficheiro: ");
            gets(nome_fich);
        }

	init_rand();
    // Preenche matriz de adjacencias
    grafo = init_dados(nome_fich, &ele, &num_iter);
	sol = (int *)malloc(sizeof(int)*ele);
	best = (int *)malloc(sizeof(int)*ele);
	if(sol == NULL || best == NULL)
	{
		printf("Erro na alocacao de memoria");
		exit(1);
	}
	for(k=0; k<runs; k++)
	{
		if (k == 0) {//se 1ª iteracao gera solucao inicial
			// Gerar solucao inicial
			gera_sol_inicial(sol, ele, &rand_1);
			best_rand1 = rand_1;

		}
		else if (!flag) {//usa a solucao encontrada anterior
			rand_1 = best_rand1;
		}
		else//caso a mesma solucao tenha sido encontrada 5 vezes gera uma nova aleatoria
			flag = 0;

		escreve_sol(sol, ele);
		printf("Numero de items selecionados: %d\n", rand_1);
		

		// Trepa colinas
		custo = trepa_colinas(sol, grafo, ele, num_iter, rand_1, &best_rand1);
		// Escreve resultados da repeticao k
		printf("\nRepeticao %d:", k);
		escreve_sol(sol, ele);
		printf("Custo final: %.2f\n", custo);
		printf("Numero de items selecionados: %d\n", best_rand1);

		mbf += custo;
		if(k==0 || best_custo < custo)
		{
			best_custo = custo;
			substitui(best, sol, ele);
			//best_rand1 = rand_1;
		}
		else if (best_custo == custo) {
			if (++cont == 5) {
				gera_sol_inicial(sol, ele, &rand_1);
				flag = 1; //para o rand1 nao ser alterado no inicio da prox iteracao
			}

		}
    }
	// Escreve eresultados globais
	printf("\n Media das Solucoes: %.2f \n", mbf / k);
	printf("\nMelhor solucao encontrada");
	escreve_sol(best, ele);
	printf("Custo final: %.2f\n", best_custo);
	printf("Numero de items selecionados: %d\n", rand_1);
	free(grafo);
    free(sol);
	free(best);
	printf("\nPrima qualquer tecla para fechar\n");

	getch();
    return 0;
}
