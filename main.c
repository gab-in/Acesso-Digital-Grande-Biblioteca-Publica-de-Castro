#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <time.h>

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

void amzLivro(Livro *LLI);
void amzLeitor(Leitor *LLL);
void amzFunc(Funcionario *LLF);
void amzRez(Reserva *LLR);
void amzEmp(Emprestimo *LLE);


//Funções Gab

void Cadastros(Leitor *LLL, Funcionario *LLF, Livro *LLI);

void CadLeitor(Leitor *LLL);
void CadFunc(Funcionario *LLF);
void CadLivro(Livro *LLI);

Emprestimo *Emp(Leitor *LLL, Livro *LLI, Emprestimo *LLE);

void Dev(Leitor *LLL, Livro *LLI, Emprestimo *LLE);
float devMulta(Emprestimo *LLE, int aux);
int temReserva(Livro *LLI, int i);
int tempoPassado(int data, int data_atual);


void Registros(Leitor *LLL, Livro *LLI, Emprestimo *LLE);


//Funções gerais/básicas do programa

void menuOp();

void menuAdm(Leitor *LLL, Funcionario *LLF, Livro *LLI, Emprestimo *LLE, Reserva *LLR);

//leitura de dados
Reserva *LogReserva();

Emprestimo *LogEmprestimo();

Livro *LogLivro();

Funcionario *LogFuncionario();

Leitor *LogLeitor();


 //relatorios
void relatorios(Leitor *LLL, Funcionario *LLF, Livro *LLI, Emprestimo *LLE, Reserva *LLR);

void livroDisp(Livro *LLI);
void livroEmp(Livro *LLI);
void empAtivo(Leitor *LLL,Livro *LLI,Emprestimo *LLE);

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
	
	int aux=login(LLF);
	while(aux==0) aux=login(LLF);
	
	switch(aux){
		case 1:
			menuAdm(LLL, LLF, LLI, LLE, LLR);
			break;
		case 2:
			menuOp();
			break;
		default:
			break;
	}

	printf("\n-----------------------------------------------------------------------");
	printf("\nAgradecemos a preferencia! Volte sempre.");
	printf("\n-----------------------------------------------------------------------");
}

int login(Funcionario *user){
	int i,validaNome=0, validaSenha=0;
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
			return 1;
		}
	}
	
	if(strcmp("operador",cargo)==0){
		if(strcmp(SENHA_OP,senha)==0){
			validaSenha++;
			printf("\nUsuario Logado!\n");
			return 2;	
		}
	}

	if(validaNome==0 || validaSenha==0){
		if(validaNome==0){
			printf("\nNome fora do sistema.");
		}
		if(validaSenha==0){
			printf("\nSenha incorreta.");
			
		}
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
			break;
		case 2:
			return;
		default:
			menuOp();
			break;
	}menuOp();
}

void menuAdm(Leitor *LLL, Funcionario *LLF, Livro *LLI, Emprestimo *LLE, Reserva *LLR){
	int esc;
	
	printf("\n-----------------------------------------------------------------------");
	printf("\nPor favor, escolha uma das opcoes listadas abaixo!");
	printf("\n-----------------------------------------------------------------------");
	printf("\n(1) Registrar | (2) Cadastrar | (3) Relatorios | (4) Configuracoes | (5) Permissoes |(6) Sair"); 
	printf("\n\nDigite um numero: "); scanf("%d",&esc);
	
	switch(esc){
		case 1: //Escolheu registrar
			Registros(LLL,LLI,LLE);
			break;
		case 2: //Escolheu cadastrar
			Cadastros(LLL, LLF, LLI);
			break;
		case 3: //Escolheu ver relatorios
			relatorios(LLL,LLF,LLI,LLE,LLR);
			break;
		case 4: //Escolheu configurar (o que quer que isso seja)
			break;
		case 5: //Escolheu gerenciar permissoes
			break;
		case 6:
			return;
		default:
			menuAdm(LLL,LLF,LLI,LLE,LLR);
			break;
	}menuAdm(LLL,LLF,LLI,LLE,LLR);
}

