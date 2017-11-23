#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "utils.h"
#include "funcao.h"


// Preenche uma estrutura com os progenitores da próxima geração, de acordo com o resultados do torneio binario (tamanho de torneio: 2)
// Parâmetros de entrada: população actual (pop), estrutura com parâmetros (d) e população de pais a encher

int check(int m[], int i) {
	int aux, j;
	for (j = i; j >=0; j--) {
		if (m[i] == m[j] && i!=j)
			return 1;
	}
	return 0;
}


void tournament(pchrom pop, struct info d, pchrom parents)
{
	int i, j, k, sair, best, *pos;

	pos = malloc(d.tsize * sizeof(int));
	// Realiza popsize torneios
	for (i = 0; i<d.popsize; i++)
	{
		// Seleciona tsize soluções diferentes para entrarem em torneio de seleção
		for (j = 0; j<d.tsize; j++)
		{
			do
			{
				pos[j] = random_l_h(0, d.popsize - 1);
				// Verifica se a nova posição escolhida é igual a alguma das outras posições escolhidas
				sair = 0;
				for (k = 0; k<j; k++)
				{
					if (pos[k] == pos[j])
						sair = 1;
				}
			} while (sair);
			// Guarda a posição da melhor solução de todas as que entraram em torneio
			if (j == 0 || pop[pos[j]].fitness > pop[pos[best]].fitness)		// Problema de maximizacao
				best = j;
		}
		parents[i] = pop[pos[best]];
		parents[i].num_ele = pop[pos[best]].num_ele;
	}
	free(pos);
	/*
	int * c = (int*)malloc(sizeof(int)*d.tsize);

	if (c == NULL)
	{
		printf("Erro na alocacao de memoria\n");
		exit(1);
	}
	for (a = 0; a < d.popsize; a++)
	{
		for (i = 0; i < d.tsize; i++)
		{
			do {
				c[i] = random_l_h(0, d.popsize - 1);
			} while (check(c, i));

			if (i == 0 || pop[c[i]].fitness >pop[c_best].fitness)
			{
				c_best = c[i];
			}
		}
		parents[a] = pop[c_best];
	}

	free(c);*/
}

// Operadores geneticos a usar na geração dos filhos
// Parâmetros de entrada: estrutura com os pais (parents), estrutura com parâmetros (d), estrutura que guardará os descendentes (offspring)
void genetic_operators(pchrom parents, struct info d, pchrom offspring)
{
    // Recombinação com um ponto de corte
	crossover(parents, d, offspring);
	// Mutação binária
	mutation(offspring, d);
}

// Preenche o vector descendentes com o resultado das operações de recombinação
// Parâmetros de entrada: estrutura com os pais (parents), estrutura com parâmetros (d), estrutura que guardará os descendentes (offspring)
void crossover(pchrom parents, struct info d, pchrom offspring)
{
	int i, j, point;

	for (i=0; i<d.popsize; i+=2)
	{
		offspring[i].num_ele = 0;
		if (rand_01() < d.pr)
		{
			point = random_l_h(0, d.numGenes-1);
			for (j=0; j<point; j++)
			{
				offspring[i].p[j] = parents[i].p[j];
				offspring[i+1].p[j] = parents[i+1].p[j];
				if (offspring[i].p[j] == 1)
				{
					offspring[i].num_ele++;
				}
				if (offspring[i + 1].p[j] == 1)
				{
					offspring[i + 1].num_ele++;
				}
			}
			for (j=point; j<d.numGenes; j++)
			{
				offspring[i].p[j]= parents[i+1].p[j];
				offspring[i+1].p[j] = parents[i].p[j];
				if (offspring[i].p[j] == 1)
				{
					offspring[i].num_ele++;
				}
				if (offspring[i + 1].p[j] == 1)
				{
					offspring[i + 1].num_ele++;
				}
			}
		}
		else
		{
			offspring[i] = parents[i];
			offspring[i+1] = parents[i+1];
			offspring[i].num_ele = parents[i].num_ele;
			offspring[i+1].num_ele = parents[i+1].num_ele;
		}
	}
}

// Mutação binária com vários pontos de mutação
// Parâmetros de entrada: estrutura com os descendentes (offspring) e estrutura com parâmetros (d)
void mutation(pchrom offspring, struct info d)
{
	int i, j;

	for (i = 0; i < d.popsize; i++)
		for (j = 0; j < d.numGenes; j++)
			if (rand_01() < d.pm)
			{
				if (offspring[i].p[j] == 1)
				{
					offspring[i].num_ele--;
					offspring[i].p[j] = !(offspring[i].p[j]);
				}
				else
				{
					offspring[i].num_ele++;
					offspring[i].p[j] = !(offspring[i].p[j]);
				}
			}
}

/*void gera_vizinho(int sol[], int nova_sol[], int obj)
{
	int p;

	substitui(nova_sol, sol, obj);
	p = random_l_h(0, obj - 1);

	nova_sol[p] = !nova_sol[p];
}*/

void gera_vizinho(int a[], int b[], int n,int *tam)
{
	int i, p1, p2, var;

	for (i = 0; i<n; i++)
		b[i] = a[i];

	if (*tam <= 2) {
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
	else if (*tam >= n) {
		var = 1;
	}
	else
		var = random_l_h(0, 2);

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
		(*tam) = (*tam) + 1;


		break;
	case 1:
		// Encontra posicao com valor 0
		do
			p1 = random_l_h(0, n - 1);
		while (b[p1] != 1);
		// Encontra posicao com valor 0

		// Troca
		b[p1] = 0;

		(*tam) = (*tam) - 1;
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

void substitui(int a[], int b[], int n)
{
	int i;
	for (i = 0; i<n; i++) {
		a[i] = b[i];
	}
}

float trepa_colinas(int sol[], float mat[][MAX_OBJ], struct info d, int iteracoes, int *num_ele_sol)
{
	int *nova_sol, i;
	float  custo, custo_viz;

	nova_sol = malloc(sizeof(int) *d.numGenes);

	if (nova_sol == NULL)
	{
		printf("Erro na alocacao de memoria");
		exit(1);
	}
	// Avalia solucao inicial
	custo = eval_individual(sol, d, mat, *num_ele_sol);
	for (i = 0; i < iteracoes; i++)
	{
		// Gera vizinho
		gera_vizinho(sol, nova_sol, d.numGenes, &num_ele_sol);
		// Avalia vizinho
		custo_viz = eval_individual(nova_sol, d, mat, *num_ele_sol);
		// Aceita vizinho se o custo diminuir (problema de minimizacao)
		if (custo_viz > custo)
		{
			substitui(sol, nova_sol, d.numGenes);
			custo = custo_viz;
		}
	}
	free(nova_sol);
	return custo;
}
