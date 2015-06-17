CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g
CLIB=-lfcgi
CMYSQLLIB=`mysql_config --cflags --libs`



all:main.o sql.o
	$(CC) -g main.c -o wallpapers_cgi $(CLIB) $(CMYSQLLIB)

clean:
	rm -rf *.o wallpapers_cgi a.out

install:
	mkdir -p /data/wallpapers/cgi
	mv ./wallpapers_cgi /data/wallpapers/cgi/

	


