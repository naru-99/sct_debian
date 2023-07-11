#ifndef SCI_CLIENT_H
#define SCI_CLIENT_H

#include <linux/net.h>
#include <linux/socket.h>
#include <linux/ip.h>
#include <linux/in.h>
#include <linux/netpoll.h>

#include <linux/mutex.h>
#include <linux/spinlock.h>

//192.168.10.4
#define sci_server_ip ((unsigned long int)0xc0a83801)
#define PACKET_STR_SIZE ((int)1024)
#define SCI_SEPCHAR ((char)0x05)

struct sci_client_struct {
	struct socket *sock;
	struct sockaddr_in addr;
	struct msghdr msg;
	struct iov_iter iov_it;
};

void init_sci_client(struct sci_client_struct *, int);
void sci_send(char *, int, struct sci_client_struct *);

#endif // SCI_CLIENT_H
