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
#include "log.h"

char mysql_host[] = "localhost";
char mysql_user[] = "root";
char mysql_passwd[] = "dev2014";
char mysql_database[] = "wallpapers";
int mysql_conn_port = 3306;

#define EXIT_MYSQL_CONN 5
#define EXIT_INSERT_MORE 6

MYSQL * mysql_create() {
    static MYSQL *conn = NULL;
    if (NULL == conn) {
        conn = mysql_init(NULL);
        if (NULL != conn) {
            if (mysql_real_connect(conn, mysql_host, mysql_user, mysql_passwd, mysql_database, mysql_conn_port, NULL, 0) == NULL) {
                log_error(mysql_error(conn));
                exit(EXIT_MYSQL_CONN);
            }
            return conn;
        } else {
            log_error(mysql_error(conn));
            exit(EXIT_MYSQL_CONN);
            return NULL;
        }
    } else {
        return conn;
    }
}
void mysql_delete(MYSQL * conn) {
    mysql_close(conn);
    conn = NULL;
}

void insert(MYSQL * conn, const char * file, const char * url) {
    if (conn == NULL) {
        log_error("conn can't be NULL");
        exit(EXIT_MYSQL_CONN);
    }
    if (strlen(file) >= 40 || strlen(url) >= 400) {
        log_error("url is too longer");       
        exit(EXIT_INSERT_MORE);
    }
    char insert[500];
    sprintf(insert, "INSERT INTO wallpapers(file,url) VALUES('%s','%s')", file, url);

    if (0 != mysql_query(conn, insert)) {
        log_error(mysql_error(conn));
    }
}

char * get_url(MYSQL *conn) {
    if (conn == NULL) {
        log_error("conn can't be NULL");
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
    sprintf(select, "select url from wallpapers limit %d, 1", rand_row);
    mysql_query(conn, select);
    result = mysql_store_result(conn);
    if ((row = mysql_fetch_row(result))) {
        char * url = (char *) malloc(strlen(row[0]) + 1);
        memcpy(url, row[0], strlen(row[0])+1);

        return url;
        
    }
    mysql_free_result(result);

    return NULL;
}

#ifdef SQLDEBUG
int main() {

    MYSQL * conn = mysql_create();
    if (NULL != conn) {
        
        mysql_query(conn, "CREATE TABLE writers(name VARCHAR(25))");
    }
    //insert(conn, "dfd1dfsd3434", "apacal.cndfdf");
    char * url = get_url(conn);
    if (url != NULL) {
        printf("%s", url);
    }
    free(url);

}
#endif


