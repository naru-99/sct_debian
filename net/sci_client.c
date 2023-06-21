#include <net/sci_client.h>

void init_sci_client(struct sci_client_struct *sci_cs_ptr, int port)
{
	sock_create_kern(&init_net, PF_INET, SOCK_DGRAM, IPPROTO_UDP,
			 &(sci_cs_ptr->sock));

	sci_cs_ptr->addr.sin_family = PF_INET;
	sci_cs_ptr->addr.sin_port = htons(port);
	sci_cs_ptr->addr.sin_addr.s_addr = htonl(sci_server_ip);

	kernel_connect(sci_cs_ptr->sock,
		       (struct sockaddr *)(&(sci_cs_ptr->addr)),
		       sizeof(struct sockaddr), 0);

	sci_cs_ptr->msg.msg_name = &(sci_cs_ptr->addr);
	sci_cs_ptr->msg.msg_namelen = sizeof(struct sockaddr_in);
	sci_cs_ptr->msg.msg_iter = sci_cs_ptr->iov_it;
	sci_cs_ptr->msg.msg_control = NULL;
	sci_cs_ptr->msg.msg_controllen = 0;
	sci_cs_ptr->msg.msg_flags = 0;
}

static struct kvec iov;
static DEFINE_MUTEX(sci_send_mutex);
void sci_send(char *buf, int len, struct sci_client_struct *sci_cs_ptr)
{
		mutex_lock(&sci_send_mutex);
		iov.iov_base = buf;
		iov.iov_len = len;
		kernel_sendmsg(sci_cs_ptr->sock, &(sci_cs_ptr->msg), &iov, 1,
			       len);
		mutex_unlock(&sci_send_mutex);
}