void Cadastros(Leitor *LLL, Funcionario *LLF, Livro *LLI){
	int tipo;

	printf("\n-----------------------------------------------------------------------");
	printf("\nQue tipo de cadastro? Escolha uma das opcoes listadas abaixo");
	printf("\n-----------------------------------------------------------------------");
	printf("\n(1) Leitores | (2) Funcionarios | (3) Livro | (4) Voltar");
	printf("\n\nDigite um numero: "); scanf("%d",&tipo); while ((getchar()) != '\n');
	
	switch(tipo){
		case 1: //Escolheu Cadastrar Leitor
			CadLeitor(LLL);			
			return;
		case 2: //Escolheu Cadastrar Funcionario
			CadFunc(LLF);
			break;
		case 3: //escolheu livro
			CadLivro(LLI);
			break;
		case 4:
			return;
		}
}

void CadLeitor(Leitor *LLL){
	char nome[20],email[25];
	Leitor novoLeitor;
	novoLeitor.codigo=((LLL[0].codigo)+1);
	novoLeitor.qtdeEmp=0;
	novoLeitor.histMulta=0;
		
		//Nome
	printf("\n-----------------------------------------------------------------------");
	printf("\nInforme o seu nome (20 caracteres max.)");
	printf("\n-----------------------------------------------------------------------");
	printf("\n\nDigite: ");inputStr(nome,20);
	formatarString(nome,1);
	strcpy(novoLeitor.nome,nome);
	//email
	printf("\n-----------------------------------------------------------------------");
	printf("\nInforme o email (25 caracteres max.)");
	printf("\n-----------------------------------------------------------------------");
	printf("\n\nDigite: ");inputStr(email,25);
	strcpy(novoLeitor.email,email);

	LLL=realloc(LLL,((LLL[0].codigo)+1)*(sizeof(Leitor)));

	LLL[(LLL[0].codigo)+1]=novoLeitor;
	LLL[0].codigo+=1;
	
	//tirar dps
	printf("Leitores: ");			
	printf("\nPrimeiro coisa do vetor: %d",LLL[0].codigo);
	for(int i=1;i<=LLL[0].codigo;i++){
		printf("\n%d %s %s %d %d",LLL[i].codigo, LLL[i].nome, LLL[i].email, LLL[i].qtdeEmp, LLL[i].histMulta);
	}
	//
}

void CadFunc(Funcionario *LLF){
	char n[20];
	Funcionario novoFunc;
	novoFunc.codigo=((LLF[0].codigo)+1);
	novoFunc.totalEmp=0;
	novoFunc.totalDev=0;
	
	//Nome
	printf("\n-----------------------------------------------------------------------");
	printf("\nInforme o seu nome (20 caracteres max.)");
	printf("\n-----------------------------------------------------------------------");
	printf("\n\nDigite: ");inputStr(n,20);
	formatarString(n,1);
	strcpy(novoFunc.nome,n);
	//Cargo
	printf("\n-----------------------------------------------------------------------");
	printf("\nInforme o cargo (15 caracteres max.)");
	printf("\n-----------------------------------------------------------------------");
	printf("\n\nDigite: ");inputStr(novoFunc.cargo,15);

	LLF=realloc(LLF,((LLF[0].codigo)+1)*(sizeof(Funcionario)));
	LLF[(LLF[0].codigo)+1]=novoFunc;
	LLF[0].codigo+=1;

	//tirar dps
	printf("Funcionarios: ");			
	printf("\nPrimeiro coisa do vetor: %d",LLF[0].codigo);
	for(int i=1;i<=LLF[0].codigo;i++){
		printf("\n%d %s %s %d %d",LLF[i].codigo, LLF[i].nome, LLF[i].cargo, LLF[i].totalEmp, LLF[i].totalDev);
	}
}

