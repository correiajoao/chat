/*
	Universidade Federal de Alagoas - Campus A.C Simões
	Desenvolvedor: João Correia
	Data: 25/09/2015
	GitHub: www.github.com/correiajoao/chat 
*/
#include <time.h>
#include <stdio.h>
#include <string.h>

#include "interface.h"

void printHeader(char * indentifier){
	int i;	
	int size = strlen(indentifier);
	int padding = (78 - size)/2;
	system("clear");
	printf("--------------------------------------------------------------------------------\n");	
	
	for(i=0;i<padding; i++){
		printf("#");
	}
	
	printf(" %s ", indentifier);
	
	for(i=0;i<padding; i++){
		printf("#");	
	}
	
	printf("                                                         Último acesso: %s\n", __TIME__);
	printf("--------------------------------------------------------------------------------\n");
}

void printMenuOptions(){
	printf("\n");
	printf("1 | Participar\n");
	printf("2 | Entenda como funcina\n");
	printf("3 | Sair\n");
	printf("\n");
	printf("Escolha sua opção: ");
}

void printSecondMenuOptions(){
	printf("\n");
	printf("1 | Verificar Lista de usuários ativos\n");
	printf("2 | Entrar no bate papo\n");
	printf("3 | Desconectar\n");
	printf("\n");
	printf("Escolha sua opção: ");
}

void printUserList(struct userList _users){
	int i = 0;
	printHeader("LISTA DE USUARIOS ATIVOS");								
	printf("Usuário número                  Usuário                  Atualizado às: %s\n", __TIME__);
	
	for(i=0;i<_users.size;i++){
		printf("-- >> %d                     -->> %s\n", i, _users.name[i]);
	}
								
	printf("\n");
	printf("------------------------------- FIM DA LISTA -----------------------------------\n");
}

void printMessageList(struct messageList _messages){
	int i = 0;
	
	for(i=0;i<_messages.size;i++){
		printf("> %s\n",_messages.content[i]);
	}
}

void printAlert(char *message){
	int i;	
	int size = strlen(message);
	int padding = (76 - size)/2;
	
	printf("\n");
	printf("\n");
	
	for(i=0;i<padding; i++){
		printf(" ");
	}	

	printf(">> %s <<", message);
	
	for(i=0;i<padding; i++){
		printf(" ");	
	}
	printf("\n");
}

void printHowWorks(){
	printHeader("ENTENDA COMO FUNCIONA");
	printf("\n");
	printAlert("O bate-papo versão 1.0 é simples e intuitivo!");	
	printf("\n\n");
	printf("Siga os passos: \n");
	printf("* Escolha a opçao participar.\n");
	printf("* Insira um nome valido.\n");
	printf("* Apos entrar no bate-papo algumas opçoes sao possiveis:\n");
	printf("         *Insira a tecla '>' para digitar uma menssagem.\n");
	printf("         *Insira a tecla 's' para voltar ao menu anterior.\n");
	printf("         *Menssagens com '@nome ' sao direcionadas apenas para o usuario 'nome'.\n");
	printf("         		*Exemplo: '@joao Bom dia'\n");
	printf("\n\n");
}

void printAnimation(){
	system("clear");
	printf("\n\n\n\n\n\n");
	printf("888888b.            888\n");
	usleep(100000);
	printf("888   88b           888\n");
	usleep(100000);
	printf("888  .88P           888\n"); 
	usleep(100000);
	printf("8888888K.   8888b.  888888  .d88b.         88888b.   8888b.  88888b.   .d88b.\n");  
	usleep(100000);
	printf("888   Y88b      88b 888    d8P  Y8b        888  88b      88b 888  88b d88  88b\n"); 
	usleep(100000);
	printf("888    888 .d888888 888    88888888 888888 888  888 .d888888 888  888 888  888\n"); 
	usleep(100000);
	printf("888   d88P 888  888 Y88b.  Y8b.            888 d88P 888  888 888 d88P Y88..88P\n");
	usleep(100000);
	printf("8888888P    Y888888   Y888   Y8888         88888P    Y888888 88888P     Y88P \n"); 
	usleep(100000);
   	printf("                                           888               888\n");    
	usleep(100000);
    printf("                                           888               888\n");
	usleep(100000);
    printf("                                           888               888\n");  
	sleep(2);
}

