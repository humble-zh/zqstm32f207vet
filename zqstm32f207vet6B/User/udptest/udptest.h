/******************************************************************************
  FileName: udptest.h
  Author: Li_Zhihong
  Date: 20170214
******************************************************************************/
#ifndef __UDPTEST_H__
#define __UDPTEST_H__

//#define UDP_SERVER_TEST
//#define UDP_CLIENT_TEST

#ifdef UDP_SERVER_TEST
extern void udptest_server_init(void);
#else
#define udptest_server_init()	
#endif	//UDP_SERVER_TEST


#ifdef UDP_CLIENT_TEST
extern void udptest_client_init(void);
extern void udptest_send_data(void);
#else
#define udptest_client_init()	
#define udptest_send_data()	
#endif	//UDP_CLIENT_TEST


#endif	//__UDPTEST_H__

