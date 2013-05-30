#include "bs-tree.h"


node *Raiz;
int vezes;


/*----------------------------------------------------------------------------*/
/* Calcula altura da arvore                                                   */
/*----------------------------------------------------------------------------*/
int h_tree( node **n) {
	node *current =*n;
	int hl, hr;
	if ( !current ) {
		return 0;
	}
	hl =h_tree( &(current->left) );
	hr =h_tree( &(current->right) );
	if (hl>hr) {
		return hl+1;
	}
	else {
		return hr+1; 
	}
}


/*----------------------------------------------------------------------------*/
/* Visualizacao da arvore sem arquivo                                         */
/*----------------------------------------------------------------------------*/
void show_tree_sem_arq( node *n, int b ) {
	int i;
	object o;
	if (n == NULL) {
		for (i = 0; i < b; i++) 
			printf("      ");
		printf("*\n"); //aponta pra NULL
		return;
	}
	show_tree_sem_arq( n->right, b+1 );
	for (i = 0; i < b; i++) 
		printf("      ");
	o =n->value;
    	printf("%d", o );
	printf("(%i)", n->balance );
	printf("\n");
	show_tree_sem_arq( n->left, b+1 );
}

void show_tree_sem_arq1( node *n,int b ) {
	printf("-------------------------------------------------------------------------------------------------\n");
	show_tree_sem_arq (n, b);
	printf("-------------------------------------------------------------------------------------------------\n");
}


/*----------------------------------------------------------------------------*/
/* Faz a compraracao entre dois objects                                       */
/*----------------------------------------------------------------------------*/
int objectcmp( object *o1, object *o2 ) {
  return *o1 < *o2 ? -1 : *o1 > *o2 ? 1 : 0;
}


/*----------------------------------------------------------------------------*/
/* Cria e aloca um novo no                                                    */
/*----------------------------------------------------------------------------*/
node *create_node( node **n) {
	node *new_node;
	if ( !(new_node = malloc(sizeof(node)))) {
		 fprintf (stderr, "Error while running Binary Tree Library: Alloc node failed.\n");
		 exit (1);
	}
	new_node->value = 0;
	new_node->balance = 0;
	new_node->left = NULL;
	new_node->right = NULL;
	*n = new_node;
	return *n;
}


/*----------------------------------------------------------------------------*/
/* Rotaciona o node para a esquerda                                           */
/*----------------------------------------------------------------------------*/
void rotation_left( node **n) {

	node *a = *n;
	node *b = (*n)->right;

	a->right = b->left;
	b->left = a;

	(*n) = b;

	int al, ar, bl, br;

	al = h_tree ( &(a->left) );
	ar = h_tree ( &(a->right) );
	bl = h_tree ( &(b->left) );
	br = h_tree ( &(b->right) );
	a->balance = al - ar;
	b->balance = bl - br;

	vezes = vezes +1;
	printf("fez %d rotacoes \n", vezes);

}

/*----------------------------------------------------------------------------*/
/* Rotaciona o node para a direita                                            */
/*----------------------------------------------------------------------------*/
void rotation_right( node **n) {

	node *a = *n;
	node *b = (*n)->left;

	a->left = b->right;
	b->right = a;

	(*n) = b;

	int al, ar, bl, br;

	al = h_tree ( &(a->left) );
	ar = h_tree ( &(a->right) );
	bl = h_tree ( &(b->left) );
	br = h_tree ( &(b->right) );
	a->balance = al - ar;
	b->balance = bl - br;

	vezes = vezes +1;
	printf("fez %d rotacoes \n", vezes);

}


/*----------------------------------------------------------------------------*/
/* Conta Node                                                                 */
/*----------------------------------------------------------------------------*/
int conta_node( node **n) {
	int conta = 0 ;
	node *current = *n;
	if ( !current ) return 0;
	conta = 1 + conta_node( &(current->left) ) + conta_node( &(current->right) ); 
	return conta;
}


/*----------------------------------------------------------------------------*/
/* Insere um node na arvore                                                   */
/*----------------------------------------------------------------------------*/
int insert_node_r( node **n, object *o) {
	// curret = endereco de uma estrutura de um ponteiro node
	node *current = *n;

	// Se nao tem current alocado, cria um node  (BASE)
	if( !current ) {

		// Se nao conseguir criar um novo node
		if( !(current = create_node( &current ) ) ) 
            return 0;
		current->value = *o;
		*n = current;
		return 1;

	// Senao compara o objeto com o objeto do valor que tem na arvore
	} else if( objectcmp( o, &current->value ) == -1 ) {
		if( insert_node_r( &(current->left ), o ) == 1){
			current->balance++;
			return 1;
		}
	} else if( objectcmp( o, &current->value ) == 1 ) {
		if( insert_node_r( &(current->right ), o) == 1){
			current->balance--;
			return 1;
		}
	}
	return 0;
}
int insert_node( node **n, object *o) {
	// curret =enderco de uma estrutura de um ponteiro node
	if ( !Raiz ) {

		// Se nao conseguir criar um novo node
		if( !(Raiz = create_node( &Raiz ) ) ) 
			return 0;
		Raiz->value = *o;
		return 1;
	}
	if ( !(insert_node_r( n, o ) ) )
		return 0;
	return 1;
}


