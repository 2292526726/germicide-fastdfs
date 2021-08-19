
#ifndef __CREATEDIRS_H__
#define __CREATEDIRS_H__

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_FILENAME_LENGTH 512

void createalltempdirs(char *pathprefix);

#endif