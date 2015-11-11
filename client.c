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
#include "header/struct.h"
#include "header/systime.h"
#include "header/message.h"
#include "header/interface.h"

#define MAXDATASIZE 500
#define MAXALLOC 500

int main(){
	char userName[50];
	char messageChat[250];
	char bufferKey, *bufferSend, *bufferRcv, *_bufferRcv;
	int flow,opt,opt2,numBytes,isChatting;
	
	struct userList _users;
	struct messageList _messages;
	
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
	
	printAnimation();
	
		do{
		printHeader("Bate-papo");
		printMenuOptions();
		scanf("%d", &opt);
			
			//Verificação do primeiro menu
			switch(opt){
				case 1:{	
					flow = 0;				
					while(!flow){	
						printHeader("Fase inicial");
						printf("Escolha seu apelido : ");
						scanf(" %s", userName);	

						bufferSend = generateMessage(userName, USERNAME,0);
						send(localSocket, bufferSend, MAXDATASIZE, 0);	

						numBytes = recv(localSocket, bufferRcv, MAXDATASIZE, 0);
						bufferRcv[numBytes] = '\0';
						strcpy(_bufferRcv, bufferRcv);

						if(checkKindMessage(_bufferRcv,0) == CONNECTED){
							printAlert("Conexão estabelecida");
							sleep(1);
							flow = 1;
						}else if(checkKindMessage(_bufferRcv,0) == INVALIDUSERNAME){
							printAlert("Nome inválido");
							sleep(1);
							flow = 0;
						}
					}
	
						do{
							printHeader("Bate-papo");
							printSecondMenuOptions();
							scanf("%d", &opt2);
							
							//Verificação do segundo menu
							switch(opt2){
								//Solicita ao servidor a lista de usuários onlines
								case 1:{
									bufferSend = generateMessage("", ACTIVEUSERS,0);
									send(localSocket, bufferSend, MAXDATASIZE, 0);	

									int i = 0;
									_users.size = i;

									numBytes = recv(localSocket, bufferRcv, MAXDATASIZE, 0);
									bufferRcv[numBytes] = '\0';
									strcpy(_bufferRcv, bufferRcv);

									while(checkKindMessage(_bufferRcv,0) != FINISHED){
										_users.size = i+1;
										strcpy(_users.name[i], checkMessage(bufferRcv));
										i++;

										numBytes = recv(localSocket, bufferRcv, MAXDATASIZE, 0);
										bufferRcv[numBytes] = '\0';
										strcpy(_bufferRcv, bufferRcv);

										if(checkKindMessage(_bufferRcv,0) == FINISHED){
											printUserList(_users);		
											waitKey();

										}
										strcpy(_bufferRcv, bufferRcv);
									}

								break;
								//Entra na sala de conversa	
								}case 2:{
									printHeader("Sala de conversa");

									isChatting = 1;
									while(isChatting){
										 fflush(stdin);
										 while(!kbhit()){

											bufferSend = generateMessage("", UPDATECHAT,0);
											send(localSocket, bufferSend, MAXDATASIZE, 0);	

											int i = 0;
											_messages.size = i;

											numBytes = recv(localSocket, bufferRcv, MAXDATASIZE, 0);
											bufferRcv[numBytes] = '\0';
											strcpy(_bufferRcv, bufferRcv);

											while(checkKindMessage(_bufferRcv,0) != FINISHED){
												_messages.size = i+1;	
												strcpy(_messages.content[i], checkMessage(bufferRcv));
												i++;

												numBytes = recv(localSocket, bufferRcv, MAXDATASIZE, 0);
												bufferRcv[numBytes] = '\0';
												strcpy(_bufferRcv, bufferRcv);

												if(checkKindMessage(_bufferRcv,0) == FINISHED){
													printMessageList(_messages);		
												}

												strcpy(_bufferRcv, bufferRcv);
											}
											 usleep(500000);
										}

										bufferKey = getchar();
										if(bufferKey == '>'){	
											printf(" [%s] - Voce: ", getHourMinutes());
											scanf(" %[^\n]s", messageChat);
											printf("\n");
											
											bufferSend = generateMessage(messageChat, MESSAGECHAT,0);
											send(localSocket, bufferSend, MAXDATASIZE, 0);
										}else if(bufferKey == 'v'){
											isChatting = 0;
										}else if(bufferKey == 'l'){
											printHeader("Sala de conversa");
										}else{
											fflush(stdin);
										}
								}

								break;	
								//Solicita o fechamento de conexão ao servidor e finaliza o cliente
								}case 3:{
									bufferSend = generateMessage("",CLOSE,0);
									send(localSocket, bufferSend, MAXDATASIZE, 0);	
									printAlert("Até mais ver, em francês, Au revoir");
									
									free(bufferSend);
									free(bufferRcv);
									free(_bufferRcv);
									return 0;
								break;
								}
							}
						}while(opt2 != 3);
					break;
				//Mostra as instruções de uso ao cliente	
				}case 2:{
					printHowWorks();
					waitKey();
					break;
					
				}case 3:{
					bufferSend = generateMessage("",CLOSE,0);
					send(localSocket, bufferSend, MAXDATASIZE, 0);	
					printAlert("Até mais ver, em francês, Au revoir");
				
					free(bufferSend);
					free(bufferRcv);
					free(_bufferRcv);
					return 0;
				}	
			}
		}while(opt != 3);	
		
		free(bufferSend);
		free(bufferRcv);
		free(_bufferRcv);
				
		return 0;
}