/*----------------------------------------------------------------------------*/
/* Particonamento da Arvore                                                   */
/*----------------------------------------------------------------------------*/
node *particao_arv_teste( node **n, int k ){
	node *current = *n;
	int t = conta_node ( &(current->left) ),
  	l = conta_node ( &(current->right) );
	if ( t+1 == k) {
		return current;
	}
	if ( k <= t) {
		current->left = particao_arv_teste( &(current->left), k );
		rotation_right( &current );

		vezes = vezes +1;
		printf("fez %d rotacoes \n", vezes);

		return current;
	}
	current->right = particao_arv_teste( &(current->right), k - t - 1);
	rotation_left( &current );

	vezes = vezes +1;
	printf("fez %d rotacoes \n", vezes);

	return current;
}


node *particao_arv_r( node **n, int k ){
  	int t, l;
	node *current = *n;
  	t = conta_node ( &(current->left) );
  	if( t > k ) {
     	current->left = particao_arv_r( &(current->left), k );
		rotation_right( &current );

		vezes = vezes +1;
		printf("fez %d rotacoes \n", vezes);

  	} 
  	if( t < k ) {
     	current->right = particao_arv_r( &(current->right), k -t -1 );
 		rotation_left( &current );

		vezes = vezes +1;
		printf("fez %d rotacoes \n", vezes);

  	} 
  	return current;
}

node *particao( node **n, int k ){
	printf("Iniciando particionamento\n");
	node *current = *n;
  	if( (conta_node( &current )) <= k ) {
    		return current;
	}
  	else {
		printf("Particao recursiva\n");
    		return particao_arv_teste( &current, k );
	}
}


/*----------------------------------------------------------------------------*/
/* Arruma Arvore                                                              */
/*----------------------------------------------------------------------------*/
node	*arruma_arvore_r (node **n ) {
	node *current = *n;
	int qtd_nl = conta_node ( &(current->left) )/2, 
	    qtd_nr = conta_node ( &(current->right) )/2; 

	printf("Aruma Recursivamente\n");

	// Se o numero for par
	if ( !(qtd_nl % 2) )
		qtd_nl = qtd_nl/2;
	else
		qtd_nl = qtd_nl/2 + 1;

	// Se o numero for par
	if ( !(qtd_nr % 2) ) 
		qtd_nr = qtd_nr/2;
	else
		qtd_nr = qtd_nr/2 + 1;

		printf("metade dos nodos esquerdo %d\n", qtd_nl);
		printf("metade dos nodos direito %d\n", qtd_nr);

	if ( !current )
		return NULL;	

	if ( qtd_nl > 0 ) {
		printf("Particiona sub-arvore esquerda\n");
		current->left = particao( &(current->left), qtd_nl );
	}

	if (qtd_nr > 0 ) {
		printf("Particiona sub-arvore esquerda\n");
		current->right = particao( &(current->right), qtd_nr );
	}
	return current;
}


node *arruma_arvore () {
	node *l =Raiz->left, 
		*r =Raiz->right;
	int qtd_n = conta_node ( &Raiz );

	// Se o numero for par
	if ( !(qtd_n % 2) )
		qtd_n = qtd_n/2;
	else
		qtd_n = qtd_n/2 + 1;

	printf("metade dos nodos da raiz = %d\n", qtd_n );
 	Raiz = particao( &Raiz, qtd_n );
	printf("Aruma lado esquerdo\n");
	Raiz->left = arruma_arvore_r ( &(Raiz->left) );
	printf("Aruma lado direito\n");
	Raiz->right = arruma_arvore_r ( &(Raiz->right) );
	return Raiz;
}

main () {
	char choose;
	int control = 1, altura;
	object valor;
	Raiz = NULL;
	vezes = 0;
	printf("Iniciando interacoes\n");
	// Enquanto nao acabar o arquivo de leitura
	while ( control ) {
		printf("\nIniciando nova secao\n");
		scanf("%c", &choose );
		switch ( choose ) {
		case 'i': printf("++ insercao\n");
				scanf("%d", &valor );
				printf("%d\n", valor );
				insert_node( &Raiz, &valor );
			break;
		case 'b': printf("++ busca\n");
				scanf("%d", &valor);
				printf("%d\n", valor);
			break;
		case 'r': printf("++ remocao\n");
				scanf("%d", &valor);
				printf("%d\n", valor);
			break;
		default:	printf("++ nada\n");
				printf("Finalizando o Programa\n");
		 		control =0;
			break;
		}
		// Se existir uma Raiz, possibilidade do arquivo estar vazio
		if (Raiz) {
			// Enquanto nao chegar no final da linha do arquivo lido
			while (choose != 10) {
				scanf("%c", &choose );
			}
			altura = h_tree( &Raiz );
 			show_tree_sem_arq1 ( Raiz, altura );
		}
	}
	// Se existir uma Raiz, possibilidade do arquivo estar vazio
	if (Raiz) {
		printf("Arrumando arvore\n");
		Raiz = arruma_arvore ();
		printf("arvore final \n");
		altura = h_tree( &Raiz );
 		show_tree_sem_arq1 ( Raiz, altura );
		printf("fez %d rotacoes \n", vezes);
	}
}
