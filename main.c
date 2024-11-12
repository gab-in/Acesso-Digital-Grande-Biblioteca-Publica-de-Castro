#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>

const char SENHA_ADM[]="5678";
const char SENHA_OP[]="1234";

typedef struct Leitor{
	int codigo;
	char nome[20], email[25];
	int qtdeEmp, histMulta;
}Leitor;

typedef struct Funcionario{
	int codigo;
	char nome[20], cargo[15];
	int totalEmp, totalDev;
}Funcionario;


typedef struct Livro{
	int codigo;
	char titulo[30], autor[15], genero[15];
	int Status; // 1-Disponível, 2-Reservado, 3-Emprestado
	int numReservas, quTotal;
}Livro;

typedef struct emprestimo{
	int codigo, codLivro, codLeitor;
	char data_emp[20], data_dev[20];
	int status; //0-ativo 1-finalizado
}Emprestimo;

typedef struct reserva{
	int codigo, codLivro, codLeitor;
	char data_reserva[20];
}Reserva;


//Funcoes Danh
int login(Funcionario *user);

void formatarString(char *s,int op);

void inputStr(char *str,int tamanho);

//Funções da minha parte

void Cadastros(){
	int tipo;

	printf("\n-----------------------------------------------------------------------");
	printf("\nQue tipo de cadastro? Escolha uma das opcoes listadas abaixo");
	printf("\n-----------------------------------------------------------------------");
	printf("\n(1) Leitores | (2) Funcionarios | (3) Voltar");
	printf("\n\nDigite um número: "); scanf("%d",&tipo); while ((getchar()) != '\n');
	
	switch(tipo){
		case 1: //Escolheu Cadastrar Leitor
			system("clear");
			Leitor *novoLeitor=(Leitor*)malloc(sizeof(Leitor));
			novoLeitor->qtdeEmp=0;
			novoLeitor->histMulta=0;
			
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
		case 2: //Escolheu Cadastrar Funcionario
			system("clear");
			Funcionario *novoFunc=(Funcionario*)malloc(sizeof(Funcionario));
			novoFunc->totalEmp=0;
			novoFunc->totalDev=0;
			
			//Nome
			printf("\n-----------------------------------------------------------------------");
			printf("\nInforme o seu nome (20 caracteres max.)");
			printf("\n-----------------------------------------------------------------------");
			printf("\n\nDigite: ");fgets(novoFunc->nome, 20, stdin);
			//Cargo
			printf("\n-----------------------------------------------------------------------");
			printf("\nInforme o cargo (15 caracteres max.)");
			printf("\n-----------------------------------------------------------------------");
			printf("\n\nDigite: "); fgets(novoFunc->cargo, 15, stdin);
			break;
		case 3: //Escolheu Sair

			return;
	} Cadastros();
}

//Funções gerais/básicas do programa

void menuOp();

void menuAdm();

void InUser(){ //EXISTE SISTEMA DE CONTA!!! Vai ter que existir MenuLeitor(); MenuFuncionario(); futuramente
	int esc;
	
	printf("\n-----------------------------------------------------------------------");
	printf("\nPor favor, escolha uma das opcoes listadas abaixo!");
	printf("\n-----------------------------------------------------------------------");
	printf("\n(1) Cadastrar | (2) Login | (3) Sair"); 
	printf("\n\nDigite um numero: "); scanf("%d",&esc);
	
	switch(esc){
		case 1: //Escolheu Cadastrar
			Cadastros();
			break;
		case 2:
			break;
		case 3: //Escolheu Sair
			return;
		default:
			InUser();
			break;
	}InUser();
}


//
//
//A PARTIR DAQUI ATÉ O PRÓXIMO PONTO MARCADO, E SOMENTE PARA O RESGATE DE DADOS------------------------------------------
//
//
Reserva *LogReserva(){
	FILE *poLog = fopen("reservas.txt","r");
	int linhas;
	fscanf(poLog,"%d",&linhas);
	if(linhas==0){ 
		printf("\n-----------------------------------------------------------------------");
		printf("\nAVISO: O arquivo de dados 'reservas.txt' nao foi encontrado nesta maquina, entao um novo foi criado.");
		printf("\n-----------------------------------------------------------------------\n");
		fprintf(poLog,"0");
	}
	
	Reserva *liveLog = (Reserva *)malloc((linhas+1)*sizeof(Reserva));
	
	int i;	
	for(i=1;i<=linhas;i++){
		fscanf(poLog,"%d %d %d %s",&liveLog[i].codigo, &liveLog[i].codLivro, &liveLog[i].codLeitor, liveLog[i].data_reserva);
	}
	
	fclose(poLog);
	return liveLog;
}

