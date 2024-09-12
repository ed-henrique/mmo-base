CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
LDFLAGS = -lprotobuf-c
CFLAGS_PROD = -Wall -Werror -Wextra -lprotobuf-c -O3 -s
LDFLAGS_PROD = -lprotobuf-c

build/dev:
	@mkdir -p out
	$(CC) $(CFLAGS) -o out/server src/server.c src/proto/message.pb-c.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o out/client src/clients/main.c src/clients/tcp.c \
		                 src/clients/udp.c src/proto/message.pb-c.c $(LDFLAGS)

build/prod:
	@mkdir -p out
	$(CC) $(CFLAGS_PROD) -o out/server src/server.c src/proto/message.pb-c.c \
		                      $(LDFLAGS_PROD)
	$(CC) $(CFLAGS_PROD) -o out/client src/clients/main.c src/clients/tcp.c \
		                      src/clients/udp.c src/proto/message.pb-c.c \
													$(LDFLAGS_PROD)

build/proto:
	protoc --c_out=. src/proto/message.proto

debug:
	valgrind --leak-check=full --track-origins=yes out/client
	valgrind --leak-check=full --track-origins=yes out/server

clean:
	@rm -rf out

dev:
	@$(MAKE) clean
	bear -- $(MAKE) build/dev
