server:server.o message.o
	gcc -g server.o message.o -o server
server.o:server.c server.h
	gcc -c server.c
message.o:message.c message.h server.h
	gcc -c message.c

clean:
	rm -f *.o
