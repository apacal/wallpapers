/**
 *       Filename:  main.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年01月05日 13时19分33秒
 *       Compiler:  gcc
 *         Author:  Apacal (|http://apacal.cn|), apacalzqz@gmail.com
 **/

#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <fcgi_stdio.h>
#include <stdlib.h>
#include "sql.c"

 
int is_self_domain(char * query_string) {
    if (query_string == NULL) {
        return 0;
    }
    char * pch;
    pch = strstr(query_string, "a=");
    if (pch != NULL) {
        pch = pch + 2;
        if (strncmp(pch, "self", 4) == 0) {
            return 1;
        }
    }

    return 0;
}

int main(void) {
    char * file_name;
    char *query_string;
    //char yun[] = "http://yun.apacal.cn/";
    char yun[] = "http://7u2fwx.com1.z0.glb.clouddn.com/";
    char self[] = "http://wallpapers.apacal.cn/";
    pid_t pid;
    int status;

    while(1) {
        pid = fork();
        if (pid == -1) {
            fprintf(stderr, "fork() error.errno:%d error:%s\n", errno, strerror(errno));
            break;
        }

        if (pid == 0) {
            MYSQL *conn = mysql_create();
            while(FCGI_Accept() >= 0) {

                printf("Content-type: text/html\r\n");
                printf("Location:");

                query_string = getenv("QUERY_STRING");

                if (conn == NULL) {
                    file_name = NULL;

                } else {

                    file_name = get_file_name(conn);
                }
                if (file_name != NULL && strlen(file_name) > 0) {
                    if (is_self_domain(query_string)) {
                        printf("%s%s", self, file_name);
                    } else {
                        printf("%s%s", yun, file_name);
                    }
                } else {
                    printf("%s%s", self, "demo.jpg");
                }
                printf("\r\n\r\n");

                free(file_name);

            }
            mysql_delete(conn);
        }

        if (pid > 0) {
            pid = wait(&status);
        }

    }

    return 0;
}


 
 
