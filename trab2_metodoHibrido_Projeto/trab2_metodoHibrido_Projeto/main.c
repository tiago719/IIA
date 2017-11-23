
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

#define DEFAULT_RUNS	10

int main(int argc, char *argv[])
{
	char        nome_fich[100];
	struct info EA_param;
	pchrom      pop = NULL, parents = NULL;
	chrom       best_run, best_ever;
	int         gen_actual, r, runs, count_rep = 0, i, j, op;
	float		mat[MAX_OBJ][MAX_OBJ];
	float       mbf = 0.0;

	// Lê os argumentos de entrada
	if (argc == 3)
	{
		runs = atoi(argv[2]);
		strcpy(nome_fich, argv[1]);
	}
	else
		// Se o número de execuções do processo não for colocado nos argumentos de entrada, define-o com um valor por defeito
		if (argc == 2)
		{
			runs = DEFAULT_RUNS;
			strcpy(nome_fich, argv[1]);
		}
	// Se o nome do ficheiro de informações não for colocado nos argumentos de entrada, pede-o novamente
		else
		{
			runs = DEFAULT_RUNS;
			printf("Nome do Ficheiro: ");
			gets(nome_fich);
		}
	// Se o número de execuções do processo for menor ou igual a 0, termina o programa
	if (runs <= 0)
		return 0;
	//Inicializa a geração dos números aleatórios
	init_rand();

	do {
		printf("\n 1 - Pesquisa local para melhoramento da populacao inicial");
		printf("\n 2 - Pesquisa local para melhoramento da populacao final");
		printf("\n 3 - Pesquisa local para melhoramento da populacao media");
		printf("\n 0 - Sair\n");
		scanf(" %d", &op);
	} while (op<=0 && op>3);
	if (op == 0)
		return 0;
	

	// Preenche a matriz com dados dos objectos (peso e valor) e a estrutura EA_param que foram definidos no ficheiro de input
	EA_param = init_data(nome_fich, mat);
	// Faz um ciclo com o número de execuções definidas
	for (r = 0; r<runs; r++)
	{
		printf("Repeticao %d\n", r + 1);
		// Geração da população inicial
		pop = init_pop(EA_param);
		// Avalia a população inicial
		//evaluate(pop, EA_param, mat);
		gen_actual = 1;
		
		// Como ainda não existe, escolhe-se como melhor solução a primeira da população (poderia ser outra qualquer)
		best_run = pop[0];
		//write_best(best_run, EA_param);
		// Encontra-se a melhor solução dentro de toda a população
		best_run = get_best(pop, EA_param, best_run);
		// Reserva espaço para os pais da população seguinte
		parents = malloc(sizeof(chrom)*EA_param.popsize);
		// Caso não consiga fazer a alocação, envia aviso e termina o programa
		if (parents == NULL)
		{
			printf("Erro na alocacao de memoria\n");
			exit(1);
		}
		if (op == 1) {
			for (i = 0; i < EA_param.popsize; i++)
			{
				pop[i].fitness = trepa_colinas(pop[i].p, mat, EA_param, 50, &pop[i].num_ele);
			}
		}
		//write_best(best_run, EA_param);
		// Ciclo de optimização
		while (gen_actual <= EA_param.numGenerations)
		{
			// Torneio binário para encontrar os progenitores (ficam armazenados no vector parents)
			tournament(pop, EA_param, parents);
			// Aplica os operadores genéticos aos pais (os descendentes ficam armazenados na estrutura pop)
			genetic_operators(parents, EA_param, pop);
			// Avalia a nova população (a dos filhos)
			evaluate(pop, EA_param, mat);
			if (op == 2) {
				for (i = 0; i < EA_param.popsize; i++)
				{
					pop[i].fitness = trepa_colinas(pop[i].p, mat, EA_param, 50, &pop[i].num_ele);
				}
			}
			// Actualiza a melhor solução encontrada
			best_run = get_best(pop, EA_param, best_run);
			gen_actual++;
		}
		if (op == 3) {
			for (i = 0; i < EA_param.popsize; i++)
			{
				pop[i].fitness = trepa_colinas(pop[i].p, mat, EA_param, 50, &pop[i].num_ele);
			}
		}
		write_best(best_run, EA_param);
		printf("\nNumero de elementos %d\n", best_run.num_ele);
		//printf("\nPercentagem Invalidos: %f\n", 100*(float)inv/EA_param.popsize);
		mbf += best_run.fitness;
		if (r == 0 || best_run.fitness > best_ever.fitness)
			best_ever = best_run;
		// Liberta a memória usada
		free(parents);
		free(pop);
	}
	// Escreve resultados globais
	printf("\n\nMBF: %f\n", mbf / r);
	printf("\nMelhor solucao encontrada");
	write_best(best_ever, EA_param);
	printf("\nNumero de elementos %d\n", best_ever.num_ele);

	printf("\nPrima qualquer tecla para fechar\n");

	getch();
	return 0;
}
