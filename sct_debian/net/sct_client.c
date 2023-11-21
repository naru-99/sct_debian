#include <net/sct_client.h>

// 与えられたportおよびsctクライアントの初期化を行う
void init_sct_client(struct sct_client_struct *sct_cs_ptr, int port)
{
	sock_create_kern(&init_net, PF_INET, SOCK_DGRAM, IPPROTO_UDP,
			 &(sct_cs_ptr->sock));

	sct_cs_ptr->addr.sin_family = PF_INET;
	sct_cs_ptr->addr.sin_port = htons(port);
	sct_cs_ptr->addr.sin_addr.s_addr = htonl(sci_server_ip);

	kernel_connect(sct_cs_ptr->sock,
		       (struct sockaddr *)(&(sct_cs_ptr->addr)),
		       sizeof(struct sockaddr), 0);

	sct_cs_ptr->msg.msg_name = &(sct_cs_ptr->addr);
	sct_cs_ptr->msg.msg_namelen = sizeof(struct sockaddr_in);
	sct_cs_ptr->msg.msg_iter = sct_cs_ptr->iov_it;
	sct_cs_ptr->msg.msg_control = NULL;
	sct_cs_ptr->msg.msg_controllen = 0;
	sct_cs_ptr->msg.msg_flags = 0;
}

// 与えられた文字列情報を送信する
// 送信先はsctクライアントで定義したサーバ
static struct kvec iov;
static DEFINE_MUTEX(sct_send_mutex);
void sci_send(char *buf, int len, struct sct_client_struct *sct_cs_ptr)
{
	mutex_lock(&sct_send_mutex);
	iov.iov_base = buf;
	iov.iov_len = len;
	kernel_sendmsg(sct_cs_ptr->sock, &(sct_cs_ptr->msg), &iov, 1, len);
	mutex_unlock(&sct_send_mutex);
}

int get_current_pid()
{
	return (int)pid_nr(get_task_pid(current, PIDTYPE_PID));
}
