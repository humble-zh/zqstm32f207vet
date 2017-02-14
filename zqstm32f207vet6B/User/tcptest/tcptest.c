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
		tcp_recved(pcb, p->tot_len);				//��ȡ���ݳ��� tot_len��tcp���ݿ�ĳ���
		/******������ԭ������*******************/
		tcp_write(pcb,p->payload,p->tot_len,TCP_WRITE_FLAG_COPY); 	// payloadΪTCP���ݿ����ʼλ��
		tcp_output(pcb);
	}
	else{
		tcp_close(pcb); 				/* ��ΪTCP��������Ӧ�����ر�������ӣ� */
	}
	/* �ͷŸ�TCP�� */
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
		tcp_recved(pcb, p->tot_len);				//��ȡ���ݳ��� tot_len��tcp���ݿ�ĳ���
		//p_data = p->payload;  //��dataָ�����ݿ�ʼ
		tcp_write(pcb,p->payload,p->tot_len,TCP_WRITE_FLAG_COPY);
		tcp_output(pcb);
	}
	else{	 										//����������Ͽ����ӣ���ͻ���ҲӦ�Ͽ�
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
	IP4_ADDR(&ipaddr,192,168,1,123);           //������IP��ַ
	tcp_client_pcb = tcp_new(); /* ����ͨ�ŵ�TCP���ƿ�(Clipcb) */
	if(!tcp_client_pcb){
		return ;
	}
	err = tcp_bind(tcp_client_pcb,IP_ADDR_ANY,4003); /* �󶨱���IP��ַ�Ͷ˿ں� ������ip��ַ��LwIP_Init()���Ѿ���ʼ��*/
	if(err != ERR_OK){
		return ;
	}
	tcp_connect(tcp_client_pcb,&ipaddr,4001,TCP_Connected);//ע��ص�����
	tcp_recv(tcp_client_pcb,TCP_Client_Recv); 				/* ����tcp���ջص����� */
}

void check_tcp_connected(void)
{
	struct tcp_pcb *cpcb = 0;
	connect_flag = 0;
	for(cpcb = tcp_active_pcbs;cpcb != NULL; cpcb = cpcb->next)
	{
	//	if(cpcb->local_port == TCP_LOCAL_PORT && cpcb->remote_port == TCP_SERVER_PORT)		//���TCP_LOCAL_PORT�˿�ָ��������û�жϿ�
		if(cpcb -> state == ESTABLISHED)  //����õ�Ӧ����֤���Ѿ�������
		{
			connect_flag = 1;  						//���ӱ�־
			break;
		}
	}

	if(connect_flag == 0)  	// TCP_LOCAL_PORTָ���Ķ˿�δ���ӻ��ѶϿ�
	{
		tcptest_client_init(); //��������
		cpcb = 0;
	}
	check_connected_pcb = cpcb;
}

static err_t TCP_Client_Send_Data(struct tcp_pcb *cpcb,unsigned char *buff,unsigned int length)
{
	err_t err;

	err = tcp_write(cpcb,buff,length,TCP_WRITE_FLAG_COPY);	//��������
	tcp_output(cpcb);
	//tcp_close(tcp_client_pcb);				//���������ݹر�����,���ݾ������ѡ��ʹ��
	return err;
}

void tcptest_send_data(void)
{
	if(check_connected_pcb != NULL){
		TCP_Client_Send_Data(check_connected_pcb,tcp_data,sizeof(tcp_data));	//�ú���Ϊ��������������ͺ�����
	}
}
#endif	//TCP_CLIENT_TEST

