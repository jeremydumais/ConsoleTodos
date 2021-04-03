#include "typeUtil.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

bool isStringEmptyOrWhiteSpace(const char *value) 
{
    if (value == NULL) {
        return true;
    }
    size_t len = strlen(value);
    if (len == 0) {
        return true;
    }
    
    bool empty = true;
    for(int i = 0; i < len; i++) {
        if (!isspace(value[i])) {
            empty = false;
        }
    }
    return empty;
}
