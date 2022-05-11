prog : agent.o draughtboard_Env.o
	gcc -o prog draughtboard_Env.o agent.o -lm

draughtboard_Env.o : draughtboard_Env.c draughtboard_Env.h agent.h 
	gcc -c -Wall -Werror -Wfatal-errors draughtboard_Env.c

agent.o : agent.c draughtboard_Env.h agent.h
	gcc -c -Wall -Werror -Wfatal-errors agent.c -lm

clean :
	rm -f prog draughtboard_Env.o agent.o
