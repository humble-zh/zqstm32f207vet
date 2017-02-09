/******************************************************************************
  Mini shell
  FileName: shell.h
  Author: Li_Zhihong
  Date: 20170116
******************************************************************************/
#ifndef __SHELL_H__
#define __SHELL_H__
#include "humble.h"
#ifdef _SHELL_

#ifdef STM32F2XX
#include "stm32f2xx.h"
#include <string.h>
#define fstrtok(s,delim)	strtok(s,delim)
#define fstrcmp(s1,s2)		strcmp(s1,s2)
#else
#include "types_def.h"
#include "fstring.h"
#endif

//添加一个命令ID
#define HELP_ID		(0)
#define ECHO_ID		(1)
#define PSTAT_ID	(2)

//再用ADD_CMD宏把命令放入结构体
#define ADD_CMD(ID,CMD,INFO)	[ID]={#CMD,CMD##_main,INFO}


#define CMD_LEN			(12)
#define CMD_LINE_LEN	(40)
#define ARGV_CNT		(10)
#define ARGV_LEN		(10)
#define CMD_INFO_LEN	(80)

typedef int (*CMD_MAIN)(int argc, char **argv);

typedef struct {
	u8			cmd[CMD_LEN];
	CMD_MAIN	cmd_main;
	u8			cmd_info[CMD_INFO_LEN];
}CMD_OP;

extern u8 bidx;//Current Byte index
extern u8 cmd_line[CMD_LINE_LEN];
extern void shell_init(void);
extern void set_char(u8 ch);
extern void shell_main(u8* cmd_line);
extern int help_main(int argc, char **argv);

#define HELLO_LOGO	"\
\n\
\n\
\n\
\n\
\n\
\t**************************************************************\n\
\n\
\t\tmini shell\n\
\n\
\n\
\t\t\t\tauthor:humble\n\
\n\
\n\
\t**************************************************************\n\
\n\
\n\
\n\
\n\
\n\
"
#else	//_SHELL_
#define shell_init() 
#define set_char(x) 
#define shell_main(x) 
#define help_main(x,y) 
#endif	//_SHELL_
#endif	//__SHELL_H__