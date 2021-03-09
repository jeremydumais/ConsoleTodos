#ifndef ADDRESS_H
#define ADDRESS_H

#include <time.h>

#define NAMESIZE 128
#define DESCRSIZE 512

typedef struct {
    char name[NAMESIZE];
    char description[DESCRSIZE];
    time_t datetime;
} address;

#endif