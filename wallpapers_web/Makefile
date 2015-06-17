CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g
CLIB=-lcurl -lssl -lcrypto -lm
CMYSQLLIB=`mysql_config --cflags --libs`

SERVER_SOURCE_FILES=\
	./lib/b64/urlsafe_b64.c\
	./lib/qiniu/conf.c\
	./lib/qiniu/base.c\
	./lib/qiniu/base_io.c\
	./lib/qiniu/http.c\
	./lib/qiniu/auth_mac.c\
	./lib/qiniu/rs.c\
	./lib/qiniu/io.c\


all:log.o main.o cJSON.o sql.o
	$(CC) -g main.o log.o cJSON.o sql.o $(SERVER_SOURCE_FILES) -o wallpapers_web $(CLIB) $(CMYSQLLIB)
log.o:
	$(CC) $(CFLAGS) -c log.c -o log.o
main.o:
	$(CC) $(CFLAGS) -c main.c
cJSON.o:
	$(CC) $(CFLAGS) -c lib/cJSON/cJSON.c
sql.o:
	$(CC) $(CFLAGS) -c sql.c
clean:
	rm -rf *.o wallpapers_web a.out

install:
	#rm -fr /usr/local/wallpapers 
	#rm /usr/bin/wallpapers
	mkdir -p /data/wallpapers/picture
	mkdir -p /data/wallpapers/log
	mkdir -p /data/wallpapers/bin
	chmod 777 -R /data/wallpapers
	chmod +x ./wallpapers_web
	cp ./wallpapers_web /usr/bin/
	echo "install success"

uninstall:
	rm /usr/bin/wallpapers_web


crontab:
	crontab ./crontab.conf
	


