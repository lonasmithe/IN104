Sortie entrée
-commande


prog:dfs.o functions.o mazeEnv.o
	gcc -o prog dfs.o functions.o mazeEnv.o

dfs.o dfs.c mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors dfs.c

functions.o functions.c functions.h
	gcc -c -Wall -Werror -Werror -Wfatal-errors. functions. c

mazeEnv.o : mazeEnv.c mazeEnv.h 
	gcc -c -Wall -Werror -Wfatlerror mazeEnv.c

clear.
rm -f prog dfs.o functions.o mazEnv.i

