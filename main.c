#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "createdirs.h"
#include "execmd.h"
#include "log.h"
#include "stringutil.h"
#include "getlocalip.h"

#define FLAG_IMAGE_EXIST "fdfs"
#define FLAG_DOCKER_NAME "fastdfs"
#define CMD_DOCKER_IS_RUNNING "docker ps|grep fastdfs"
#define CMD_DOCKER_IS_EXIST "docker ps -a | grep fastdfs"
#define CMD_DOCKER_START "docker start fastdfs"
#define CMD_DOCKER_STOP "docker stop fastdfs"
#define CMD_START_FROME_IMAGE_1 "docker run -tid --name report_fastdfs -v @@@ -v @@@/ -v @@@/ -v @@@ -v @@@ "
#define CMD_EXECUTE_SHELL_IN_DOCKER "docker exec fastdfs /bin/sh -c 'dockerapp start "
#define CMD_IS_IMAGE_EXIST "docker images|grep fdfs|grep v1"
char logpath[100] = "."; 
void isdockerrunning(char * ngport){
    const char *isdockeruning = CMD_DOCKER_IS_RUNNING;
    int retisdockeruning = getExecInfo(isdockeruning, FLAG_DOCKER_NAME);
    if(retisdockeruning == 1){                    
            LogWrite(INFO, "fdfs docker is running.", "");
    }else{
        LogWrite(ERROR, "fdfs docker is not running.", "");
    }

    char ips[1024]="";
    get_local_ip(ips,".1");
    char *delim = "|";
    char local_ip[64]="";
    split(local_ip,ips,delim,1);

    char cmd[1024]="";
    strcat(cmd,CMD_EXECUTE_SHELL_IN_DOCKER);
    strcat(cmd,trim(local_ip));
    strcat(cmd,":");
    strcat(cmd,trim(ngport));
    strcat(cmd,"'");

    int retstartshellindocker = getExecInfo(trim(cmd), "null");
    if( retstartshellindocker == 1 ){
        LogWrite(INFO, "executing shell in docker success.", "");
    }else{
        LogWrite(ERROR, "fexecuting shell in docker fail.", "");                    
    }
}



void startdockerfromimage(char* desdir,char *nginx_port,char *tracker_port,char *storage_port,char *rtmp_port1,char *rtmp_port2,char *rtmp_port3,char *rtmp_port4){
    LogWrite(INFO, "starting fdfs docker from image.", "");
    char cmd[1024]="";
    char tmp[1024]="";
    strcat(tmp,CMD_START_FROME_IMAGE_1);
    StrReplace(tmp,"@@@",trim(desdir));
    strcat(cmd,trim(tmp));
    strcat(cmd," -p ");
    strcat(cmd,trim(nginx_port));
    strcat(cmd,":80 ");
    strcat(cmd,"-p ");
    strcat(cmd,trim(tracker_port));
    strcat(cmd,":22122 ");
    strcat(cmd,"-p ");
    strcat(cmd,trim(storage_port));
    strcat(cmd,":23000 ");
    strcat(cmd,"-p ");
    strcat(cmd,trim(rtmp_port1));
    strcat(cmd,":1935 ");
    strcat(cmd,"-p ");
    strcat(cmd,trim(rtmp_port2));
    strcat(cmd,":6935 ");
    strcat(cmd,"-p ");
    strcat(cmd,trim(rtmp_port3));
    strcat(cmd,":7935 ");
    strcat(cmd,"-p ");
    strcat(cmd,trim(rtmp_port4));
    strcat(cmd,":8935 ");
    strcat(cmd,"b_fdfs:v1");

    int retstartdockerfromimage = getExecInfo(trim(cmd), "null");    
    if(retstartdockerfromimage == 0){       
        isdockerrunning(nginx_port);
    }else{
        LogWrite(ERROR, "starting fdfs docker from image fail.", "");
    }                   
}



