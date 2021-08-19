#include "stringutil.h"

char *trim(char *pstr)
{
    int len;
    char *pRet;
    char *pValue;
    pRet = pstr;
    while (((*pRet) == ' ') || ((*pRet) == '\t'))
        pRet++;

    if ((pValue = strchr(pRet, '#')))
    {
        *pValue = 0;
    }
    if ((pValue = strchr(pRet, ';')))
    {
        *pValue = 0;
    }
    len = strlen(pRet);
    while (len > 0)
    {
        if ((pRet[len - 1] == ' ') || (pRet[len - 1] == '\t') || (pRet[len - 1] == '\r') || (pRet[len - 1] == '\n'))
            len--;
        else
            break;
    }
    *(pRet + len) = 0;
    return pRet;
}


int StrReplace(char strRes[],char from[], char to[]) 
{
    int i,flag = 0;
    char *p,*q,*ts;
    for(i = 0; strRes[i]; ++i) 
    {
        if(strRes[i] == from[0]) 
        {
            p = strRes + i;
            q = from;
            while(*q && (*p++ == *q++));
            if(*q == '\0') 
            {
                ts = (char *)malloc(strlen(strRes) + 1);
                strcpy(ts,p);
                strRes[i] = '\0';
                strcat(strRes,to);
                strcat(strRes,ts);
                free(ts);
                flag = 1;
            }
        }
    }
    return flag;
}


int isdigitstr(char *str)
{
   return (strspn(str, "0123456789")==strlen(str));
}



int is_begin_with(const char * str1,char *str2)
{
    if(str1 == NULL || str2 == NULL)
        return -1;
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    if((len1 < len2) ||  (len1 == 0 || len2 == 0))
        return -1;
    char *p = str2;
    int i = 0;
    while(*p != '\0')
    {
        if(*p != str1[i])
            return 0;
        p++;
        i++;
    }
    return 1;
}


int is_end_with(const char *str1, char *str2)
{
    if(str1 == NULL || str2 == NULL)
        return -1;
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    if((len1 < len2) ||  (len1 == 0 || len2 == 0))
        return -1;
    while(len2 >= 1)
    {
        if(str2[len2 - 1] != str1[len1 - 1])
            return 0;
        len2--;
        len1--;
    }
    return 1;
}


void split(char * reslutstr,char * sourcestr,char * delim,int k){
    char *p;
    int i =1;
    char * tmp = strtok(sourcestr, delim);    
    if(i==k){
        strcat(reslutstr, tmp);
        return;
    } 
    i++;
    while((p = strtok(NULL, delim))){
        if(i==k){
            strcat(reslutstr, p);
            return ;
        } 
        i++;
    }    
}

