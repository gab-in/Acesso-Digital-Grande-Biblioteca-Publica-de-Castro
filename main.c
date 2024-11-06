#include <stdio.h>
#include <stdlib.h>

//É óbvio que a professora queria de um jeito, então eu tentei seguir o padrão, mas eu deixei as variáveis de um jeito que >>>>eu<<<<< acho mais bonito e original;

typedef struct Livro{
	int codigo;
	char titulo[20], autor[15], genero[15];
	int Status; // 1-Disponível, 2-Reservado, 3-Emprestado
	int numReservas, quTotal;
}Livro;

typedef struct Leitor{
	int codigo;
	char nome[20], email[15];
	int qtdeEmp, histMulta;
}Leitor;

typedef struct Funcionario{
	int codigo;
	char nome[20], cargo[15];
	int totalEmp, totalDev;
}Funcionario;




//Funções da minha parte

void Cadastros(){
	int tipo;

	printf("\n-----------------------------------------------------------------------");
	printf("\nQue tipo de cadastro? Escolha uma das opções listadas abaixo");
	printf("\n-----------------------------------------------------------------------");
	printf("\n(1) Leitores | (2) Funcionários | (3) Voltar");
	printf("\n\nDigite um número: "); scanf("%d",&tipo); while ((getchar()) != '\n');
	
	switch(tipo){
		case 1:
			system("clear");
			Leitor *novoLeitor=(Leitor*)malloc(sizeof(Leitor));
			novoLeitor->qtdeEmp=0;
			novoLeitor->histMulta=0;
			//O sistema de  atribuição de código que vale para todos os typedef que eu vou fazer vai ter que ser dinâmico, o que significa que depende de vocêKKKKKKKK
			
			//Nome
			printf("\n-----------------------------------------------------------------------");
			printf("\nInforme o seu nome (20 caracteres max.)");
			printf("\n-----------------------------------------------------------------------");
			printf("\n\nDigite: ");fgets(novoLeitor->nome, 20, stdin);
			//Email
			printf("\n-----------------------------------------------------------------------");
			printf("\nInforme o email (15 caracteres max.)");
			printf("\n-----------------------------------------------------------------------");
			printf("\n\nDigite: "); fgets(novoLeitor->email, 15, stdin);
			
			return;
		case 2:
			
			break;
		case 3:

			return;
	} Cadastros();
}

//Funções gerais/básicas do programa

void Inicio(){ //EXISTE SISTEMA DE CONTA!!! Vai ter que existir MenuLeitor(); MenuFuncionario(); futuramente
	int esc;
	
	printf("\n-----------------------------------------------------------------------");
	printf("\nPor favor, escolha uma das opções listadas abaixo!");
	printf("\n-----------------------------------------------------------------------");
	printf("\n(1) Cadastrar | (2) Login | (3) Sair"); 
	printf("\n\nDigite um número: "); scanf("%d",&esc);
	
	switch(esc){
		case 1: //Escolheu Cadastrar
			Cadastros();
			break;
		case 2: //Escolheu Login
			break;
		case 3: //Escolheu Sair
			return;
	} Inicio();
}






int main(){ //Vamo fazer igual foi no jogo, onde a main só faz chamar função
	printf("-----------------------------------------------------------------------");	
	printf("\nBem vindo(a) ao acesso digital da Grande Biblioteca Publica de Castro!"); //Interface bonitinha
	printf("\n-----------------------------------------------------------------------\n\n");
	
	Inicio();
	
	printf("\n-----------------------------------------------------------------------");
	printf("\nAgradecemos a prefrência! Volte sempre.");
	printf("\n-----------------------------------------------------------------------");
}
