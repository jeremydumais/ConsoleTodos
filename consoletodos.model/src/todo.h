#ifndef ADDRESS_H
#define ADDRESS_H

#include <time.h>

#define NAMESIZE 128
#define DESCRSIZE 512

typedef struct {
    char *name;
    char *description;
    time_t datetime;
    int priority;
} todo;

#endif