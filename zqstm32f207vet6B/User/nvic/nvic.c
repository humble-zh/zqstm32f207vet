/******************************************************************************
  FileName: nvic.c
  Author: Li_Zhihong
  Date: 20170114
******************************************************************************/
#include "nvic.h"
#include "misc.h"

//�����ж���������ռ���ȼ�λ��Ϊ2
void nvic_global_init(void)
{
	/* Set the Vector Table base location at 0x08000000 */
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
	
	/* 2 bit for pre-emption priority, 2 bits for subpriority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}