void CadLivro(Livro *LLI){
	char titulo[30],autor[20], genero[15];
	Livro novoLivro;
	novoLivro.codigo=((LLI[0].codigo)+1);
	novoLivro.Status=1;
	novoLivro.numReservas=0;
	//titulo
	printf("\n-----------------------------------------------------------------------");
	printf("\nInforme o titulo do livro (30 caracteres max.)");
	printf("\n-----------------------------------------------------------------------");
	printf("\n\nDigite: ");inputStr(titulo,30);
	formatarString(titulo,1);
	strcpy(novoLivro.titulo,titulo);
	//autor
	printf("\n-----------------------------------------------------------------------");
	printf("\nInforme o autor (20 caracteres max.)");
	printf("\n-----------------------------------------------------------------------");
	printf("\n\nDigite: ");inputStr(autor,20);
	formatarString(autor,1);
	strcpy(novoLivro.autor,autor);
	//genero
	printf("\n-----------------------------------------------------------------------");
	printf("\nInforme o genero (15 caracteres max.)");
	printf("\n-----------------------------------------------------------------------");
	printf("\n\nDigite: ");inputStr(genero,15);
	formatarString(genero,1);
	strcpy(novoLivro.genero,genero);
	//quantidade
	printf("\n-----------------------------------------------------------------------");
	printf("\nInforme quantos livros tem");
	printf("\n-----------------------------------------------------------------------");
	printf("\n\nDigite: ");
	scanf("%d",&novoLivro.quTotal);

	LLI=realloc(LLI,((LLI[0].codigo)+1)*(sizeof(Livro)));
	LLI[(LLI[0].codigo)+1]=novoLivro;
	LLI[0].codigo+=1;

	//tirar dps
	printf("Livros: ");			
	printf("\nPrimeiro coisa do vetor: %d",LLI[0].codigo);
	for(int i=1;i<=LLI[0].codigo;i++){
		printf("\n%d %s %s %s %d %d %d",LLI[i].codigo, LLI[i].titulo, LLI[i].autor, LLI[i].genero, LLI[i].Status,LLI[i].numReservas, LLI[i].quTotal);
	}
}


void relatorios(Leitor *LLL, Funcionario *LLF, Livro *LLI, Emprestimo *LLE, Reserva *LLR){
	int esc;	
	printf("\n-----------------------------------------------------------------------");
	printf("\nRelatorios disponiveis:");
	printf("\n-----------------------------------------------------------------------");
	printf("\n(1) Lista de Livros Disponiveis | (2) Lista de Livros Emprestados | (3) Emprestimos ativos | (4) Historico de multas | (5) Movimentacoes funcionarios |(6) Livros mais emprestados | (7) Reservas em aberto | (8) Sair"); 
	printf("\n\nDigite um numero: "); scanf("%d",&esc);
	
	switch(esc){
		case 1: //livros disponiveis
			livroDisp(LLI);
			break;
		case 2: //livros emprestados
			livroEmp(LLI);
			break;
		case 3: //emprestimos ativos
			break;
		case 4: //historicos multas
			break;
		case 5: //movimentacoes
			break;
		case 6: //mais emprestados
			break;
		case 7: //reservas em aberto
			break;
		case 8: //sair
			return;
		default:
			relatorios(LLL,LLF,LLI,LLE,LLR);
			break;
	}relatorios(LLL,LLF,LLI,LLE,LLR);
}

void livroDisp(Livro *LLI){
	int i;
	printf("\nLivros Disponiveis:");
	printf("\n-----------------------------------------------------------------------");
	
	for(i=1;i<=LLI[0].codigo;i++){
		if(LLI[i].Status==1){
			formatarString(LLI[i].titulo,0);
			printf("\n\n%s", LLI[i].titulo );
			printf("\nQuantidade disponivel: %d", (LLI[i].quTotal-LLI[i].numReservas));
			formatarString(LLI[i].titulo,1);
		}
	}
	printf("\n\n-----------------------------------------------------------------------");

	
}

void livroEmp(Livro *LLI){
	int i;
	printf("\nLivros Emprestados:");
	printf("\n-----------------------------------------------------------------------");
	
	for(i=1;i<=LLI[0].codigo;i++){
		if(LLI[i].Status==3){
			formatarString(LLI[i].titulo,0);
			printf("\n\n%s", LLI[i].titulo );
			printf("\nQuantidade total: %d", LLI[i].quTotal);
			printf(" | Quantidade reservada: %d", LLI[i].numReservas);
			formatarString(LLI[i].titulo,1);
		}
	}
	printf("\n\n-----------------------------------------------------------------------");
}

