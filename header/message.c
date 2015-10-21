/*
	Universidade Federal de Alagoas - Campus A.C Simões
	Desenvolvedor: João Correia
	Data: 25/09/2015
	GitHub: www.github.com/correiajoao/chat 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "message.h"

char* generateMessage(char *value, int type, int isServer){
	char *result, tag[15], content[300];

	result = (char *) calloc ((strlen(value)+20),sizeof(char));
	
	switch(type){
		case USERNAME:{
			strcpy(tag, "userName=");
			strcpy(content, value);
			strcat(result, tag);
			strcat(result, content);						
			break;		
		}case INVALIDUSERNAME:{
			strcpy(tag, "invalidUserName=");
			strcpy(content, value);
			strcat(result, tag);
			strcat(result, content);						
			break;		
		}case ACTIVEUSERS:{
			strcpy(tag, "activeUsers=");
			strcpy(content, value);
			strcat(result, tag);
			strcat(result, content);						
			break;		
		}case CONNECTED:{
			strcpy(tag, "connected=");
			strcpy(content, value);
			strcat(result, tag);
			strcat(result, content);						
			break;		
		}case MESSAGECHAT:{
			strcpy(tag, "messageChat=");
			strcpy(content, value);
			strcat(result, tag);
			strcat(result, content);						
			break;		
		}case UPDATECHAT:{
			strcpy(tag, "updateChat=");
			strcpy(content, value);
			strcat(result, tag);
			strcat(result, content);						
			break;		
		}case FINISHED:{
			strcpy(tag, "finished=");
			strcpy(content, value);
			strcat(result, tag);
			strcat(result, content);						
			break;		
		}case CLOSE:{
			strcpy(tag, "close=");
			strcpy(content, value);
			strcat(result, tag);
			strcat(result, content);						
			break;		
		}     
		
		default:{
			break;
		}

	}
	
	if(isServer){
		printf("Mensagem gerada: %s\n", result);
		fflush(stdout);
	}
	
	return result;
	free(result);
}

int checkKindMessage(char *bufferRcv, int isServer){	
	
	if(isServer){
		printf("Mensagem recebida: %s\n", bufferRcv);
		fflush(stdout);
	}	
	
	char *tag;
	tag = strtok(bufferRcv, "=");	
	
	if(strcmp(tag, "userName") == 0){
		return USERNAME;	
	}if(strcmp(tag, "invalidUserName") == 0){
		return INVALIDUSERNAME;	
	}if(strcmp(tag, "activeUsers") == 0){
		return ACTIVEUSERS;	
	}if(strcmp(tag, "connected") == 0){
		return CONNECTED;	
	}if(strcmp(tag, "messageChat") == 0){
		return MESSAGECHAT;	
	}if(strcmp(tag, "updateChat") == 0){
		return UPDATECHAT;	
	}if(strcmp(tag, "finished") == 0){
		return FINISHED;	
	}if(strcmp(tag, "close") == 0){
		return CLOSE;	
	}
	
	return 0;			
}

char* checkMessage(char *bufferRcv){
	char *token;
	
	token = strtok(bufferRcv, "=");	
	token = strtok(NULL,"=");

	return token;			
}
