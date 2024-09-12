#ifndef UDP_H
#define UDP_H

#include "../network.h"

ClientUDP initudp();
void endudp(ClientUDP *c);
ssize_t sendudp(ClientUDP *c, const void *data, size_t datalen);

#endif /* UDP_H */
