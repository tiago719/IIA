#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

// Gera um vizinho
// Parametros: solucao actual, vizinho, numero de vertices
//swap two vertices
void gera_vizinho(int a[], int b[], int n, int * rand_1)
{
    int i, p1, p2, var;

    for(i=0; i<n; i++)
        b[i]=a[i];

	if (*rand_1 <= 2) {
		switch (random_l_h(0, 1))
		{
		case 0:
			var = 0;
			break;
		case 1:
			var = 2;
			break;
		}
	}
	else if (*rand_1 >= n) {
		var = 1;
	}
	else
		var = random_l_h(0, 2);

	//var = 2;
	switch (var) {
	case 0:

		// Encontra posicao com valor 0
		do
			p1 = random_l_h(0, n - 1);
		while (b[p1] != 0);
		// Encontra posicao com valor 0
		
		// Troca
		b[p1] = 1;

		//(*rand_1)++;
		(*rand_1) = (*rand_1) + 1;


		break;
	case 1:
		// Encontra posicao com valor 0
		do
			p1 = random_l_h(0, n - 1);
		while (b[p1] != 1);
		// Encontra posicao com valor 0

		// Troca
		b[p1] = 0;

		(*rand_1) = (*rand_1)-1;
		break;
	case 2:
		// Encontra posicao com valor 0
		do
			p1 = random_l_h(0, n - 1);
		while (b[p1] != 0);
		// Encontra posicao com valor 0
		do
			p2 = random_l_h(0, n - 1);
		while (b[p2] != 1);
		// Troca
		b[p1] = 1;
		b[p2] = 0;
		break;
	}	
}

// Trepa colinas first-choice
// Parametros: solucao, matriz de adjacencias, numero de vertices e numero de iteracoes
// Devolve o custo da melhor solucao encontrada
float trepa_colinas(int sol[], float *mat, int vert, int num_iter, int rand_1, int *best_rand1)
{
	*best_rand1 = rand_1;
	int *nova_sol, i;
	float custo, custo_viz;

	nova_sol = malloc(sizeof(int)*vert);
    if(nova_sol == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }
	// Avalia solucao inicial
    custo = calcula_fit(sol, mat, vert)/(rand_1);
    for(i=0; i<num_iter; i++)
    {
		rand_1 = *best_rand1;

		// Gera vizinho
		gera_vizinho(sol, nova_sol, vert, &rand_1);
		//escreve_sol(nova_sol, 20);
		// Avalia vizinho
		custo_viz = calcula_fit(nova_sol, mat, vert) / (rand_1);
		// Aceita vizinho se o custo diminuir (problema de minimizacao)
        if(custo_viz >= custo)
        {
			//escreve_sol(sol, 20);

			substitui(sol, nova_sol, vert);
			custo = custo_viz;
			//printf("\nANTES : %d  DEPOIS: %d", *best_rand1,rand_1);
			*best_rand1 = rand_1;
			//escreve_sol(sol, 20);
        }
    }
    free(nova_sol);
    return custo;
}
