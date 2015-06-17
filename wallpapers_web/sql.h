/**
 *       Filename:  sql.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年01月07日 22时53分32秒
 *       Compiler:  gcc
 *         Author:  Apacal (|http://apacal.cn|), apacalzqz@gmail.com
 **/
#include <mysql/mysql.h>

MYSQL * mysql_create();

void mysql_delete(MYSQL *);

char * get_url(MYSQL *);

void insert(MYSQL * conn, const char * md5, const char * url);
