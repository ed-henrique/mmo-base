#ifndef TCP_H
#define TCP_H

#include "../network.h"

ClientTCP inittcp();
void endtcp(ClientTCP *c);
ssize_t sendtcp(ClientTCP *c, const void *data, size_t datalen);

#endif /* TCP_H */
