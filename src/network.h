#ifndef NETWORK_H
#define NETWORK_H

#include <netinet/in.h>

#ifndef PORT
#define PORT 8080
#endif

#ifndef PACKET_SIZE
#define PACKET_SIZE 1024
#endif

#ifndef MAX_CLIENTS
#define MAX_CLIENTS 512
#endif

typedef enum protocol {
  UDP,
  TCP
} Protocol;

typedef struct client {
  int sockfd;
  struct sockaddr_in addr;
} ClientUDP;

typedef struct clienttcp {
  int sockfd;
} ClientTCP;

typedef struct server {
  int sockfd;
  Protocol prot;
  struct sockaddr_in addr;
} Server;

typedef struct servers {
  Server *tcp;
  Server *udp;

  int active_conn;
  int conn_fds[MAX_CLIENTS];
  struct sockaddr_in conn_addrs[MAX_CLIENTS];
} Servers;


#endif /* NETWORK_H */
