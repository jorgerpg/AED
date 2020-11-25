// Lista dinamica para receber n pokemons
// Utilizada como estrutura auxiliar ao ler o arquivo 'pokedex.bin'

// o 'L' apos as palavras no e NO foi usado para diferenciar a declaracao do deck e da mao
typedef struct nol{ 
	POKEMON dados;   
	struct nol *prox;
} NOL;

typedef NOL* LISTAE;	//Lista encadeada

LISTAE* cria_lista(){ 			// ela ir� alocar um espa�o na mem�ria;
	LISTAE *li = (LISTAE*) malloc(sizeof(LISTAE));		//Ponteiro cabe�a
	if(li != NULL) 				// Deu certo a aloca��o
		*li = NULL; 			// Faz o ponteiro apontar para NULL, ou seja, a lista est� vazia
	return li;
}	

int listase_vazia(LISTAE *l){
	if(l==NULL) return 1;
	return 0;
}

int tamanho_listase(LISTAE *l){
    int cont=0;
    NOL *atu = *l;
    while(atu!=NULL){
        cont++;
        atu=atu->prox;
    }
    return cont;
}

void destroi_listase(LISTAE *l){
	NOL *atu = *l;                  //             atu
	while (atu!=NULL){             //              l
		*l=atu->prox;              //             NULL
		free(atu);
		atu=*l;
	}
	*l=NULL;
}
// Fun��o que insere ao final da lista
int insere_fim(LISTAE *l, POKEMON p){ // Esse *l � um ponteiro que est� apontando para outro ponteiro para o endere�o de mem�ria original da LISTA*, o que est� apontando para o NULL
	if(l==NULL) return 0;
	NOL* novo_no = (NOL*)malloc(sizeof(NOL));
	if(novo_no==NULL) return 0; // N�o alocou mem�ria
	// atribuir os valores para o novo n�;
	novo_no->dados = p;		//Conte�do do n�
	novo_no->prox = NULL;	// aponta para NULL; � o �ltimo n�
	if((*l)==NULL)// Lista est� vazia, vamos inserir no in�cio
		*l = novo_no;
	else{
		NOL *aux = *l;              // novo ponteiro que aponta para a mesma posi��o do n� cabe�a. Ele ser� movido, n�o a cabe�a
		while(aux->prox != NULL){  // enquanto o pr�ximo n� n�o for nulo
			aux = aux->prox;	   // aux aponta para o pr�ximo n�
		}
		aux->prox = novo_no;	   //o antigo �ltimo n� passa a apontar para novo_no, que se torna o fim da lista
	}
	return 1;						// inser��o deu certo
}


int insereOrd(LISTAE* l, POKEMON p){
	if(l==NULL) return 0;
	NOL* novo_no = (NOL*)malloc(sizeof(NOL));
	if(novo_no==NULL) return 0; // N�o alocou mem�ria

	novo_no->dados = p;		//Conte�do do n�
// Lista est� vazia, vamos inserir no in�cio
	if((*l)==NULL || listase_vazia(l)){
		novo_no->prox = NULL;
		*l = novo_no;
	} else {
		NOL *atu = *l;              // novo ponteiro que aponta para a mesma posi��o do n� cabe�a. Ele ser� movido, n�o a cabe�a
		NOL *ant = NULL;
		int cont = 0;
		while(atu != NULL && strcmp(atu->dados.nome, p.nome) == 1){  // enquanto o pr�ximo n� n�o for nulo
			ant = atu;
			atu = atu->prox;	   // aux aponta para o pr�ximo n�
			cont++;
		}
		if(ant == NULL){
			*l = novo_no;
			novo_no->prox = NULL;
		} else {
			novo_no->prox = atu;
			ant->prox = novo_no;
		}
		
	}
	return 1;						// inser��o deu certo
}

// Remove todos os pokemons com o mesmo nome do pokemon 'p'
void remover_pokemon(LISTAE *l, POKEMON p){
	NOL* aux = *l;
	NOL* rem = *l;
	
	// Cuidado especial com a cabe�a da lista!!!
	// Enquanto os dados a serem removidos estiverem na cabe�a da lista
	// precisamos deslocar a cabe�a da lista para o pr�ximo
	while(strcmp(aux->dados.nome, p.nome)==0){
		rem = aux;
		(*l) = aux->prox; // Desloca o no cabeca para o proximo
		free(rem);
		aux = *l;
	}
	
	// N�o h� mais dados a serem removidos da cabe�a da lista
	// Remove os demais dados da lista
	while(aux->prox!=NULL){
		if(strcmp(aux->dados.nome, p.nome)==0){
			rem = aux->prox;
			aux->prox = aux->prox->prox;
			rem->prox = NULL;
			free(rem);
		}
		else aux=aux->prox;
	}
}

//ESTA COM ALGUM ERRO
// Remove um pokemon aleatorio da lista e o retorna
/*POKEMON* retira_random(LISTAE *l){
	NOL* aux = *l;
	NOL* rem = *l;
	POKEMON* temp;
	srand(time(NULL));
	
	int pos = rand() % (tamanho_listase(l)-1);	// numero aleatorio entre 0 e o ultimo elemento da lista
	printf("pos random = %d\n", pos);
	// Cuidado especial com a cabe�a da lista!!!
	// Enquanto os dados a serem removidos estiverem na cabe�a da lista
	// precisamos deslocar a cabe�a da lista para o pr�ximo
	if(pos==0){
		*temp = aux->dados;
		rem = aux;
		(*l) = aux->prox; // Desloca o no cabeca para o proximo
		free(rem);
		aux = *l;
	} else {
		int cont = 0;
		while(cont < pos){
			aux = aux->prox;
			cont++;
		}
		rem = aux->prox;
		*temp = rem->dados;
		aux->prox = aux->prox->prox;
		rem->prox = NULL;
		free(rem);
	}
	return temp;
	
}*/

void print_lista(LISTAE* l){
	NOL *aux = *l;
	int cont = 1;
	printf("LISTA ENCADEADA\n");
	while(aux != NULL){
		printf("%d - %s\n", cont, aux->dados.nome);
		aux = aux->prox;
		cont++;
	}
	printf("FIM DA LISTA\n");
}


//printa a lista l em ordem alfab�tica sem modifica-la 
void print_ord_alfabetico(LISTAE* l){
	LISTAE* clone = cria_lista();
	NOL *aux = *l;
	while(aux != NULL){
		insereOrd(clone, aux->dados);
		aux = aux->prox;
	}
	
	aux = *clone;
	int cont = 1;
	printf("LISTA ENCADEADA\n");
	while(aux != NULL){
		printf("%d - %s\n", cont, aux->dados.nome);
		aux = aux->prox;
		cont++;
	}
	printf("FIM DA LISTA\n");
}

//Enche uma lista com os pokemons da pokedex
LISTAE* enche_lista(){
	LISTAE* l = cria_lista();
	FILE *pArq;
	pArq = fopen("pokedex.bin", "rb");
	if(pArq == NULL){
		printf("Erro ao abrir arquivo\n");
		exit(1);
	}
	
	int cont = 0;
	while(getc(pArq) != EOF){				//Loop enquanto n�o chegar ao fim do arquivo
		POKEMON temp;
		fseek(pArq, cont*sizeof(POKEMON), SEEK_SET);
		fread(&temp, sizeof(POKEMON), 1, pArq);
		insere_fim(l, temp);
		cont++;
	}
	fclose(pArq);
	return l;
}
