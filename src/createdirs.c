#include "createdirs.h"
#include "log.h"

int  mkdirs(char *muldir)
{
    int  iRetVal = 0;
    char tempStr[MAX_FILENAME_LENGTH] = { 0 }; 
    if (!muldir)
    {
        return iRetVal;
    } 
    strncpy(tempStr, muldir, MAX_FILENAME_LENGTH);
    int i;
    for (i = 1; i<strlen(tempStr); i++)
    {
        if (tempStr[i] == '/')
        {
           tempStr[i] = '\0';
           if (access(tempStr, 0) != 0)
           {
               if (0 != mkdir(tempStr, 0777))
               {
                  iRetVal = 0;
                  break;
                }
            }
           tempStr[i] = '/';
         }
     } 
     if (strlen(tempStr)>0 && access(tempStr, 0) != 0)
     {
	    if (0 != mkdir(tempStr, 0777))
	    {
		    iRetVal = 0;
	    }
     }
 
     iRetVal = 1;
     return iRetVal;
}

int  mkdirsuffix(char *pathprefix,char * pathsuffix)
{
        int ret;  
        char dirpath[MAX_FILENAME_LENGTH];
        strcpy(dirpath,pathprefix);
        strcat(dirpath,pathsuffix);      
        if((access(dirpath,F_OK))!=-1)   
        {   
            LogWrite(INFO, "Info: dir exist!", dirpath);  
            return -1;
        } else {   
            ret = mkdirs(dirpath);
            if(ret == 0)
            {
               LogWrite(INFO, "Could not create directory: ", dirpath); 
			   return -1;
            } 
        }       
        return 0;   
}

void createalltempdirs(char *pathprefix){
        mkdirsuffix(pathprefix,"/data/aibifront/app/static");
        mkdirsuffix(pathprefix,"/data/aibifront/aibi/component");
        mkdirsuffix(pathprefix,"/log");
        mkdirsuffix(pathprefix,"/nginx_module");
        mkdirsuffix(pathprefix,"/storage");
        mkdirsuffix(pathprefix,"/tracker");
}