Emprestimo *LogEmprestimo(){
	FILE *poLog = fopen("emprestimos.txt","r");
	int linhas;
	fscanf(poLog,"%d",&linhas);
	if(linhas==0){ 
		printf("\n-----------------------------------------------------------------------");
		printf("\nAVISO: O arquivo de dados 'emprestimos.txt' nao foi encontrado nesta maquina, entao um novo foi criado.");
		printf("\n-----------------------------------------------------------------------\n");
		fprintf(poLog,"0");
	}
	
	Emprestimo *liveLog = (Emprestimo *)malloc((linhas+1)*sizeof(Emprestimo));
	
	int i;	
	for(i=1;i<=linhas;i++){
		fscanf(poLog,"%d %d %d %s %s %d",&liveLog[i].codigo, &liveLog[i].codLivro, &liveLog[i].codLeitor, liveLog[i].data_emp, liveLog[i].data_dev, &liveLog[i].status);
	}
	
	fclose(poLog);
	return liveLog;
}

Livro *LogLivro(){
	FILE *poLog = fopen("livros.txt","a+");
	int linhas;
	fscanf(poLog,"%d",&linhas);
	if(linhas==0){ 
		printf("\n-----------------------------------------------------------------------");
		printf("\nAVISO: O arquivo de dados 'livros.txt' nao foi encontrado nesta maquina, entao um novo foi criado.");
		printf("\n-----------------------------------------------------------------------\n");
		fprintf(poLog,"0");
	}
	
	Livro *liveLog = (Livro *)malloc((linhas+1)*sizeof(Livro));
	
	int i;	
	for(i=1;i<=linhas;i++){
		fscanf(poLog,"%d %s %s %s %d %d %d",&liveLog[i].codigo, liveLog[i].titulo, liveLog[i].autor, liveLog[i].genero, &liveLog[i].Status, &liveLog[i].numReservas, &liveLog[i].quTotal);
	}
	
	fclose(poLog);
	return liveLog;
}

Funcionario *LogFuncionario(){
	FILE *poLog = fopen("funcionarios.txt","a+");
	int linhas;
	fscanf(poLog,"%d",&linhas);
	if(linhas==0){ 
		printf("\n-----------------------------------------------------------------------");
		printf("\nAVISO: O arquivo de dados 'funcionarios.txt' nao foi encontrado nesta maquina, entao um novo foi criado.");
		printf("\n-----------------------------------------------------------------------\n");
		fprintf(poLog,"0");
	}	
	
	Funcionario *liveLog = (Funcionario *)malloc((linhas+1)*sizeof(Funcionario));
	
	int i;	
	for(i=1;i<=linhas;i++){
		fscanf(poLog,"%d %s %s %d %d",&liveLog[i].codigo,liveLog[i].nome,liveLog[i].cargo,&liveLog[i].totalEmp, &liveLog[i].totalDev);
	}
	
	fclose(poLog);
	return liveLog;
}

Leitor *LogLeitor(){
	FILE *poLog = fopen("leitores.txt","a+");
	int linhas;
	fscanf(poLog,"%d",&linhas);
	if(linhas==0){ 
		printf("\n-----------------------------------------------------------------------");
		printf("\nAVISO: O arquivo de dados 'leitores.txt' nao foi encontrado nesta maquina, entao um novo foi criado.");
		printf("\n-----------------------------------------------------------------------\n");
		fprintf(poLog,"0");
	}
	
	Leitor *liveLog = (Leitor *)malloc((linhas+1)*sizeof(Leitor));
	
	int i;	
	for(i=1;i<=linhas;i++){
		fscanf(poLog,"%d %s %s %d %d",&liveLog[i].codigo, liveLog[i].nome, liveLog[i].email, &liveLog[i].qtdeEmp, &liveLog[i].histMulta);
	}

	fclose(poLog);
	return liveLog;
}

void registrar();

//
//
//FIM DO RESGATE DE DADOS--------------------------------------------------------------------------------------------
//
//


