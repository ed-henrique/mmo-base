#include "../models.h"
#include "../proto/message.pb-c.h"
#include "tcp.h"
#include "udp.h"
#include <netinet/in.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void send_chat_message(ClientTCP *ctcp, Msg__V1__ChatMessage__Scope scope,
                       int sender, int recipient, const char *content) {
  Msg__V1__ChatMessage msg;
  msg__v1__chat_message__init(&msg);
  msg.scope = scope;
  msg.sender = sender;
  msg.recipient = recipient;
  msg.content = strdup(content);

  size_t msglen = msg__v1__chat_message__get_packed_size(&msg);
  uint8_t *buffer = malloc(msglen);

  msg__v1__chat_message__pack(&msg, buffer);
  free(msg.content);

  uint32_t network_msglen = htonl((uint32_t)msglen);
  size_t total_size = sizeof(network_msglen) + msglen;
  uint8_t *sbuffer = malloc(total_size);

  memcpy(sbuffer, &network_msglen, sizeof(network_msglen));
  memcpy(sbuffer + sizeof(network_msglen), buffer, msglen);

  free(buffer);

  if ((sendtcp(ctcp, sbuffer, total_size)) < 0) {
    perror("could not send TCP message");
    exit(EXIT_FAILURE);
  };

  free(sbuffer);
}

int main() {
  ClientTCP ctcp = inittcp();
  ClientUDP cudp = initudp();

  Player p;
  p.id = 1;
  strncpy(p.name, "Hello", 6);
  p.x = 0;
  p.y = 0;

  while (1) {
    send_chat_message(&ctcp, MSG__V1__CHAT_MESSAGE__SCOPE__GUILD, 1, 2,
                      "Hello Guys");

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
