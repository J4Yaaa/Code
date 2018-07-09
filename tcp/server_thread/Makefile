.PHONY:all
all:client server

client:client.c
	gcc -o $@ $^

server:server.c
	gcc -o $@ $^ -lpthread

.PHONY:clean
clean:
	rm server client