int main(){ //Vamo fazer igual foi no jogo, onde a main só faz chamar função
	printf("-----------------------------------------------------------------------");	
	printf("\nBem vindo(a) ao acesso digital da Grande Biblioteca Publica de Castro!");
	printf("\n-----------------------------------------------------------------------\n");
	
	//Leitura do banco de dados de cada arquivo
	//Acabei fazendo função separada para cada para poder retornar os ponteiros de cada, e usar quando necessário
	
	Leitor * LLL/*Live Log Leitor*/ = LogLeitor();
	Funcionario * LLF /*Live Log Funcionario*/= LogFuncionario();
	Livro * LLI /*Live Log lIvro*/= LogLivro();
	Emprestimo * LLE /*Live Log Emprestimo*/= LogEmprestimo();
	Reserva * LLR /*Live Log Reserva*/= LogReserva();
	

	while(login(LLF));
	
	printf("\n-----------------------------------------------------------------------");
	printf("\nAgradecemos a preferencia! Volte sempre.");
	printf("\n-----------------------------------------------------------------------");
}

int login(Funcionario *user){
	int i,tamanho,validaNome=0, validaSenha=0;
	char nome[20],senha[20],cargo[15];
	fflush(stdin);
	printf("\nDigite seu nome:");
	inputStr(nome,20);
	printf("\nDigite a senha:");
	inputStr(senha,20);
	formatarString(nome,1);

	for(i=1;i<=sizeof(user);i++){
		if(strcmp(nome,user[i].nome)==0){
			validaNome++;
			strcpy(cargo,user[i].cargo);
		}
	}
	if(strcmp("adm",cargo)==0){
		if(strcmp(SENHA_ADM,senha)==0){
			validaSenha++;
			printf("\nUsuario Logado!\n");
			menuAdm();	
		}
	}
		
	if(strcmp("operador",cargo)==0){
		if(strcmp(SENHA_OP,senha)==0){
			validaSenha++;
			printf("\nUsuario Logado!\n");
			menuOp();	
		}
	}

	if(validaNome==0 || validaSenha==0){
		if(validaNome==0){
			printf("\nNome fora do sistema.");
		}
		if(validaSenha==0){
			printf("\nSenha incorreta.");
			
		}
		return 1;
	}
	return 0;
	
}
void formatarString(char *s,int op){
	int i,inicial=1;

	if(op==1){//1 para formatar e ficar como no arquivo
		for(i=0;*(s+i)!='\0';i++){
			if(*(s+i)==' '){
				*(s+i)='_';
				inicial=1;
			}
			else if(inicial==1){
				*(s+i)=toupper(*(s+i));
				inicial=0;
			}
			else{
				*(s+i)=tolower(*(s+i));
			}
		}
	}
	else{//Ler o que esta no arquivo sem '_'
		for(i=0;*(s+i)!='\0';i++){
			if(*(s+i)=='_'){
				*(s+i)=' ';
				inicial=1;
			}
		}
	}
}

void inputStr(char *str,int tamanho){
	if (fgets(str, tamanho, stdin) != NULL) {
        size_t len = strlen(str); //esse tipo garante a compatibilidade entre plataformas, tamanho em bytes
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0'; // Remove o caractere de nova linha
        }
    }
}

void menuOp(){
	int esc;
	
	printf("\n-----------------------------------------------------------------------");
	printf("\nPor favor, escolha uma das opcoes listadas abaixo!");
	printf("\n-----------------------------------------------------------------------");
	printf("\n(1) Registrar | (2) Sair"); 
	printf("\n\nDigite um numero: "); scanf("%d",&esc);
	
	switch(esc){
		case 1: //Escolheu registrar
			registrar();
			break;
		case 2:
			return;
		default:
			menuOp();
			break;
	}menuOp();
}

void menuAdm(){
	int esc;
	
	printf("\n-----------------------------------------------------------------------");
	printf("\nPor favor, escolha uma das opcoes listadas abaixo!");
	printf("\n-----------------------------------------------------------------------");
	printf("\n(1) Registrar | (2) Cadastrar | (3) Relatorios | (4) Configuracoes | (5) Permissoes |(6) Sair"); 
	printf("\n\nDigite um numero: "); scanf("%d",&esc);
	
	switch(esc){
		case 1: //Escolheu registrar
			registrar();
			break;
		case 2: //Escolheu cadastrar
			Cadastros();
			break;
		case 3: //Escolheu ver relatorios
			break;
		case 4: //Escolheu configurar (o que quer que isso seja)
			break;
		case 5: //Escolheu gerenciar permissoes
			break;
		case 6:
			return;
		default:
			menuAdm();
			break;
	}menuAdm();
}

void registrar(){}
