//Henrique Alves Ferreira de Paiva - 5968 ---------- Thiago Mendes - 5959
//Bibliotecas necessarias para o codigo funcionar: STDLIB.H, STDIO.H, STRING.H;
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct sCliente{ //função para armazenar os dados dos clientes
	char nome[51], rua[51], bairro[51];
	int numero_casa, distancia/*variável de distancia do cliente ao supermercado*/, entrega/*variável de controle da entrega*/, pedidos, pesquisas;
	long long int cpf;
}Cliente;

typedef struct sCompras{
	int arroz, feijao, suco, refrigerante, material_de_limpeza, carnes; //variáveis que armazenam os valores das compras
}Compras;

typedef struct sLista{
	Cliente info;
	Compras c;
	int cabecalho; /*variável do nó cabeçalho que vai armazenar quantos clientes estão cadastrados*/
	struct sLista *esq;
	struct sLista *dir;
}Lista;

void inicializar(Lista** lista, Lista* cabecalho){ /*inicializa criando o nó cabeçalho*/
	(*lista) = cabecalho;
	(*lista)->cabecalho = 0;
	(*lista)->info.pedidos=0;
	(*lista)->info.distancia=0;
	(*lista)->info.pesquisas=0;
	(*lista)->info.entrega=0;
	(*lista)->esq = (*lista);
	(*lista)->dir = (*lista);
}

int vazia(Lista* lista){ //funcao para verificar se a lista esta vazia
	if (lista->dir == lista){
		return 1;
	}
	return 0;
}

Lista* getnode(){ //funcao para criar o no
	return (Lista*) malloc (sizeof(Lista));
}

void freenode(Lista* lista){ //funcao para apagar o no
	free(lista);
}

int inserir(Lista** lista, Cliente inserir){ //funcao insere(1)
	int ctr = 0; //variavel de controle
	Lista* aux = (*lista);
	Lista* no = getnode();

	if (no == NULL){
		printf("\n\nERRO: o no nao foi criado.\n\n");
		return 0;
	}

	no->info = inserir;
	no->cabecalho=0;
	no->info.entrega = 0;
	no->info.pedidos = 0;

	aux = aux->dir; //posicionando o auxiliar no no apos o no cabecalho
	
	if (vazia(aux)){ //se a lista tiver vazia o no vai para a primeira posicao
		(*lista)->esq = no;
		no->dir = (*lista);
		no->esq = (*lista);
		(*lista)->dir = no;
		(*lista)->cabecalho+=1;
		return 1;
	}
	do{
		if (aux->info.distancia >= no->info.distancia){ //insere o novo no ordenado pela distancia
			no->dir = aux;
			no->esq = aux->esq;
			(aux->esq)->dir = no;
			aux->esq = no;
			ctr = 1;
		}else if(aux == (*lista)->esq){
			aux->dir = no;
			no->dir = (*lista);
			(*lista)->esq = no;
			no->esq = aux;
			ctr = 1;
		}else{
			aux = aux->dir;
			ctr = 0;
		}
	}while(ctr == 0);
	(*lista)->cabecalho+=1; /*adiciona +1 ao valor int do cabecalho*/
	printf("\n\nInserido com sucesso.\n\n");
	return 1;
}

int remove_cliente(Lista** lista, long long int cpf_remover){ //funcao remove(2)
	int ctr=0;
	Lista* aux;
	aux = (*lista)->dir; //ponteiro auxiliar recebe o no apos o no cabecalho
	do{
		if (aux == (*lista)){ //se o ponteiro aux for igual ao (*lista) isso quer dizer que o do{}while japercorreu todos elementos da lista e nao encontrou
			printf("\n\nERRO: Usuario nao encontrado.\n\n");
			return 0;
		}
		if (aux->info.cpf == cpf_remover){ //se o cpf for igual o cpf que sera removido entao:
			if (aux->dir == (*lista)){ //se o no seguinte for o no cabecalho, entao o no anterior vai receber o ponteiro
				(*lista)->esq = aux->esq;
				(aux->esq)->dir = aux->dir;
				freenode(aux); //apaga o no
				(*lista)->cabecalho -=1; //remove 1 do valor total do no cabecalho
				return 1;
			}else{ //se o no seguinte nao for o no cabecalho, entao o no encontrado sera deletado
				(aux->esq)->dir = aux->dir;
				(aux->dir)->esq = aux->esq;
				freenode(aux); //apaga o no
				(*lista)->cabecalho -=1; //remove 1 do valor total do no cabecalho
				return 1;
			}
		}else{
			aux = aux->dir;
			ctr=0;
		}
	}while(ctr == 0);
}

