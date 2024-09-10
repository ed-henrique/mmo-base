#include "network.h"
#include "player.c"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void init(int *sockfd, struct sockaddr_in *cliaddr,
          struct sockaddr_in *servaddr) {
  if ((*sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(cliaddr, 0, sizeof(*cliaddr));
  memset(servaddr, 0, sizeof(*servaddr));

  servaddr->sin_family = AF_INET;
  servaddr->sin_port = htons(PORT);
  servaddr->sin_addr.s_addr = INADDR_ANY;

  if (bind(*sockfd, (const struct sockaddr *)servaddr, sizeof(*servaddr)) < 0) {
    perror("Bind failed");
    exit(EXIT_FAILURE);
  }
}

int receivemessage(int sockfd, struct sockaddr_in cliaddr, socklen_t len,
                   char *buffer) {
  return recvfrom(sockfd, (char *)buffer, PACKET_SIZE, MSG_WAITALL,
                  (struct sockaddr *)&cliaddr, &len);
}

int receiveplayer(int sockfd, struct sockaddr_in cliaddr, socklen_t len,
                  Player *player) {
  return recvfrom(sockfd, (Player *)player, sizeof(*player), MSG_WAITALL,
                  (struct sockaddr *)&cliaddr, &len);
}

int main() {
  int sockfd;
  char buffer[PACKET_SIZE];
  struct sockaddr_in cliaddr, servaddr;

  init(&sockfd, &cliaddr, &servaddr);

  int n;
  Player p;
  socklen_t len;
  len = sizeof(cliaddr);

  while (1) {
    n = receiveplayer(sockfd, cliaddr, len, &p);
    printf("Client (ID=%d Username=%c X=%.2lf Y=%.2lf)\n", p.id, p.username,
           p.x, p.y);
  }

  return 0;
}
