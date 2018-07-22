.PHONY:all
all:poll_server poll_client

poll_server:poll_server.c
	gcc -o $@ $^
poll_client:poll_client.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm poll_server poll_client
