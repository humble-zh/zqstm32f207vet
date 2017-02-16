/******************************************************************************
  FileName: httpfs.h
  Author: Li_Zhihong
  Date: 20170215
******************************************************************************/
#ifndef __HTTPFS_H__
#define __HTTPFS_H__

#include "stm32f2xx.h"

typedef s16 (*FILL)(u8* buf, u16 buf_len, u8 pos);
typedef struct{
	//u32 hash;		/* �����ļ���ӳ���ID��ͨ���Ƚ�ID�õ��±�(����)[��ʱû��] */
	uc8 f_name[8];	/* ��ʱ���ļ�������������ȡ���ļ� */
	uc8* f_start_ptr;
	u32 f_len;
	FILL fill;
}HTTP_FILE_DEC;

#endif	//__HTTPFS_H__

