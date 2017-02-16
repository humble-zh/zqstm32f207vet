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
	//u32 hash;		/* 用于文件名映射的ID，通过比较ID得到下标(索引)[暂时没用] */
	uc8 f_name[8];	/* 暂时用文件名来进行索引取得文件 */
	uc8* f_start_ptr;
	u32 f_len;
	FILL fill;
}HTTP_FILE_DEC;

#endif	//__HTTPFS_H__

