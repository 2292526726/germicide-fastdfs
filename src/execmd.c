#include "execmd.h"


void executeCmd(char * retdata[3],const char * cmd){
  FILE *fstream=NULL;  
  char buff[CHAR_MAX_LENGTH]; 
  memset(buff,0,sizeof(buff)); 
 
  if(NULL==(fstream=popen(cmd,"r")))     
  { 
    fprintf(stderr,"execute command failed: %s",strerror(errno)); 
    strcpy(retdata[0], "execute command failed"); 
    return;  
  } 

  int i =0;
  while(NULL!=fgets(buff, sizeof(buff), fstream)) {
     strcpy(retdata[i], buff);
     i++;      
  }

  pclose(fstream); 
}

int getExecInfo(const char * cmd,const char *content){
  char retdata0[CHAR_MAX_LENGTH]="null";
  char retdata1[CHAR_MAX_LENGTH]="";
  char retdata2[CHAR_MAX_LENGTH]="";
  char * retdata[3];    
  retdata[0] = retdata0;
  retdata[1] = retdata1;
  retdata[2] = retdata2;
  executeCmd(retdata,cmd);
  if(strstr(retdata[0],content)){
    return 1;
  }else{
    return 0;
  }
}
