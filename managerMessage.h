//Enumerador para os tipos de mensagens trocadas.	
enum tag{
	USERNAME,
	INVALIDUSERNAME,
	ACTIVEUSERS,
	CONNECTED,
	MESSAGECHAT,
	FINISHED,
	CLOSE
};

//Essa função recebe um conteúdo e um tipo de mensagem, assim gera uma string pronta para ser enviada através do método send().
char* generateMessage(char *value, int type){
	char *result, *tag, *content;

	tag = (char *) calloc (15,sizeof(char));
	content = (char *) calloc (strlen(value),sizeof(char));
	result = (char *) calloc ((strlen(value)+10),sizeof(char));
	
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
	return result;
}

//Atenção: funções modificam o ponteiro recebido como parâmetro
//Essa função recebe uma string e retorna somente o seu tipo.
int checkKindMessage(char * bufferRcv){	
	char *tag;
	tag = (char *) calloc (50,sizeof(char));
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
	}if(strcmp(tag, "finished") == 0){
		return FINISHED;	
	}if(strcmp(tag, "close") == 0){
		return CLOSE;	
	}
	
	return 0;			
}

//Atenção: funções modificam o ponteiro recebido como parâmetro.
//Essa função recebe uma mensagem e retorna somente o seu conteúdo.
char* checkMessage(char * bufferRcv){
	char *token;
	token = (char *) calloc (50,sizeof(char));

	token = strtok(bufferRcv, "=");	
	token = strtok(NULL,"=");

	return token;			
}
