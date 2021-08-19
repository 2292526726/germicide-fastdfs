#ifndef __STRINGUTIL_H__
#define __STRINGUTIL_H__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>

#define MAX_LENGTH 1024

char *trim(char *pstr);
int StrReplace(char strRes[],char from[], char to[]);
int isdigitstr(char *str);
int is_begin_with(const char * str1,char *str2);
int is_end_with(const char *str1, char *str2);
void split(char * reslutstr,char * sourcestr,char * delim,int k);


#endif /* __STRINGUTIL_H__ */