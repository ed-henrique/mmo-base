#include "../models.h"
#include "tcp.h"
#include "udp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  ClientTCP ctcp = inittcp();
  ClientUDP cudp = initudp();

  Player p;
  p.id = 1;
  strncpy(p.name, "Hello", 6);
  p.x = 0;
  p.y = 0;

  while (1) {
    if ((sendtcp(&ctcp, (const char *)&p.name, strlen(p.name))) < 0) {
      perror("could not send TCP message");
      exit(EXIT_FAILURE);
    };

    if ((sendudp(&cudp, (const uint8_t *)&p, sizeof(p))) < 0) {
      perror("could not send UDP message");
      exit(EXIT_FAILURE);
    };

    p.x++;
    p.y++;

    sleep(1);
  }

  endtcp(&ctcp);
  endudp(&cudp);
  return 0;
}
