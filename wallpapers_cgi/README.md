wallpapers_cgi
==========
wallpapers_cgi 是一个用c编写的fastcgi，提供一个存在mysql中的随机图片，充当网页背景，例子可以看apacal.cn中的用户登陆和注册背景。在css中使用wallpapers.apacal.cn就可以随机使用背景图片。

## Dependencies

* curl
sudo apt-get install libcurl4-openssl-dev 
* openssl
sudo apt-get install libssl-dev
* crypto 
* libmysqlclient
sudo apt-get install libmysqlclient-dev
* libfcgi
sudo apt-get install libfcgi-dev
* qiniu sdk


## Dependecies Server

* nginx sudo apt-get install nginx
* spawn sudo apt-get install spawn-fcgi
## Extend lib
* cJSON

## Environment

### Linux


INSTALL
-------

### modify database name, user, password
    modify sql.c file to change you database password, create table sql is doc/wallpapers.sql

    char mysql_host[] = "localhost";
    char mysql_user[] = "root";
    char mysql_passwd[] = "dev2014";
    char mysql_database[] = "wallpapers";
    int mysql_conn_port = 3306;

###automatic installation
    make && make install

###add nginx conf
    
    server {
        listen 80;
        server_name cgi.apacal.cn;

        location / {
            fastcgi_pass   127.0.0.1:8000;
            fastcgi_index index.cgi;
            include fastcgi_params;
        }
    }

    or compelete

    server {
        listen 80;
        server_name cgi.apacal.cn;

        location / {
          fastcgi_pass   127.0.0.1:8000;

          fastcgi_param  GATEWAY_INTERFACE  CGI/1.1;
          fastcgi_param  SERVER_SOFTWARE    nginx;
          fastcgi_param  QUERY_STRING       $query_string;
          fastcgi_param  REQUEST_METHOD     $request_method;
          fastcgi_param  CONTENT_TYPE       $content_type;
          fastcgi_param  CONTENT_LENGTH     $content_length;
          fastcgi_param  SCRIPT_FILENAME    $document_root$fastcgi_script_name;
          fastcgi_param  SCRIPT_NAME        $fastcgi_script_name;
          fastcgi_param  REQUEST_URI        $request_uri;
          fastcgi_param  DOCUMENT_URI       $document_uri;
          fastcgi_param  DOCUMENT_ROOT      $document_root;
          fastcgi_param  SERVER_PROTOCOL    $server_protocol;
          fastcgi_param  REMOTE_ADDR        $remote_addr;
          fastcgi_param  REMOTE_PORT        $remote_port;
          fastcgi_param  SERVER_ADDR        $server_addr;
          fastcgi_param  SERVER_PORT        $server_port;
          fastcgi_param  SERVER_NAME        $server_name;
        }
    }



###run spawn-fcgi
    spawn-fcgi -a 127.0.0.1 -p 8000 -f /data/wallpapers/cgi/wallpapers_cgi

    # run server when system start
    sudo echo "spawn-fcgi -a 127.0.0.1 -p 8000 -f /data/wallpapers/cgi/wallpapers_cgi" >> /etc/rc.local

