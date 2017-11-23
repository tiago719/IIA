#include "funcao.h"

// Calcula a qualidade de uma solução
// Recebe:  A solução, a, a matriz de adjacências, mat, e o número de vértices, vert
// Devolve: O custo que é o número de ligações que existem na solução
float calcula_fit(int a[], float *mat, int vert)
{
	int flag=0;
	int i, j, iaux;
	float total = 0;

	for(i=0; i<vert; i++){
		if(a[i]==1)
		{
			for(j=i+1; j<vert;j++){
				if (a[j] == 1) {
					total += *(mat + (i)*vert + (j));
					//printf("\nCUSTO: i = %d    j=  %d    conta= %.2f", i, j , *(mat + (i)*vert + (j )));

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
			
				    //total++;
		}
		
	}
	return total;
}
