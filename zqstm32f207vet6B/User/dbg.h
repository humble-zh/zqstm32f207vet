/******************************************************************************
  FileName: dbg.h
  Author: Li_Zhihong
  Date: 20170113
******************************************************************************/
#ifndef __DBG_H__
#define __DBG_H__
#include "humble.h"

#ifdef _DEBUG_
#include <stdio.h>
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

extern void usart_init(void);
extern void put_char(const char ch);

#define dbg_init() usart_init()
#define dbp(format, ...)	printf(format, ##__VA_ARGS__)
#define perr(format, ...)	printf(format, ##__VA_ARGS__)
#define pinfo(format, ...)	printf(format, ##__VA_ARGS__)
#else	//_DEBUG_
#define dbg_init() 
#define put_char(x)	
#define dbp(format, ...)	
#define perr(format, ...)	
#define pinfo(format, ...)	
#endif	//_DEBUG_
#endif	//__DBG_H__

