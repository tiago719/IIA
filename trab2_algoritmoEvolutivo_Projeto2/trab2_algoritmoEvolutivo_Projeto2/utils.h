struct info init_data(char *s, float max[][MAX_OBJ]);

pchrom init_pop(struct info d);

void escreve_sol(int *sol, int vert);//TODO: APAGAR ISTO

//void print_pop(pchrom pop, struct info d);

chrom get_best(pchrom pop, struct info d, chrom best);

int compare(pchrom s1, pchrom s2);

void write_best(chrom x, struct info d);

void init_rand();

int random_l_h(int min, int max);

float rand_01();

int flip();
