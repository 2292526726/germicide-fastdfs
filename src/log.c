/** log.c **/
#include "log.h"
#include "globalvar.h"

LOGSET logsetting;
LOG loging;
 
const static char LogLevelText[4][10]={"INFO","DEBUG","WARN","ERROR"};
 
static char * getdate(char *date);
 
static unsigned char getcode(char *path){
	unsigned char code=255;
	if(strcmp("INFO",path)==0)
		code=1;
	else if(strcmp("WARN",path)==0)
		code=3;
	else if(strcmp("ERROR",path)==0)
		code=4;
	else if(strcmp("NONE",path)==0)
		code=0;
	else if(strcmp("DEBUG",path)==0)
		code=2;
	return code;
}
 
static unsigned char ReadConfig(char *path){
	char value[512]={0x0};
	char data[50]={0x0};
 
	FILE *fpath=fopen(path,"r");
	if(fpath==NULL)
		return -1;
	fscanf(fpath,"path=%s\n",value);
	getdate(data);
	strcat(data,".log");
	strcat(value,"/");
	strcat(value,data);
	if(strcmp(value,logsetting.filepath)!=0)
		memcpy(logsetting.filepath,value,strlen(value));
	memset(value,0,sizeof(value));
 
	fscanf(fpath,"level=%s\n",value);
	logsetting.loglevel=getcode(value);
	fclose(fpath);
	return 0;
}

static LOGSET *getlogset(char *logpath){
	char path[512]={0x0};
	strcat(path,logpath);
	strcat(path,"/log.conf");
	if(access(path,F_OK)==0){
		if(ReadConfig(path)!=0){
			logsetting.loglevel=INFO;
			logsetting.maxfilelen=4096;
		}
	}else{
		logsetting.loglevel=INFO;
		logsetting.maxfilelen=4096;
	}
	return &logsetting;
}
 

static char * getdate(char *date){
	time_t timer=time(NULL);
	strftime(date,11,"%Y-%m-%d",localtime(&timer));
	return date;
}
 

static void settime(){
	time_t timer=time(NULL);
	strftime(loging.logtime,20,"%Y-%m-%d %H:%M:%S",localtime(&timer));
}
 

 
static int initlog(unsigned char loglevel,char *logpath){
	char strdate[30]={0x0};
	LOGSET *logsetting;
	if((logsetting=getlogset(logpath))==NULL){
		perror("Get Log Set Fail!");
		return -1;
	}
	if((loglevel&(logsetting->loglevel))!=loglevel)
		return -1;
 
	memset(&loging,0,sizeof(LOG));
	//获取日志时间
	settime();
	if(strlen(logsetting->filepath)==0){
		char *path=getenv("HOME");
		memcpy(logsetting->filepath,path,strlen(path));
 
		getdate(strdate);
		strcat(strdate,".log");
		strcat(logsetting->filepath,"/");
		strcat(logsetting->filepath,strdate);
	}
	memcpy(loging.filepath,logsetting->filepath,MAXFILEPATH);
	if(loging.logfile==NULL){		
		loging.logfile=fopen(loging.filepath,"a+");
    }
	if(loging.logfile==NULL){
		perror("Open Log File Fail!");
		return -1;
	}
	fprintf(loging.logfile,"[%s] [%s] ",LogLevelText[loglevel-1],loging.logtime);
	return 0;
}
 
pthread_mutex_t mutex_log = PTHREAD_MUTEX_INITIALIZER;

int LogWrite(unsigned char loglevel,char *format,char *content)
{	
	int  rtv = -1;
	pthread_mutex_lock(&mutex_log); 
	do{
		if(initlog(loglevel,logpath) != 0)
		{			
			rtv = -1;
			break;
		}
        fprintf(loging.logfile,"%s",format);
		fprintf(loging.logfile,"%s",content);
		fprintf(loging.logfile,"%s","\n");
		fflush(loging.logfile);
		if(loging.logfile != NULL)
			fclose(loging.logfile);
		loging.logfile=NULL;
		rtv = 0;
	}while(0);	
	pthread_mutex_unlock(&mutex_log); 
	return rtv;
}

