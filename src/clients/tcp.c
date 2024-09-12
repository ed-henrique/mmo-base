#include "tcp.h"
#include "../models.h"
#include "../utils/logger.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

ClientTCP inittcp() {
  int sockfd;
  struct sockaddr_in addr;

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  if (connect(sockfd, (const struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("Connection failed for TCP");
    exit(EXIT_FAILURE);
  }

  ClientTCP c;
  c.sockfd = sockfd;

  return c;
}

void endtcp(ClientTCP *c) { close(c->sockfd); }

ssize_t sendtcp(ClientTCP *c, const void *data, size_t datalen) {
  return send(c->sockfd, data, datalen, MSG_CONFIRM);
}