int alterar_dados(Lista** lista, long long int cpf_procurar, Cliente novo){ //funcaoo de alterar os dados dos clientes(3)
	int ctr=0, ctr2=0, ctr3=0; //variavel de controle do do{}while.
	int dado, res;
	Lista* aux;
	Lista* aux2;
	aux2 = (*lista); //aux2 aponta para o no cabecalho
	aux = (*lista)->dir; //aux aponta para o nodepois do cabecalho
	
	do{
		if (aux->info.cpf == cpf_procurar){
			system("cls");
			printf("\n\nCliente encontrado: %s\n\n", aux->info.nome);
			ctr2=1;
		}else{
			aux = aux->dir;
			ctr2=0;
		}
		if (aux == (*lista)){ //se o ponteiro aux for igual ao (*lista) isso quer dizer que o do{}while já percorreu todos elementos da lista e não encontrou
			printf("\n\nERRO: Usuario nao encontrado.\n\n");
			return 0;
		}
	}while(ctr2 == 0);

	do{
		system("cls");
		printf("\n\nInsira qual dado deseja alterar:\n\n");
		printf("1 - Rua\n");
		printf("2 - Bairro\n");
		printf("3 - Numero da casa\n");
		printf("4 - Distancia\n");
		printf("0 - Finalizar\n\n");
		scanf("%d", &dado);

		if (dado > 0 && dado < 7){ //if para verificar se a escolha vai ser válida
			ctr = 0;
		}else if(dado == 0){
			ctr = 1;
			return 1;
		}else{
			printf("\n\nERRO: Escolha invalida.\n\n");
		}
		
		if (dado == 1){
			printf("\n\nDigite a nova rua: ");
			fflush(stdin);
			scanf("%[^\n]", novo.rua);
			(*lista) = aux; //*lista vai para o no que sera alterado
			strcpy ((*lista)->info.rua,novo.rua); //altera a informacao do no
			(*lista) = aux2; //*lista retora ao no cabecalho
		}else if (dado == 2){
			printf("\n\nDigite o novo bairro: ");
			fflush(stdin);
			scanf("%[^\n]", novo.bairro);
			(*lista) = aux;
			strcpy ((*lista)->info.bairro, novo.bairro);
			(*lista) = aux2;
		}else if (dado == 3){
			printf("\n\nDigite o novo numero da casa: ");
			scanf("%d", &novo.numero_casa);
			(*lista) = aux;
			(*lista)->info.numero_casa = novo.numero_casa;
			(*lista) = aux2;
		}else if (dado == 4){
			do{
				printf("\n\nDigite a nova distancia da sua casa ao supermercado: ");
				scanf("%d", &novo.distancia);
				if (novo.distancia > 0){
					(*lista) = aux;
					(*lista)->info.distancia = novo.distancia;
					(*lista) = aux2;
					ctr3 = 1;
				}else{
					printf("\nInsira uma distancia valida.\n\n");
					ctr3 = 0;
				}
			}while(ctr3 == 0);
		}
	}while(ctr == 0);
}

void imprimir(Lista** lista){ //funçao para imprimir os dados de todos clientes(4)
	int ctr=0; //variavel de controle do do{}while.
	Lista* aux;
	aux = (*lista); //aux recebe o nó cabeçalho

	do{
		aux = aux->dir; //aux vai para o próx nó
		printf("\nNome: %s\n", aux->info.nome);
		printf("CPF: %lld\n", aux->info.cpf);
		printf("Bairro: %s\n", aux->info.bairro);
		printf("Rua: %s\n", aux->info.rua);
		printf("Numero: %d\n", aux->info.numero_casa);
		printf("Distancia: %d\n", aux->info.distancia);
		printf("Pedidos realizados: %d\n\n", aux->info.pedidos);
		if (aux->dir == (*lista)){ //se o aux for igual o *lista entao ele ja percorreu todos elementos
			ctr = 1;
		}
	}while(ctr == 0);
}

