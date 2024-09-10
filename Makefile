CC = gcc
CFLAGS = -Wall -Werror -Wextra

build:
	@mkdir -p out
	$(CC) $(CFLAG) -o out/server src/server.c
	$(CC) $(CFLAG) -o out/client src/client.c

clean:
	@rm -rf out
