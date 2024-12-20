#include "conf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t HASHSIZE = 37;
size_t KV_STR_SIZE = 64; 


char* get_config_key(ConfigItem *config_item){
    return config_item->key;
}
char* get_config_value(ConfigItem *config_item){
    return config_item->value;
}
void set_config_key(ConfigItem *config_item, char *key){
    config_item->key=key;
}
void set_config_value(ConfigItem *config_item, char *value){
    config_item->value=value;
}



// djb2 hash algo
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

char* get_value_from_key(ApplicationConfig *application_config, char* key){
    return application_config->config_item[hash((unsigned char *)key)%HASHSIZE].value;
}



ApplicationConfig loadConfig(char* file_name) {
    ApplicationConfig app_config;

    ConfigItem *configItems = malloc(sizeof(*configItems)*HASHSIZE);
    FILE* fp;
    fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("Could not read config file!");
        exit(0);
    }

    char line[256];

    int index_increment = 0;
    while (fgets(line, sizeof(line), fp))
    {
        //KVs for now can only be 63 chars in length 
        char *key = malloc(sizeof(char)*KV_STR_SIZE);
        char *value = malloc(sizeof(char)*KV_STR_SIZE);
        ConfigItem *configitem = malloc(sizeof(*configitem));

        sscanf(line, "%s %s", key, value);

        set_config_key(configitem, key);
        set_config_value(configitem, value);
        
        //unsafe? maybe? doubt it for now. 
        size_t hash_value = hash((unsigned char *)key) % HASHSIZE;
        configItems[hash_value] = *configitem;

        index_increment++;
        
    }

    fclose(fp);

    app_config.config_item = configItems;
    
    return app_config;
}

int main() {
    ApplicationConfig app_config = loadConfig("app.conf");
    printf("%s\n", get_value_from_key(&app_config,  "savesfolder"));
    return 0;
}
