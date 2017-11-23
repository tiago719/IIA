#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algoritmo.h"
#include "utils.h"

// Inicialização do gerador de números aleatórios
void init_rand()
{
	srand((unsigned)time(NULL));
}

// Leitura dos parâmetros e dos dados do problema
// Parâmetros de entrada: Nome do ficheiro e matriz a preencher com os dados dos objectos (peso e valor)
// Parâmetros de saída: Devolve a estrutura com os parâmetros
struct info init_data(char *filename, float mat[][MAX_OBJ])
{
	struct  info x;
	FILE    *f;
	int     i, j, a, b, temp, n;
	float	dist;

	//strcpy(filename, "../../Instancias_EDP_TP2/MDPI1_20.txt");//TODO:APAGAR ISTO

	f = fopen(filename, "rt");
	if (!f)
	{
		printf("File not found\n");
		exit(1);
	}

	int as = -1;
	do {
		fseek(f, as, SEEK_END);
		as--;
	} while (fgetc(f) != '\n');
	fscanf(f, " %d %d %f", &temp, &n, &temp);
	fseek(f, 0, SEEK_SET);


	x.numGenes = n;
	/*x.pr = 0.3;
	x.popsize = 100;
	x.pm = 0.01;
	x.tsize = 2;
	x.numGenerations = 2500;*/

	printf("\nDefina tamanho da populacao: ");
	scanf(" %d", &x.popsize);
	printf("\nDefina probabilidade de recombinacao: ");
	scanf(" %f", &x.pr);
	if (x.pr > 1 || x.pr < 0)
	{
		x.pr = 0.3;
		printf("\nProbabilidade de recombinacao invalida. Valor definido por defeito: %f\n", x.pr);
	}
	printf("\nDefina probabilidade de mutacao: ");
	scanf(" %f", &x.pm);
	if (x.pm > 1 || x.pm < 0)
	{
		x.pr = 0.01;
		printf("\nProbabilidade de mutacao invalida. Valor definido por defeito: %f\n", x.pm);
	}
	printf("\nDefina tamanho do torneio para definir o pai da proxima geracao: ");
	scanf(" %d", &x.tsize);
	if (x.tsize < 2 || x.tsize>4)
	{
		x.tsize = 2;
		printf("\nTamanho de torneio invalido. Valor definido por defeito: %d\n", x.tsize);
	}
	printf("\nDefina numero de geracoes maximo: ");
	scanf(" %d", &x.numGenerations);
	if (x.numGenerations < 500 || x.numGenerations>5000)
	{
		x.numGenerations = 2500;
		printf("\nNumero de geracoes invalido. Valor definido por defeito: %d\n", x.numGenerations);
	}

	if (x.numGenes > MAX_OBJ)
	{
		printf("Number of itens is superior to MAX_OBJ\n");
		exit(1);
	}
	x.ro = 0.0;
	
	while (fscanf(f, " %d %d %f", &a, &b, &dist) == 3)
	{
		mat[a-1][b-1] = dist;
	}

	fclose(f);
	// Devolve a estrutura com os parâmetros
	return x;
}

// Simula o lançamento de uma moeda, retornando o valor 0 ou 1
int flip()
{
	if ((((float)rand()) / RAND_MAX) < 0.5)
		return 0;
	else
		return 1;
}

// Criacao da populacao inicial. O vector e alocado dinamicamente
// Parâmetro de entrada: Estrutura com parâmetros do problema
// Parâmetro de saída: Preenche da estrutura da população apenas o vector binário com os elementos que estão dentro ou fora da mochila
pchrom init_pop(struct info d)
{
	int     i, j;
	pchrom  indiv;

	indiv = malloc(sizeof(chrom)*d.popsize);
	if (indiv==NULL)
	{
		printf("Erro na alocacao de memoria\n");
		exit(1);
	}
	
	for (i=0; i<d.popsize; i++)
	{
		indiv[i].num_ele = 0;
		for (j = 0; j < d.numGenes; j++)
		{
			indiv[i].p[j] = flip();
			if (indiv[i].p[j] == 1)
			{
				indiv[i].num_ele++;
			}
		}
	}
	return indiv;
}

// Actualiza a melhor solução encontrada
// Parâmetro de entrada: populacao actual (pop), estrutura com parâmetros (d) e a melhor solucao encontrada até a geraçãoo imediatamente anterior (best)
// Parâmetro de saída: a melhor solucao encontrada até a geração actual
chrom get_best(pchrom pop, struct info d, chrom best)
{
	int i;

	for (i=0; i<d.popsize; i++)
	{
		if (best.fitness < pop[i].fitness)
			best=pop[i];
	}
	return best;
}

// Compara duas solucoes
// Parâmetro de entrada: solucao 1 (s1), solucao 2 (s2)
// Parâmetro de saída: 1 se for a mesma solucao, 0 se for diferente
int compare(pchrom s1, pchrom s2)
{
	int i;
	if (s1->num_ele != s2->num_ele)
		return 0;

	for (i = 0; i < s1->num_ele; i++) {
		if (s1->p[i] != s2->p[i])
			return 0;
	}
	return 1;
}

// Devolve um valor inteiro distribuido uniformemente entre min e max
int random_l_h(int min, int max)
{
	return min + rand() % (max-min+1);
}

// Devolve um valor real distribuido uniformemente entre 0 e 1
float rand_01()
{
	return ((float)rand())/RAND_MAX;
}

// Escreve uma solução na consola
// Parâmetro de entrada: populacao actual (pop) e estrutura com parâmetros (d)
void write_best(chrom x, struct info d)
{
	int i;

	printf("\nBest individual: %4.1f\n", x.fitness);
	for (i=0; i<d.numGenes; i++)
		printf("%d ", x.p[i]);
	putchar('\n');
}

void escreve_sol(int *sol, int vert)//TODO:APAGAR ISTO
{
	int i;

	printf("\nConjunto A: ");
	for (i = 0; i<vert; i++)
		if (sol[i] == 0)
			printf("%2d  ", i);
	printf("\nConjunto B: ");
	for (i = 0; i<vert; i++)
		if (sol[i] == 1)
			printf("%2d  ", i);
	printf("\n");
}
