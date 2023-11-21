#ifndef SCT_CLIENT_H
#define SCT_CLIENT_H

#include <linux/net.h>
#include <linux/socket.h>
#include <linux/ip.h>
#include <linux/in.h>
#include <linux/netpoll.h>

#include <linux/mutex.h>
#include <linux/spinlock.h>

// server ip: 192.168.56.1
#define SCT_SERVER_IP ((unsigned long int)0xc0a83801)
// separating character
#define SCT_DELIMITER ((char)0x05)

// struct for client
struct sct_client_struct {
	struct socket *sock;
	struct sockaddr_in addr;
	struct msghdr msg;
	struct iov_iter iov_it;
};

// クライアントの初期化を行う
void init_sct_client(struct sct_client_struct *, int);
// 文字列の情報を送信する関数
void sct_send(char *, int, struct sct_client_struct *);
// pidを取得する関数
int get_current_pid();
#endif // SCT_CLIENT_H
