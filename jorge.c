#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 5

typedef struct ataque{ //Bem basic�o struct do atk
    char nome[20];
    char tipo[20];
    int dano;
}ataque;

ataque cria_ataque(char *nome, char *tipo, int dano){ //Cria a struct do atk, bem obvio.
	ataque atk;
	
	strcpy(atk.nome, nome);
	strcpy(atk.tipo, tipo);
	atk.dano = dano;
	
	return atk;
}

int compara_vantagens(char *atkp1, char *tipopk2){	// compara atks, retorna 0 se � igual ou normal, retorna 1 se tem desvantagem, retorna 2 se tem vantagem
	if(strcmp(atkp1, "Normal") == 0){
		return 0;
	}
	else if(strcmp(atkp1, "Water") == 0){
		if(strcmp(tipopk2, "Grass") == 0) return 1;
		else if(strcmp(tipopk2, "Fire") == 0) return 2;
	}
	else if(strcmp(atkp1, "Fire") == 0){
		if(strcmp(tipopk2, "Water") == 0) return 1;
		else if(strcmp(tipopk2, "Grass") == 0) return 2;
	}
	else if(strcmp(atkp1, "Grass") == 0){
		if(strcmp(tipopk2, "Fire") == 0) return 1;
		else if(strcmp(tipopk2, "Water") == 0) return 2;
	}
	return 0;
}


typedef struct pokemon{ //Struct do pokemongo
	char nome[30];
	char tipo[20];
	int hp;
	ataque atk[2];
} POKEMON;

POKEMON* cria_pokemon(char *nome, char *tipo, int hp, ataque atk1, ataque atk2){ 
	//cria o pokemongo, foi complicado por conta desse malloc ai, tinha esquecido dele. Retorna o ponteiro pokemongo para ser usado na pilha(deck).
    POKEMON *p = (POKEMON*) malloc(sizeof(POKEMON));
    
    strcpy(p->nome, nome);
    strcpy(p->tipo, tipo);
    p->hp = hp;
    strcpy(p->atk[0].nome, atk1.nome);
    strcpy(p->atk[0].tipo, atk1.tipo);
    p->atk[0].dano = atk1.dano;
    strcpy(p->atk[1].nome, atk2.nome);
    strcpy(p->atk[1].tipo, atk2.tipo);
    p->atk[1].dano = atk2.dano;

    return p;
}

void imprimirPokemon(POKEMON *v){
	printf("======================\n");
	printf("Pokemon: \n");
    printf("Nome: %s\n", v->nome);
    printf("Tipo: %s\n", v->tipo);
    printf("HP: %d\n", v->hp);
    printf("Ataques: %s // %s\n", v->atk[0].nome, v->atk[1].nome);
	printf("======================\n");
}

typedef struct no{ //Struct da pilha(deck)
    POKEMON *pokemon;    
	struct no *prox;
} NO;

typedef NO* PILHA;

PILHA* cria_pilha(){  
    PILHA *pi = (PILHA*) malloc(sizeof(PILHA));
    if(pi != NULL)
        *pi = NULL;
    return pi; 
}

int pilha_vazia(PILHA *p){ 
    if(p==NULL) return 1; 
return 0; 
}

int empilha(PILHA *p, POKEMON *c){
    if(p==NULL) return 0;
    NO *novo_no = (NO*)malloc(sizeof(NO));
    if(novo_no==NULL) return 0;

    novo_no->pokemon = c;
    novo_no->prox=NULL;
    if((*p)==NULL)
        *p = novo_no;
    else{
        novo_no->prox = *p;
        *p = novo_no;
    }
    return 1;
}

void imprime_pilha(PILHA *p){ //Imprime deck
    NO *aux = *p;

    while(aux!=NULL){
        imprimirPokemon(aux->pokemon);
        aux=aux->prox;
    }
}

