#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utils.h"

// Leitura do ficheiro de input
// Recebe: nome do ficheiro, numero de vertices (ptr), numero de iteracoes (ptr)
// Devolve a matriz de adjacencias
float* init_dados(char *nome, int *n, int *iter)
{

	//strcpy(nome, "../../Instancias_EDP_TP2/MDPII2_500.txt");//TODO:APAGAR ISTO

	FILE *f;
	float *p;
	int i;
	int temp_el1 = 0, temp_el2 = 0;
	float temp_dist;

	f=fopen(nome, "r");
	if(!f)
	{
		printf("Erro no acesso ao ficheiro dos dados\n");
		exit(1);
	}

	int as=-1;
	do{
		fseek(f, as, SEEK_END);
		as--;
	} while (fgetc(f) != '\n');
	fscanf(f, " %d %d %f", &temp_el1, n, &temp_dist);
	fseek(f, 0, SEEK_SET);

	// Alocacao dinamica da matriz
	p = (float *)malloc(sizeof(float)*(*n)*(*n));

	if(!p)
	{
	    printf("Erro na alocacao de memoria\n");
	    exit(1);
	}
	
	for (i = 0; i < (*n)*(*n); i++)
	{
		*(p + i) = 0;
	}
	
	
	// Preenchimento da matriz
	while(fscanf(f, " %d %d %f", &temp_el1, &temp_el2, &temp_dist)==3)
	{

         *(p+(temp_el1-1)*(*n)+ temp_el2-1) = temp_dist;
		 //printf("%d %d = %.2f\n", temp_el1 - 1, temp_el2 - 1,*(p + (temp_el1 - 1)*(*n) + temp_el2 - 1) );

	}

	fclose(f);
	return p;
}

// Gera a solucao inicial
// Parametros: solucao, numero de vertices
void gera_sol_inicial(int *sol, int v, int *rand_1)
{
	int i, x;

	for(i=0; i<v; i++)
        sol[i]=0;


	*rand_1 = random_l_h(2, v-1);
	//*rand_1 = 7;//TOODO:APAGAR ISTO

	for(i=0; i<*rand_1; i++)
    {
        do
			x = random_l_h(0, v-1);
        while(sol[x] != 0);
        sol[x]=1;
    }
	/*for (i = 0; i < v; i++)
		printf("%d ", sol[i]);*/

}

// Escreve solucao
// Parametros: solucao e numero de vertices
void escreve_sol(int *sol, int vert)
{
	int i;

	printf("\nConjunto A: ");
	for(i=0; i<vert; i++)
		if(sol[i]==0)
			printf("%2d  ", i);
	printf("\nConjunto B: ");
	for(i=0; i<vert; i++)
		if(sol[i]==1)
			printf("%2d  ", i);
	printf("\n");
}

// copia vector b para a (tamanho n)
void substitui(int a[], int b[], int n)
{
    int i;
    for(i=0; i<n; i++){
        a[i]=b[i];
		;
	}
}

// Inicializa o gerador de numeros aleatorios
void init_rand()
{
	srand(time(NULL));

}

// Devolve valor inteiro aleatorio entre min e max
int random_l_h(int min, int max)
{
	return min + rand() % (max-min+1);
}

// Devolve um valor real aleatorio do intervalo [0, 1]
float rand_01()
{
	return ((float)rand())/RAND_MAX;
}

//compara o vetor a com b (tamanho n)
int compare(int a[], int b[], int n)
{
	int i;

	for (i = 0; i < n; i++) {
		if (a[i] != b[i])
			return 0;
	}
	
	return 1;
}
