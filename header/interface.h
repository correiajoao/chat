/*
	Universidade Federal de Alagoas - Campus A.C Simões
	Desenvolvedor: João Correia
	Data: 25/09/2015
	GitHub: www.github.com/correiajoao/chat 
*/

#ifndef INTERFACE_H
#define INTERFACE_H

#include "struct.h"

//Essa função mostra o cabeçalho da interface
void printHeader(char * indentifier);

//Essa função mostra o menu inicial
void printMenuOptions();

//Essa função mostra o menu para usuários conectados
void printSecondMenuOptions();

//Essa função recebe uma estrutura de listas de usuário e a imprime  
void printUserList(struct userList _users);

//Essa função recebe uma estrutura de lista de mensagem e a imprime
void printMessageList(struct messageList _messages);

//Essa função recebe uma string e a mostra em forma de alerta
void printAlert(char *message);

//Essa função imprime como funciona o chat
void printHowWorks();

//Essa funçao imprime na tela a apresentaçao inicial
void printAnimation();

#endif