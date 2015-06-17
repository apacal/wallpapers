/**
 *       Filename:  sql.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年01月07日 13时46分15秒
 *       Compiler:  gcc
 *         Author:  Apacal (|http://apacal.cn|), apacalzqz@gmail.com
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sql.h"

char mysql_host[] = "localhost";
char mysql_user[] = "root";
char mysql_passwd[] = "dev2014";
char mysql_database[] = "wallpapers";
int mysql_conn_port = 3306;

#define EXIT_MYSQL_CONN 5
#define EXIT_INSERT_MORE 6

MYSQL * mysql_create() {
    MYSQL *conn = NULL;
    conn = mysql_init(NULL);
    if (NULL != conn) {
        if (mysql_real_connect(conn, mysql_host, mysql_user, mysql_passwd, mysql_database, mysql_conn_port, NULL, 0) == NULL) {
            printf("mysql connect error:%s\n", mysql_error(conn));
        }
        return conn;
    } else {
        printf("mysql init error:%s\n", mysql_error(conn));
        return NULL;
    }
}
void mysql_delete(MYSQL * conn) {
    mysql_close(conn);
    conn = NULL;
}


char * get_file_name(MYSQL *conn) {
    if (conn == NULL) {
        fprintf(stderr, "conn can't be NULL\n");
        exit(EXIT_MYSQL_CONN);
    }
    MYSQL_RES *result;
    MYSQL_ROW row;
    int count = 1;
    
    mysql_query(conn, "SELECT count(*) as count FROM wallpapers");
    result = mysql_store_result(conn);
    if ((row = mysql_fetch_row(result))) {
        count = atoi(row[0]);
    }
    mysql_free_result(result);
    int rand_row;
    srand (time(NULL));
    rand_row = rand() % count;

    char select[100];
    sprintf(select, "select file from wallpapers limit %d, 1", rand_row);
    mysql_query(conn, select);
    result = mysql_store_result(conn);
    if ((row = mysql_fetch_row(result))) {
        char * file_name = (char *) malloc(strlen(row[0]) + 1);
        memcpy(file_name, row[0], strlen(row[0])+1);

        return file_name;
        
    }
    mysql_free_result(result);

    return NULL;
}

#ifdef SQLDEBUG
int main() {

    MYSQL * conn = mysql_create();
    if (NULL != conn) {
        
        char * url = get_url(conn);
        if (url != NULL) {
            printf("%s", url);
        }
        free(url);
    }

}
#endif


