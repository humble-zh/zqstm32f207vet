/******************************************************************************
  FileName: tcptest.h
  Author: Li_Zhihong
  Date: 20170214
******************************************************************************/
#ifndef __TCPTEST_H__
#define __TCPTEST_H__

//#define TCP_SERVER_TEST
//#define TCP_CLIENT_TEST

#ifdef TCP_SERVER_TEST
extern void tcptest_server_init(void);
#else
#define tcptest_server_init()	
#endif	//TCP_SERVER_TEST


#ifdef TCP_CLIENT_TEST
extern void tcptest_client_init(void);
extern void check_tcp_connected(void);
extern void tcptest_send_data(void);
#else
#define tcptest_client_init()	
#define check_tcp_connected()	
#define tcptest_send_data()	
#endif	//TCP_CLIENT_TEST


#endif	//__TCPTEST_H__

