#!/bin/bash

	gcc -o server server.c header/error.h header/error.c header/struct.h header/managerdata.h header/managerdata.c header/message.h header/message.c
	
	gcc -o client client.c header/error.h header/error.c header/interface.h header/interface.c header/buffer.h header/buffer.c header/struct.h header/kbhit.h header/kbhit.c header/message.h header/message.c
