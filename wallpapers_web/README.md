wallpapers_web
==========
wallpapers_web is that download wallpaper to qiniu server and insert this url into mysql database.

## Dependencies

* curl
* ssl
* crypto 
* libmysqlclient sudo apt-get install libmysqlclient-dev
* qiniu sdk

## Extend lib
* cJSON

## Environment

### Linux


INSTALL
-------

### change mysql password
    modify sql.c file to change you database password, create table sql is doc/wallpapers.sql

    char mysql_host[] = "localhost";
    char mysql_user[] = "root";
    char mysql_passwd[] = "dev2014";
    char mysql_database[] = "wallpapers";
    int mysql_conn_port = 3306;

###auto installation
    make && make install

###auto crontab
    make crontab



   


