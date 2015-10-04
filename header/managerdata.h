/*
	Universidade Federal de Alagoas - Campus A.C Simões
	Desenvolvedor: João Correia
	Data: 25/09/2015
	GitHub: www.github.com/correiajoao/chat 
*/
#ifndef MANAGERDATA_H
#define MANAGERDATA_H

#include "struct.h"

//Limpa todos os arquivos usados pelo programa
void deleteFiles();

//Limpa os arquivos gerados por um usuário específico
void deleteUserFiles(char *userName);

//Verifica se o userName existe na lista de usuários online
int checkUserName(char *userName);

//Insere um usuário da lista de usuários onlines
void insertUser(char *userName, char *address);

//Remove um usuário da lista de usuários onlines
void removeUser(char *userName);

//Retorna a lista de usuários ativos
struct userList checkActiveUsers();

//Escreve uma mensagem no log de todos os outros usuarios onlines a menos que
//a mensagem seja acompanhada de "@userName" que direciona a mensagem para um só um cliente.
void putMessageChatInLog(char *userName, char *messageChat);

//Retorna as mensagens direcionadas a um cliente
struct messageList checkLog(char *userName);

#endif