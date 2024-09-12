#include "udp.h"
#include "../models.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

ClientUDP initudp() {
  int sockfd;
  struct sockaddr_in addr;

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&addr, 0, sizeof(addr));

  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  ClientUDP c;
  c.sockfd = sockfd;
  c.addr = addr;

  return c;
}

void endudp(ClientUDP *c) { close(c->sockfd); }

ssize_t sendudp(ClientUDP *c, const void *data, size_t datalen) {
  return sendto(c->sockfd, data, datalen, MSG_CONFIRM,
                (const struct sockaddr *)&c->addr, sizeof(c->addr));
}
