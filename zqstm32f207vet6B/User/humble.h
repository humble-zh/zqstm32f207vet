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
#define DP83848_PHY_ADDRESS (0x01)
#endif	//_MAC2PHY_