POKEMON *desempilha(PILHA *p){// cava o deck
    NO *topo = *p;
    int i;
    POKEMON *c = (POKEMON*) malloc(sizeof(POKEMON));

    if(topo != NULL){
        printf("======================\n");
        printf("Cavando: %s\n", topo->pokemon->nome);
		printf("======================\n\n");


        strcpy(c->nome, topo->pokemon->nome);
        strcpy(c->tipo, topo->pokemon->tipo);
        c->hp = topo->pokemon->hp;
        for(i=0;i<2;i++){
            c->atk[i] = topo->pokemon->atk[i];
        }
        
        printf("GO %s!\n", c->nome);

        *p = topo->prox;

        free(topo);

        return c;
    }else{
        printf("PILHA VAZIA!");
        return 0;
    }
}

typedef struct{ //Mão, coloquei 5 pokemons mas foi só pra teste
	int cont;
	POKEMON *pokemon[TAM];   
} Mao;

Mao* criarMao(){
	Mao *l;
	l = (Mao*)malloc(sizeof(Mao));
	if(l != NULL){
		l->cont = 0;
	}
	return l;
}

void destruirMao(Mao* l){
	free(l);
}

int tamanhoMao(Mao* l){
	if(l == NULL) return -1;
	else return l->cont;		
}

int estahVaziaMao(Mao* l){
	if(l == NULL) return -1;
	else return l->cont == 0;
}

int estaCheiaMao(Mao* l){
	if(l == NULL) return -1;
	else return l->cont == 5;
}

int inserirOrdenadoMao(Mao* l, POKEMON *v){
	int i, posicao;
	if(l==NULL) return 0;
	if(estaCheiaMao(l)) return 0;
	if(estahVaziaMao(l)) 
		posicao = 0;
	else{ // Acha a posicao para inserir
		for(i=l->cont-1; i>=0 && (strcmp(l->pokemon[i]->nome, v->nome) > 0); i--){
			l->pokemon[i+1] = l->pokemon[i];
		}
		posicao = i+1;
	}
	l->pokemon[posicao] = v;
	l->cont++;
	return 1;
}

void imprimirMao(Mao* l){
	int i;
	if(l != NULL){
		if(!estahVaziaMao(l)){
			for(i=0; i<l->cont; i++){
				imprimirPokemon(l->pokemon[i]);
			}
		}else{
			printf("Mao esta vazia!\n");
		}
	}else{
		printf("Mao nao foi criada!\n");
	}
}

int buscaBinaria(Mao *l, char *nome){ 
	int inf, sup, meio;
	inf=0;
	sup=(l->cont - 1);
	while (inf<=sup)
	{
		meio=(inf+sup)/2;
		if (strcmp(l->pokemon[meio]->nome, nome) == 0)
			return meio;
		else if (strcmp(l->pokemon[meio]->nome, nome) > 0)
			sup = meio-1;
		else
			inf=meio+1;
	}
    return -1; 
}

int remover(Mao *l, char *nome){
	int i;
	int posRem; 
	
	if(l == NULL) return -1;
	if(estahVaziaMao(l)) return -1;
	
	posRem = buscaBinaria(l, nome);
	
	// Se encontrou o nome para remover
	if(posRem >= 0){
		// Desloca os pokemons que estiverem � direita da posicao encontrada, 1 casa para esquerda
		for(i=posRem; i<l->cont; i++){
			l->pokemon[i] = l->pokemon[i+1];
		}
		l->cont--; // N�o � preciso remover o �ltimo item do vetor, pois o cont controla essa informacao	
	}
    return 1;
}


int main(){
    Mao *m;
    ataque TACKLE, BUBBLES, VINE;
    POKEMON *squirtle, *bulbasaur;
    PILHA *p;

    p = cria_pilha();
	m = criarMao();

	TACKLE = cria_ataque("Tackle", "Normal", 10);
    BUBBLES = cria_ataque("Bubbles", "Water", 10);
    VINE = cria_ataque("Vine Whip", "Grass", 10);
    
	squirtle = cria_pokemon("Squirtle", "Water", 35, TACKLE, BUBBLES);
    
    bulbasaur = cria_pokemon("Bulbasaur", "Grass", 35, TACKLE, VINE);

    empilha(p, squirtle);
    empilha(p, bulbasaur);

    inserirOrdenadoMao(m, desempilha(p));

    inserirOrdenadoMao(m, desempilha(p));

    imprimirMao(m);

	printf("%d", compara_vantagens(bulbasaur->atk[1].tipo, squirtle->tipo));

    return 0;
}
