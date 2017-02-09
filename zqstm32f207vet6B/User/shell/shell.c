/******************************************************************************
  Mini shell
  FileName: shell.c
  Author: Li_Zhihong
  Date: 20170116
******************************************************************************/
#include "shell.h"
#ifdef _SHELL_
#include "dbg.h"
#include "cmd/echo/echo.h"

/*   test start   */
#define PSET_MAIN_INFO	"--port setting."
int pset_main(int argc, char **argv)
{
	u8	i;
	dbp("pset_main\n");
	for(i = 0; i < argc; i++)
	{
		dbp("argv[%d]:>%s<\n", i, argv[i]);
	}
	return 0;
}
#define PSTAT_MAIN_INFO	"--show port status."
int pstat_main(int argc, char **argv)
{
	u8	i;
	dbp("pstat_main\n");
	for(i = 0; i < argc; i++)
	{
		dbp("argv[%d]:>%s<\n", i, argv[i]);
	}
	return 0;
}
/*   test end   */

CMD_OP cmd_op[] = {
	ADD_CMD(HELP_ID,	help,	"--print the help info."),
	ADD_CMD(ECHO_ID,	echo,	ECHO_MAIN_INFO),
	ADD_CMD(PSTAT_ID,	pstat,	PSTAT_MAIN_INFO)
};
#define CMD_TOTAL	(sizeof(cmd_op)/sizeof(CMD_OP))

u8 bidx = 0;//Current Byte index
u8 cmd_line[CMD_LINE_LEN]={0};
static s32 fargc = 0;
static u8 *fargv[ARGV_CNT]={NULL};

static s32 getarg(u8 *cmd_line, u8 *argv[])
{
	s32	i = 0;
	u8	*p;
	p = (u8*)fstrtok((char*)cmd_line,(char*)" ");
	while(p!=_NULL){
		argv[i] = p;
		i++;
		p = (u8*)fstrtok((char*)_NULL,(char*)" ");
	}
	return i;
}

static u32 getcmdindex(u8 *cmd_ptr)
{
	s32 i = 0;
	for(i = 0; i < CMD_TOTAL; i++)
	{
		if(!fstrcmp((char*)cmd_ptr, (char*)cmd_op[i].cmd)){
			return i;
		}
	}
	return CMD_TOTAL;
}

static void show_tipsline(void)
{
	pinfo("[Ritern]# ");
}

void shell_init(void)
{
	show_tipsline();
}

void set_char(u8 ch)
{
	if('\r' == ch){//回车
		put_char('\n');
		shell_main(cmd_line);
		memset((void*)cmd_line, 0, CMD_LINE_LEN);
		bidx = 0;
		show_tipsline();
	}
	else if(8 == ch){//退格
		if(bidx){
			cmd_line[--bidx] = 0;
			pinfo("\b \b");
		}
	}
	else if('\t' == ch){}//tab
	else{
		cmd_line[bidx++] = ch;
		put_char(ch);
		if(CMD_LINE_LEN <= bidx){
			perr("\n[E]Commandline too long\n");
			memset((void*)cmd_line, 0, CMD_LINE_LEN);
			bidx = 0;
			show_tipsline();
		}
	}
}

void shell_main(u8* cmd_line)
{
	u8 cmd_idx = CMD_TOTAL;
	//dbp("shell_main[%s]\n", cmd_line);

	//解析命令
	fargc = getarg(cmd_line, fargv);
	if(!fargc){
		return;
	}

	//查找命令
	cmd_idx = getcmdindex(fargv[0]);
	if(CMD_TOTAL <= cmd_idx){
		perr("[E]Command '%s' not found.\n", fargv[0]);
		pinfo("Please input 'help' for more information.\n");
		return;
	}

	//调用命令，传入参数
	cmd_op[cmd_idx].cmd_main(fargc, (char **)fargv);
}

int help_main(int argc, char **argv)
{
	int i = 0;
	pinfo("command\t\tinfo\n");
	for(i = 0; i < CMD_TOTAL; i++)
	{
		pinfo(" %s", cmd_op[i].cmd);
		pinfo("\t");
		pinfo(" %s", cmd_op[i].cmd_info);
		pinfo("\n");
	}
	return 0;
}


/*
s32 main(s32 argc, u8 **argv)
{
	u8	cmd_idx = CMD_TOTAL;

	printf(HELLO_LOGO);
	while(1)
	{
		printf("humble@cmd:~$");
		gets((char*)cmd_line);//input you cmd line
		
		//解析命令
		printf("cmd_line:>%s<\n", cmd_line);
		fargc = getarg(cmd_line,fargv);
		if(fargc == 0){
			continue;
		}

		//查找命令
		printf(">%s<\n",fargv[0]);
		cmd_idx = getcmdindex(fargv[0]);
		if(CMD_TOTAL <= cmd_idx){
			printf("[ERR]:Command '%s' not found.\n", fargv[0]);
			printf("Please input 'help' for more information.\n");
			continue;
		}

		//调用命令，传入参数
		cmd_op[cmd_idx].cmd_main(fargc, (char **)fargv);
	}
}
*/

/*
static void argv_get(char *cmd_line)
{
	int i = 0,
		j = 0,
		k = 0;
	while(1)
	{
		//printf("%c ",cmd_line[i]);
		if(cmd_line[i] == '\0'){
			argv[j][k] = '\0';
			break;
		}
		if(cmd_line[i] == ' '){
			argv[j][k] = '\0';
			i++;
			j++;
			k = 0;
			continue;
		}
		argv[j][k] = cmd_line[i];
		i++;
		k++;
	}
}
*/
#endif	//_SHELL_
