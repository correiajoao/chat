#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

//Cabeçalhos 
#include "structs.h"
#include "interface.h"
#include "error.h"
#include "managerMessage.h"
#include "managerFile.h"

#define MAXDATASIZE 1500
#define MAXALLOC 500
#define BACKLOG 5


int main(){
	//Variáveis comuns
	char *userName;
	pid_t pid;
	struct userList _users;
	struct messageList _messages;
	int fluxo;	

	//Variáveis de mensagens
	char *bufferRcv;
	char *_bufferRcv;
	char *msgContent;
	int msgKind;	
	
	//Variaveis de socket
	int localSocket;
	int remoteSocket;

	int structSize;
	struct sockaddr_in local;
	struct sockaddr_in remote;
	
	//Alocação de memória necessária
	bufferRcv = (char *) calloc (MAXALLOC, sizeof(char));
	_bufferRcv = (char *) calloc (MAXALLOC, sizeof(char));	
	msgContent = (char *) calloc (MAXALLOC, sizeof(char));	
	userName = (char *) calloc (MAXALLOC, sizeof(char));

	//Apagando todos os dados de seções passadas
	deleteFiles();

	localSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(localSocket == -1)
		errorSocket();
		
	local.sin_family = AF_INET; 
	local.sin_port = htons(31337);  	
	local.sin_addr.s_addr = INADDR_ANY;
	
	bzero(&(local.sin_zero), 8);// Trocar por memset

	if(bind(localSocket, (struct sockaddr *)&local, sizeof(local)) == -1)
		errorBind();
	if(listen (localSocket, BACKLOG) == -1)
		errorListen();
	
	structSize = sizeof(struct sockaddr_in);
	
	while(1){
		remoteSocket = accept(localSocket, (struct sockaddr *)&remote, &structSize);

		pid = fork();
		
		if(pid == 0){
			
				fluxo = 0;
				while(!fluxo){				
					recv(remoteSocket, bufferRcv, MAXDATASIZE,  0);
					strcpy(_bufferRcv, bufferRcv); 		
					
					if(checkKindMessage(_bufferRcv) == USERNAME){
						
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
								send(remoteSocket,generateMessage("",CONNECTED),MAXDATASIZE,0);	
								fluxo = 1;
							}else{
							
								//Sinaliza que o nome de usuário é inválido
								send(remoteSocket,generateMessage("",INVALIDUSERNAME),MAXDATASIZE,0);
								fluxo = 0;
							}
						}
					}
			
			
			fluxo = 0;	
			while(!fluxo){
				
				int isActive = recv(remoteSocket, bufferRcv, MAXDATASIZE,  0);
				strcpy(_bufferRcv, bufferRcv); 		
		
				msgKind = checkKindMessage(_bufferRcv);
				strcpy(_bufferRcv, bufferRcv);  		
				msgContent = checkMessage(_bufferRcv);
				
				//Se o cliente fechar a conexao o processo filho e terminado
				if(isActive){
					printf("Mensagem recebida\n");
					fflush(stdout);
					switch(msgKind){
						case ACTIVEUSERS:{
								int i = 0;
								_users = checkActiveUsers();
		
								for(i=0;i<_users.size;i++){
									send(remoteSocket,generateMessage(_users.name[i],USERNAME),MAXDATASIZE,0);
								}
							
								send(remoteSocket,generateMessage("",FINISHED),MAXDATASIZE,0);
							break;
						}
						case MESSAGECHAT:{
							printf("MessageChat recebida\n");
							fflush(stdout);
							putMessageChatInLog(userName, msgContent);
							break;
						}case UPDATECHAT:{
							int i = 0;
							_messages = checkLog(userName);
							
							for(i=0;i<_messages.size;i++){
								printf("Enviando mensagens : %s\n", _messages.content[i]);
								fflush(stdout);
								send(remoteSocket,generateMessage(_messages.content[i],MESSAGECHAT),MAXDATASIZE,0);
							}
							
							send(remoteSocket,generateMessage("",FINISHED),MAXDATASIZE,0);
							break;
						}case CLOSE:{
							removeUser(userName);
							break;
						}

					}
				}else{
					putMessageChatInLog(userName,"Estou indo embora");
					removeUser(userName);
					deleteUserFiles(userName);
					close(remoteSocket);
					break;
				}
				
				
			}
			
		break;
		}		
	}
	
	return 0;
}