void empAtivo(Leitor *LLL,Livro *LLI,Emprestimo *LLE){
	printf("\nEmprestimos Ativos:");
	printf("\n-----------------------------------------------------------------------");
	for(int i=1;i<=LLE[0].codigo;i++){
		if(LLE[i].status==0){
			formatarString(LLL[LLE[i].codLeitor].nome,0);
			formatarString(LLI[LLE[i].codLivro].titulo,0);
			printf("\n\n%s emprestou \"%s\" em %s, prazo para devolucao ate %s", LLL[LLE[i].codLeitor].nome, LLI[LLE[i].codLivro].titulo, LLE[i].data_emp, LLE[i].data_dev);
			formatarString(LLL[LLE[i].codLeitor].nome,1);
			formatarString(LLI[LLE[i].codLivro].titulo,1);
		}
	}
	printf("\n\n-----------------------------------------------------------------------");
}

void Registros(Leitor *LLL, Livro *LLI, Emprestimo *LLE){
	int esc;
	
	printf("\n-----------------------------------------------------------------------");
	printf("\nQue registro deseja fazer? Escolha uma das opções abaixo");
	printf("\n-----------------------------------------------------------------------");
	printf("\n(1) Emprestimo | (2) Devolucao | (3) Voltar");
	printf("\n\nDigite um numero: "); scanf("%d",&esc); while ((getchar()) != '\n');
	printf("\nLinhas totais(na registros): %d",LLE[0].codigo);
	printf("\nLocal da LLE depois dentro da Registros: %p",LLE);
	switch(esc){
		case 1:
			LLE=Emp(LLL,LLI,LLE);
			break;
		case 2:
			Dev(LLL,LLI,LLE);
			break;
		case 3:
			return;
		default:
			Registros(LLL,LLI,LLE);
			break;
	} Registros(LLL,LLI,LLE);
}


