//void gotoxy(int x, int y){
//	printf("%c[%d;%df", 0x1B,y,x);
//}

//Essa função apresenta o cabeçalho da interface
void header(char * indentifier){
	int i;	
	int size = strlen(indentifier);
	int padding = (78 - size)/2;
	
	system("clear");

	printf("--------------------------------------------------------------------------------\n");	
	for(i=0;i<padding; i++){
		printf("#");
	}	

	printf(" %s ", indentifier);
	
	for(i=0;i<padding; i++){
		printf("#");	
	}
	
	printf("                                                         Último acesso: %s\n", __TIME__);
	printf("--------------------------------------------------------------------------------\n");
}

//Essa função apresenta o menu inicial
void printMenuOptions(){
	printf("\n");
	printf("1 | Participar\n");
	printf("2 | Entenda como funcina\n");
	printf("3 | Sair\n");
	printf("\n");
	printf("Escolha sua opção: ");
}

//Essa função apresenta o menu inicial
void printSecondMenuOptions(){
	printf("\n");
	printf("1 | Verificar Lista de usuários ativos\n");
	printf("2 | Entrar no bate papo\n");
	printf("3 | Desconectar\n");
	printf("\n");
	printf("Escolha sua opção: ");
}

void printUserList(struct userList _users){
	int i = 0;
	header("LISTA DE USUARIOS ATIVOS");								
	printf("Tamanho da lista recebida %d\n", _users.size);
	printf("Usuário número                  Usuário                  Atualizado às: %s\n", __TIME__);
	for(i=0;i<_users.size;i++){
	printf("-- >> %d                     -->> %s\n", i, _users.name[i]);
	}
								
	printf("\n");
	printf("------------------------------- FIM DA LISTA -----------------------------------\n");
}

void printHowWorks(){
	header("ENTENDA COMO FUNCIONA");
	printf("Funciona bem ... \n");
}

void printAlert(char *message){
	int i;	
	int size = strlen(message);
	int padding = (76 - size)/2;
	
	printf("\n");
	printf("\n");
	
	for(i=0;i<padding; i++){
		printf(" ");
	}	

	printf(">> %s <<", message);
	
	for(i=0;i<padding; i++){
		printf(" ");	
	}
	printf("\n");
}