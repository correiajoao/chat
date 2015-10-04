/*
	Universidade Federal de Alagoas - Campus A.C Simões
	Desenvolvedor: João Correia
	Data: 25/09/2015
	GitHub: www.github.com/correiajoao/chat 
*/

#ifndef STRUCT_H
#define STRUCT_H

struct userList{
	int size;
	char name[150][100];
};

struct messageList{
	int size;
	char content[150][100];
};

#endif