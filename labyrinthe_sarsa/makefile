prog : dfs.o functions.o mazeEnv.o td2_sarsa_nett.o
	gcc -o prog dfs.o functions.o mazeEnv.o td2_sarsa_nett.o -lm

dfs.o : dfs.c mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors dfs.c

functions.o : functions.c functions.h
	gcc -c -Wall -Werror -Werror -Wfatal-errors functions.c

mazeEnv.o : mazeEnv.c mazeEnv.h 
	gcc -c -Wall -Werror -Wfatal-errors mazeEnv.c

td2_sarsa_nett.o : td2_sarsa_nett.c td2.h mazeEnv.h
	gcc -c -Wall -Werror -Wfatal-errors td2_sarsa_nett.c -lm

clear :
	rm -f prog dfs.o functions.o mazEnv.o td2_sarsa_nett.o

