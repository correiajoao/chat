/*
	Universidade Federal de Alagoas - Campus A.C Simões
	Desenvolvedor: João Correia
	Data: 25/09/2015
	GitHub: www.github.com/correiajoao/chat 
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "interface.h"
#include "systime.h"	

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
	
	printf("                                                         Último acesso: %s\n", getHourMinutesSeconds());
	printf("--------------------------------------------------------------------------------\n");
}

void printMenuOptions(){
	printf("\n");
	printf("1 | Conectar-se\n");
	printf("2 | Funcionalidades\n");
	printf("3 | Sair\n");
	printf("\n");
	printf("Escolha sua opção: ");
}

void printSecondMenuOptions(){
	printf("\n");
	printf("1 | Usuários ativos\n");
	printf("2 | Bate papo\n");
	printf("3 | Sair\n");
	printf("\n");
	printf("Escolha sua opção: ");
}

void printUserList(struct userList _users){
	int i = 0;
	printHeader("Usuários ativos");								
	printf("Usuário número                  Usuário                  Atualizado às: %s\n", getHourMinutesSeconds());
	
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
	printHeader("Funcionalidades");
	printAlert("O Bate-papo versão beta é simples e intuitivo!");	
	printf("\n");
	printf("Siga os passos: \n");
	printf("* Escolha a opçao conectar-se.\n");
	printf("* Insira um nome valido.\n");
	printf("* A opção usuários online mostra todos os usuários em tempo real.\n");
	printf("* Na sala de conversa algumas opções estão disponíveis:\n");
	printf("         *Insira a tecla '>' para digitar uma menssagem.\n");
	printf("         *Insira a tecla 'v' para voltar ao menu anterior.\n");
	printf("         *Insira a tecla 'l' para limpar a tela.\n");
	printf("         *Menssagens com '@nome ' sao direcionadas apenas para o usuario 'nome'.\n");
	printf("         		*Exemplo: '@joao Bom dia'\n");

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
	usleep(100000);	
	printf("\n"); 		
	printf("                                                                  Versão beta\n"); 		
	sleep(1);
}

