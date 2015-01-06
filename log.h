/**
 *       Filename:  log.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年01月05日 13时19分33秒
 *       Compiler:  gcc
 *         Author:  Apacal (|http://apacal.cn|), apacalzqz@gmail.com
 **/
#include <stdio.h>
#include <stdlib.h>

static char info_file[] = "/usr/local/wallpapers/log/info_log";
static char error_file[] = "/usr/local/wallpapers/log/error_log";

/* * 
 * log info
 * */
void log_info(const char*);

/* *
 * log error
 * */
void log_error(const char *);


