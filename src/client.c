#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "player.c"
#include "network.h"

void init(int *sockfd, struct sockaddr_in *servaddr) {
  if ((*sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(servaddr, 0, sizeof(*servaddr));

  servaddr->sin_family = AF_INET;
  servaddr->sin_port = htons(PORT);
  servaddr->sin_addr.s_addr = INADDR_ANY;
}

void sendmessage(int sockfd, struct sockaddr_in servaddr, char *message) {
  sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM,
         (const struct sockaddr *)&servaddr, sizeof(servaddr));
}

void sendplayer(int sockfd, struct sockaddr_in servaddr, Player *player) {
  sendto(sockfd, (uint8_t *)player, sizeof(*player), MSG_CONFIRM,
         (const struct sockaddr *)&servaddr, sizeof(servaddr));
}

int main() {
  int sockfd;
  char buffer[PACKET_SIZE];
  struct sockaddr_in servaddr;

  init(&sockfd, &servaddr);

  Player p;
  p.id = 1;
  p.username = 'W';
  p.x = 0;
  p.y = 0;

  while (1) {
    // sendmessage(sockfd, servaddr, "Hello");
    sendplayer(sockfd, servaddr, &p);
    p.x++;
    p.y++;

    sleep(1);
  }

  close(sockfd);
  return 0;
}