Cliente cadastrar(Cliente cli){ //funcao que cadastra um cliente novo coletando seus dados
	system("cls");
	printf("\n----------Cadastro de Cliente----------\n\n");
	printf("Digite o nome do cliente: ");
	fflush(stdin);
	gets(cli.nome);
	fflush(stdin);
	printf("\nDigite o CPF do cliente: ");
	scanf("%lld", &cli.cpf);
	printf("\nDigite o bairro do cliente: ");
	fflush(stdin);
	gets(cli.bairro);
	fflush(stdin);
	printf("\nDigite a rua do cliente: ");
	fflush(stdin);
	gets(cli.rua);
	fflush(stdin);
	printf("\nDigite o numero da casa do cliente: ");
	scanf("%d", &cli.numero_casa);
	printf("\nDigite a distancia entre a casa do cliente ao supermercado(em metros): ");
	scanf("%d", &cli.distancia);
	printf("\n\n----------Cadastro Finalizado----------\n");
	return cli;
}

void compras(Lista** lista){ // funcao de coletar os produtos que o cliente vai comprar
	Lista* aux;
	Lista* aux2;
	int ctr, ctr2, ctr3, compra, qtd;
	aux2 = (*lista);
	aux = (*lista)->dir;
	system("cls");
	printf("----------Realizar as compras----------\n");
	do{
		system("cls");
		printf("\n----------Opcoes----------\n");
		printf("Responda 1 para sim        -\n");
		printf("Responda 0 para nao        -\n");
		printf("----------------------------\n");
		printf("\nCliente %s deseja fazer as compras? ", aux->info.nome); //pergunta se o cliente quer fazer a compra do mes
		scanf("%d", &compra);
		do{
			if (compra == 1){
				system("cls");
				printf("\n-------------------------------Compras--------------------------------\n");
				printf("\n------------------------------Opcoes----------------------------------\n");
				printf("Responda qualquer numero para adicionar aquela quantidade ao carrinho-\n");
				printf("Responda 0 para nao adicionar ao carrinho                            -\n");
				printf("----------------------------------------------------------------------\n");
				do{																	// armazena os produtos que o cliente deseja receber
					printf("\nDeseja adicionar arroz(por 5kg) ao carrinho? ");
					scanf("%d", &qtd);
					if (qtd >= 1){
						(*lista) = aux; //*lista vai para o cliente
						(*lista)->c.arroz = qtd; //*lista altera a compra do cliente
						(*lista) = aux2; //*lista volta para o cabeçalho
						ctr2=1;
					}else if(qtd == 0){
						(*lista) = aux; 
						(*lista)->c.arroz = qtd; 
						(*lista) = aux2; 
						ctr2=1;
					}else{
						printf("ERRO: Escolha invalida.");
						ctr2=0;
					}
				}while(ctr2 == 0);
				
				do{
					printf("\nDeseja adicionar feijao(por 1kg) ao carrinho? ");
					scanf("%d", &qtd);
					if (qtd >= 1){
						(*lista) = aux; 
						(*lista)->c.feijao = qtd; 
						(*lista) = aux2; 
						ctr2=1;
					}else if(qtd == 0){
						(*lista) = aux; 
						(*lista)->c.feijao = qtd; 
						(*lista) = aux2; 
						ctr2=1;
					}else{
						printf("ERRO: Escolha invalida.");
						ctr2=0;
					}
				}while(ctr2 == 0);
				
				do{
					printf("\nDeseja adicionar suco(por 1 litro) ao carrinho? ");
					scanf("%d", &qtd);
					if (qtd >= 1){
						(*lista) = aux; 
						(*lista)->c.suco = qtd; 
						(*lista) = aux2; 
						ctr2=1;
					}else if(qtd == 0){
						(*lista) = aux; 
						(*lista)->c.suco = qtd; 
						(*lista) = aux2;
						ctr2=1;
					}else{
						printf("ERRO: Escolha invalida.");
						ctr2=0;
					}
				}while(ctr2 == 0);
				
				do{
					printf("\nDeseja adicionar refrigerante(por 2 litros) ao carrinho? ");
					scanf("%d", &qtd);
					if (qtd >= 1){
						(*lista) = aux; 
						(*lista)->c.refrigerante = qtd; 
						(*lista) = aux2; 
						ctr2=1;
					}else if(qtd == 0){
						(*lista) = aux; 
						(*lista)->c.refrigerante = qtd; 
						(*lista) = aux2; 
						ctr2=1;
					}else{
						printf("ERRO: Escolha invalida.");
						ctr2=0;
					}
				}while(ctr2 == 0);
				
				do{
					printf("\nDeseja adicionar material de limpeza (por kit completo) ao carrinho? ");
					scanf("%d", &qtd);
					if (qtd >= 1){
						(*lista) = aux; 
						(*lista)->c.material_de_limpeza = qtd; 
						(*lista) = aux2; 
						ctr2=1;
					}else if(qtd == 0){
						(*lista) = aux; 
						(*lista)->c.material_de_limpeza = qtd; 
						(*lista) = aux2; 
						ctr2=1;
					}else{
						printf("ERRO: Escolha invalida.");
						ctr2=0;
					}
				}while(ctr2 == 0);
				
				do{
					printf("\nDeseja adicionar carne(por 1 kg) ao carrinho? ");
					scanf("%d", &qtd);
					if (qtd >= 1){
						(*lista) = aux; 
						(*lista)->c.carnes = qtd; 
						(*lista) = aux2; 
						ctr2=1;
					}else if(qtd == 0){
						(*lista) = aux; 
						(*lista)->c.carnes = qtd; 
						(*lista) = aux2;
						ctr2=1;
					}else{
						printf("ERRO: Escolha invalida.");
						ctr2=0;
					}
				}while(ctr2 == 0);
				system("cls");
				printf("----------Compras realizadas----------\n");
				printf("\nCliente: %s", aux->info.nome);
				printf("\nArroz: %d", aux->c.arroz);
				printf("\nFeijao: %d", aux->c.feijao);
				printf("\nSuco: %d", aux->c.suco);
				printf("\nRefrigerante: %d", aux->c.refrigerante);
				printf("\nMaterial de Limpeza: %d", aux->c.material_de_limpeza);
				printf("\nCarne: %d", aux->c.carnes);
				printf("\n-----------------------------------\n");
				(*lista) = aux;
				(*lista)->info.pedidos += 1; //a variavel de pedidos aumenta em 1
				(*lista)->info.entrega = 1; //a variavel de entrega passa a ser 1 para o cliente receber seu pedido
				(*lista) = aux2;
				system("pause");
				aux = aux->dir;
				ctr=0;
				ctr3 = 1;
			}else if(compra == 0){
				aux = aux->dir;
				ctr=0;
				ctr3 = 1;
			}else{
				printf("\n\nERRO: Valor invalido.\n\n");
				ctr3 = 0;
			}
		}while(ctr3 == 0);
		if (aux == (*lista)){
			ctr=1;
			printf("\n\nClientes atendidos!!\n\n");
		}
	}while(ctr == 0);
}

