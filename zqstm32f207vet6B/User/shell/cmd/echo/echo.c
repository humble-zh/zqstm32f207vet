/******************************************************************************
  FileName: echo.c
  Author: Li_Zhihong
  Date: 20170116
******************************************************************************/
#include "dbg.h"
#include "echo.h"
#include "fgetopt/fgetopt.h"

int echo_main(int argc,char **argv)
{
	int c;
	static char* l_opt_arg = NULL;
	static char* const short_options = "nbl:d:";
	static struct option long_options[] = {
		{ "name", 0, NULL, 'n' },
		{ "bf_name", 0, NULL, 'b' },
		{ "love", 1, NULL, 'l' },
		{ "douhao", 1, NULL, 'd' },
		{ 0, 0, 0, 0},
	};
	reset_fgetopt_status();
	while((c = fgetopt_long (argc, argv, short_options, long_options, NULL)) != -1)
	{
		switch (c)
		{
			case 'n':
				dbp("My name is XL.\n");
				break;
			case 'b':
				dbp("His name is ST.\n");
				break;
			case 'l':
				l_opt_arg = optarg;
				dbp("Our love is %s!\n", l_opt_arg);
				break;
			case 'd':
				l_opt_arg = optarg;
				dbp("the arg is %s!\n", l_opt_arg);
				break;
			default:
				break;
		}
	}
	return 0;
}
