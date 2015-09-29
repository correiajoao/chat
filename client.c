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

int main(){

	//Variáveis Comuns
	char *userName;
	struct userList _users;
	char *msg;
	char *bufferRcv;
	char *_bufferRcv;
	int fluxo;
	int opc,opc2;
	int numBytes;

	//Variáves de socket
	int conection;
	int localSocket;
	struct sockaddr_in remoto;	
	
	//Alocação de memória
	bufferRcv = (char *) calloc (MAXALLOC, sizeof(char));
	_bufferRcv = (char *) calloc (MAXALLOC, sizeof(char));
	msg = (char *) calloc (MAXALLOC, sizeof(char));
	userName = (char *) calloc (MAXALLOC, sizeof(char));

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
				fluxo = 0;				
				while(!fluxo){	
					header("Fase inicial");
					printf("Escolha seu apelido : ");
					scanf(" %s", userName);	
				
					msg = generateMessage(userName, USERNAME);
					send(localSocket, msg, MAXDATASIZE, 0);	
					
					numBytes = recv(localSocket, bufferRcv, MAXDATASIZE, 0);
					bufferRcv[numBytes] = '\0';
					strcpy(_bufferRcv, bufferRcv);
					
					if(checkKindMessage(_bufferRcv) == CONNECTED){
						printAlert("Conexão estabelecida");
						sleep(1);
						fluxo = 1;
					}else if(checkKindMessage(_bufferRcv) == INVALIDUSERNAME){
						printAlert("Nome inválido");
						sleep(1);
						fluxo = 0;
					}
				}
				
				
				fluxo = 0;				
				while(!fluxo){	
						header("BATE PAPO ATIVO");
						printSecondMenuOptions();
						scanf("%d", &opc2);
				
						switch(opc2){
							case 1:{
								msg = generateMessage("", ACTIVEUSERS);
								send(localSocket, msg, MAXDATASIZE, 0);	
							
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
								}
								
								printUserList(_users);
								
								sleep(5);//Mudar pela verificaçao do buffer
								
							break;
							}case 2:{
								
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
				return 0;			
			}
		}	
		return 0;
}