Emprestimo *Emp(Leitor *LLL, Livro *LLI, Emprestimo *LLE){
	int aux=0,codli,codle, i;
	
	printf("\n-----------------------------------------------------------------------");
	printf("\nObserve a lista de livros: ");
	printf("\n-----------------------------------------------------------------------");
	
	for(int i=1;i<=LLI[0].codigo;i++){
		printf("\n\nCódigo: %d | %s - %s - %s | ",LLI[i].codigo, LLI[i].titulo, LLI[i].autor, LLI[i].genero);
		switch(LLI[i].Status){
			case 1:
				printf("Disponivel");
				break;
			case 2:
				printf("Reservado");
				break;
			case 3:
				printf("Emprestado");
				break;
		}
	}
	
	while(!aux){
		printf("\n-----------------------------------------------------------------------");
		printf("\nInsira o codigo do livro que deseja emprestar: ( (0) Para retornar )");
		printf("\n-----------------------------------------------------------------------");
		printf("\n\nDigite um numero: "); scanf("%d",&codli);
		
		if(codli==0)return LLE;//Escolheu retornar
		
		for(i=1;i<=LLI[0].codigo;i++){
			if(LLI[i].codigo==codli)aux=1;//Verifica se o livro existe
		}if(!aux)printf("\nEste livro não existe!");
		switch(aux){
			case 0://Se não existir o while continua rerodando
				break;
			default://Se existir, verifica o resto das coisas
				if(LLI[codli].Status!=1){printf("\nEste livro esta indisponivel!!"); aux=0;}
				break;
		}
	}
	
	printf("\n-----------------------------------------------------------------------");
	printf("\nObserve a lista de leitores: ");
	printf("\n-----------------------------------------------------------------------");
	
	for(int i=1;i<=LLL[0].codigo;i++){
		printf("\n\nCódigo: %d | %s - %s - %d - %d | ",LLL[i].codigo, LLL[i].nome, LLL[i].email, LLL[i].qtdeEmp, LLL[i].histMulta);
	}
		
	aux=0;
	while(!aux){
		printf("\n-----------------------------------------------------------------------");
		printf("\nInsira o codigo do usuario para o qual deseja emprestar: ( (0) Para retornar )");
		printf("\n-----------------------------------------------------------------------");
		printf("\n\nDigite um numero: "); scanf("%d",&codle);
		
		if(codle==0)return LLE;//Escolheu retornar
		
		for(i=1;i<=LLL[0].codigo;i++){
			if(LLL[i].codigo==codle)aux=1;//Veririca se o usuário existe
		}if(!aux)printf("\nUsuário inválido");
		switch(aux){
			case 0://Se não existir o while continua rerodando
				break;
			default://Se existir, verifica o resto das coisas
				if(LLL[codle].qtdeEmp>=3){printf("\nLimite de emprestimos atingido para este usuario!!"); return LLE;}
				break;
		}		
	}
			
	char data[20];
	Emprestimo novoEmp;
	
	time_t agora; //Foi definido numa biblioteca de tempo
	time(&agora);//Função da bib.h que retorna todos os segundos passados desde 1970 (Não ironicamente)
	struct tm *tempoStruct;
	tempoStruct=localtime(&agora);//Função da bib.h que converte os segundos nas formas de contar
	
	novoEmp.codigo=(LLE->codigo)+1;
	novoEmp.codLivro=codli;
	novoEmp.codLeitor=codle;
	
	strftime(data,19,"%d/%m/%Y",tempoStruct);
	strcpy(novoEmp.data_emp,data);
	time(&agora);
	agora=agora+604800;//Segundos em 1 semana
	tempoStruct=localtime(&agora);
			
	strftime(data,19,"%d/%m/%Y",tempoStruct);
	strcpy(novoEmp.data_dev,data);
	novoEmp.status=0;
	printf("\nLocal da LLE antes da Realloc: %p",LLE);
	Emprestimo *ptraux=(Emprestimo *)realloc(LLE,sizeof(Emprestimo)*(LLE->codigo+2));
	if(ptraux==NULL){
		printf("\nRealloc de Emprestimo falhou!");
		return LLE;
	}
	else{
		LLE=ptraux;
		printf("\nLocal da LLE depois da Realloc: %p",LLE);
	}
	LLE->codigo+=1;
	LLE[LLE[0].codigo]=novoEmp;
	
	
	printf("\nLinhas totais: %d",LLE[0].codigo);
	for(int i=1;i<=LLE[0].codigo;i++){
		printf("\n%d %d %d %s %s %d",LLE[i].codigo, LLE[i].codLivro, LLE[i].codLeitor, LLE[i].data_emp, LLE[i].data_dev, LLE[i].status);
	}
	
	LLI[codli].quTotal-=1;
	if(LLI[codli].quTotal<=0)LLI[codli].Status=3;
	LLL[codle].qtdeEmp+=1;

	amzEmp(LLE);
	amzLeitor(LLL);
	amzLivro(LLI);
	
	printf("\nLinhas totais(final da emp): %d",(LLE[0].codigo));
	
	return LLE;
}