void compras_contar(Lista** lista){ //funcao que mostra quais clientes realizaram compras e estão esperando a entrega
	Lista* aux;
	int total=0, ctr;
	
	aux = (*lista)->dir;
	printf("\nClientes que fizeram suas compras:\n\n");
	
	do{
		if (aux->info.entrega == 1){
			total+= 1;  //variavel que guarda a quantidade de clientes que fizeram compras
			printf("\n%s\n", aux->info.nome);
			ctr = 0;
		}
		
		aux = aux->dir;
		
		if (aux == (*lista)){
			ctr = 1;
		}
		
	}while(ctr == 0);
	printf("\n\n");
	if (total == 0){
		printf("\nNenhum cliente realizou compras.\n\n");
	}
}

void entregar(Lista** lista){ //funcao responsavel por organizar as entregas
	Lista* aux;
	int ctr = 0, n = 1, etr /*variavel para armazenar a entrega*/;

	aux = (*lista)->dir;

	printf("\n----------Entregas----------\n");
	if(verifica_pedidos(lista)){
		do{
			if (aux->info.entrega == 1){  //se a variavel de entrega for 1, entao o cliente sera atendido
				printf("\n\nEntrega %d:\n\n", n);
				printf("Cliente: %s\n\n", aux->info.nome);
				printf("Endereco: Bairro %s, Rua %s, Numero: %d\n\n", aux->info.bairro, aux->info.rua, aux->info.numero_casa);
				printf("Produtos:\n\n");
				if (aux->c.arroz > 0){
					printf("%d sacos de arroz\n", aux->c.arroz);
				}
				if (aux->c.feijao > 0){
					printf("%d sacos de feijao\n", aux->c.feijao);
				}
				if (aux->c.suco > 0){
					printf("%d caixas de suco\n", aux->c.suco);
				}
				if (aux->c.refrigerante > 0){
					printf("%d litros de refrigerante\n", aux->c.refrigerante);
				}
				if (aux->c.material_de_limpeza > 0){
					printf("%d kits de material de limpeza\n", aux->c.material_de_limpeza);
				}
				if (aux->c.carnes > 0){
					printf("%dkg de carne\n\n", aux->c.carnes);
				}
				printf("Entrega realizada? (1 para sim / 0 para nao): ");
				scanf("%d", &etr);
				printf("\n\n");
				if (etr == 1){  //caso a entrega seja realizada, a variavel de entrega volta ao valor 0
					aux->info.entrega = 0;
				} //caso nao seja realizada a variavel continua 1 para o cliente ser atendido
				n++;
			}
			if (ctr == 0) { // se a variavel ctr for 0 a lista percorre o caminho normal
				aux = aux->dir;
			}else {  //se a variavel nao for 0 a lista percorre o caminho inverso
				aux = aux->esq;
			}
	
			if (aux == (*lista)) {
				if (ctr == 0) {
					ctr = 1;
				} else {
					printf("\n\nTodos clientes foram atendidos.\n\n");
					break;
				}
			}
		}while(1);
	}else{
		printf("\n\nERRO: Nao ha nenhum cliente com pedidos.\n\n");
	}
}

