/*
	Universidade Federal de Alagoas - Campus A.C Simões
	Desenvolvedor: João Correia
	Data: 25/09/2015
	GitHub: www.github.com/correiajoao/chat 
*/

#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "header/kbhit.h"
#include "header/error.h"
#include "header/buffer.h"
#include "header/struct.h"
#include "header/message.h"
#include "header/interface.h"

#define MAXDATASIZE 1500
#define MAXALLOC 500

int main(){
	//Variáveis Comuns
	char userName[50];
	char messageChat[250];
	char bufferKey;
	char *bufferSend;
	char *bufferRcv;
	char *_bufferRcv;
	
	int flow,opc,opc2,numBytes,isChatting;
	
	struct userList _users;
	struct messageList _messages;
	
	//Variáves de socket
	int localSocket,conection;
	struct sockaddr_in remoto;	
	
	//Alocação de memória
	bufferRcv = (char *) calloc (MAXALLOC, sizeof(char));
	_bufferRcv = (char *) calloc (MAXALLOC, sizeof(char));
	bufferSend = (char *) calloc (MAXALLOC, sizeof(char));

	localSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(localSocket == -1)
		errorSocket();
	
	//Configuração do socket para a conexão
	//Mais detalhes consulte as manpages
	remoto.sin_family = AF_INET; 
	remoto.sin_port = htons(31337);  	
	remoto.sin_addr.s_addr = inet_addr("127.0.0.1");
	bzero(&(remoto.sin_zero), 8); //Trocar por memser

	//Função de conexão ao host remoto
	conection = connect(localSocket, (struct sockaddr *)&remoto, sizeof(remoto));
	if(conection == -1)
		errorConnection();	
	
	
	header("BATE PAPO ");
	printMenuOptions();
	scanf("%d", &opc);

		switch(opc){
			case 1:{
				flow = 0;				
				while(!flow){	
					header("Fase inicial");
					printf("Escolha seu apelido : ");
					scanf(" %s", userName);	
				
					bufferSend = generateMessage(userName, USERNAME);
					send(localSocket, bufferSend, MAXDATASIZE, 0);	
					
					numBytes = recv(localSocket, bufferRcv, MAXDATASIZE, 0);
					bufferRcv[numBytes] = '\0';
					strcpy(_bufferRcv, bufferRcv);
					
					if(checkKindMessage(_bufferRcv) == CONNECTED){
						printAlert("Conexão estabelecida");
						sleep(1);
						flow = 1;
					}else if(checkKindMessage(_bufferRcv) == INVALIDUSERNAME){
						printAlert("Nome inválido");
						sleep(1);
						flow = 0;
					}
				}
				
				
				flow = 0;				
				while(!flow){	
						header("BATE PAPO ATIVO");
						printSecondMenuOptions();
						scanf("%d", &opc2);
				
						switch(opc2){
							case 1:{
								bufferSend = generateMessage("", ACTIVEUSERS);
								send(localSocket, bufferSend, MAXDATASIZE, 0);	
							
								int i = 0;
								_users.size = i;
								
								numBytes = recv(localSocket, bufferRcv, MAXDATASIZE, 0);
								bufferRcv[numBytes] = '\0';
								strcpy(_bufferRcv, bufferRcv);
								
								while(checkKindMessage(_bufferRcv) != FINISHED){
									_users.size = i+1;
									strcpy(_users.name[i], checkMessage(bufferRcv));
									i++;
								
									numBytes = recv(localSocket, bufferRcv, MAXDATASIZE, 0);
									bufferRcv[numBytes] = '\0';
									strcpy(_bufferRcv, bufferRcv);
									
									if(checkKindMessage(_bufferRcv) == FINISHED){
										printUserList(_users);		
										sleep(2);//Mudar pela verificaçao do buffer
								
									}
									strcpy(_bufferRcv, bufferRcv);
								}
								
							break;
							}case 2:{
								header("MENSAGENS DE BATE PAPO");
								
								isChatting = 1;
								while(isChatting){
									 fflush(stdin);
									 while(!kbhit()){
										 
										bufferSend = generateMessage("", UPDATECHAT);
										send(localSocket, bufferSend, MAXDATASIZE, 0);	

										int i = 0;
										_messages.size = i;

										numBytes = recv(localSocket, bufferRcv, MAXDATASIZE, 0);
										bufferRcv[numBytes] = '\0';
										strcpy(_bufferRcv, bufferRcv);

										while(checkKindMessage(_bufferRcv) != FINISHED){
											_messages.size = i+1;	
											strcpy(_messages.content[i], checkMessage(bufferRcv));
											i++;

											numBytes = recv(localSocket, bufferRcv, MAXDATASIZE, 0);
											bufferRcv[numBytes] = '\0';
											strcpy(_bufferRcv, bufferRcv);

											if(checkKindMessage(_bufferRcv) == FINISHED){
												printMessageList(_messages);		
												sleep(1);//Mudar pela verificaçao do buffer
											}

											strcpy(_bufferRcv, bufferRcv);
										}
										 sleep(1);
									}
									
									bufferKey = getchar();
									if(bufferKey == '>'){	
										printf(" Voce: ");
										scanf(" %[^\n]s", messageChat);
										printf("\n");
										bufferSend = generateMessage(messageChat, MESSAGECHAT);
										send(localSocket, bufferSend, MAXDATASIZE, 0);
									}else{
										fflush(stdin);
									}
							}
								
							break;	
							}case 3:{
								printAlert("Até mais ver, em francês, Au revoir");
								return 0;
							break;
							}
					
						}				
				}
			}case 2:{
							
			}case 3:{
				free(bufferSend);
				free(bufferRcv);
				free(_bufferRcv);
				return 0;			
			}
		}
		
		free(bufferSend);
		free(bufferRcv);
		free(_bufferRcv);
				
		return 0;
}
