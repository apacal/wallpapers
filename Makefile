CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g
CLIB=-lcurl -lssl -lcrypto -lm


all:log.o main.o cJSON.o
	$(CC) -g main.o log.o cJSON.o -o getwallpapers $(CLIB)
log.o:
	$(CC) $(CFLAGS) -c log.c -o log.o
main.o:
	$(CC) $(CFLAGS) -c main.c 
cJSON.o:
	$(CC) $(CFLAGS) -c lib/cJSON/cJSON.c
clean:
	rm -rf *o getwallpapers

install:
	#rm -fr /usr/local/wallpapers 
	#rm /usr/bin/wallpapers
	mkdir -p /usr/local/wallpapers/log
	mkdir -p /usr/local/wallpapers/picture
	mkdir -p /usr/local/wallpapers/bin
	chmod -R 777 /usr/local/wallpapers
	chmod +x ./wallpapers
	cp ./getwallpapers /usr/local/wallpapers/bin
	cp ./wallpapers /usr/local/wallpapers/bin
	ln -s /usr/local/wallpapers/bin/wallpapers /usr/bin/wallpapers
	echo "install success"

uninstall:
	rm -fr /usr/local/wallpapers
	rm /usr/bin/wallpapers

link:
	ln -s /usr/local/wallpapers ~/wallpapers

remove_picture:
	rm -fr /usr/local/wallpapers/picture/*

crontab:
	crontab ./crontab.conf
	