void Dev(Leitor *LLL, Livro *LLI, Emprestimo *LLE){
	int aux=0,codli,codle,i;
	
	printf("\nLinhas totais: %d",LLE[0].codigo);
	
	printf("\n-----------------------------------------------------------------------");
	printf("\nObserve a lista de livros: ");
	printf("\n-----------------------------------------------------------------------");
	
	for(int i=1;i<=LLI[0].codigo;i++){
		printf("\n\nCódigo: %d | %s - %s - %s | ",LLI[i].codigo, LLI[i].titulo, LLI[i].autor, LLI[i].genero);
		switch(LLI[i].Status){
			case 1:
				printf("Disponivel");
				break;
			case 2:
				printf("Reservado");
				break;
			case 3:
				printf("Emprestado");
				break;
		}
	}
	
	while(!aux){
		printf("\n-----------------------------------------------------------------------");
		printf("\n:Insira o codigo do livro que deseja devolver: ( (0) Para retornar )");
		printf("\n-----------------------------------------------------------------------");
		printf("\n\nDigite um numero: "); scanf("%d",&codli);
		
		if(codli==0)return;//Escolheu retornar;
		for(int i=1;i<=LLI[0].codigo;i++){
			if(LLI[i].codigo==codli)aux=1;//Verifica se o livro existe
		}
		if(!aux)printf("\nEste livro não existe!");
		if(LLI[codli].Status!=3){printf("Este livro não foi emprestado");aux=0;}
	}
	
	printf("\n-----------------------------------------------------------------------");
	printf("\nObserve a lista de leitores: ");
	printf("\n-----------------------------------------------------------------------");
	
	for(int i=1;i<=LLL[0].codigo;i++){
		printf("\n\nCódigo: %d | %s - %s - %d - %d | ",LLL[i].codigo, LLL[i].nome, LLL[i].email, LLL[i].qtdeEmp, LLL[i].histMulta);
	}
		
	aux=0;
	while(!aux){
		printf("\n-----------------------------------------------------------------------");
		printf("\nInsira o codigo do usuario que esta devolvendo: ( (0) Para retornar )");
		printf("\n-----------------------------------------------------------------------");
		printf("\n\nDigite um numero: "); scanf("%d",&codle);
		
		if(codle==0)return;//Escolheu retornar
		
		for(i=1;i<=LLL[0].codigo;i++){
			if(LLL[i].codigo==codle)aux=1;//Veririca se o usuário existe
		}if(!aux)printf("\nUsuário inválido");
	}
	
	aux=0;
	printf("\nLLE[0]: %d",LLE[0].codigo);
	
	for(i=1;i<=LLE[0].codigo;i++){
		printf("\nComeço iteração: %d",i);
		if(LLE[i].codLeitor==codle){//Procura um codigo de leitor igual ao fornecido
			if(LLE[i].codLivro==codli){//Quando acha um codigo, ve se o codigo do livro é igual ao fornecido
				if(LLE[i].status==0){//Se encontra, ve se o emprestimo já foi finalizado no passado ou ainda é pendente 
					aux=i;
					printf("\nChegou?");
				}
			}
		}
		printf("\nComeço iteração: %d",i);
	}
	
	if(aux==0){
	printf("\nO usuário não emprestou este livro"); 
	return;
	}
	
	float multa=devMulta(LLE,aux);
	printf("\nMulta: %f",multa); //Tem que formatar para dar print 
	
	if(multa>0)LLL[codle].histMulta+=1;//Se teve multa, poe no historico
	LLI[codli].Status=temReserva(LLI,codli);//Se nao tem reserva fica disponivel, se tem fica reservado
	LLI[codli].quTotal+=1;//Coloca a existencia do livro
	LLE[aux].status=1;//Finaliza o emprestimo

	amzEmp(LLE);
	amzLeitor(LLL);
	amzLivro(LLI);
	
	for(int i=1;i<=LLE[0].codigo;i++){
		printf("\n%d %d %d %s %s %d",LLE[i].codigo, LLE[i].codLivro, LLE[i].codLeitor, LLE[i].data_emp, LLE[i].data_dev, LLE[i].status);
	}
}



float devMulta(Emprestimo *LLE, int aux){
	time_t agora;
	
	time(&agora);
	struct tm *tempoStruct=localtime(&agora);

		const char s[2] = "/";//Delimitador 
		char str[20];
		strcpy(str,LLE[aux].data_dev);
		char *dataD=strtok(str, s);//Quebra a string em 3, se deus quiser
		
		int diaD=atoi(dataD);
		dataD=strtok(0,s);//Quer dobrar ou passar pro proximo? Passar pra o proximo!	
		int mesD=atoi(dataD);
		dataD=strtok(0,s);
		int anoD=atoi(dataD);

		char diaHj_c[20], mesHj_c[20], anoHj_c[20];
		strftime(diaHj_c,20,"%d",tempoStruct);
		int diaHj=atoi(diaHj_c);
		strftime(mesHj_c,20,"%m",tempoStruct);
		int mesHj=atoi(mesHj_c);
		strftime(anoHj_c,20,"%Y",tempoStruct);
		int anoHj=atoi(anoHj_c);
			
		if(anoD>=anoHj){
			if(mesD>=mesHj){
				if(diaD>=diaHj)return 0.0;
				else{	
					float res=(diaHj-diaD)*0.50;
					return res;
				}
			}
			else{
				int aux = 31-diaD;
				float res=(aux+diaHj)*0.50;
				return res;
			}
		}
		else{
			int aux = 12-mesD;
			float res=(aux+(mesHj-1)+diaHj)*0.50;
			return res;
		}
		
	return 0.0;
}

