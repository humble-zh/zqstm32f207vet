/******************************************************************************
  FileName: echo.h
  Author: Li_Zhihong
  Date: 20170116
******************************************************************************/
#ifndef __ECHO_H__
#define __ECHO_H__

#define ECHO_MAIN_INFO	"--Print a string on usart1."
#define PSET_USAGE	"\
Usage:\n\
  echo\n\
    -n show name\n\
    -b show boyfriend's name\n\
    -l <love_word> show our Love is 'love_word'\n\
    -d <arg> show the arg is 'arg'\n\
  eg:\n\
    echo -n\n"

extern int echo_main(int argc,char **argv);

#endif //__ECHO_H__
