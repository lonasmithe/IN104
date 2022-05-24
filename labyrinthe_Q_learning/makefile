prog : dfs.o functions.o mazeEnv.o tdfinal.o
	gcc -o prog dfs.o functions.o mazeEnv.o tdfinal.o -lm

dfs.o : dfs.c mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors dfs.c

functions.o : functions.c functions.h
	gcc -c -Wall -Werror -Werror -Wfatal-errors functions.c

mazeEnv.o : mazeEnv.c mazeEnv.h 
	gcc -c -Wall -Werror -Wfatal-errors mazeEnv.c

tdfinal.o : tdfinal.c td2.h mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors tdfinal.c -lm

clear :
	rm -f prog dfs.o functions.o mazEnv.o tdfinal.o

