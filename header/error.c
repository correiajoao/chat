/*
	Universidade Federal de Alagoas - Campus A.C Simões
	Desenvolvedor: João Correia
	Data: 25/09/2015
	GitHub: www.github.com/correiajoao/chat 
*/

#include "error.h"
#include <stdlib.h>

//Alerta erros na criação de sockets 
void errorSocket(){
	perror("Erro ao criar socket");
	exit(1);	
}

//Alerta erros na criação de sockets 
void errorConnection(){
	perror("Erro durante a conexão");
	exit(1);	
}

//Alerta erros durante a recepção de dados
void errorReceiver(){
	perror("Erro ao se conectar ao servidor, tente mais tarde");
	exit(1);
}

//Alerta erros durante a associação de porta
void errorBind(){
	perror("Erro ao associar porta");
	exit(1);
}

//Alerta erros durante o inicio da escuta de uma conexão
void errorListen(){
	perror("Erro ao iniciar a escuta");
	exit(1);
}

//Alerta erros durante a abertura de arquivo
void errorOpenFile(){
	perror("Erro ao abrir arquivo");
	exit(1);
}
