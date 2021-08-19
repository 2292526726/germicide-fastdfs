#ifndef __EXECMD_H__
#define __EXECMD_H__
#define CHAR_MAX_LENGTH 1024

#include<stdio.h>
#include<string.h>
#include<errno.h>

int getExecInfo(const char * cmd,const char *content);

#endif /* __EXECMD_H__ */