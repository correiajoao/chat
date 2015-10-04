/*
	Universidade Federal de Alagoas - Campus A.C Simões
	Desenvolvedor: João Correia
	Data: 25/09/2015
	GitHub: www.github.com/correiajoao/chat 
*/

#ifndef MESSAGE_H
#define MESSAGE_H

//Enumerador para os tipos de mensagens trocadas.	
enum tag{
	USERNAME,
	INVALIDUSERNAME,
	ACTIVEUSERS,
	CONNECTED,
	MESSAGECHAT,
	UPDATECHAT,
	FINISHED,
	CLOSE
};

//Essa função recebe um conteúdo e um tipo de mensagem, assim gera uma string pronta para ser enviada através do método send().
char* generateMessage(char *value, int type);

//Atenção: funções modificam o ponteiro recebido como parâmetro
//Essa função recebe uma string e retorna somente o seu tipo.
int checkKindMessage(char *bufferRcv);

//Atenção: funções modificam o ponteiro recebido como parâmetro.
//Essa função recebe uma mensagem e retorna somente o seu conteúdo.
char* checkMessage(char *bufferRcv);

#endif