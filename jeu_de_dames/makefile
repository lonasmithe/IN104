prog : agent.o draughtboard_Env.o storage.o
	gcc -o prog draughtboard_Env.o agent.o storage.o -lm

draughtboard_Env.o : draughtboard_Env.c draughtboard_Env.h agent.h storage.h
	gcc -c -Wall -Werror -Wfatal-errors draughtboard_Env.c

agent.o : agent.c draughtboard_Env.h agent.h storage.h
	gcc -c -Wall -Werror -Wfatal-errors agent.c -lm

storage.o : agent.c draughtboard_Env.h agent.h storage.h
	gcc -c -Wall -Werror -Wfatal-errors storage.c -lm

clean :
	rm -f prog draughtboard_Env.o agent.o
