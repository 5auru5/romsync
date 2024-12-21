#ifndef CONF_H
#define CONF_H

#include <stdlib.h>


// Look into use realloc instead of hard coded mallocs
extern size_t KV_STR_SIZE;
extern size_t CONFIG_SIZE;


typedef struct ConfigItem{
    char *key; 
    char *value;
} ConfigItem;

typedef struct ApplicationConfig{
    ConfigItem *config_item;   
} ApplicationConfig;

extern ApplicationConfig loadConfig(char* file_name);

extern char* get_config_key(ConfigItem *config_item);
extern char* get_config_value(ConfigItem *config_item);
extern void set_config_key(ConfigItem *config_item, char *key);
extern void set_config_value(ConfigItem *config_item, char *value);
extern char* get_value_from_key(ApplicationConfig *application_config, char* key);

#endif