void pesquisa(Lista** lista, long long int cpf){
	Lista* aux;
	Lista* aux2;
	int ctr = 1;
	aux = (*lista)->dir;
	aux2 = (*lista);
	
	do{
		if (cpf == aux->info.cpf){
			(*lista) = aux;
			(*lista)->info.pesquisas +=1;
			(*lista) = aux2;
			printf("\nNome: %s\n", aux->info.nome);
			printf("CPF: %lld\n", aux->info.cpf);
			printf("Bairro: %s\n", aux->info.bairro);
			printf("Rua: %s\n", aux->info.rua);
			printf("Numero: %d\n", aux->info.numero_casa);
			printf("Distancia: %d\n", aux->info.distancia);
			printf("Pedidos realizados: %d\n\n", aux->info.pedidos);
			printf("Pesquisas realizadas: %d\n\n", aux->info.pesquisas);
			ctr = 1;
		}else{
			aux = aux->dir;
			ctr = 0;
			if (aux == (*lista)){
				printf("\n\nCliente nao encontrado.\n\n");
				ctr = 1;
			}
		}
	}while(ctr == 0);
}

void mais_pesquisados(Lista** lista){ //funcao que imprime em ordem os clientes com mais pedidos
	Lista* aux;
	aux = (*lista)->dir;     
	int mais_pesquisado=0, ctr=0, i;
	
	do{
		if (aux->info.pesquisas >= mais_pesquisado){
			mais_pesquisado = aux->info.pesquisas;
		}
		
		aux = aux->dir; //aux vai para o proximo no
		
		if (aux == (*lista)){ // se o aux estiver no cabecalho ele sai do do{}while 	
			ctr = 1;
		}
	}while(ctr == 0);
	
	aux = aux->dir;
	
	if (mais_pesquisado == 0){
		printf("\n\nNenhuma pesquisa foi realizada.\n\n");
	}else{
		for(i=mais_pesquisado; i>=0; i--){
			ctr = 0; //reinicia a variavel de controle do do{}while
			if (aux->cabecalho != 0){
				aux = aux->dir;
			}
			do{
				if (aux->info.pesquisas == i){
					printf("\nNome: %s\n", aux->info.nome);
					printf("CPF: %lld\n", aux->info.cpf);
					printf("Bairro: %s\n", aux->info.bairro);
					printf("Rua: %s\n", aux->info.rua);
					printf("Numero: %d\n", aux->info.numero_casa);
					printf("Distancia: %d\n", aux->info.distancia);
					printf("Pesquisas realizadas: %d\n\n", aux->info.pesquisas);
					aux = aux->dir;
					if (aux == (*lista)){ // se o aux estiver no cabecalho ele sai do do{}while 	
						ctr = 1;
					}
				}else{
					aux = aux->dir;
					if (aux == (*lista)){ // se o aux estiver no cabecalho ele sai do do{}while 	
						ctr = 1;
					}
				}
			}while(ctr == 0);
		}
	}
}

