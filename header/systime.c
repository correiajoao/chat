/*
	Universidade Federal de Alagoas - Campus A.C Simões
	Desenvolvedor: João Correia
	Data: 25/09/2015
	GitHub: www.github.com/correiajoao/chat 
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "systime.h"

char* getHourMinutesSeconds(){
	char *result = (char*) calloc(20,sizeof(char)); 
	struct tm *local;
	time_t t;
	
	t= time(NULL);
	local=localtime(&t);

	int hour=local->tm_hour;
	int min=local->tm_min;
	int sec=local->tm_sec;
	
	sprintf(result,"%d:%d:%d", hour, min, sec);
	
	return result;
	free(result);
}

char* getHourMinutes(){
	char *result = (char*) calloc(20,sizeof(char)); 
	struct tm *local;
	time_t t;
	
	t= time(NULL);
	local=localtime(&t);

	int hour=local->tm_hour;
	int min=local->tm_min;
	
	sprintf(result,"%d:%d", hour, min);
	
	return result;
	free(result);
}