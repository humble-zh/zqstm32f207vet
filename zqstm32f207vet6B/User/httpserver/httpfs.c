/******************************************************************************
  FileName: httpfs.c
  Author: Li_Zhihong
  Date: 20170215
******************************************************************************/
#include "httpfs.h"
#include <stdio.h>
#include "allpages.h"

HTTP_FILE_DEC http_fs[] = {
{"ptest",	ptest_file, PTEST_FILE_LEN, NULL},
{NULL,	NULL,	0,	NULL}
};

