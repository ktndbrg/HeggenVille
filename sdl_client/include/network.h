#ifndef NETWORK
#define NETWORK

void network (void);
void client_close (void);

extern int sock;
extern int port;
extern struct sockaddr_in sa;
extern struct hostent *hostlist;
extern char dotted_ip[15];

#endif
