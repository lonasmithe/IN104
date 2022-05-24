prog : dfs.o functions.o mazeEnv.o td2.o
	gcc -o prog dfs.o functions.o mazeEnv.o td2.o -lm

dfs.o : dfs.c mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors dfs.c

functions.o : functions.c functions.h
	gcc -c -Wall -Werror -Werror -Wfatal-errors functions.c

mazeEnv.o : mazeEnv.c mazeEnv.h 
	gcc -c -Wall -Werror -Wfatal-errors mazeEnv.c

td2.o : td2.c td2.h mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors td2.c -lm

clear :
	rm -f prog dfs.o functions.o mazEnv.o td2.o

