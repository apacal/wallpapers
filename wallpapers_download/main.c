/**
 *       Filename:  main.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年01月05日 13时19分33秒
 *       Compiler:  gcc
 *         Author:  Apacal (|http://apacal.cn|), apacalzqz@gmail.com
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>
#include <unistd.h>

 
#include "lib/cJSON/cJSON.h"
#include "log.h"
#include <curl/curl.h>
//#define DEBUG
 
struct MemoryStruct {
    char *memory;
    size_t size;
};
void memory_struck_delete(struct MemoryStruct * chunk) {
    /* free chunk memory */
    free(chunk->memory);
    chunk->memory = NULL;
    chunk->size = 0;
}
 
 
static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp){
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
    mem->memory = (char *)realloc(mem->memory, mem->size + realsize + 1);
    if(mem->memory == NULL) {
        /* out of memory! */     
        log_error("not enough memory (realloc returned NULL)");
        return 0;
    }
 
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
 
    return realsize;
}
 
void get_wallpapers_data(struct MemoryStruct *chunk) {

    CURL *curl_handle;
    CURLcode res;
    
 
    chunk->memory = (char *)malloc(1);  /* will be grown as needed by the realloc above */ 
    chunk->size = 0;    /* no data at this point */ 
 
    curl_global_init(CURL_GLOBAL_ALL);
 
    /* init the curl session */ 
    curl_handle = curl_easy_init();
 
    /* specify URL to get */ 
    curl_easy_setopt(curl_handle, CURLOPT_URL, "https://api.desktoppr.co/1/wallpapers/random");
 
    /* send all data to this function  */ 
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
 
    /* we pass our 'chunk' struct to the callback function */ 
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)chunk);
 
    curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYPEER, 0);

    /* some servers don't like requests that are made without a user-agent
     field, so we provide one */ 
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
 
    /* get it! */ 
    res = curl_easy_perform(curl_handle);
 
    /* check for errors */ 
    if(res != CURLE_OK) {
        log_error(curl_easy_strerror(res));
        exit(-1);
    } else {
        log_info("get wallpapers_url");
    }

    /* cleanup curl stuff */ 
    curl_easy_cleanup(curl_handle);
 
    /* we're done with libcurl, so clean it up */ 
    curl_global_cleanup();
}

char * get_wallpapers_url(const char * json) {

    char * image_url;
    cJSON * root = cJSON_Parse(json);
    if (root) {
        char * url =  cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(root,"response"), "image"), "url")->valuestring;

        image_url = (char *)malloc(sizeof(char) * (strlen(url) + 1));
        memcpy(image_url, url, strlen(url) + 1);
        if (image_url) {
            log_info("get image url from json");
            log_info(image_url);
            return image_url;
        } else {
            log_error("can't get image_url from json");
            return NULL;
        }
    } else {
        log_error("can't get json parse");
        log_error(json);
    }
    return NULL;
}

char * get_file_md5(char * file_name) {
    unsigned char md5[MD5_DIGEST_LENGTH];
    FILE *inFile = fopen (file_name, "rb");
    MD5_CTX mdContext;
    int bytes;
    int n;
    unsigned char data[1024];
    char * out = (char *) malloc(MD5_DIGEST_LENGTH * 2 + 1);

    if (inFile == NULL) {
        log_error("file can't be opened.");
    }

    MD5_Init (&mdContext);
    while ((bytes = fread (data, 1, 1024, inFile)) != 0)
        MD5_Update (&mdContext, data, bytes);
    MD5_Final(md5,&mdContext);

    
    for (n = 0; n < 16; ++n) {
        snprintf(&(out[n*2]), 16*2, "%02x", (unsigned int)md5[n]);
    }

    return out;

}

char * save_image(const char * wallpapers_url) {

    CURLcode res;

    CURL* easyhandle = curl_easy_init();

    curl_easy_setopt( easyhandle, CURLOPT_URL, wallpapers_url ) ;

      
    char file_name[] = "wallpapers_tmp";

    
    FILE* file = fopen(file_name, "w");
    curl_easy_setopt( easyhandle, CURLOPT_WRITEDATA, file) ;

    res = curl_easy_perform( easyhandle );
    if(res != CURLE_OK) {
        log_error("can't download image");
        log_error(curl_easy_strerror(res));
        exit(-1);
    }
    curl_easy_cleanup( easyhandle );
    fclose(file);

    char * md5 = get_file_md5(file_name);

    char * image_name = (char *)malloc(strlen(md5) + 10);
    if (!image_name) {
        log_error("cant malloc for image file name");
        return NULL;
    }
    memcpy(image_name, md5, strlen(md5) + 1);

    const char *dot = strrchr(wallpapers_url, '.');
    if(dot && dot != wallpapers_url) {
        strcat(image_name, dot);
    }
    
    rename(file_name, image_name);
    return image_name;
}

 
int main(void) {
    chdir("/usr/local/wallpapers/picture");
#ifdef DEBUG
    char wallpapers_url[] = "http://apacal.cn/Public/images/bg1.jpg";
    char * image_name = save_image(wallpapers_url);
    printf("%s", image_name);
    free(image_name);
#else
    struct MemoryStruct chunk;
    get_wallpapers_data(&chunk);
    if (chunk.memory) {
        char * wallpapers_url = get_wallpapers_url(chunk.memory);
        memory_struck_delete(&chunk);

        if (wallpapers_url == NULL || strlen(wallpapers_url) == 0) {
            log_error("can not get wallpapers_url");
            exit(-1);
        }
        char * image_name = save_image(wallpapers_url);
        free(wallpapers_url);

        if (image_name) {
            printf("%s", image_name);
            free(image_name);
        }
        

    }
 
#endif
    return 0;
}
