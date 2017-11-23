#define _CRT_SECURE_NO_WARNINGS 1
#include "algoritmo.h"
#include "funcao.h"

// Calcula a qualidade de uma solução
// Parâmetros de entrada: solução (sol), capacidade da mochila (d), matriz com dados do problema (mat) e numero de objectos (v)
// Parâmetros de saída: qualidade da solução (se a capacidade for excedida devolve 0)
float eval_individual(int sol[], struct info d, float mat[][MAX_OBJ], int num_ele)
{
	int     i, j,iaux=0 , flag = 0;
	float   sum_profit=0;

	// Percorre todos os objectos
	for (i=0; i < d.numGenes; i++)
	{
        // Verifica se o objecto i esta na mochila
		if (sol[i] == 1)
		{	
			for (j = i + 1; j < d.numGenes; j++)
			{
				if(sol[j]==1)
				{
					sum_profit += mat[i][j];
					if (flag == 0)
					{
						iaux = j;
						flag = 1;
					}
				}
			}

			if (flag == 0)
			{
				break;
			}
			i = iaux - 1;
			flag = 0;
		}
		
	}
	float temp = sum_profit / (float)(num_ele);

	return temp;
}

// Avaliacao da população
// Parâmetros de entrada: populacao (pop), estrutura com parametros (d) e matriz com dados do problema (mat)
// Parâmetros de saída: Preenche pop com os valores de fitness e de validade para cada solução
void evaluate(pchrom pop, struct info d, float mat[][MAX_OBJ])
{
	int i, a=0;

	for (i = 0; i < d.popsize; i++)
	{
		pop[i].fitness = eval_individual(pop[i].p, d, mat, pop[i].num_ele);	
		
	}
		
}
