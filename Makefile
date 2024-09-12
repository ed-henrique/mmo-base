CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
CFLAGS_PROD = -Wall -Werror -Wextra -g

build:
	@mkdir -p out
	$(CC) $(CFLAGS) -o out/server src/server.c src/utils/logger.c
	$(CC) $(CFLAGS) -o out/client src/clients/main.c src/clients/tcp.c \
		                 src/clients/udp.c src/models.c src/network.h \
										 src/utils/logger.c

build/prod:
	@mkdir -p out
	$(CC) $(CFLAGS_PROD) -o out/server src/server.c src/utils/logger.c
	$(CC) $(CFLAGS_PROD) -o out/client src/clients/main.c src/clients/tcp.c \
		                      src/clients/udp.c src/models.c src/network.h \
													src/utils/logger.c

debug:
	valgrind --leak-check=full --track-origins=yes out/client
	valgrind --leak-check=full --track-origins=yes out/server

clean:
	@rm -rf out
