/******************************************************************************
  FileName: tcptest.c
  Author: Li_Zhihong
  Date: 20170214
******************************************************************************/
#include "tcptest.h"
#include "lwip/tcp.h"
#if 0
#include "arch/cc.h"
#else
#include "stm32f2xx.h"
#endif

#include "dbg.h"
#ifdef TCP_SERVER_TEST
static err_t tcp_server_recv(void *arg, struct tcp_pcb *pcb,struct pbuf *p,err_t err)
{
	if(p != NULL){
		dbp("%s\n", (u8*)p->payload);
		tcp_recved(pcb, p->tot_len);				//获取数据长度 tot_len：tcp数据块的长度
		/******将数据原样返回*******************/
		tcp_write(pcb,p->payload,p->tot_len,TCP_WRITE_FLAG_COPY); 	// payload为TCP数据块的起始位置
		tcp_output(pcb);
	}
	else{
		tcp_close(pcb); 				/* 作为TCP服务器不应主动关闭这个连接？ */
	}
	/* 释放该TCP段 */
	pbuf_free(p);
	err = ERR_OK;
	return err;
}

static err_t tcp_server_accept(void *arg,struct tcp_pcb *pcb,err_t err)
{
	tcp_setprio(pcb, TCP_PRIO_MIN);
	tcp_recv(pcb,tcp_server_recv);
	err = ERR_OK;
	return err;
}

void tcptest_server_init(void)
{
	struct tcp_pcb *pcb;
	pcb = tcp_new();
	tcp_bind(pcb,IP_ADDR_ANY, 4002);
	pcb = tcp_listen(pcb);
	tcp_accept(pcb,tcp_server_accept);
}
#endif	//TCP_SERVER_TEST

#ifdef TCP_CLIENT_TEST
struct tcp_pcb *tcp_client_pcb;
struct tcp_pcb *check_connected_pcb;
u8 connect_flag = 0;
u8 tcp_data[]="Hello, i am a string of TCP_CLIENT_TEST\n";
static err_t TCP_Connected(void *arg,struct tcp_pcb *pcb,err_t err)
{
	//tcp_client_pcb = pcb;
	return ERR_OK;
}

static err_t  TCP_Client_Recv(void *arg, struct tcp_pcb *pcb,struct pbuf *p,err_t err)
{
	if(p != NULL){
		tcp_recved(pcb, p->tot_len);				//获取数据长度 tot_len：tcp数据块的长度
		//p_data = p->payload;  //将data指向数据开始
		tcp_write(pcb,p->payload,p->tot_len,TCP_WRITE_FLAG_COPY);
		tcp_output(pcb);
	}
	else{	 										//如果服务器断开连接，则客户端也应断开
		tcp_close(pcb);
	}
	pbuf_free(p);
	err = ERR_OK;
	return err;
}

void tcptest_client_init(void)
{
	struct ip_addr ipaddr;
	err_t err;
	IP4_ADDR(&ipaddr,192,168,1,123);           //服务器IP地址
	tcp_client_pcb = tcp_new(); /* 建立通信的TCP控制块(Clipcb) */
	if(!tcp_client_pcb){
		return ;
	}
	err = tcp_bind(tcp_client_pcb,IP_ADDR_ANY,4003); /* 绑定本地IP地址和端口号 ，本地ip地址在LwIP_Init()中已经初始化*/
	if(err != ERR_OK){
		return ;
	}
	tcp_connect(tcp_client_pcb,&ipaddr,4001,TCP_Connected);//注册回调函数
	tcp_recv(tcp_client_pcb,TCP_Client_Recv); 				/* 设置tcp接收回调函数 */
}

void check_tcp_connected(void)
{
	struct tcp_pcb *cpcb = 0;
	connect_flag = 0;
	for(cpcb = tcp_active_pcbs;cpcb != NULL; cpcb = cpcb->next)
	{
	//	if(cpcb->local_port == TCP_LOCAL_PORT && cpcb->remote_port == TCP_SERVER_PORT)		//如果TCP_LOCAL_PORT端口指定的连接没有断开
		if(cpcb -> state == ESTABLISHED)  //如果得到应答，则证明已经连接上
		{
			connect_flag = 1;  						//连接标志
			break;
		}
	}

	if(connect_flag == 0)  	// TCP_LOCAL_PORT指定的端口未连接或已断开
	{
		tcptest_client_init(); //重新连接
		cpcb = 0;
	}
	check_connected_pcb = cpcb;
}

static err_t TCP_Client_Send_Data(struct tcp_pcb *cpcb,unsigned char *buff,unsigned int length)
{
	err_t err;

	err = tcp_write(cpcb,buff,length,TCP_WRITE_FLAG_COPY);	//发送数据
	tcp_output(cpcb);
	//tcp_close(tcp_client_pcb);				//发送完数据关闭连接,根据具体情况选择使用
	return err;
}

void tcptest_send_data(void)
{
	if(check_connected_pcb != NULL){
		TCP_Client_Send_Data(check_connected_pcb,tcp_data,sizeof(tcp_data));	//该函数为主动向服务器发送函数，
	}
}
#endif	//TCP_CLIENT_TEST

