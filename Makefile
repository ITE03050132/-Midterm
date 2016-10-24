Lab06_1: Server.c Client.c
	gcc -o Server Server.c
	gcc -o Client Client.c
Server.o: Server.c
	gcc -c Server.c
Client.o: Client.c
	gcc -c Client.c
clean:
	rm *.o Lab06_1
