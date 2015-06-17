/**
 *       Filename:  a.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年01月10日 16时42分32秒
 *       Compiler:  gcc
 *         Author:  Apacal (|http://apacal.cn|), apacalzqz@gmail.com
 **/


#include <stdio.h>
#include <string.h>

int main ()
{
  char str[] ="a= is a simple string";
  char * pch;
  
  pch = strstr (str,"a=");
  if (pch != NULL) {
      printf("get it\n");
  }
  strncpy (pch,"sample",6);
  puts (str);
  return 0;
}