int main(int argc, char **argv){   
    if (argc < 2){
        printf("%s\n", "Error: parameter error.Please input location to store data.");
		printf("%s\n", "Example:./fdfservice /home/disk4/tmp");
        printf("%s\n", "Example:./fdfservice /home/disk4/tmp ng_port tracker_port storage_port rtmp_port");
        printf("%s\n", "Example:./fdfservice stop");
    }else{      
        const char *isdockeruning = CMD_DOCKER_IS_RUNNING;
		int retisdockeruning = getExecInfo(isdockeruning, FLAG_DOCKER_NAME);
        if(retisdockeruning == 1){
           if(strcmp(argv[1],"stop")==0){               
                const char *dockerstop = CMD_DOCKER_STOP;
                int retisdockerstop = getExecInfo(dockerstop, FLAG_DOCKER_NAME);
                if( retisdockerstop == 1 ){
                     printf("%s\n","INFO: service stop success.");
                     LogWrite(INFO, "fdfs docker is stopped.", "");
                }
           }else{
              printf("%s\n","Warning: fdfs service is already running.");
              LogWrite(WARN, "fdfs docker is already running.", "");
           }
        }else{
            if(strcmp(argv[1],"stop")==0){
                 printf("%s\n","INFO: service already stop.");
                 LogWrite(INFO, "INFO: service already stop.", "");
                 return 0;
            }
            char nport[8] = "8888";   
            if(argc >= 3 && isdigitstr(argv[2])==1){    
                bzero(nport, sizeof(nport));             
                strcpy(nport,argv[2]);
            } 

            const char *isdockerexist = CMD_DOCKER_IS_EXIST;
	    	int retisdockerexist = getExecInfo(isdockerexist, FLAG_DOCKER_NAME);
            if( retisdockerexist == 1 ){
                LogWrite(INFO, "start fdfs docker from existing.", "");
                const char *dockerstart = CMD_DOCKER_START;
		        int retdockerstart = getExecInfo(dockerstart, FLAG_DOCKER_NAME);
                if(retdockerstart == 1){
                    LogWrite(INFO, "fdfs docker has started.", "");
                }else{
                    LogWrite(ERROR, "fdfs docker start fail.", "");
                }
               
                isdockerrunning(nport);

            }else{               
                createalltempdirs(argv[1]);
                char f1port[8] = "22122";   
                if(argc >= 4 && isdigitstr(argv[3])==1){   
                    bzero(f1port, sizeof(f1port));               
                    strcpy(f1port,argv[3]);
                }  

                char f2port[8] = "23000";   
                if(argc >= 5 && isdigitstr(argv[4])==1){  
                    bzero(f2port, sizeof(f2port));               
                    strcpy(f2port,argv[4]);
                }
                char f3port[9] = "9935";   
                if(argc >= 6 && isdigitstr(argv[5])==1){  
                    bzero(f3port, sizeof(f3port));               
                    strcpy(f3port,argv[5]);
                }  

                char f4port[9] = "6935";   
                if(argc >= 7 && isdigitstr(argv[6])==1){  
                    bzero(f4port, sizeof(f4port));               
                    strcpy(f4port,argv[6]);
                }  
  
                char f5port[9] = "7935";   
                if(argc >= 8 && isdigitstr(argv[7])==1){  
                    bzero(f5port, sizeof(f5port));               
                    strcpy(f5port,argv[7]);
                }  
  
                char f6port[9] = "8935";   
                if(argc >= 9 && isdigitstr(argv[8])==1){  
                    bzero(f6port, sizeof(f6port));               
                    strcpy(f6port,argv[8]);
                }  
              
                const char *isimageexist = CMD_IS_IMAGE_EXIST;
		        int retisimageexist = getExecInfo(isimageexist, FLAG_IMAGE_EXIST);
                if(retisimageexist == 1){                    
                     startdockerfromimage(argv[1],nport,f1port,f2port,f3port,f4port,f5port,f6port);
                }else{ 
                    LogWrite(WARN, "docker image is not exist,will be loaded from current loacation.", "");
                    printf("%s\n","docker image is not exist,will be loaded from current loacation.");
                    const char *loadiamge = CMD_LOAD_IMAGE;
                    int retloadiamge = getExecInfo(loadiamge, "no such file");
                    if(retloadiamge == 1){
                        LogWrite(ERROR, "fdfs image file not find.", "");
                    }else{
                        LogWrite(INFO, "fdfs image loadding.", "");
                        const char *isimageexist = CMD_IS_IMAGE_EXIST;
		                int retisimageexist = getExecInfo(isimageexist, FLAG_IMAGE_EXIST);
                        if(retisimageexist == 1){    
                            LogWrite(INFO, "fdfs image has been loadded.", "");
                            startdockerfromimage(argv[1],nport,f1port,f2port,f3port,f4port,f5port,f6port);
                        }else{
                            LogWrite(INFO, "fdfs image load fail.", "");
                        }

                    }

                }

            }
        }        
    }
    return 0;
    
}

 
