/**
 *       Filename:  log.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年01月05日 17时05分09秒
 *       Compiler:  gcc
 *         Author:  Apacal (|http://apacal.cn|), apacalzqz@gmail.com
 **/
#include <stdio.h>
#include <time.h>
#include "log.h"

static char info_file[] = "/data/wallpapers/log/info_log";
static char error_file[] = "/data/wallpapers/log/error_log";

void log_info(const char * msg) {
    FILE * pFile;
    pFile = fopen (info_file,"a");
    if (pFile!=NULL) {
        char buffer [30];
        time_t rawtime;
        struct tm * timeinfo;
        time (&rawtime);
        timeinfo = localtime (&rawtime);

        strftime(buffer,30,"%c",timeinfo);

        fprintf(pFile, "%s : %s \n", buffer, msg);
        fclose (pFile);
    }
}
void log_error(const char *msg) {

    FILE * pFile;
    pFile = fopen (error_file,"a");
    if (pFile!=NULL) {
        char buffer [30];
        time_t rawtime;
        struct tm * timeinfo;
        time (&rawtime);
        timeinfo = localtime (&rawtime);

        strftime(buffer,30,"%c",timeinfo);

        fprintf(pFile, "%s : %s \n", buffer, msg);
        fclose (pFile);
    }
}

