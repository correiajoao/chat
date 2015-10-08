/*
	Universidade Federal de Alagoas - Campus A.C Simões
	Desenvolvedor: João Correia
	Data: 25/09/2015
	GitHub: www.github.com/correiajoao/chat 
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "managerdata.h"

//Essa função limpa todos os arquivos usados pelo programa
void deleteFile(){
	remove("file/users.txt");
	system("rm -rf file");
}

void makeDirectory(){
	system("mkdir file");		
}

void deleteUserFiles(char *userName){
	char fileName[50];
	memset (fileName,'\0',49);
	
	strcpy(fileName,"file/");
	strcat(fileName,userName);
	strcat(fileName,".txt");
	
	remove(fileName);
}

//Essa função verifica se o useName é válido
int checkUserName(char *userName){
							
	FILE *users;
	char *token;
	char line[300];
	memset (line,'\0',299);
	
	users = fopen("file/users.txt","r");
	
	if(!users){
		return 0;
	}

	while(feof(users) == 0){
		fscanf(users,"%s", line);
		token = strtok(line,"@");	
			
		if(strcmp(token, userName) == 0){
			fclose(users);
			return 1;
		}
	}
	
	fclose(users);
	return 0;
}

//Insere um usuário da lista de usuários onlines
void insertUser(char *userName, char *address){
	FILE *users;
	char putInFile[300];
	memset (putInFile,'\0',299);

	
	//Tenta abrir o arquivo de usuários, se nao existir(situação onde não existem usuários ativos) o arquivo é criado
	users = fopen("file/users.txt","a+");
	
	if(!users)
			errorOpenFile();			
			
	//Insere o nome do usuário na lista de usuários ativos
	strcat(putInFile,userName);
	strcat(putInFile,"@");
	strcat(putInFile, address);
	strcat(putInFile,"\n");
	fputs(putInFile, users);
						
	fclose(users);
	
	printf("Usuário conectado: %s", putInFile);
	fflush(stdout);
}


//Remove um usuário da lista de usuários onlines
void removeUser(char *userName){
	int control = 0;	
	FILE *users;
	FILE *_users;
	char line[300];
	char _line[300];
	memset (line,'\0',299);
	memset (_line,'\0',299);
	
	char *token;
	char *_token;
	token = (char *) calloc (15, sizeof(char));
	_token = (char *) calloc (15, sizeof(char));
	
	users = fopen("file/users.txt","r+");
		if(!users)
			errorOpenFile();
	
	_users = fopen("file/usersTemp.txt","w+");
		if(!_users)
			errorOpenFile();
	
	while(feof(users) == 0){
		memset (line,'\0',299);
		memset (_line,'\0',299);
	
		fscanf(users,"%s", line);
		strcpy(_line, line);
		token = strtok(_line,"@");
		
		//Isso corrige um bug implementado por satanás, não sei porque ele lê o ultimo nome do arquivo duas vezes
		
			if(strcmp(token,userName) != 0){
				strcat(line,"\n");
				fputs(line,_users);
				control = 1;
			}
		
		strcpy(_token, token);
	}
	
	fclose(users);
	fclose(_users);
	
	//Verifica se existe pelo menos um usuário, se não os arquivos de usuários serão apagados
	if(control){
		remove("file/users.txt");
		rename("file/usersTemp.txt","file/users.txt");
	}else{
		remove("file/users.txt");
		remove("file/usersTemp.txt");
	}
	
	printf("Usuário desconectado: %s\n", userName);
	fflush(stdout);
	
	putMessageChatInLog(userName,"Desconectando!");
}

//Essa função retorna uma lista de usuários ativos
struct userList checkActiveUsers(){
	FILE *users;
	char *token;
	char line[300];
	memset (line,'\0',299);

	
	//Lista de usuarios ativos
	int i = 0;
	struct userList _users;

	_users.size = i;
	users = fopen("file/users.txt","r");
	
	while(feof(users) == 0){
		fscanf(users,"%s", line);
		token = strtok(line,"@");	
		
		strcpy(_users.name[i], token);
		_users.size = i;
		i++;
	}
	
	fclose(users);
	return _users;
}

//Essa funçao recebe um userName e escreve a mensagem desse usuario no log de todos os outros usuarios onlines,
//ao menos que a mensagem seja acompanhada de "@userName" que direciona a mensagem para um so cliente.
void putMessageChatInLog(char *userName, char *messageChat){
	int i;
	char fileName[50];
	char finalMessageChat[300];	
	memset (fileName,'\0',49);
	memset (finalMessageChat,'\0',299);

	FILE *logUser;

	struct userList _users = checkActiveUsers();
	for(i=0;i<_users.size;i++){
				
		if(strcmp(_users.name[i],userName) != 0){
			memset (fileName,'\0',49);
			memset (finalMessageChat,'\0',299);
			
			strcpy(fileName,"file/");
			strcat(fileName,_users.name[i]);
			strcat(fileName,".txt");
				
			logUser = fopen(fileName, "a+");
			
			strcat(finalMessageChat, userName);
			strcat(finalMessageChat, ": ");
			strcat(finalMessageChat, messageChat);
			strcat(finalMessageChat, "\n");
			
			fputs(finalMessageChat, logUser);
			fclose(logUser);
		
			fflush(stdout);
		
		}
		
	}
}

//Essa funçao recebe o userName e retorna as mensagens direcionadas para ele armazenadas pelo servidor
struct messageList checkLog(char *userName){
	FILE *logUser;
	char line[300];
	char _line[300];
	char fileName[50];
	memset (line,'\0',299);
	memset (_line,'\0',299);

	memset (fileName,'\0',300);
	
	struct messageList messages;
	
	int i = 0;
	messages.size = i;
	
	strcpy(fileName,"file/");
	strcat(fileName,userName);
	strcat(fileName,".txt");
	
	logUser = fopen(fileName, "r");
	
	if(!logUser){
		return messages;
	}
	
	while(feof(logUser) == 0){
		fgets(line,300,logUser);

		//if(strcmp(line,_line) != 0){
			strcpy(messages.content[i], line);
			messages.size = i;
			i++;
		//}	
		
		strcpy(_line, line);
	}
	
	fclose(logUser);
	remove(fileName);
	return messages;
}