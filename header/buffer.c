/*
	Universidade Federal de Alagoas - Campus A.C Simões
	Desenvolvedor: João Correia
	Data: 25/09/2015
	GitHub: www.github.com/correiajoao/chat 
*/
#include <stdio.h>
#include "buffer.h"

void flush_in(){ 
   int ch;
   while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){} 
}