int verifica_pedidos(Lista** lista){ //funcao que verifica se ainda tem clientes que nao foram atendidos
	Lista* aux;
	int ctr=0;
	
	aux = (*lista)->dir;
	do{
		if (aux->info.pedidos != 0){ //se a variavel pedido for diferente de 0 então o cliente ainda nao foi atendido
			return 1;
		}else{
			aux = aux->dir;	
		}
		
		if (aux == (*lista)){ //se a lista foi percorrida e nenhum cliente precisa ser atendido, a função retorna 0
			return 0; 
		}
	}while(ctr == 0);
}

void cadastrados(Lista** lista){
	printf("\n\nClientes cadastrados: %d\n\n", (*lista)->cabecalho);
}

int main(){
	int op;
	long long int cpf;
	Lista* lista;
	Lista* cabecalho = getnode();
	Cliente cli;
	Cliente novo;

	inicializar(&lista, cabecalho);

	do{
		system("cls"); //limpar o console
		printf("--------------------------MENU-------------------------\n");
		printf("                                                      -\n");
		printf("Escolha uma opcao:                                    -\n");
		printf("                                                      -\n");
		printf("1 - Cadastrar cliente                                 -\n");
		printf("2 - Remover cliente                                   -\n");
		printf("3 - Alterar dados do cliente                          -\n");
		printf("4 - Imprimir dados dos clientes                       -\n");
		printf("5 - Pesquisar um cliente especifico                   -\n");
		printf("6 - Imprimir lista de clientes mais pesquisado        -\n");
		printf("7 - Fazer o pedido das compras                        -\n");
		printf("8 - Verificar quantos clientes realizaram as compras  -\n");
		printf("9 - Realizar entregas                                 -\n");
		printf("10 - Quantos clientes estao cadastrados               -\n");
		printf("0 - Finalizar                                         -\n");
		printf("                                                      -\n");
		printf("-------------------------------------------------------\n\n");
		scanf("%d", &op);
		printf("\n");

		if (op == 1){
			cli = cadastrar(cli);
			inserir(&lista, cli);
		}else if (op == 2){
			system("cls");
			if(vazia(lista)){
				printf("\n\nERRO: Lista vazia.\n\n");
			}else{
				printf("\nInsira o CPF do cliente que sera removido: ");
				scanf("%lld", &cpf);
				if(remove_cliente(&lista, cpf)){
					printf("\nRemovido com sucesso.\n\n");
				}
			}
		}else if (op == 3){
			system("cls");
			if(vazia(lista)){
				printf("\n\nERRO: Lista vazia.\n\n");
			}else{
				printf("\nInsira o CPF do cliente que tera um dado alterado: ");
				scanf("%lld", &cpf);
				if(alterar_dados(&lista, cpf, novo)){
					printf("\n\nDados alterados com sucesso.\n\n");
				}
			}
		}else if (op == 4){
			system("cls");
			if(vazia(lista)){
				printf("\n\nERRO: Lista vazia.\n\n");
			}else{
				imprimir(&lista);
			}
		}else if (op == 5){
			system("cls");
			if(vazia(lista)){
				printf("\n\nERRO: Lista vazia.\n\n");
			}else{
				printf("\nInsira o CPF do cliente que deseja pesquisar: ");
				scanf("%lld", &cpf);
				pesquisa(&lista, cpf);
			}
		}else if (op == 6){
			system("cls");
			if(vazia(lista)){
				printf("\n\nERRO: Lista vazia.\n\n");
			}else{
				mais_pesquisados(&lista);
			}
		}else if (op == 7){
			system("cls");
			if(vazia(lista)){
				printf("\n\nERRO: Lista vazia.\n\n");
			}else{
				compras(&lista);
			}
		}else if (op == 8){
			system("cls");
			if(vazia(lista)){
				printf("\n\nERRO: Lista vazia.\n\n");
			}else{
				compras_contar(&lista);
			}
		}else if (op == 9){
			system("cls");
			if(vazia(lista)){
				printf("\n\nERRO: Lista vazia.\n\n");
			}else{
				entregar(&lista);
			}
		}else if (op == 10){
			system("cls");
			if(vazia(lista)){
				printf("\n\nERRO: Lista vazia.\n\n");
			}else{
				cadastrados(&lista);
			}
		}else if (op == 0){
			printf("\n\nFinalizando...\n\n");
			return 0;
		}else{
			printf("\n\nERRO: Escolha invalida.\n");
		}
		system("pause");
	}while(op != 0);
	return 0;
}
