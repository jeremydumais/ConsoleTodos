#ifndef CONFIGSTORAGE_H
#define CONFIGSTORAGE_H

#include <stdbool.h>
#include <stdlib.h>

enum _config_storage_error {
    E_CONFIGSTORAGE_SUCCESS = 0,
    E_CONFIGSTORAGE_UNABLEOPENFILE = -1,
    E_CONFIGSTORAGE_UNABLECLOSEFILE = -2,
    E_CONFIGSTORAGE_NOVALUE = -3,
    E_CONFIGSTORAGE_UNABLEREADVALUE = -4
};

int openConfigFile(const char *fileName);
int readConfigFileStringValue(const char *item, char *value, size_t valueLength);
int closeConfigFile();

#endif