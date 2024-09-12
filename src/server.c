#include "models.h"
#include "network.h"
#include "utils/logger.h"
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

Servers init() {
  int sockfd_udp, sockfd_tcp;
  struct sockaddr_in addr;

  if ((sockfd_udp = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation for UDP failed");
    exit(EXIT_FAILURE);
  }

  if ((sockfd_tcp = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket creation for TCP failed");
    exit(EXIT_FAILURE);
  }

  flog_info("sockets are udp=%d tcp=%d", sockfd_udp, sockfd_tcp);

  memset(&addr, 0, sizeof(addr));

  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  if (bind(sockfd_udp, (const struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("Bind failed for UDP");
    exit(EXIT_FAILURE);
  }

  if (bind(sockfd_tcp, (const struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("Bind failed for TCP");
    exit(EXIT_FAILURE);
  }

  if (listen(sockfd_tcp, MAX_CLIENTS) < 0) {
    perror("Could not listen to connections");
    exit(EXIT_FAILURE);
  }

  Server udp;
  udp.prot = UDP;
  udp.sockfd = sockfd_udp;
  udp.addr = addr;

  Server tcp;
  tcp.prot = TCP;
  tcp.sockfd = sockfd_tcp;
  tcp.addr = addr;

  Servers ss;
  ss.udp = &udp;
  ss.tcp = &tcp;
  ss.active_conn = 0;

  return ss;
}

int recvudp(Server *s, struct sockaddr_in *c, void *restrict buffer,
            size_t buffersize) {
  return recvfrom(s->sockfd, buffer, buffersize, 0, (struct sockaddr *)c,
                  (socklen_t *restrict)sizeof(*c));
}

int recvtcp(ClientTCP *c, void *restrict buffer, size_t buffersize) {
  return recv(c->sockfd, buffer, buffersize, 0);
}

void remove_closed_tcp_conns(ClientTCP tcpcs[MAX_CLIENTS], int *active_tcp_conns, int i) {
  close(tcpcs[i].sockfd);

  for (int j = i; j < *active_tcp_conns; j++) {
    tcpcs[j] = tcpcs[j + 1];
  }

  (*active_tcp_conns)--;
}

int main() {
  fd_set readfds;
  Servers ss = init();
  char buffer[PACKET_SIZE];
  ClientTCP tcpcs[MAX_CLIENTS];
  int n, ns, max_sd, activity;

  struct timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 500000;

  int active_tcp_conns = 0;
  struct sockaddr_in caddr;
  memset(&caddr, 0, sizeof(caddr));
  socklen_t addr_len = sizeof(ss.tcp->addr);

  Player p;
  while (1) {
    FD_ZERO(&readfds);

    FD_SET(ss.udp->sockfd, &readfds);
    FD_SET(ss.tcp->sockfd, &readfds);
    max_sd = ss.udp->sockfd > ss.tcp->sockfd ? ss.udp->sockfd : ss.tcp->sockfd;

    for (int i = 0; i < active_tcp_conns; i++) {
      FD_SET(tcpcs[i].sockfd, &readfds);
      if (tcpcs[i].sockfd > max_sd)
        max_sd = tcpcs[i].sockfd;
    }

    activity = select(max_sd + 1, &readfds, NULL, NULL, &timeout);

    if (activity < 0 && errno != EINTR) {
      log_error("There was an error when selecting the socket");
    }

    if (FD_ISSET(ss.udp->sockfd, &readfds)) {
      n = recvudp(ss.udp, &caddr, (Player *restrict)&p, sizeof(p));
      printf("Client (ID=%d Username=%s X=%d Y=%d)\n", p.id, p.name, p.x, p.y);
    }

    if (FD_ISSET(ss.tcp->sockfd, &readfds) && active_tcp_conns < MAX_CLIENTS) {
      ns = accept(ss.tcp->sockfd, (struct sockaddr *)&caddr, &addr_len);

      if (ns < 0) {
        perror("Could not accept new connections");
        exit(EXIT_FAILURE);
      }

      ClientTCP tcpc;
      tcpc.sockfd = ns;
      tcpcs[active_tcp_conns++] = tcpc;
    }

    for (int i = 0; i < active_tcp_conns; i++) {
      if (FD_ISSET(tcpcs[i].sockfd, &readfds)) {
        n = recvtcp(&tcpcs[i], buffer, PACKET_SIZE);

        if (n == 0) {
          log_info("Client disconnected");
          remove_closed_tcp_conns(tcpcs, &active_tcp_conns, i);
          i--;
        } else {
          buffer[n] = '\0';
          log_info(buffer);
        }
      }
    }
  }

  return 0;
}
