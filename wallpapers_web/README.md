wallpapers_web
==========
wallpapers_web is that download wallpaper to qiniu server and insert this url into mysql database.

## Dependencies

* curl
sudo apt-get install libcurl4-openssl-dev 
* openssl
sudo apt-get install libssl-dev
* crypto 

* libmysqlclient
sudo apt-get install libmysqlclient-dev
* qiniu sdk

## Extend lib
* cJSON

## Environment

### Linux


INSTALL
-------



### create database && change mysql password
    modify sql.c file to change you database password, create table sql is doc/wallpapers.sql

    char mysql_host[] = "localhost";
    char mysql_user[] = "root";
    char mysql_passwd[] = "dev2014";
    char mysql_database[] = "wallpapers";
    int mysql_conn_port = 3306;
### change qiniu sdk key and space name
    modify main.c file to change you qiniu server access key

    ...
    int upload_to_qiniu(const char * file) {
	    Qiniu_Client client;
        QINIU_ACCESS_KEY			= "YE8xRB-EPWeoE1_JrTzm2HXYNQnaUFYXJKQXDuqj"; // must change
        QINIU_SECRET_KEY			= "jIPtBZBxJw3a1RwuAxRCz6xPGiMj046Od-rxZ2az"; // must change
	    Qiniu_Servend_Init(-1);                        /* 全局初始化函数，整个进程只需要调用一次 */
	    Qiniu_Client_InitMacAuth(&client, 1024, NULL); /* HTTP客户端初始化。HTTP客户端是线程不安全的，不要在多个线程间共用 */

        char * token = uptoken(&client, "wallpapers"); // must change, wallpapers to your onwn space name
        ...
    }
    ...


###auto installation
    make && make install

###auto crontab
    make crontab



   