int temReserva(Livro *LLI, int i){
	if(LLI[i].numReservas>=1){
		if(LLI[i].quTotal<=LLI[i].numReservas)return 2;
		else return 1;
	}
	else return 1;
}

int tempoPassado(int data, int data_atual){
	if(data>=data_atual)return 0;
	else return data_atual-data;
}

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
	liveLog[0].codigo=linhas;
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
	liveLog[0].codigo=linhas;
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
	liveLog[0].codigo=linhas;
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
	liveLog[0].codigo=linhas;
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
	liveLog[0].codigo=linhas;
	
	for(i=1;i<=linhas;i++){
		fscanf(poLog,"%d %s %s %d %d",&liveLog[i].codigo, liveLog[i].nome, liveLog[i].email, &liveLog[i].qtdeEmp, &liveLog[i].histMulta);
	}
	//Tirar depois
	printf("Leitores: ");
	printf("\nPrimeiro coisa do vetor: %d",liveLog[0].codigo);
	for(int i=1;i<=linhas;i++){
		printf("\n%d %s %s %d %d",liveLog[i].codigo, liveLog[i].nome, liveLog[i].email, liveLog[i].qtdeEmp, liveLog[i].histMulta);
	}
	fclose(poLog);
	return liveLog;
}



void amzLivro(Livro *LLI){
	FILE *aqv = fopen("livros.txt","w");	
	fprintf(aqv,"%d",LLI[0].codigo);
	for(int i=1;i<=LLI[0].codigo;i++){
		fprintf(aqv,"\n%d %s %s %s %d %d %d",LLI[i].codigo, LLI[i].titulo, LLI[i].autor, LLI[i].genero, LLI[i].Status,LLI[i].numReservas, LLI[i].quTotal);
	}
	fclose(aqv);	
}
void amzFunc(Funcionario *LLF){
	FILE *aqv = fopen("funcionarios.txt","w");	
	fprintf(aqv,"%d",LLF[0].codigo);
	for(int i=1;i<=LLF[0].codigo;i++){
		fprintf(aqv,"\n%d %s %s %d %d",LLF[i].codigo, LLF[i].nome, LLF[i].cargo, LLF[i].totalEmp, LLF[i].totalDev);
	}
	fclose(aqv);	
}
void amzLeitor(Leitor *LLL){
	FILE *aqv = fopen("leitores.txt","w");	
	fprintf(aqv,"%d",LLL[0].codigo);
	for(int i=1;i<=LLL[0].codigo;i++){
		fprintf(aqv,"\n%d %s %s %d %d",LLL[i].codigo, LLL[i].nome, LLL[i].email, LLL[i].qtdeEmp, LLL[i].histMulta);
	}
	fclose(aqv);	
}
void amzRez(Reserva *LLR){
	FILE *aqv = fopen("reservas.txt","w");	
	fprintf(aqv,"%d",LLR[0].codigo);
	for(int i=1;i<=LLR[0].codigo;i++){
		fprintf(aqv,"\n%d %d %d %s",LLR[i].codigo, LLR[i].codLivro, LLR[i].codLeitor, LLR[i].data_reserva);
	}
	fclose(aqv);	
}
void amzEmp(Emprestimo *LLE){
	FILE *aqv = fopen("emprestimos.txt","w");	
	fprintf(aqv,"%d",LLE[0].codigo);
	for(int i=1;i<=LLE[0].codigo;i++){
		fprintf(aqv,"\n%d %d %d %s %s %d",LLE[i].codigo, LLE[i].codLivro, LLE[i].codLeitor, LLE[i].data_emp, LLE[i].data_dev, LLE[i].status);
	}
	fclose(aqv);	
}
