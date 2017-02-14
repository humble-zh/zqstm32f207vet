/******************************************************************************
  FileName: humble.h
  Author: Li_Zhihong
  Date: 20170113
******************************************************************************/
/* 使用串口1 调试 */
#define _DEBUG_

/* 使用串口1 实现shell */
#define _SHELL_

/* 以太网MAC控制器 */
#define _MAC2PHY_
#ifdef _MAC2PHY_
/* MAC ADDRESS*/
#define MAC_ADDR0   02
#define MAC_ADDR1   01
#define MAC_ADDR2   23
#define MAC_ADDR3   00
#define MAC_ADDR4   00
#define MAC_ADDR5   01
#define DP83848_PHY_ADDRESS (0x01)
#endif	//_MAC2PHY_

/* LWIP */
#define _LWIP_
#ifdef _LWIP_
/*Static IP ADDRESS*/
#define IP_ADDR0   192
#define IP_ADDR1   168
#define IP_ADDR2   1
#define IP_ADDR3   253
/*NETMASK*/
#define NETMASK_ADDR0   255
#define NETMASK_ADDR1   255
#define NETMASK_ADDR2   255
#define NETMASK_ADDR3   0
/*Gateway Address*/
#define GW_ADDR0   192
#define GW_ADDR1   168
#define GW_ADDR2   1
#define GW_ADDR3   1
#endif	//_LWIP_

