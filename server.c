/*
	Universidade Federal de Alagoas - Campus A.C Simões
	Desenvolvedor: João Correia
	Data: 25/09/2015
	GitHub: www.github.com/correiajoao/chat 
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

//Cabeçalhos 
#include "header/struct.h"
#include "header/error.h"
#include "header/message.h"
#include "header/managerdata.h"

#define MAXDATASIZE 500
#define MAXALLOC 500
#define BACKLOG 5


int main(){
	//Variaveis comuns
	pid_t pid;
	int fluxo, msgKind;
	char userName[50];
	char *bufferRcv, *_bufferRcv, *msgContent;	
	
	//Estruturas de listas	
	struct userList _users;
	struct messageList _messages;
	
	//Variaveis de socket
	int localSocket,remoteSocket,structSize;
	struct sockaddr_in local;
	struct sockaddr_in remote;
		
	//Inicio da execução
	
	system("clear");
	//Apagando todos os dados de seções passadas
	deleteFile();
	//Criando diretórios necessários
	makeDirectory();
	//Mensagem de inicio
	printf("Servidor iniciado\n");
	
	//Configurações do socket local
	//Mais detalhes consulte as manpages
	localSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(localSocket == -1)
		errorSocket();
		
	//Configuração do socket local
	//Mais detalhes consulte as manpages
	local.sin_family = AF_INET; 
	local.sin_port = htons(31337);  	
	local.sin_addr.s_addr = INADDR_ANY;
	memset(local.sin_zero,0,8);

	//Associação da porta
	if(bind(localSocket, (struct sockaddr *)&local, sizeof(local)) == -1)
		errorBind();
	
	//Inicio da escuta
	if(listen (localSocket, BACKLOG) == -1)
		errorListen();
	
	structSize = sizeof(struct sockaddr_in);
	
	while(1){
		//Agurda um processo conectars-se
		remoteSocket = accept(localSocket, (struct sockaddr *)&remote, &structSize);
		
		//Após a conxão ser aceita, o processo servidor é duplicado
		pid = fork();
		if(pid == 0){
			
				//Alocação de memória necessária
				bufferRcv = (char*) calloc (MAXALLOC, sizeof(char));
				_bufferRcv = (char*) calloc (MAXALLOC, sizeof(char));	
				msgContent = (char*) calloc (MAXALLOC, sizeof(char));			
			
				fluxo = 0;
				while(!fluxo){	
					recv(remoteSocket, bufferRcv, MAXDATASIZE,  0);
					strcpy(_bufferRcv, bufferRcv);
					
					//Após a conexão de um cliente, a primeira mensagem que o servidor espera é do tipo USERNAME,
					//caso contrário o processo servidor é finalizado
					if(checkKindMessage(_bufferRcv,1) == USERNAME){
						printf("Mensagem recebida por: %d\n", pid);
						//Resgata o conteudo da mensagem
						strcpy(_bufferRcv, bufferRcv);  		
						msgContent = checkMessage(_bufferRcv);
						
						//Verifica se o userName é válido
						if(!checkUserName(msgContent)){
							
								//Se o userName é válido o servidor guarda esse nome para o processo corrente identificar a qual usuário está associado
								strcpy(userName,msgContent);
							
								//Insere o usuário na lista de usuários ativos passando como parâmetros o seu nome e endereço
								insertUser(msgContent,inet_ntoa(remote.sin_addr));
								
								//Informa ao cliente que ele foi conectado		   
								send(remoteSocket,generateMessage("",CONNECTED,1),MAXDATASIZE,0);	
								fluxo = 1;
							}else{
							
								//Sinaliza que o nome de usuário é inválido
								send(remoteSocket,generateMessage("",INVALIDUSERNAME,1),MAXDATASIZE,0);
								fluxo = 0;
							}
					}else{
						close(remoteSocket);
						return 0;
					}
				}
			
			fluxo = 0;	
			while(!fluxo){
				
				//Recebe uma mensagem e guarda o estado de atividade do cliente
				int isActive = recv(remoteSocket, bufferRcv, MAXDATASIZE,  0);
				strcpy(_bufferRcv, bufferRcv); 		
				
				//Verifica o tipo da mensagem
				msgKind = checkKindMessage(_bufferRcv,1);
				strcpy(_bufferRcv, bufferRcv);  		
				msgContent = checkMessage(_bufferRcv);
				
				//Se o estado de conexão é ativo
				if(isActive){
					//Trata as mensagem de acordo com o seu tipo
					switch(msgKind){
						//ACTIVEUSERS: O servidor envia para o cliente a lista de usuários ativos
						case ACTIVEUSERS:{
							int i = 0;
							_users = checkActiveUsers();	
							for(i=0;i<_users.size;i++){
								send(remoteSocket,generateMessage(_users.name[i],USERNAME,1),MAXDATASIZE,0);
							}
							send(remoteSocket,generateMessage("",FINISHED,1),MAXDATASIZE,0);
							break;
						}
						//MESSAGECHAT: O servidor armazena a mensagem enviada pelo cliente	
						case MESSAGECHAT:{
							putMessageChatInLog(userName, msgContent);
							break;
						//UPDATECHAT: O servidor retorna as mensagens direcionadas ao cliente 	
						}case UPDATECHAT:{
							int i = 0;
							_messages = checkLog(userName);
							for(i=0;i<_messages.size;i++){
								send(remoteSocket,generateMessage(_messages.content[i],MESSAGECHAT,1),MAXDATASIZE,0);
							}
							send(remoteSocket,generateMessage("",FINISHED,1),MAXDATASIZE,0);
							break;
						//CLOSE: O servidor fecha a conexão 	
						}case CLOSE:{
							removeUser(userName);
							deleteUserFiles(userName);
							close(remoteSocket);
							
							free(bufferRcv);
							free(_bufferRcv);
							free(msgContent);
							return 0;
						}
					
					}
				}else{
					removeUser(userName);
					deleteUserFiles(userName);
					close(remoteSocket);
					break;
				}
				
				
			}
			
		free(bufferRcv);
		free(_bufferRcv);
		free(msgContent);	
		break;
		}		
	}
	
	return 0;
}
