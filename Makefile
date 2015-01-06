all:
	gcc -g main.c lib/cJSON/cJSON.c log.c -o getwallpapers -lcurl -lm -lssl -lcrypto
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
	echo "*/5 * * * * root wallpapers now" >> /etc/crontab
	echo "* * */10 * * root wallpapers" >> /etc/crontab

