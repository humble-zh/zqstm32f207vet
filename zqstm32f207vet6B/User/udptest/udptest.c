/******************************************************************************
  FileName: udptest.c
  Author: Li_Zhihong
  Date: 20170214
******************************************************************************/
#include "udptest.h"
#include "lwip/udp.h"
#if 0
#include "arch/cc.h"
#else
#include "stm32f2xx.h"
#endif

#include "dbg.h"
#ifdef UDP_SERVER_TEST
static void udp_server_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p,struct ip_addr *addr, u16_t port)
{
	struct ip_addr destAddr = *addr;
	dbp("port:%u\n", port);
	if(p != NULL){
		dbp("%s", (u8*)p->payload);
		udp_sendto(pcb,p,&destAddr,port);
	}
	pbuf_free(p);
}

void udptest_server_init(void)
{
	struct udp_pcb *pcb;
	pcb = udp_new();
	udp_bind(pcb, IP_ADDR_ANY, 3001);
	udp_recv(pcb, udp_server_recv, NULL);
}
#endif	//UDP_SERVER_TEST

#ifdef UDP_CLIENT_TEST
uc8 udp_data[] = "Hello world!\n";
struct udp_pcb *udp_pcb;
struct ip_addr ipaddr;
struct pbuf *udp_p;
void udptest_client_init(void)
{
	udp_p = pbuf_alloc(PBUF_RAW,sizeof(udp_data),PBUF_RAM);
	udp_p->payload = (void *)udp_data;
	ipaddr.addr = htonl((	(u32_t)((192) & 0xff) << 24) | \
                           	((u32_t)((168) & 0xff) << 16) | \
                           	((u32_t)((1) & 0xff) << 8) | \
                            (u32_t)((123) & 0xff));
	udp_pcb = udp_new();
	udp_bind(udp_pcb,IP_ADDR_ANY,3002);
	udp_connect(udp_pcb,&ipaddr,3003);
}

void udptest_send_data(void)
{
	udp_send(udp_pcb, udp_p);
}
#endif	//UDP_CLIENT_TEST

