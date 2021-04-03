#include "configStorage.h"
#include "linux/limits.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONFIGFILELINEMAX (PATH_MAX+129)
#define CONFIGFIELDMAX 128

typedef struct {
    char name[CONFIGFIELDMAX];
    char value[PATH_MAX + 1];
} configFileEntry;

FILE *configFileFD = NULL;
configFileEntry *configEntries = NULL;
size_t configEntriesLength = 0;
size_t configEntriesAllocatedLength = 0;

int openConfigFile(const char *fileName) 
{
    configFileFD = fopen(fileName, "r");
    if (!configFileFD) {
        return E_CONFIGSTORAGE_UNABLEOPENFILE;
    }
    //Read all values
    char line[CONFIGFILELINEMAX];
    while(fgets(line, CONFIGFILELINEMAX, configFileFD)) {
        if (strlen(line)) {
            if (line[0] == '#') {
                continue;
            }
            if (configEntries == NULL) {
                configEntries = malloc(sizeof(configFileEntry) * 4);
                configEntriesAllocatedLength = 4;
            }
            else if (configEntriesLength + 1 == configEntriesAllocatedLength) {
                //Reallocate 4 more entries
                configEntriesAllocatedLength += 4;
                configFileEntry *reallocatedEntries = realloc(configEntries, sizeof(configFileEntry) * configEntriesAllocatedLength);
                if (reallocatedEntries == NULL) {
                    printf("Not enough memory to allocate 4 more config entries.");
                    abort();
                }
                else {
                    configEntries = reallocatedEntries;
                }
            }

            if (sscanf(line, "%s = %s", configEntries[configEntriesLength].name, configEntries[configEntriesLength].value) == 2) {
                configEntriesLength++;
            }
            else {
                continue;
            }
        }
    }
    return E_CONFIGSTORAGE_SUCCESS;
}

int readConfigFileStringValue(const char *item, char *value, size_t valueLength) 
{
    for(size_t i=0; i<configEntriesLength; i++) {
        if (strcmp(configEntries[i].name, item) == 0) {
            size_t entryValueLength = strlen(configEntries[i].value);
            strncpy(value, configEntries[i].value, valueLength-1);
            value[valueLength < entryValueLength ? valueLength - 1 : entryValueLength] = '\0';
        }
    }
    return E_CONFIGSTORAGE_SUCCESS;
}

int closeConfigFile() 
{
    int retVal = E_CONFIGSTORAGE_SUCCESS;
    if (fclose(configFileFD) != 0) {
        retVal = E_CONFIGSTORAGE_UNABLECLOSEFILE;
    }
    free(configEntries);
    configEntries = NULL;
    configEntriesLength = 0;
    configEntriesAllocatedLength = 0;
    return retVal;
}
